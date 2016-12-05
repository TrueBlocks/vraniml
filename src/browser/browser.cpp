//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Browser.h"
#ifdef FULL_VERSION // full version supports rendering
#include "Traversers\OGLTraverser.h"
#endif
#include "Traversers\ActionTraverser.h"
#include "Parser\Parser.h"
#include "direct.h"

IMPLEMENT_NODE(vrBrowser, vrTransform);

extern int yyparse();
extern FILE *yyin;
void CleanupParser(void);

#ifdef _DEBUG
// Just to keep the versions consistant
SFBool VersionCheck()
{
	// should be version 0.9.04
	vrVersionInfo info;
	vrGetVersion(&info);
	return ((info.majorNum==0) && 
						(info.minorNum==9) &&
						(info.releaseNum==4));
}
#endif

//-------------------------------------------------------------------
vrBrowser::vrBrowser(void) : vrTransform()
{
	ASSERT(VersionCheck());
	
	m_Console = NULL;
	//m_RendererList = []; // list

	m_PickedObject = NULL;

	SetFrameRate(30.0);
}

vrBrowser::vrBrowser(void *hWnd, vrRenderTraverser *drawTraverser)  : vrTransform()
{
	ASSERT(VersionCheck());

	m_Console = NULL;

	m_PickedObject = NULL;

	if (!drawTraverser)
	{
#ifdef FULL_VERSION // full version supports rendering
		drawTraverser = new vrOGLTraverser(this, hWnd);
		drawTraverser->m_hWnd = hWnd;
#else
		drawTraverser = NULL;
		drawTraverser->m_hWnd = hWnd;
#endif
	}

	vrActionTraverser *ac = new vrActionTraverser(this, hWnd);
	SetTraverser(ac, 0, TRUE);
	SetTraverser(drawTraverser, 1, TRUE);

	SetFrameRate(30.0);
}

vrBrowser::~vrBrowser()
{
	Clear(FALSE);
}

void vrBrowser::Clear(SFBool resetOnly)
{
	if (resetOnly)
	{
		LISTPOS pos = m_TraverserList.GetHeadPosition();
		while (pos)
		{
			vrTraverser *trav = m_TraverserList.GetNext(pos);
			trav->Reset();
		}
	} else
	{
		LISTPOS pos = m_TraverserList.GetHeadPosition();
		while (pos)
		{
			vrTraverser *trav = m_TraverserList.GetNext(pos);
			delete trav;
		}
		m_TraverserList.RemoveAll();
	}

	Bind(GetViewpoint(), FALSE);
	Bind(GetNavigationInfo(), FALSE);
	Bind(GetFog(), FALSE);
	Bind(GetBackground(), FALSE);

	vrTransform::Clear();
}

void vrBrowser::Traverse(vrTraverser *t) const
{
	if (t)
	{
		t->PreTraverse();
		t->Traverse(this);
		t->PostTraverse();
	} else
	{
		LISTPOS pos = m_TraverserList.GetHeadPosition();
		while (pos)
		{
			vrTraverser *trav = m_TraverserList.GetNext(pos);
			trav->PreTraverse();
			trav->Traverse(this);
			trav->PostTraverse();
		}
	}
}

//--------------------------------------------------------------------
SFBool vrBrowser::ProcessUserMessage(const vrUserMessage& msg)
{
	// All windows messages come through here prior to being 
	// processed by any application.  Normally we just send these
	// messages on to the active traversers and let them handle it

	// Return TRUE if we processed this message and caller should ignore it
	SFBool res = FALSE;
	
	LISTPOS pos = m_TraverserList.GetHeadPosition();
	while (pos)
	{
		vrTraverser *trav = m_TraverserList.GetNext(pos);
		SFInt32 r = trav->ProcessUserMessage(msg);
		// return results for first traverser only
		if (!res)
			res = r;
	}
	return res;
}

template<class TYPE>
void DoBindStuff(vrBrowser *b, vrNodeStack<TYPE> *stk, TYPE node, SFBool val)
{
	TYPE current = stk->Peek();
	if (val)
	{
		if (node != current)
		{
			if (current)
			{
				SFBool v = FALSE;
				current->SetIsBound(v);
				current->SetBoundTo(NULL);
				current->SendEventOut(VRML_ISBOUND_STR, &v);
			}
			if (node)
			{
				stk->Push(node);
				node->SetIsBound(TRUE);
				node->SetBoundTo(b);
				node->SendEventOut(VRML_ISBOUND_STR, &val);
			}
		}
	} else
	{
		if (node == current)
		{
			if (node)
			{
				stk->Pop();
				node->SetIsBound(val);
				node->SetBoundTo(((val) ? b : NULL));
				node->SendEventOut(VRML_ISBOUND_STR, &val);
				current = stk->Peek();
				if (current)
				{
					SFBool v = TRUE;
					current->SetIsBound(v);
					current->SetBoundTo(b);
					current->SendEventOut(VRML_ISBOUND_STR, &v);
				}
			}
		} else
		{
			LISTPOS pos = stk->Find(node);
			if (pos)
				stk->RemoveAt(pos);
		}
	}
}

void vrBrowser::Bind(vrBackground *b, SFBool val)
{
	DoBindStuff(this, &m_BackgroundStack, b, val);
}

void vrBrowser::Bind(vrFog *f, SFBool val)
{
	DoBindStuff(this, &m_FogStack, f, val);
}

void vrBrowser::Bind(vrViewpoint *v, SFBool val)
{
	DoBindStuff(this, &m_ViewpointStack, v, val);
}

void vrBrowser::Bind(vrNavigationInfo *n, SFBool val)
{
	DoBindStuff(this, &m_NavInfoStack, n, val);
}

vrGroupingNode *vrBrowser::PickScene(SFVec3f pt)
{	
	vrRenderTraverser *rt = (vrRenderTraverser *)GetTraverserByType(GETRUNTIME_CLASS(vrRenderTraverser));
	if (rt)
	{
		rt->SetMousePos(pt);
		rt->m_isPicking=TRUE;
		ASSERT(rt->m_Browser == this);
		m_PickedObject=NULL;
		rt->Traverse(this);
		rt->m_isPicking=FALSE;
	}
	return m_PickedObject;
}

void vrBrowser::Bind(vrBindable *b, SFBool val)
{
	if (b->IsKindOf(GETRUNTIME_CLASS(vrViewpoint)))
	{
		Bind((vrViewpoint*)b, val);
	} else if (b->IsKindOf(GETRUNTIME_CLASS(vrNavigationInfo)))
	{
		Bind((vrNavigationInfo*)b, val);
	} else if (b->IsKindOf(GETRUNTIME_CLASS(vrBackground)))
	{
		Bind((vrBackground*)b, val);
	} else
	{
		ASSERT(b->IsKindOf(GETRUNTIME_CLASS(vrFog)));
		Bind((vrFog*)b, val);
	}
}

//---------------------------------------------------------------------------------------
vrRoute *vrBrowser::AddRoute(const SFString& srcName, const SFString& srcTypeStr, const SFString& dstName, const SFString& dstTypeStr, SFBool internal)
{
	SFNode src = FindByName(srcName);
	if (!src)
	{
		if (m_Console)
			m_Console->Error("Invalid ROUTE: source node: " + srcName + " not found.");
		return NULL;
	}

	SFNode dst = FindByName(dstName);
	if (!dst)
	{
		if (m_Console)
			m_Console->Error("Invalid ROUTE: destination node: " + dstName + " not found.");
		return NULL;
	}

	return src->AddRoute(srcTypeStr, dst, dstTypeStr, internal);
}

//----------------------------------------------------------------------------
void vrBrowser::ChangeViewpoint(vrViewpoint *newVP, SFInt32 nFrames)
{
	ASSERT(newVP);

	vrViewpoint *oldVP = GetViewpoint();
	if (!oldVP)
	{
		Bind(newVP, TRUE);
		return;
	}

	if (!nFrames)
	{
		Bind(oldVP, FALSE);
		Bind(newVP, TRUE);
		return;
	}
	
	vrViewpoint save = *oldVP;
	
	vrOrientationInterpolator ori;
	ori.AddKey(0.0);  ori.AddKeyValue(oldVP->GetOrientation());
	ori.AddKey(1.0);  ori.AddKeyValue(newVP->GetOrientation());

	vrPositionInterpolator pos;
	pos.AddKey(0.0);  pos.AddKeyValue(oldVP->GetPosition());
	pos.AddKey(1.0);  pos.AddKeyValue(newVP->GetPosition());

	vrScalarInterpolator sc;
	sc.AddKey(0.0); sc.AddKeyValue(oldVP->GetFieldOfView());
	sc.AddKey(1.0); sc.AddKeyValue(newVP->GetFieldOfView());

	int i=0;
//double stop = (vrNow()+vrTime(10, 0));
//double start = vrNow();
//double now = start;
//while (now < stop)
	while (i<nFrames)
	{
		SFFloat t = i / ((SFFloat)nFrames);
// 		SFFloat t = ((SFFloat)((now-start)/(stop-start)));
		oldVP->SetPosition(pos.Evaluate(t));
		oldVP->SetOrientation(ori.Evaluate(t));
		oldVP->SetFieldOfView(sc.Evaluate(t));
		if (Tick())
		{
			Traverse();
			i++;
		}
//		now = vrNow();
	}

	*oldVP = save;
	Bind(oldVP, FALSE);
	Bind(newVP, TRUE);
}

// This little helper class will save the current
// working directory and when it goes out of scope 
// it will restore the directory to this saved value.
// For use when opening files in folders other than the 
// current working directory.
class vrDirectoryPreserver
{
	char    curDir[_MAX_PATH];
	SFInt32 curDrive;

public:
	vrDirectoryPreserver(const SFString& path)
		{
			_getcwd(curDir, _MAX_PATH);
			curDrive = _getdrive();

			SFString pathCopy = path;
			// Make sure there is a trailing '/' if just drive letter.
			if (path.Length()==2 && path[1] == ':')
				pathCopy += "/";
			
			ASSERT(pathCopy.Find("\\")==-1); // UNIX style path seperators
			SFInt32 drive = curDrive;
			SFInt32 find = pathCopy.Find(":");
			if (find != -1 && find == 1)
			{
				char cDrive = tolower(path[0]);
				drive = cDrive - 'a' + 1;
				pathCopy = pathCopy.Mid(find+1);
			}

#ifdef _DEBUG
			ASSERT(_chdrive(drive)!=-1);
			pathCopy.ReplaceAll("/","\\");
			ASSERT(_chdir((const char *)pathCopy)!=-1);
#else
			_chdrive(drive);
			pathCopy.ReplaceAll("/","\\");
			_chdir((const char *)pathCopy);
#endif

#ifdef _DEBUG
			// Double check that dir change took effect
			char cc[_MAX_PATH];
			_getcwd(cc, _MAX_PATH);
			SFString cwd = cc;
			cwd.ReplaceAll("\\", "/");
			cwd.ToLower();
			SFString fn = path;
			if (path.Length()==2 && path[1] == ':')
				fn += "/";
			fn.ReplaceAll("\\", "/");
			fn.ToLower();
			ASSERT(fn == cwd);
#endif
		};
	~vrDirectoryPreserver(void)
		{
			_chdrive(curDrive);
			_chdir(curDir);
		}
};

vrDumpContext tracer;
SFBool vrBrowser::ParseFile(FILE *fp)
{
	tracer.SetFilename("d:\\out.wrl");

	if (!fp)
		fp = stdin;
	
	GetParser()->console = m_Console;
	GetParser()->top = this;
	m_NodeType = protoGroup;
	yyin = fp;
  yyparse();
	m_NodeType = normalNode;
	GetParser()->top = NULL;
	GetParser()->console = NULL;
	GetParser()->nodeStack.RemoveAll();

	CleanupParser();

//	if (fp != stdin)
//		fclose(fp);
	fseek(fp, 0, SEEK_SET);

	return TRUE;
}

SFBool CheckVRML2(SFString& given)
{
	SFString local = vrCacheFile(given, 0);
	if (!local.Empty())
	{
		FILE *fp = fopen((const char *)local, "r");
		if (fp)
		{
			char s[256];
			fgets(s, 256, fp);
			fclose(fp);
			
			if (!strstr(s, "#VRML V2.0 utf8"))
				return FALSE;
		}
	}
	return TRUE;
}

#include "ExternProtoUtils.h"
SFBool vrBrowser::ReadURL(const SFString& fileName, vrGroupingNode *insertAt)
{
	if (fileName.Empty())
	{
		ASSERT(0);
		return FALSE;
	} else
	{
		ASSERT(fileName != nullString);
		ASSERT(!fileName.Empty());
	
		SFString copy = fileName;
		if (!CheckVRML2(copy))
		{
			// First line is not correct
			if (m_Console)
				m_Console->Error("First line of VRML 2.0 files must start with #VRML V2.0 utf8");
			return FALSE;
		}

		// See if the file exists first
		FILE *fp = fopen((const char *)fileName, "r");
		if (!fp)
		{
			if (m_Console)
				m_Console->Error("Cannot open url: " + copy);
			return FALSE;
		}
		fclose(fp);

		{ // do not remove this bracket -- the vrDirectoryPreserver needs the stack frame.
			SFString path = copy;
			path.ReplaceAll("\\", "/");
			SFInt32 find = path.ReverseFind('/');
			if (find!=-1)
				path = path.Left(find);
			vrDirectoryPreserver dp(path);
			
			SFString resolved = resolveExterns(copy);
			FILE *fp;
			if ((fp = fopen((const char *)resolved, "r")) == NULL)
			{
				// silent fail for inlines
				if (!insertAt || !insertAt->IsKindOf(GETRUNTIME_CLASS(vrInline)))
				{
					if (m_Console)
						m_Console->Error("Cannot open url: " + copy);
				}
				if (resolved!=copy)
				{
					SFString cmd = "erase " + resolved;
	//				system(cmd);
				}

				return FALSE;
			}

			int ret = ReadURL(fp, insertAt);
			if (resolved!=copy)
			{
				SFString cmd = "erase " + resolved;
//				system(cmd);
			}

			return ret;
		}
	}
	ASSERT(0);
	return FALSE;
}

SFBool vrBrowser::ReadURL(FILE *fp, vrGroupingNode *insertAt)
{
	int ret = FALSE;
	
	ASSERT(!insertAt || insertAt->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)));
	if (!insertAt)
	{
		// Turn off any playing sounds
		vrPlaySound(); 
		Clear(TRUE);
		ret = ParseFile(fp);
	} else
	{
		vrBrowser b;
		ret = b.ParseFile(fp);
		if (ret)
		{
			// Move Routes
			// This is wrong and is the reason that Inlines with ROUTEs core dump
			//ASSERT(FALSE); //!b.m_nRoutes || FALSE);
			
			/*
			// Cleanup
//			m_nRoutes += b.m_nRoutes;
			*/

			// Move Children
			b.MoveChildren(insertAt);

			// Bind any bindables
			if (b.GetFog())            Bind(b.GetFog(), TRUE);
			if (b.GetBackground())     Bind(b.GetBackground(), TRUE);
			if (b.GetViewpoint())      Bind(b.GetViewpoint(), TRUE);
			if (b.GetNavigationInfo()) Bind(b.GetNavigationInfo(), TRUE);
		}
	}

	if (fp && fp != stdin)
		fclose(fp);

	return ret;
}

vrTraverser *vrBrowser::GetTraverserByNumber(SFInt32 location) const
{
	SFInt32 n = 0;
	LISTPOS pos = m_TraverserList.GetHeadPosition();
	while (pos)
	{
		vrTraverser *trav = m_TraverserList.GetNext(pos);
		if (n == location)
			return trav;
		n++;
	}
	return NULL;
}

vrTraverser *vrBrowser::GetTraverserByType(vrRuntimeClass *pClass) const
{
	LISTPOS pos = m_TraverserList.GetHeadPosition();
	while (pos)
	{
		vrTraverser *trav = m_TraverserList.GetNext(pos);
		if (trav->IsKindOf(pClass))
			return trav;
	}
	return NULL;
}

vrTraverser *vrBrowser::SetTraverser(vrTraverser *t, SFInt32 location, SFBool insert)
{
	vrTraverser *removed = NULL;
	
	// has to be a valid place to put it (can be one past last one in list)
	location = vrClamp(location, (SFInt32)0, GetNTraversers());
	SFInt32 n = 0;

	// save all current traversers
	vrArrayBase<vrTraverser*> array;
	LISTPOS pos = m_TraverserList.GetHeadPosition();
	while (pos)
	{
		vrTraverser *trav = m_TraverserList.GetNext(pos);
		array[n++] = trav;
	}
	ASSERT(location >= 0 && location <= n);

	// make room and insert or replace
	if (insert)
	{
		for (SFInt32 k=location;k<n;k++)
		{
			array[k+1] = array[k];
		}
	} else
	{
		removed = array[location];
	}
	array[location] = t;	
	
	m_TraverserList.RemoveAll();
	for (int i=0;i<array.GetCount();i++)
		m_TraverserList.AddTail(array[i]);
	
	return removed;
}

SFInt32 vrBrowser::GetNTraversers (void) const
{
	return m_TraverserList.GetCount();
}
