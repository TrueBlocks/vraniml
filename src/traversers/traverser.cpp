//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Windows.h"

#include "Traverser.h"
#include "Nodes\Node.h"
#include "Nodes\AllNodes.h"
#include "Browser\Browser.h"

IMPLEMENT_NODE(vrTraverser, vrBaseNode);

//--------------------
vrTraverser::vrTraverser(vrBrowser *b, void *h)
{
	m_Browser   = b;
	m_hWnd      = h;
	if (h)
		SetWindowLong((HWND)h, GWL_USERDATA, (long)b);
	m_CurrMouse = SFVec3f(0);
	m_LastMouse = SFVec3f(0);
	m_Viewport  = vrRect2D(0, 0, 640, 480);
}

void vrTraverser::Traverse(const vrNode *node)
{
}

void vrTraverser::TraverseChildren(const vrGroupingNode *node)
{
	if (node->HasChildren())
	{
		parentStack.Push((vrGroupingNode*)node);

		LISTPOS pos = node->GetChildren()->GetHeadPosition();
		while (pos)
		{
			SFNode ob = node->GetChildren()->GetNext(pos);
			ob->Traverse(this);
		}

		parentStack.Pop();
	}
}

//--------------------
void vrTraverser::Traverse(const vrBoundingBox *node)
{
	if (!node->IsDefault())
	{
		vrBox box; 
		box.SetSize(node->GetMax() - node->GetMin());
		box.Traverse(this);
	}
}

vrMatrix vrTraverser::GetTotalTransformation(void) const
{
	vrMatrix ret;
	
	SFInt32 nParents = parentStack.GetCount();

	if (nParents)
	{
		vrMatrix *mats = new vrMatrix[nParents+1];

		SFInt32 i = 0;
		LISTPOS pos = parentStack.GetHeadPosition();
		while (pos)
		{
			SFNode node = parentStack.GetNext(pos);
			mats[i++] = node->GetLocalMatrix();
		}
	
		// Don't forget the browser's matrix
		ret = ret * m_Browser->matrix;
		for (SFInt32 n=0; n<nParents+1; n++)
		{
			ret = ret * mats[(nParents+1)-n-1];
		}

		delete[] mats;
	}

	return ret;
}

void vrTraverser::Traverse(const vrGroupingNode *node)
{
	TraverseChildren(node);
}

void vrTraverser::Traverse(const vrAnchor *node)
{
	Traverse((vrGroupingNode*)node);
}

void vrTraverser::Traverse(const vrBillboard *node)
{
	Traverse((vrGroupingNode*)node);
}

void vrTraverser::Traverse(const vrCollision *node)
{
	Traverse((vrGroupingNode*)node);
}

void vrTraverser::Traverse(const vrGroup *node)
{
	Traverse((vrGroupingNode*)node);
}

void vrTraverser::Traverse(const vrTransform *node)
{
	Traverse((vrGroupingNode*)node);
}

void vrTraverser::Traverse(const vrInline *node)
{
	Traverse((vrGroupingNode*)node);
}

void vrTraverser::Traverse(const vrLOD *node)
{
	for (int i=0;i<node->GetNLevels();i++)
	{
		node->GetLevel(i)->Traverse(this);
	}
}

void vrTraverser::Traverse(const vrSwitch *node)
{
	// Actions should effects all children of Switch's even inactive ones
	for (int i=0;i<node->GetNChoices();i++)
	{
		node->GetChoice(i)->Traverse(this);
	}
}

void vrTraverser::SetViewport(long x, long y, long w, long h)
{
	m_Viewport = vrRect2D(x, y, w, h);
}

static SFString Stringify(const void *ptr)
{
	char str[20];
	sprintf(str, "0x%X", ptr);
	return SFString(str);
}

SFString vrTraverser::GetUniqueID(const vrNode *node) const
{
	SFString id = Stringify(node);
	
	LISTPOS pos = parentStack.GetHeadPosition();
	while (pos)
	{
		SFNode node = parentStack.GetNext(pos);
		id += Stringify(node);
	}
	return id;
}
