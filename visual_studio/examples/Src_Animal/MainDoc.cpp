#include "stdafx.h"

#include "MainApp.h"
#include "MainDoc.h"
#include "MainFrm.h"
#include "Import.h"
#include "stdio.h"
#include "math.h"
#include "string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainDoc, CDocument)

BEGIN_MESSAGE_MAP(CMainDoc, CDocument)
	//{{AFX_MSG_MAP(CMainDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_KILLALL, OnFileKillAll)
	ON_UPDATE_COMMAND_UI(ID_FILE_KILLALL, OnUpdateFileKillAll)
	ON_COMMAND(ID_NAVIGATION_SLIDE, OnNavigationSlide)
	ON_UPDATE_COMMAND_UI(ID_NAVIGATION_SLIDE, OnUpdateNavigationSlide)
	ON_COMMAND(ID_NAVIGATION_ROTATEZ, OnNavigationRotateZ)
	ON_UPDATE_COMMAND_UI(ID_NAVIGATION_ROTATEZ, OnUpdateNavigationRotateZ)
	ON_COMMAND(ID_NAVIGATION_EXAMINE, OnNavigationExamine)
	ON_UPDATE_COMMAND_UI(ID_NAVIGATION_EXAMINE, OnUpdateNavigationExamine)
	ON_COMMAND(ID_NAVIGATION_ROTATEX, OnNavigationRotateX)
	ON_UPDATE_COMMAND_UI(ID_NAVIGATION_ROTATEX, OnUpdateNavigationRotateX)
	ON_COMMAND(ID_NAVIGATION_WALK, OnNavigationWalk)
	ON_UPDATE_COMMAND_UI(ID_NAVIGATION_WALK, OnUpdateNavigationWalk)
	ON_COMMAND(ID_VIEW_SOURCE, OnViewSource)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SOURCE, OnUpdateViewSource)
	ON_COMMAND(ID_VIEW_BACKGROUND, OnViewBackground)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BACKGROUND, OnUpdateViewBackground)
	ON_COMMAND(ID_INSERT_INSERT, OnInsert)
	ON_UPDATE_COMMAND_UI(ID_INSERT_INSERT, OnUpdateInsert)
	ON_COMMAND(ID_VIEW_DRAWMODE_POLYGONS, OnViewDrawmodePolygons)
	ON_COMMAND(ID_VIEW_DRAWMODE_LINES, OnViewDrawmodeLines)
	ON_COMMAND(ID_VIEW_DRAWMODE_POINTS, OnViewDrawmodePoints)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAWMODE_LINES, OnUpdateViewDrawmodeLines)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAWMODE_POINTS, OnUpdateViewDrawmodePoints)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DRAWMODE_POLYGONS, OnUpdateViewDrawmodePolygons)
	ON_COMMAND(ID_VIEW_LIGHTS, OnViewLights)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LIGHTS, OnUpdateViewLights)
	ON_COMMAND(ID_FILE_RELOAD, OnFileReload)
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_COMMAND(ID_VIEW_CENTER, OnViewCenterobjects)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CENTER, OnUpdateViewCenterobjects)
	ON_COMMAND(ID_VIEW_BOUNDINGBOXES, OnViewBoundingboxes)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BOUNDINGBOXES, OnUpdateViewBoundingboxes)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, OnUpdateFileExport)
	ON_COMMAND(ID_VIEW_HEADSUPDISPLAY, OnViewHeadsupdisplay)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HEADSUPDISPLAY, OnUpdateViewHeadsupdisplay)
	ON_COMMAND(ID_NAVIGATION_ROTATEY, OnNavigationRotateY)
	ON_UPDATE_COMMAND_UI(ID_NAVIGATION_ROTATEY, OnUpdateNavigationRotateY)
	ON_COMMAND(ID_NAVIGATION_AUTOANIMATE, OnNavigationAutoanimate)
	ON_UPDATE_COMMAND_UI(ID_NAVIGATION_AUTOANIMATE, OnUpdateNavigationAutoanimate)
	ON_COMMAND(ID_NAVIGATION_STRAIGHTEN, OnNavigationStraighten)
	ON_UPDATE_COMMAND_UI(ID_NAVIGATION_STRAIGHTEN, OnUpdateNavigationStraighten)
	ON_COMMAND(ID_VIEW_INBROWSER, OnViewInbrowser)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INBROWSER, OnUpdateViewInbrowser)
	ON_COMMAND(ID_HIDDEN_QUICKOPEN, OnHiddenQuickopen)
	ON_COMMAND(ID_FILE_PREFERENCES, OnFilePreferences)
	ON_COMMAND(ID_HELP_CONTENTS, OnHelpContents)
	ON_COMMAND(ID_VIEWPOINTS_LIST, OnViewpointsList)
	ON_UPDATE_COMMAND_UI(ID_VIEWPOINTS_LIST, OnUpdateViewpointsList)
	ON_COMMAND(ID_VIEWPOINTS_NEXT, OnViewpointsNext)
	ON_UPDATE_COMMAND_UI(ID_VIEWPOINTS_NEXT, OnUpdateViewpointsNext)
	ON_COMMAND(ID_VIEWPOINTS_PREV, OnViewpointsPrev)
	ON_UPDATE_COMMAND_UI(ID_VIEWPOINTS_PREV, OnUpdateViewpointsPrev)
	ON_UPDATE_COMMAND_UI(ID_HELP_CONTENTS, OnUpdateHelpContents)
	ON_UPDATE_COMMAND_UI(ID_FILE_IMPORT, OnUpdateFileImport)
	ON_COMMAND(ID_0_TESTING, On0Testing)
	ON_UPDATE_COMMAND_UI(ID_0_TESTING, OnUpdate0Testing)
	ON_COMMAND(ID_SOLIDMODEL_PROPERTIES, OnSolidmodelProperties)
	ON_UPDATE_COMMAND_UI(ID_SOLIDMODEL_PROPERTIES, OnUpdateSolidmodelProperties)
	ON_COMMAND(ID_SOLIDMODEL_OBJECTS_BALL, OnSolidmodelObjectsBall)
	ON_COMMAND(ID_SOLIDMODEL_OBJECTS_CAR, OnSolidmodelObjectsCar)
	ON_COMMAND(ID_SOLIDMODEL_OBJECTS_PEDRO, OnSolidmodelObjectsPedro)
	ON_COMMAND(ID_SOLIDMODEL_OBJECTS_PLANT, OnSolidmodelObjectsPlant)
	ON_COMMAND(ID_SOLIDMODEL_OBJECTS_TWIST, OnSolidmodelObjectsTwist)
	ON_COMMAND(ID_INSERT_SOLIDOBJECTS_TWIST2, OnInsertSolidobjectsTwist2)
	ON_COMMAND(ID_INSERT_SOLIDALGORITHMS_TRANSLATIONALSWEEP, OnInsertSolidalgorithmsTranslationalsweep)
	ON_COMMAND(ID_INSERT_SOLIDALGORITHMS_ROTATIONALSWEEP, OnInsertSolidalgorithmsRotationalsweep)
	ON_COMMAND(ID_SOLIDMODEL_SPLITPLANE_TEST1, OnSolidmodelSplitplaneTest1)
	ON_COMMAND(ID_INSERT_SOLIDBOOLEAN, OnInsertSolidboolean)
	ON_COMMAND(ID_INSERT_BOOLTESTS2_FACTORYPART, OnInsertBooltests2Factorypart)
	ON_COMMAND(ID_INSERT_BOOLTESTS2_TABLE, OnInsertBooltests2Table)
	ON_COMMAND(ID_0_AUTOTEST, On0Autotest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainDoc::CMainDoc()
{
	m_IsActive = TRUE;
	m_Browser = NULL;
	m_Loaded = FALSE;
}

CMainDoc::~CMainDoc()
{
	vrDELETE(m_Browser);
}

void CMainDoc::AttachBrowser(HWND hWnd)
{
	vrDELETE(m_Browser);

	m_Browser = new vrMyBrowser(hWnd);
	m_Browser->Reference();

	OnNewDocument();

	// Any app specific registry initialization here
	AfxGetApp()->WriteProfileInt("Settings", "LastInsert", 0);
}

BOOL CMainDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (m_Browser)
	{
		CString str = CString("file://") + AfxGetApp()->GetProfileString("Settings", "Filename", GetProgramDir() + "/logo.wrl");

		char filename[256];
		strcpy(filename, (LPCTSTR)str);
		DoOpenFile(filename);
	}
	SetModifiedFlag(TRUE);

	return TRUE;
}

void CMainDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef _DEBUG
void CMainDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMainDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

BOOL CMainDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	SetModifiedFlag(FALSE);
	AfxGetApp()->WriteProfileInt("Settings", "ProperExit", TRUE);
	return CDocument::CanCloseFrame(pFrame);
}

#include "OpenURL.h"
void CMainDoc::OnFileOpen() 
{
	COpenURL dlg;
	if (dlg.DoModal()==IDOK)
	{
		if (dlg.m_URL.GetLength())
		{
			char filename[256];
			strcpy(filename, (LPCTSTR)dlg.m_URL);
			DoOpenFile(filename);
		}
	}
}

void CMainDoc::OnFileKillAll() 
{
	SetTitle("None");
	m_Browser->Clear(TRUE);
	UpdateAllViews(NULL);
	AfxGetApp()->WriteProfileInt("Settings", "LastInsert", 0);
}

void CMainDoc::UpdateUI(CCmdUI *pCmdUI, SFBool checkState, SFBool enableState)
{
	ASSERT(pCmdUI);
	
	if (checkState!=-1)
		pCmdUI->SetCheck(checkState);
	
	if (enableState!=-1)
		pCmdUI->Enable(enableState);

	if (GetFrame())
		GetFrame()->UpdateButtons(pCmdUI->m_nID, checkState, enableState);
}

void CMainDoc::OnUpdateFileKillAll(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnNavigationWalk() 
{
	m_Browser->SetNavigationMode(MOVEMODE_WALK);
}

void CMainDoc::OnUpdateNavigationWalk(CCmdUI* pCmdUI) 
{
	SFBool check  = (m_Browser && m_Browser->GetNavigationMode()==MOVEMODE_WALK);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnNavigationSlide() 
{
	m_Browser->SetNavigationMode(MOVEMODE_SLIDE);
}

void CMainDoc::OnUpdateNavigationSlide(CCmdUI* pCmdUI) 
{
	SFBool check  = (m_Browser && m_Browser->GetNavigationMode()==MOVEMODE_SLIDE);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnNavigationExamine() 
{
	m_Browser->SetNavigationMode(MOVEMODE_EXAMINE);
}

void CMainDoc::OnUpdateNavigationExamine(CCmdUI* pCmdUI) 
{
	SFBool check  = (m_Browser && m_Browser->GetNavigationMode()==MOVEMODE_EXAMINE);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnNavigationRotateX() 
{
	m_Browser->SetNavigationMode(MOVEMODE_ROTATEX);
}

void CMainDoc::OnUpdateNavigationRotateX(CCmdUI* pCmdUI) 
{
	SFBool check  = (m_Browser && m_Browser->GetNavigationMode()==MOVEMODE_ROTATEX);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnNavigationRotateY() 
{
	m_Browser->SetNavigationMode(MOVEMODE_ROTATEY);
}

void CMainDoc::OnUpdateNavigationRotateY(CCmdUI* pCmdUI) 
{
	SFBool check  = (m_Browser && m_Browser->GetNavigationMode()==MOVEMODE_ROTATEY);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnNavigationRotateZ() 
{
	m_Browser->SetNavigationMode(MOVEMODE_ROTATEZ);
}

void CMainDoc::OnUpdateNavigationRotateZ(CCmdUI* pCmdUI) 
{
	SFBool check  = (m_Browser && m_Browser->GetNavigationMode()==MOVEMODE_ROTATEZ);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnViewSource() 
{
	ASSERT(GetTitle().GetLength());
	
	SFString filename = GetPathName();
	//char filename[256];
	//strcpy(filename, (LPCTSTR)GetPathName());
	SFString local = CacheFile(filename, 0);
	if (local!=nullString)
	{
		SFString cmd = SFString("notepad ") + local;
		WinExec((char*)cmd, SW_SHOW);
	}
}

void CMainDoc::OnUpdateViewSource(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = (GetBrowser() && GetBrowser()->GetChildren());
	UpdateUI(pCmdUI, check, enable);
}

#pragma warning(disable: 4101)
void CMainDoc::SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU) 
{
	// store the path fully qualified
	TCHAR szFullPath[_MAX_PATH];
	//AfxFullPath(szFullPath, lpszPathName);
	m_strPathName = lpszPathName; //szFullPath;
//	ASSERT(!m_strPathName.IsEmpty());       // must be set to something
	m_bEmbedded = FALSE;
	ASSERT_VALID(this);

	// set the document title based on path name
	//TCHAR szTitle[_MAX_FNAME];
	//if (AfxGetFileTitle(lpszPathName, szTitle, _MAX_FNAME) == 0) //szFullPath, szTitle, _MAX_FNAME) == 0)
	//	SetTitle(szTitle);

	// add it to the file MRU list
	if (bAddToMRU)
		AfxGetApp()->AddToRecentFileList(m_strPathName);

	ASSERT_VALID(this);
}

void CMainDoc::DoUpdateTitle(const SFString& filename)
{
	// Find the first WorldInfo node and use it for window title if found
	vrWorldInfo *worldInfo = (vrWorldInfo*)GetBrowser()->FindByType(GETRUNTIME_CLASS(vrWorldInfo));
	ASSERT(!worldInfo || worldInfo->IsKindOf(GETRUNTIME_CLASS(vrWorldInfo)));
	if (worldInfo && worldInfo->GetTitle())
	{
		SetTitle(worldInfo->GetTitle());
	} else
	{
		SetTitle(filename);
	}
	SetPathName(filename);
}

SFBool CheckVRML1(SFString& given, SFString& ret)
{
	SFString local = CacheFile(given, 0);
	if (local.Empty())
		return TRUE;
	
	ret = local;
	if (ret.Empty())
		return TRUE;

	FILE *fp = fopen((char *)ret, "r");
	if (!fp)
		return TRUE; // let it fail naturally
		
	char s[256];
	fgets(s, 256, fp);
	fclose(fp);
	if (strstr(s, "#VRML V1.0 ascii"))
	{
		CFilename prog(GetProgramDir()+"/vrml1to2.exe");
		if (!prog.Exists())
		{
			CString str;
			str.Format("The file %s appears to be a VRML 1.0 file.  You need to download\n"
			"Sony's vrml1to2.exe for VRaniML to convert the file.  Please visit the\n"
			"VRML repository for that download.", given);
			AfxMessageBox(str, MB_OK);
			return FALSE;
		} else
		{
			// appears to be a VRML 1.0 file, let's try to convert it
			CString str;
			str.Format("The file %s appears to be a VRML 1.0 file.  Would you like"
			"to convert it to VRML 2.0?", given);
			if (AfxMessageBox(str, MB_YESNO) == IDYES)
			{
				CFilename f((char *)local);
				CString dir = AfxGetApp()->GetProfileString("Settings", "LastConvert12Dir", GetProgramDir());
				CFileDialogInfo data(FALSE, "wrl", "VRML 2.0 files (*.wrl) |*.wrl||", "Convert File", dir);
				CFilename filename;
				if (GetFileName(&data, filename))
				{
					AfxGetApp()->WriteProfileString("Settings", "LastConvert12Dir", filename.GetPath());
					AfxGetApp()->WriteProfileString("Settings", "Filename", CString(filename));
					char str[256];
					sprintf(str, "vrml1to2 %s %s", (char *)local, (LPCTSTR)CString(filename));
					WinExec(str, SW_HIDE);
					// wait till it's done
					for (int i=0;i<10000;i++)
						; // spin;
					ret = (LPCTSTR)CString(filename);
				}
			} else
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CMainDoc::DoOpenFile(const SFString& fn)
{
	if (m_Browser)
	{
		m_Loaded = FALSE;
		SFString filename;
		SFString ss = fn;
		if (!CheckVRML1(ss, filename))
			return;

		SFString str = filename;
		SFString local = CacheFile(str, 0);
		if (!local.Empty())
		{
			CString defaultFile = CString("file://") + GetProgramDir() + "/logo.wrl";
			SFBool read = m_Browser->ReadURL(local);
			if (!read && CString(str) != defaultFile)
			{
				CString str;
				str.Format("Could not open file: %s", str);
				AfxMessageBox(str);
				AfxGetApp()->WriteProfileString("Settings", "Filename", GetProgramDir() + "/logo.wrl");
				char fn[256];
				strcpy(fn, (LPCTSTR)defaultFile);
				DoOpenFile(fn);
			}
			
			if (read)
			{
				DoUpdateTitle(str);
				vrNavigationInfo *nav = m_Browser->GetNavigationInfo();
				if (nav)
				{
					char *t = nav->GetType(0);
					switch (t[0])
					{
					case 'E':
						m_Browser->SetNavigationMode(MOVEMODE_EXAMINE);
						break;
					case 'F':
						m_Browser->SetNavigationMode(MOVEMODE_SLIDE);
						break;
					case 'N':
						// TODO: MOVEMODE_NONE
					case 'W':
						m_Browser->SetNavigationMode(MOVEMODE_WALK);
						break;
					}
				} else
				{
#if 1 //#ifdef _DEBUG
					int navMode = AfxGetApp()->GetProfileInt("Settings", "NavMode", MOVEMODE_WALK);
					m_Browser->SetNavigationMode(navMode);
#else
					m_Browser->SetNavigationMode(MOVEMODE_WALK);
#endif
				}
			} else
			{
				DoUpdateTitle(nullString);
			}
			SetModifiedFlag(TRUE);
			UpdateAllViews(NULL);
			m_Loaded = TRUE;
		}
	}
}

void CMainDoc::OnViewBackground() 
{
	vrBackground *b = GetBrowser()->GetBackground();
	if (b)
	{
		GetBrowser()->Bind(b, FALSE);
	} else
	{
		vrBackground *b = (vrBackground *)GetBrowser()->FindByType(GETRUNTIME_CLASS(vrBackground));
		if (b)
		{
			GetBrowser()->Bind(b, TRUE);
		}
	}
	UpdateAllViews(NULL);
}

void CMainDoc::OnUpdateViewBackground(CCmdUI* pCmdUI) 
{
	SFBool check  = ((SFBool)GetBrowser()->GetBackground());
	SFBool enable = (SFBool)(GetBrowser() && GetBrowser()->FindByType(GETRUNTIME_CLASS(vrBackground)));
	UpdateUI(pCmdUI, check, enable);
}

#include "InsertDialog.h"
void CMainDoc::OnInsert() 
{
	CInsertDialog dlg;
	dlg.pDoc = this;
	dlg.DoModal();
}

void CMainDoc::OnUpdateInsert(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnViewDrawmodePolygons() 
{
	AfxGetApp()->WriteProfileInt("Settings", "DrawMode", 0);
}

void CMainDoc::OnViewDrawmodeLines() 
{
	AfxGetApp()->WriteProfileInt("Settings", "DrawMode", 1);
}

void CMainDoc::OnViewDrawmodePoints() 
{
	AfxGetApp()->WriteProfileInt("Settings", "DrawMode", 2);
}

void CMainDoc::OnUpdateViewDrawmodeLines(CCmdUI* pCmdUI) 
{
	SFBool check  = (AfxGetApp()->GetProfileInt("Settings", "DrawMode", 0) == 1);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnUpdateViewDrawmodePoints(CCmdUI* pCmdUI) 
{
	SFBool check  = (AfxGetApp()->GetProfileInt("Settings", "DrawMode", 0) == 2);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnUpdateViewDrawmodePolygons(CCmdUI* pCmdUI) 
{
	SFBool check  = (AfxGetApp()->GetProfileInt("Settings", "DrawMode", 0) == 0);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnViewLights() 
{
//	vrRenderTraverser *t = m_Browser->GetRenderTraverser();
//	t->m_DrawLights = !t->m_DrawLights;
}

void CMainDoc::OnUpdateViewLights(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = FALSE;

//	vrRenderTraverser *t = m_Browser->GetRenderTraverser();
//	SFBool check = t->m_DrawLights;
//	vrLight *l = (vrLight *)GetBrowser()->FindByType(GETRUNTIME_CLASS(vrLight));
//	SFBool enable = (l!=NULL);

	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnFileReload() 
{
	OnFileKillAll();

	char filename[256];
	strcpy(filename, (LPCTSTR)GetPathName());
	DoOpenFile(filename);

	OnNavigationStraighten();
	m_Browser->SetNavigationMode(m_Browser->GetNavigationMode());
}

void ReplaceScene(vrBrowser *browser, vrNode *node, const vrBoundingBox& box)
{
	browser->vrGroupingNode::Clear();
	browser->Bind(browser->GetViewpoint(), FALSE);
	browser->Bind(browser->GetNavigationInfo(), FALSE);
	browser->Bind(browser->GetFog(), FALSE);
	browser->Bind(browser->GetBackground(), FALSE);

	vrTransform *trans = new vrTransform;
	
	// translate to center
	SFVec3f min = box.GetMin();
	SFVec3f max = box.GetMax();
	SFVec3f size = max - min;
	SFVec3f center = box.GetCenter();
	trans->SetTranslation(-center);
	trans->SetCenter(center);

	// scale to fit window
	double mx = MAX(size.x, MAX(size.y, size.z));
	SFVec3f sc(size.x / mx * 6.0, size.y / mx * 6.0, size.z / mx * 6.0);
	SFVec3f s;
	s.x = (double)sc.x / (double)size.x;
	s.y = (double)sc.y / (double)size.y;
	s.z = (double)sc.z / (double)size.z;
	trans->SetScale(s);
	trans->AddChild(node);

	browser->AddChild(trans);
}

void CMainDoc::Import(CString filename) 
{
	ASSERT(m_Browser);

	FILE *fp = fopen(filename, "r");
	if (fp)
	{
		vrAxisAlignedBox box;
		
		vrNode *node = NULL;
		filename.MakeLower();
		if (filename.Find(".tbl")!=-1)
		{
			AfxGetApp()->WriteProfileString("Settings", "LastImportFormat", "tbl");
			node = parse_tbl(fp, box);
		} else if (filename.Find(".nff")!=-1)
		{
			AfxGetApp()->WriteProfileString("Settings", "LastImportFormat", "nff");
			ASSERT(filename.Find(".nff")!=-1);
			node = parse_nff(fp, box);
		} else
		{
			AfxGetApp()->WriteProfileString("Settings", "LastImportFormat", "geo");
			ASSERT(filename.Find(".geo")!=-1);
			node = parse_geo(fp, box);
		}

		if (node)
		{
			ReplaceScene(m_Browser, node, box);
			DoUpdateTitle((char *)(LPCTSTR)filename);
			SetModifiedFlag(TRUE);
			UpdateAllViews(NULL);
		}
		fclose(fp);
	}
}

void CMainDoc::OnFileImport() 
{
	CString dir = AfxGetApp()->GetProfileString("Settings", "LastImportDir", GetProgramDir());

	CString formats =
		"Neutral File Format (*.nff) |*.nff|"
		"Neutral File Table (*.tbl) |*.tbl|"
		"Neutral File Format (*.geo) |*.geo|"
		"|";

	CString last = AfxGetApp()->GetProfileString("Settings", "LastImportFormat", "nff");
	CFileDialogInfo data(TRUE, last, formats, "Import File", dir);
  CFilename filename;
  if (GetFileName(&data, filename))
  {
		dir = filename.GetPath();
		AfxGetApp()->WriteProfileString("Settings", "LastImportDir", dir);
		{
			CDirectoryPreserver d(dir);
			Import(CString(filename));
		}
  }
}

void CMainDoc::OnUpdateFileImport(CCmdUI* pCmdUI) 
{
//	pCmdUI->Enable(FALSE);
}

void CMainDoc::OnViewCenterobjects() 
{
//	vrMatrix mat;
//	m_Browser->CalcBoxes(mat);
}

void CMainDoc::OnUpdateViewCenterobjects(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = FALSE; //GetBrowser() && GetBrowser()->GetChildren();
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnViewBoundingboxes() 
{
}

void CMainDoc::OnUpdateViewBoundingboxes(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = FALSE; //GetBrowser() && GetBrowser()->GetChildren();
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnFileExport() 
{
	CString dir = AfxGetApp()->GetProfileString("Settings", "LastExportDir", GetProgramDir());

	CString formats =
		"VRML 2.0 file (*.wrl) | *.wrl |"
		"|";

	CFileDialogInfo data(FALSE, "wrl", formats, "Export File", dir);
  CFilename filename;
  if (GetFileName(&data, filename))
  {
		dir = filename.GetPath();
		AfxGetApp()->WriteProfileString("Settings", "LastExportDir", dir);
		{
			// So the write traverser removes it's hold on the file
			vrWriteTraverser wt(NULL,NULL);
//			if (AfxGetApp()->GetProfileInt("Settings", "AllFields", FALSE))
//			{	
//				wt.m_Verbose = ALL_FIELDS;
//			}
			wt.SetFilename((LPCTSTR)CString(filename));
			GetBrowser()->Traverse(&wt);
		}		
		DoOpenFile((LPCTSTR)CString(filename));
		if (AfxGetApp()->GetProfileInt("Settings", "PreserveFilename", FALSE))
			AfxGetApp()->WriteProfileString("Settings", "Filename", CString(filename));
  }
}

void CMainDoc::OnUpdateFileExport(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = GetBrowser() && GetBrowser()->GetChildren();
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnViewHeadsupdisplay() 
{
	SFBool val = AfxGetApp()->GetProfileInt("Settings", "HeadsUpDisplay", FALSE);
	AfxGetApp()->WriteProfileInt("Settings", "HeadsUpDisplay", !val);
}

void CMainDoc::OnUpdateViewHeadsupdisplay(CCmdUI* pCmdUI) 
{
	SFBool check  = AfxGetApp()->GetProfileInt("Settings", "HeadsUpDisplay", FALSE);
	SFBool enable = -1;
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnNavigationAutoanimate() 
{
	SFBool val = AfxGetApp()->GetProfileInt("Settings", "AutoAnimate", TRUE);
	AfxGetApp()->WriteProfileInt("Settings", "AutoAnimate", !val);
}

void CMainDoc::OnUpdateNavigationAutoanimate(CCmdUI* pCmdUI) 
{
	SFBool check  = AfxGetApp()->GetProfileInt("Settings", "AutoAnimate", TRUE);
	SFBool enable = (m_Browser!=NULL);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnNavigationStraighten() 
{
	if (m_Browser)
	{
		vrViewpoint *vp = m_Browser->GetViewpoint();
		if (vp)
		{
			m_Browser->matrix = vrMatrix();
extern SFBool autoAnimate;
			autoAnimate = FALSE;
		}
	}
}

void CMainDoc::OnUpdateNavigationStraighten(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = TRUE;
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnViewInbrowser() 
{
	ASSERT(GetBrowser());
	HINSTANCE ret = ShellExecute(GetBrowser()->m_hWnd, "open", (LPCTSTR)GetPathName(), "", "", SW_SHOWMAXIMIZED);
	if (ret < (HINSTANCE)32)
	{
		AfxMessageBox("No browser found.");
	}
}

void CMainDoc::OnUpdateViewInbrowser(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = GetBrowser() && GetBrowser()->GetChildren();
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnHiddenQuickopen() 
{
	COpenURL dlg;
	dlg.m_QuickOpen=1;
	if (dlg.DoModal()==IDOK)
	{
		if (dlg.m_URL.GetLength())
		{
			char filename[256];
			strcpy(filename, (LPCTSTR)dlg.m_URL);
			DoOpenFile(filename);
		}
	}
}

#include "Preference.h"
void CMainDoc::OnFilePreferences() 
{
	CPreference dlg;
	if (dlg.DoModal()==IDOK)
	{
		int navMode = AfxGetApp()->GetProfileInt("Settings", "NavMode", MOVEMODE_WALK);
		m_Browser->SetNavigationMode(navMode);
	}
}

void CMainDoc::OnHelpContents() 
{
	CFilename filename(GetProgramDir()+"/../Documentation/index.htm");
	if (filename.Exists())
	{
		CDirectoryPreserver d(GetProgramDir());
		{
			CDirectoryPreserver d("../Documentation");
			CString cmd("runme.exe");
			WinExec(cmd, SW_SHOW);
		}
	} else
	{
		SFString msg = "Please download the VRaniML help file documentation available at http://www.greathill.com/vrml.htm";
		AfxMessageBox((char *)msg);
	}
}

void CMainDoc::OnUpdateHelpContents(CCmdUI* pCmdUI) 
{
//	CFilename filename(GetProgramDir()+"/../Documentation/index.htm");
//	pCmdUI->Enable(filename.Exists());
	pCmdUI->Enable(TRUE);
}

void CMainDoc::Redraw(void)
{
	if (!m_Loaded) 
		return;

	if (m_Browser && m_IsActive)
	{
		if (m_Browser->updateMatrix())
		{
			m_Browser->Tick();
			m_Browser->Traverse();
		} else
		{
			if (m_Browser->Tick())
			{
//#ifdef _DEBUG
void LoadNewFile(vrBrowser *browser);
		if (AfxGetApp()->GetProfileInt("Debug", "AutoTest", FALSE))
			LoadNewFile(m_Browser);
//#endif
				m_Browser->Traverse();
			}
		}
	}
}

#include "ViewpointDialog.h"
void CMainDoc::OnViewpointsList() 
{
	CViewpointDialog dlg;
	dlg.browser = m_Browser;
	int res = dlg.DoModal();
	if (res != IDCANCLE)
	{
		OnNavigationStraighten();
		BindViewpoint(m_Browser, res-100);
	}
}

void CMainDoc::OnViewpointsNext() 
{
	OnNavigationStraighten();
	BindViewpoint(m_Browser, -1);
}

void CMainDoc::OnViewpointsPrev() 
{
	OnNavigationStraighten();
	BindViewpoint(m_Browser, -2);
}

void CMainDoc::OnUpdateViewpointsList(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = (CountViewpoints(m_Browser)>1);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnUpdateViewpointsNext(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = (CountViewpoints(m_Browser)>1);
	UpdateUI(pCmdUI, check, enable);
}

void CMainDoc::OnUpdateViewpointsPrev(CCmdUI* pCmdUI) 
{
	SFBool check  = -1;
	SFBool enable = (CountViewpoints(m_Browser)>1);
	UpdateUI(pCmdUI, check, enable);
}


void CMainDoc::OnCloseDocument() 
{
	// Clean up here because otherwise the browser references
	// a deleted hWnd
	vrDELETE(m_Browser);

	CDocument::OnCloseDocument();
}

void CMainDoc::On0Testing() 
{
	// Clear the main browser
	m_Browser->Clear(TRUE);
	
	// Create a group into which to read file 1 (the body description)
	vrGroup *body = new vrGroup;
	// read the file into the new group
	m_Browser->ReadURL("d:/file1.wrl", body);
	// make sure the file contains the correct DEF's
	ASSERT(body->FindByName("BODY"));
	// Add the file to the browser
	m_Browser->AddChild(body);
	
	// Create another group into which to read the interpolators
	vrGroup *interp = new vrGroup;
	// read the interpolators
	m_Browser->ReadURL("d:/file2.wrl", interp);
	// make sure this file contains the correct DEF's
	ASSERT(interp->FindByName("ORI"));
	ASSERT(interp->FindByName("TS"));
	// Add the interpolators to the browser
	m_Browser->AddChild(interp);

	// HERE IS THE HACK!!!!
	// Hard code the routes since they cannot be in the 
	// .wrl files since the parser will report that a route
	// was attempted that did not exist.
	m_Browser->AddRoute("TS", "fraction_changed", "ORI", "set_fraction");
	m_Browser->AddRoute("ORI", "value_changed", "BODY", "rotation");

/*
	// Now write out the two seperate parts of the scene graph
	// to different files.
	m_Browser->Clear(TRUE);
	vrWriteTraverser wt;
	wt.SetFilename("d:/outfile1.wrl");
	m_Browser->AddChild(body);
	m_Browser->Traverse(&wt);

	m_Browser->Clear(TRUE);
	wt.SetFilename("d:/outfile2.wrl");
	m_Browser->AddChild(animation);
	m_Browser->Traverse(&wt);
*/
}

void CMainDoc::OnUpdate0Testing(CCmdUI* pCmdUI) 
{
#ifdef _DEBUG
	pCmdUI->Enable(TRUE);
#else
	pCmdUI->Enable(FALSE);
#endif
}

void CMainDoc::OnSolidmodelProperties() 
{
	vrGeometryNode *geom = (vrGeometryNode*)GetBrowser()->FindByType(GETRUNTIME_CLASS(vrGeometryNode));
	ASSERT(geom);
	ASSERT(geom->GetGeom());
	vrSolid *solid = geom->GetGeom();

	SFVec3f min, max;
	solid->Extents(min, max);
  SFFloat volume = solid->Volume();
	SFFloat area = solid->Area();
	
  Uint32 nVerts, nEdges, nFaces, nLoops, nHalfEdges;
	solid->Stats(nVerts, nEdges, nFaces, nLoops, nHalfEdges);

	vrDumpString ds;
	ds << "Min:   " << min << "\n";
	ds << "Max:   " << max << "\n";
	ds << "Vol:   " << volume << "\n";
	ds << "Area:  " << -area << "\n";
	ds << "Faces: " << (SFInt32)nFaces << "\n";
	ds << "Edges: " << (SFInt32)nEdges << "\n";
	ds << "Verts: " << (SFInt32)nVerts << "\n";
	ds << "Loops: " << (SFInt32)nLoops << "\n";
	ds << "Hes:   " << (SFInt32)nHalfEdges << "\n";
	AfxMessageBox(ds.string);
}

void CMainDoc::OnUpdateSolidmodelProperties(CCmdUI* pCmdUI) 
{
	SFBool on = FALSE;
	vrGeometryNode *geom = (vrGeometryNode*)GetBrowser()->FindByType(GETRUNTIME_CLASS(vrGeometryNode));
	if (geom)
		if (geom->GetGeom())
			on = TRUE;
	pCmdUI->Enable(on);
}

extern vrNode *MakeIFS(MFVec3f *coords, MFVec3f *normals, MFInt32 *faces, MFColor *colors);

void DoSolid1(CMainDoc *doc, vrBrowser *browser, vrSolid *solid)
{
	if (solid)
	{
		solid->CalcPlaneEquations();
		solid->Triangulate();
		
		vrAxisAlignedBox box;

		MFVec3f coords;
		MFVec3f normals;
		MFInt32 faces;
		MFColor colors;

		LISTPOS vPos = solid->verts.GetHeadPosition();
		while (vPos)
		{
			vrVertex *v = solid->verts.GetNext(vPos);
			coords.AddValue(*v);
			box.Include(*v);
		}
		
		LISTPOS fPos = solid->faces.GetHeadPosition();
		while (fPos)
		{
			vrFace *face = solid->faces.GetNext(fPos);
			LISTPOS lPos = face->loops.GetHeadPosition();
			while (lPos)
			{
				vrLoop *l = face->loops.GetNext(lPos);
				LISTPOS hPos = l->halfedges.GetTailPosition();
				while (hPos) 
				{
					vrHalfEdge *he = l->halfedges.GetPrev(hPos);
					faces.AddValue(he->GetIndex());
				}
			}
			faces.AddValue(-1);
			colors.AddValue(face->GetColor(vrWhite));
			//normals.AddValue(face->GetNormal());
		}
		
		vrNode *node = MakeIFS(&coords, &normals, &faces, &colors);
		vrIndexedFaceSet *set = (vrIndexedFaceSet *)node->FindByType(GETRUNTIME_CLASS(vrIndexedFaceSet));
		ASSERT(set && set->IsKindOf(GETRUNTIME_CLASS(vrIndexedFaceSet)));
		set->SetCreaseAngle(vrDeg2Rad(10));
		ReplaceScene(browser, node, box);

		CString filename = GetProgramDir();
		filename += ("/export.wrl");

		{// So the write traverser removes it's hold on the file
			vrWriteTraverser wt(NULL,NULL);
			wt.SetFilename((LPCTSTR)CString(filename));
			browser->Traverse(&wt);
		}		

		doc->DoOpenFile((LPCTSTR)CString(filename));
		if (AfxGetApp()->GetProfileInt("Settings", "PreserveFilename", FALSE))
			AfxGetApp()->WriteProfileString("Settings", "Filename", CString(filename));
	}
}

#include "solidtests\tests.h"
#define BALL 1
#define CAR 2
#define PART 3
#define PEDRO 4
#define PLANT 5
#define TABLE 6
#define TWIST 7
#define TWIST2 8
#define ROTSWEEP 9
#define TRANSSWEEP 10
void DoSolid(CMainDoc *doc, vrBrowser *browser, SFInt32 test)
{
	vrSolid *solid = NULL;

	switch (test)
	{
	case BALL:
		solid = Ball(0, 1);
		break;
	case CAR:
		solid = Car();
		break;
	case PART:
		solid = Part();
		break;
	case PEDRO:
		solid = Pedro();
		break;
	case PLANT:
		solid = Plant();
		break;
	case TABLE:
		solid = Table();
		break;
	case TWIST:
		solid = Twist();
		break;
	case TWIST2:
		solid = Twist2();
		break;
	case ROTSWEEP:
		solid = RotSweep();
		break;
	case TRANSSWEEP:
		solid = TransSweep();
		break;
	}
	DoSolid1(doc, browser, solid);
}

void CMainDoc::OnSolidmodelObjectsBall() 
{
	DoSolid(this, m_Browser, BALL);
}

void CMainDoc::OnSolidmodelObjectsCar() 
{	
	DoSolid(this, m_Browser, CAR);
}

void CMainDoc::OnSolidmodelObjectsPedro() 
{
	DoSolid(this, m_Browser, PEDRO);
}

void CMainDoc::OnSolidmodelObjectsPlant() 
{
	DoSolid(this, m_Browser, PLANT);
}

void CMainDoc::OnSolidmodelObjectsTwist() 
{
	DoSolid(this, m_Browser, TWIST);
}

void CMainDoc::OnInsertSolidobjectsTwist2() 
{
	DoSolid(this, m_Browser, TWIST2);
}

void CMainDoc::OnInsertSolidalgorithmsTranslationalsweep() 
{
	DoSolid(this, m_Browser, TRANSSWEEP);
}

void CMainDoc::OnInsertSolidalgorithmsRotationalsweep() 
{
	DoSolid(this, m_Browser, ROTSWEEP);
}

#include "SplitTestDialog.h"
void CMainDoc::OnSolidmodelSplitplaneTest1() 
{
	CSplitTestDialog dlg;
	
	dlg.m_TestNum    = AfxGetApp()->GetProfileInt("Tests", "SplitLastTest",  0);
	dlg.m_Merge      = AfxGetApp()->GetProfileInt("Tests", "SplitLastMerge", FALSE);
	dlg.m_Iterations = AfxGetApp()->GetProfileInt("Tests", "SplitLastIters", 10);
	dlg.m_Ball       = AfxGetApp()->GetProfileInt("Tests", "SplitBall",      FALSE);
	dlg.m_Auto       = AfxGetApp()->GetProfileInt("Tests", "SplitAutoTest",  TRUE);
	dlg.m_MoveIn     = AfxGetApp()->GetProfileInt("Tests", "SplitMoveIn",    FALSE);
	if (dlg.DoModal()==IDOK)
	{
		AfxGetApp()->WriteProfileInt("Tests", "SplitLastTest",  dlg.m_TestNum);
		AfxGetApp()->WriteProfileInt("Tests", "SplitLastIters", dlg.m_Iterations);
		AfxGetApp()->WriteProfileInt("Tests", "SplitBall",      dlg.m_Ball);
		AfxGetApp()->WriteProfileInt("Tests", "SplitLastMerge", dlg.m_Merge);
		AfxGetApp()->WriteProfileInt("Tests", "SplitAutoTest",  dlg.m_Auto);
		AfxGetApp()->WriteProfileInt("Tests", "SplitMoveIn",    dlg.m_MoveIn);

		if (dlg.m_TestNum==16)
		{
			DoSolid(this, m_Browser, BALL);
		} else
		{
			vrSolid *s = SplitTests(dlg.m_TestNum, dlg.m_Merge);
			DoSolid1(this, m_Browser, s);
		}
		if (dlg.m_Auto)
			AfxGetApp()->WriteProfileInt("Tests", "SplitLastTest", (dlg.m_TestNum%17)+1);
		if (AfxGetApp()->GetProfileInt("Tests", "SplitLastTest", 0)==17)
			AfxGetApp()->WriteProfileInt("Tests", "SplitLastTest", 1);
	}
}

#include "BoolTestDialog.h"
extern vrSolid *BoolTests(vrBoolTestRecord *rec);
void DoBoolTest(CMainDoc *doc, vrBrowser *browser)
{
	vrBoolTestRecord rec;
	rec.op     = AfxGetApp()->GetProfileInt("Tests", "BoolLastOperation", 4);
	rec.group  = AfxGetApp()->GetProfileInt("Tests", "BoolLastGroup",     0);
	rec.testId = AfxGetApp()->GetProfileInt("Tests", "BoolLastTest",      7);

	switch (rec.group)
	{
	case 4:
		rec.wide = TRUE;
		break;
	case 2:
		rec.center = TRUE;
		rec.rotate = TRUE;
		break;
	case 1:
		rec.rotate = TRUE;
		break;
	default:
		break;
	}
	
	vrSolid *s;
	CString str;
	s = BoolTests(&rec);
	if (s)
	{
		DoSolid1(doc, browser, s);

		if (AfxGetApp()->GetProfileInt("Tests", "BoolAutoTest", FALSE))
		{
			long nxt = (rec.group+1)%12;
			if (nxt==5) nxt=6;
			AfxGetApp()->WriteProfileInt("Tests", "BoolLastGroup", nxt);
		}
	}
}

void CMainDoc::OnInsertSolidboolean() 
{
	CBoolTestDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		DoBoolTest(this, m_Browser);
	}
}

void CMainDoc::OnInsertBooltests2Factorypart() 
{
	DoSolid(this, m_Browser, PART);
}

void CMainDoc::OnInsertBooltests2Table() 
{
	DoSolid(this, m_Browser, TABLE);
}

void LoadNewFile(vrBrowser *browser)
{
#define GHC
//#define ANNO
//#define SOURCEBOOK

	SFString dir1 = GetProgramDir();
	SFString dir2 = "d:/worlds/books/annotated";
	SFString dir3 = "d:/worlds/books/sourcebook/book/win";
	SFString dir4 = "d:/worlds/books/sourcebook/software";

	SFString files[] = {
#ifdef GHC
	  dir1 + "/appearance/appearance.wrl",
	  dir1 + "/appearance/appearance2.wrl",
	  dir1 + "/appearance/material.wrl",
	  dir1 + "/appearance/pixeltexture.wrl",
	  dir1 + "/appearance/texturedbox.wrl",
	  dir1 + "/appearance/texturetransform.wrl",
	  dir1 + "/appearance/texturetransform1.wrl",
	  dir1 + "/appearance/texturetransform2.wrl",

	  dir1 + "/bindable/background.wrl",
	  dir1 + "/bindable/fog.wrl",
	  dir1 + "/bindable/viewpoints.wrl",
	  dir1 + "/bindable/viewpoints1.wrl",

	  dir1 + "/common/pointlight.wrl",
	  dir1 + "/common/shape.wrl",
	  dir1 + "/common/sound.wrl",
	  dir1 + "/common/spotlight1.wrl",
	  dir1 + "/common/spotlight2.wrl",
	  dir1 + "/common/worldinfo.wrl",

	  dir1 + "/defuse/defuse1.wrl",
	  dir1 + "/defuse/defuse2.wrl",
	  dir1 + "/defuse/defuse3.wrl",

	  dir1 + "/geometry/box.wrl",
	  dir1 + "/geometry/box1.wrl",
	  dir1 + "/geometry/box2.wrl",
	  dir1 + "/geometry/box3.wrl",
	  dir1 + "/geometry/cone.wrl",
	  dir1 + "/geometry/cone1.wrl",
	  dir1 + "/geometry/cylinder.wrl",
	  dir1 + "/geometry/cylinder1.wrl",
	  dir1 + "/geometry/elevationgrid.wrl",
//	  dir1 + "/geometry/faceset1.wrl",
//	  dir1 + "/geometry/inline.wrl",
	  dir1 + "/geometry/lineset.wrl",
	  dir1 + "/geometry/lineset1.wrl",
	  dir1 + "/geometry/pointset.wrl",
	  dir1 + "/geometry/pointset1.wrl",
	  dir1 + "/geometry/sphere.wrl",
	  dir1 + "/geometry/sphere1.wrl",
	  dir1 + "/geometry/sphere2.wrl",
	  dir1 + "/geometry/textures.wrl",

	  dir1 + "/grouping/anchor.wrl",
	  dir1 + "/grouping/anchor1.wrl",
	  dir1 + "/grouping/anchor2.wrl",
	  dir1 + "/grouping/anchor3.wrl",
//	  dir1 + "/grouping/anchor4.wrl",
	  dir1 + "/grouping/billboard.wrl",
	  dir1 + "/grouping/billboard1.wrl",
	  dir1 + "/grouping/billboard2.wrl",
	  dir1 + "/grouping/lod.wrl",
//	  dir1 + "/grouping/switch.wrl",

	  dir1 + "/interpolator/coordinterpolator.wrl",
	  dir1 + "/interpolator/interpolators.wrl",
	  dir1 + "/interpolator/orientationinterpolator.wrl",
	  dir1 + "/interpolator/positioninterpolator.wrl",
	  dir1 + "/interpolator/scalarinterpolator.wrl",

	//  dir1 + "/protos/prototest1.wrl",
	//  dir1 + "/protos/prototest2.wrl",
	//  dir1 + "/protos/prototest3.wrl",

	  dir1 + "/sensor/planesensor1.wrl",
	  dir1 + "/sensor/planesensor2.wrl",
	  dir1 + "/sensor/planesensor3.wrl",
//	  dir1 + "/sensor/proximitysensor.wrl",
	  dir1 + "/sensor/timesensor.wrl",
//	  dir1 + "/sensor/touchsensor.wrl",
//	  dir1 + "/sensor/touchsensor1.wrl",
#endif

#ifdef ANNO
	  dir2 + "/egs/adclip.wrl",
	  dir2 + "/egs/anchor.wrl",
	  dir2 + "/egs/appr.wrl",
	  dir2 + "/egs/bckgd.wrl",
	  dir2 + "/egs/blbrd.wrl",
	  dir2 + "/egs/box.wrl",
//	  dir2 + "/egs/cllson.wrl",
	  dir2 + "/egs/clrnter.wrl",
	  dir2 + "/egs/color.wrl",
	  dir2 + "/egs/cone.wrl",
	  dir2 + "/egs/crdntrp.wrl",
	  dir2 + "/egs/cylinder.wrl",
	  dir2 + "/egs/cylnsen.wrl",
	  dir2 + "/egs/drlt.wrl",
	  dir2 + "/egs/elgrid.wrl",
	  dir2 + "/egs/extrsn.wrl",
	  dir2 + "/egs/fntsty.wrl",
	  dir2 + "/egs/fog.wrl",
	  dir2 + "/egs/grndplne.wrl",
	  dir2 + "/egs/group.wrl",
	  dir2 + "/egs/imgtexe.wrl",
	  dir2 + "/egs/indxfst.wrl",
	  dir2 + "/egs/indxlst.wrl",
	  dir2 + "/egs/inline.wrl",
	  dir2 + "/egs/lod.wrl",
	  dir2 + "/egs/material.wrl",
	  dir2 + "/egs/mvtexe.wrl",
	  dir2 + "/egs/navinfo.wrl",
//	  dir2 + "/egs/normal.wrl",
//	  dir2 + "/egs/nrmlntr.wrl",
	  dir2 + "/egs/orntrpl.wrl",
//	  dir2 + "/egs/pixtexe.wrl",
	  dir2 + "/egs/plansnb.wrl",
	  dir2 + "/egs/pntlt.wrl",
	  dir2 + "/egs/pointst.wrl",
	  dir2 + "/egs/posntrp.wrl",
	  dir2 + "/egs/proxsn.wrl",
	  dir2 + "/egs/scalntp.wrl",
//	  dir2 + "/egs/script.wrl",
	  dir2 + "/egs/shape.wrl",
	  dir2 + "/egs/sound.wrl",
    dir2 + "/egs/sphrb.wrl",
	  dir2 + "/egs/sphrsnb.wrl",
	  dir2 + "/egs/sptlt.wrl",
//	  dir2 + "/egs/switch.wrl",
	  dir2 + "/egs/texcrdb.wrl",
	  dir2 + "/egs/text.wrl",
	  dir2 + "/egs/texxf.wrl",
	  dir2 + "/egs/timesnb.wrl",
//	  dir2 + "/egs/touchsn.wrl",
//	  dir2 + "/egs/transfrm.wrl",
	  dir2 + "/egs/viewpnt.wrl",
	  dir2 + "/egs/vissn.wrl",
	  dir2 + "/egs/wrldnfo.wrl",

	  dir2 + "/samples/chpbdy.wrl",
	  dir2 + "/samples/chprtr.wrl",
	  dir2 + "/samples/ex10.wrl",
//	  dir2 + "/samples/ex11.wrl",
	  dir2 + "/samples/ex12.wrl",
	  dir2 + "/samples/ex13.wrl",
//	  dir2 + "/samples/ex14.wrl",
//	  dir2 + "/samples/ex15.wrl",
//	  dir2 + "/samples/ex16.wrl",
	  dir2 + "/samples/ex17.wrl",
//	  dir2 + "/samples/ex18.wrl",
//	  dir2 + "/samples/ex2.wrl",
//	  dir2 + "/samples/ex3.wrl",
//	  dir2 + "/samples/ex4.wrl",
//	  dir2 + "/samples/ex5.wrl",
//	  dir2 + "/samples/ex6.wrl",
//	  dir2 + "/samples/ex7.wrl",
//	  dir2 + "/samples/ex9.wrl",
//	  dir2 + "/samples/rfrmtl.wrl",
//	  dir2 + "/samples/rotor.wrl",
#endif

#ifdef SOURCEBOOK
		dir3 + "/ch02/02fig01.wrl",

		dir3 + "/ch03/03fig01.wrl",
		dir3 + "/ch03/03fig02.wrl",
		dir3 + "/ch03/03fig03.wrl",
		dir3 + "/ch03/03fig04.wrl",
		dir3 + "/ch03/03fig05.wrl",
		dir3 + "/ch03/03fig06.wrl",
		dir3 + "/ch03/03fig07.wrl",
		dir3 + "/ch03/03fig08.wrl",
		dir3 + "/ch03/03fig09.wrl",
		dir3 + "/ch03/03fig10.wrl",

		dir3 + "/ch04/04fig01.wrl",
		dir3 + "/ch04/04fig02.wrl",
		dir3 + "/ch04/04fig03.wrl",
		dir3 + "/ch04/04fig04.wrl",
		dir3 + "/ch04/04fig05.wrl",
		dir3 + "/ch04/04fig06a.wrl",
		dir3 + "/ch04/04fig06b.wrl",
		dir3 + "/ch04/04fig07.wrl",
		dir3 + "/ch04/04fig08a.wrl",
		dir3 + "/ch04/04fig08b.wrl",
		dir3 + "/ch04/04fig09.wrl",
		dir3 + "/ch04/04fig10.wrl",
		dir3 + "/ch04/04fig11.wrl",

		dir3 + "/ch05/05fig03b.wrl",
		dir3 + "/ch05/05fig04b.wrl",
		dir3 + "/ch05/05fig05b.wrl",
		dir3 + "/ch05/05fig06b.wrl",
		dir3 + "/ch05/05fig07b.wrl",
		dir3 + "/ch05/05fig08.wrl",
		dir3 + "/ch05/05fig10.wrl",
		dir3 + "/ch05/05fig11.wrl",

		dir3 + "/ch06/06fig04b.wrl",
		dir3 + "/ch06/06fig05b.wrl",
		dir3 + "/ch06/06fig06b.wrl",
		dir3 + "/ch06/06fig07b.wrl",
		dir3 + "/ch06/06fig08.wrl",
		dir3 + "/ch06/06fig09.wrl",
		dir3 + "/ch06/06fig10.wrl",
		dir3 + "/ch06/06fig11.wrl",
		dir3 + "/ch06/06fig12.wrl",

		dir3 + "/ch07/07fig04b.wrl",
		dir3 + "/ch07/07fig05b.wrl",
		dir3 + "/ch07/07fig06b.wrl",
		dir3 + "/ch07/07fig07b.wrl",
		dir3 + "/ch07/07fig08b.wrl",
		dir3 + "/ch07/07fig09.wrl",
		dir3 + "/ch07/07fig10.wrl",
		dir3 + "/ch07/07fig11.wrl",
		dir3 + "/ch07/07fig12a.wrl",
		dir3 + "/ch07/07fig12b.wrl",
		dir3 + "/ch07/07fig13.wrl",

		dir3 + "/ch08/08fig03.wrl",
		dir3 + "/ch08/08fig05.wrl",
		dir3 + "/ch08/08fig06.wrl",
		dir3 + "/ch08/08fig07.wrl",

		dir3 + "/ch09/09fig03.wrl",
		dir3 + "/ch09/09fig04.wrl",
		dir3 + "/ch09/09fig05.wrl",
		dir3 + "/ch09/09fig06.wrl",
		dir3 + "/ch09/09fig07.wrl",

		dir3 + "/ch10/10fig04.wrl",
		dir3 + "/ch10/10fig05.wrl",
		dir3 + "/ch10/10fig07.wrl",
		dir3 + "/ch10/10fig10.wrl",

		dir3 + "/ch11/11fig01a.wrl",
		dir3 + "/ch11/11fig01b.wrl",
		dir3 + "/ch11/11fig01c.wrl",
		dir3 + "/ch11/11fig02.wrl",
		dir3 + "/ch11/11fig03.wrl",
		dir3 + "/ch11/11fig04.wrl",

		dir3 + "/ch12/12fig01.wrl",
		dir3 + "/ch12/12fig02.wrl",
		dir3 + "/ch12/12fig03.wrl",
		dir3 + "/ch12/arch.wrl",
		dir3 + "/ch12/archrow.wrl",

		dir3 + "/ch13/13fig10.wrl",
		dir3 + "/ch13/13fig11.wrl",
		dir3 + "/ch13/13fig12.wrl",
		dir3 + "/ch13/13fig13.wrl",
		dir3 + "/ch13/13fig14.wrl",
		dir3 + "/ch13/13fig15.wrl",
		dir3 + "/ch13/13fig16.wrl",
		dir3 + "/ch13/vault.wrl",

		dir3 + "/ch14/14fig02.wrl",
		dir3 + "/ch14/14fig03.wrl",
		dir3 + "/ch14/14fig04a.wrl",
//		dir3 + "/ch14/14fig04b.wrl",
//		dir3 + "/ch14/14fig05.wrl",
		dir3 + "/ch14/14fig06.wrl",
		dir3 + "/ch14/ribbon.wrl",

		dir3 + "/ch15/15fig07.wrl",
		dir3 + "/ch15/15fig08.wrl",
		dir3 + "/ch15/15fig09.wrl",
		dir3 + "/ch15/15fig10.wrl",
		dir3 + "/ch15/15fig11.wrl",
		dir3 + "/ch15/15fig12.wrl",
		dir3 + "/ch15/15fig13.wrl",
		dir3 + "/ch15/15fig14.wrl",
		dir3 + "/ch15/15fig15.wrl",
		dir3 + "/ch15/15fig16.wrl",

		dir3 + "/ch16/16fig01.wrl",
		dir3 + "/ch16/16fig02.wrl",
		dir3 + "/ch16/16fig03.wrl",
		dir3 + "/ch16/16fig04.wrl",
		dir3 + "/ch16/16fig05.wrl",
		dir3 + "/ch16/16fig06.wrl",
		dir3 + "/ch16/16fig07.wrl",

		dir3 + "/ch17/17fig04a.wrl",
		dir3 + "/ch17/17fig04b.wrl",
		dir3 + "/ch17/17fig04c.wrl",
		dir3 + "/ch17/17fig04d.wrl",
		dir3 + "/ch17/17fig05d.wrl",
		dir3 + "/ch17/17fig06b.wrl",
		dir3 + "/ch17/17fig07b.wrl",
		dir3 + "/ch17/17fig08b.wrl",
		dir3 + "/ch17/17fig09b.wrl",

//		dir3 + "/ch17/17fig10c.wrl",
//		dir3 + "/ch17/17fig11b.wrl",
//		dir3 + "/ch17/17fig12b.wrl",
//		dir3 + "/ch17/17fig14b.wrl",

		dir3 + "/ch18/18fig19b.wrl",
		dir3 + "/ch18/18fig20b.wrl",
		dir3 + "/ch18/18fig21.wrl",
		dir3 + "/ch18/18fig22b.wrl",
		dir3 + "/ch18/18fig23b.wrl",
		dir3 + "/ch18/18fig24.wrl",
		dir3 + "/ch18/18fig25b.wrl",
		dir3 + "/ch18/18fig26b.wrl",
		dir3 + "/ch18/18fig26c.wrl",

//		dir3 + "/ch19/19fig21.wrl",
//		dir3 + "/ch19/19fig22.wrl",
//		dir3 + "/ch19/19fig23.wrl",
//		dir3 + "/ch19/19fig24a.wrl",
//		dir3 + "/ch19/19fig24b.wrl",
//		dir3 + "/ch19/19fig25a.wrl",
//		dir3 + "/ch19/19fig25b.wrl",
//		dir3 + "/ch19/19fig26.wrl",
//		dir3 + "/ch19/19fig27.wrl",
//		dir3 + "/ch19/colca1.wrl",
//		dir3 + "/ch19/colsmth.wrl",

		dir3 + "/ch20/20fig04.wrl",
		dir3 + "/ch20/20fig05.wrl",
		dir3 + "/ch20/20fig06a.wrl",
		dir3 + "/ch20/20fig06b.wrl",
		dir3 + "/ch20/20fig07.wrl",
		dir3 + "/ch20/20fig08.wrl",
		dir3 + "/ch20/20fig09.wrl",
		dir3 + "/ch20/20fig11a.wrl",
		dir3 + "/ch20/20fig11b.wrl",
		dir3 + "/ch20/20fig12.wrl",
		dir3 + "/ch20/20fig13a.wrl",
		dir3 + "/ch20/20fig13b.wrl",
		dir3 + "/ch20/20fig13c.wrl",
		dir3 + "/ch20/20fig15a.wrl",
		dir3 + "/ch20/20fig15b.wrl",
		dir3 + "/ch20/20fig16a.wrl",
		dir3 + "/ch20/20fig16b.wrl",
		dir3 + "/ch20/20fig16c.wrl",
		dir3 + "/ch20/20fig17a.wrl",
		dir3 + "/ch20/20fig17b.wrl",
		dir3 + "/ch20/mesh.wrl",
		dir3 + "/ch20/spheres.wrl",
		dir3 + "/ch20/vault.wrl",
		dir3 + "/ch20/vaulted.wrl",

	  dir3 + "/ch21/21fig04a.wrl",
	  dir3 + "/ch21/21fig04b.wrl",
	  dir3 + "/ch21/21fig04c.wrl",
	  dir3 + "/ch21/21fig04d.wrl",
	  dir3 + "/ch21/21fig05.wrl",

	  dir3 + "/ch22/22fig01.wrl",
	  dir3 + "/ch22/22fig02.wrl",
	  dir3 + "/ch22/22fig03c.wrl",

	  dir3 + "/ch23/23fig01.wrl",
	  dir3 + "/ch23/23fig02a.wrl",
	  dir3 + "/ch23/23fig02b.wrl",
	  dir3 + "/ch23/23fig02c.wrl",
	  dir3 + "/ch23/23fig02d.wrl",
	  dir3 + "/ch23/23fig03a.wrl",
	  dir3 + "/ch23/23fig03b.wrl",
	  dir3 + "/ch23/23fig03c.wrl",
	  dir3 + "/ch23/23fig04.wrl",
	  dir3 + "/ch23/23fig05.wrl",
	  dir3 + "/ch23/fogworld.wrl",

	  dir3 + "/ch24/24fig01.wrl",
	  dir3 + "/ch24/24fig02.wrl",
	  dir3 + "/ch24/24fig03.wrl",
	  dir3 + "/ch24/sndmark.wrl",

	  dir3 + "/ch25/25fig01.wrl",
	  dir3 + "/ch25/25fig02.wrl",
	  dir3 + "/ch25/25fig03.wrl",
	  dir3 + "/ch25/25fig04.wrl",
	  dir3 + "/ch25/25fig05.wrl",
	  dir3 + "/ch25/25fig06.wrl",
	  dir3 + "/ch25/25fig07.wrl",
	  dir3 + "/ch25/25fig08.wrl",
	  dir3 + "/ch25/25fig09.wrl",
	  dir3 + "/ch25/25fig10.wrl",
	  dir3 + "/ch25/25fig11.wrl",
	  dir3 + "/ch25/ddoor.wrl",
	  dir3 + "/ch25/dfloor.wrl",
	  dir3 + "/ch25/droom.wrl",
	  dir3 + "/ch25/dwall.wrl",
	  dir3 + "/ch25/dwall2.wrl",
	  dir3 + "/ch25/torch1.wrl",
	  dir3 + "/ch25/torch2.wrl",
	  dir3 + "/ch25/torch3.wrl",
	  dir3 + "/ch25/torches.wrl",

	  dir3 + "/ch26/26fig04.wrl",
	  dir3 + "/ch26/26fig05.wrl",
	  dir3 + "/ch26/26fig06a.wrl",
	  dir3 + "/ch26/26fig06b.wrl",
	  dir3 + "/ch26/26fig07.wrl",
	  dir3 + "/ch26/ddoor.wrl",
	  dir3 + "/ch26/dfloor.wrl",
	  dir3 + "/ch26/droom.wrl",
	  dir3 + "/ch26/dwall.wrl",
	  dir3 + "/ch26/dwall2.wrl",
	  dir3 + "/ch26/torch1.wrl",
	  dir3 + "/ch26/torch2.wrl",
	  dir3 + "/ch26/torch3.wrl",
	  dir3 + "/ch26/torches.wrl",

	  dir3 + "/ch27/ddoor.wrl",
	  dir3 + "/ch27/dfloor.wrl",
	  dir3 + "/ch27/droom.wrl",
	  dir3 + "/ch27/dwall.wrl",
	  dir3 + "/ch27/dwall2.wrl",
	  dir3 + "/ch27/torch1.wrl",
	  dir3 + "/ch27/torch2.wrl",
	  dir3 + "/ch27/torch3.wrl",
	  dir3 + "/ch27/torches.wrl",
	
	  dir3 + "/ch28/28fig01.wrl",
	  dir3 + "/ch28/28fig02.wrl",
	  dir3 + "/ch28/ddoor.wrl",
	  dir3 + "/ch28/dfloor.wrl",
	  dir3 + "/ch28/dngnwrld.wrl",
	  dir3 + "/ch28/droom.wrl",
	  dir3 + "/ch28/dwall.wrl",
	  dir3 + "/ch28/dwall2.wrl",
	  dir3 + "/ch28/torch1.wrl",
	  dir3 + "/ch28/torch2.wrl",
	  dir3 + "/ch28/torch3.wrl",
	  dir3 + "/ch28/torches.wrl",

	  dir3 + "/ch29/29fig01.wrl",
	  dir3 + "/ch29/ddoor.wrl",
	  dir3 + "/ch29/dfloor.wrl",
	  dir3 + "/ch29/droom.wrl",
	  dir3 + "/ch29/dwall.wrl",
	  dir3 + "/ch29/dwall2.wrl",
	  dir3 + "/ch29/torch1.wrl",
	  dir3 + "/ch29/torch2.wrl",
	  dir3 + "/ch29/torch3.wrl",
	  dir3 + "/ch29/torches.wrl",

//	  dir3 + "/ch31/31fig01.wrl",
//	  dir3 + "/ch31/31fig02.wrl",
//	  dir3 + "/ch31/31fig04.wrl",
//	  dir3 + "/ch31/31fig06.wrl",
//	  dir3 + "/ch31/31fig08.wrl",
//	  dir3 + "/ch31/applib.wrl",
//	  dir3 + "/ch31/donutpro.wrl",
//	  dir3 + "/ch31/matlib.wrl",

	  dir4 + "/3name3d/objects/win/03couch2.wrl",
	  dir4 + "/3name3d/objects/win/03hamer1.wrl",
	  dir4 + "/3name3d/objects/win/03trunk1.wrl",
	  dir4 + "/3name3d/objects/win/03wlamp4.wrl",
	  dir4 + "/3name3d/objects/win/04frplc2.wrl",
	  dir4 + "/3name3d/objects/win/05sword3.wrl",
	  dir4 + "/3name3d/objects/win/06door1.wrl",
	  dir4 + "/3name3d/objects/win/07mtlstr.wrl",
	  dir4 + "/3name3d/objects/win/08pilstr.wrl",
	  dir4 + "/3rddim/win/autos/jetta/jetta_2.wrl",
	  dir4 + "/3rddim/win/autos/lincoln/lincln_2.wrl",
	  dir4 + "/3rddim/win/autos/ls400/ls400_2.wrl",
	  dir4 + "/3rddim/win/avatars/damon/dam_m_2.wrl",
	  dir4 + "/3rddim/win/avatars/damon/damon_2.wrl",
	  dir4 + "/3rddim/win/avatars/female/ruth_2.wrl",
	  dir4 + "/3rddim/win/avatars/frank/frankm_2.wrl",
	  dir4 + "/3rddim/win/avatars/male/dmnbod_2.wrl",
	  dir4 + "/3rddim/win/avatars/ray/ray_2.wrl",
	  dir4 + "/3rddim/win/products/amp/amptst_2.wrl",
	  dir4 + "/3rddim/win/products/bigscrn/bigtvm_2.wrl",
	  dir4 + "/3rddim/win/products/hp4/hp4_2.wrl",

	  dir3 + "/ch08/08fig04.wrl",
	  dir3 + "/ch08/08fig08.wrl",
	  dir3 + "/ch09/09fig01.wrl",
	  dir3 + "/ch09/09fig02.wrl",
	  dir3 + "/ch09/09fig08.wrl",
	  dir3 + "/ch09/09fig09.wrl",
	  dir3 + "/ch10/10fig06.wrl",
	  dir3 + "/ch10/10fig08.wrl",
	  dir3 + "/ch10/10fig09.wrl",
	  dir3 + "/ch10/10fig11.wrl",
	  dir3 + "/ch10/10fig12.wrl",
	  dir3 + "/ch13/13fig17.wrl",
	  dir3 + "/ch18/18fig27.wrl",
	  dir3 + "/ch22/22fig04.wrl",
	  dir3 + "/ch24/24fig04.wrl",
	  dir3 + "/ch24/24fig05.wrl",
	  dir3 + "/ch24/24fig06.wrl",
	  dir3 + "/ch25/25fig12.wrl",
	  dir3 + "/ch26/dungeon.wrl",
	  dir3 + "/ch27/27fig01.wrl",
	  dir3 + "/ch27/27fig02.wrl",
	  dir3 + "/ch27/27fig03.wrl",
	  dir3 + "/ch28/dungeon.wrl",
	  dir3 + "/ch29/dungeon.wrl",

	  dir3 + "/ch15/15fig17.wrl",
	  dir3 + "/ch17/17fig13.wrl",
	  dir3 + "/ch20/20fig10.wrl",
	  dir3 + "/ch20/20fig14.wrl",
	  dir3 + "/ch24/24fig07.wrl",

	  dir3 + "/ch30/30fig01.wrl",
	  dir3 + "/ch30/30fig03.wrl",
	  dir3 + "/ch30/30fig04.wrl",
	  dir3 + "/ch30/30fig02.wrl",
	  dir3 + "/ch30/30fig05.wrl",
#endif
	};
	int nF = sizeof(files) / sizeof(SFString);
	
	static int i=0, n=0;
	static int solids=TRUE;

	if (solids)
	{
		if (n<10)
		{
			DoSolid(GetDoc(), browser, BALL+n);
			AfxGetApp()->WriteProfileInt("Tests", "SplitLastTest",  1);
			n++;
		} else if (n==10)
		{
			AfxGetApp()->WriteProfileInt("Tests", "SplitLastMerge", FALSE);
			AfxGetApp()->WriteProfileInt("Tests", "SplitLastIters", 10);
			AfxGetApp()->WriteProfileInt("Tests", "SplitBall",      FALSE);
			AfxGetApp()->WriteProfileInt("Tests", "SplitAutoTest",  TRUE);
			AfxGetApp()->WriteProfileInt("Tests", "SplitMoveIn",    FALSE);

			SFInt32 test = AfxGetApp()->GetProfileInt("Tests", "SplitLastTest",  0);
			vrSolid *s = SplitTests(test, FALSE);
			DoSolid1(GetDoc(), browser, s);

			test++;
			if (test < 17)
				AfxGetApp()->WriteProfileInt("Tests", "SplitLastTest", (test%17)+1);
			else
			{
				AfxGetApp()->WriteProfileInt("Tests", "BoolLastTest", 7);
				AfxGetApp()->WriteProfileInt("Tests", "BoolAutoTest", TRUE);
				AfxGetApp()->WriteProfileInt("Tests", "BoolLastOperation", 4);
				AfxGetApp()->WriteProfileInt("Tests", "BoolLastGroup", 0);
				n++;
			}
		} else if (n==11)
		{
			DoBoolTest(GetDoc(), browser);
			SFInt32 test = AfxGetApp()->GetProfileInt("Tests", "BoolLastGroup", -1);
			if (test>10)
				n++;
		} else if (n>11)
		{
			solids = FALSE;
			n=i=0;
		}
		return;
	}

	i++;
	if (!(i%5))
	{
		int index = (n%nF);
		GetDoc()->DoOpenFile(files[index]);
		n++;
		if (n>nF)
		{
			solids=TRUE;
			n=i=0;
		}
	}
}

#undef GetDoc
CMainDoc *CMainDoc::GetDoc(void)
{
	CFrameWnd *pFrame = (CFrameWnd *)AfxGetApp()->m_pMainWnd;
	return ((pFrame) ? (CMainDoc*)pFrame->GetActiveDocument() : NULL);
}


void CMainDoc::On0Autotest() 
{
	SFBool autoTest = AfxGetApp()->GetProfileInt("Debug", "AutoTest", FALSE);
	AfxGetApp()->WriteProfileInt("Debug", "AutoTest", !autoTest);
}
