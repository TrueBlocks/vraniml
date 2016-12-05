#include "stdafx.h"

#include "MainApp.h"
#include "MainFrm.h"

#include "Splitter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSplitter, CSplitterWnd)

CSplitter::CSplitter()
{
	lastCx = -1;
}

CSplitter::~CSplitter()
{
}

BEGIN_MESSAGE_MAP(CSplitter, CSplitterWnd)
	//{{AFX_MSG_MAP(CSplitter)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

#pragma warning(disable : 4244)
void CSplitter::OnSize(UINT nType, int cx, int cy) 
{
	if (GetFrame() && GetFrame()->m_Activated)
	{
		// After initialization, preserve relative percentages of split windows
		CWnd::OnSize(nType, cx, cy);
		ASSERT(cx != 0 && lastCx != 0);
		double pct = (double)cx / (double)lastCx;
		m_pColInfo->nIdealSize *= pct;
		RecalcLayout();
	} else
	{
		// Before initialization, behave as normal
		CSplitterWnd::OnSize(nType, cx, cy);
	}
	lastCx = cx;
}
