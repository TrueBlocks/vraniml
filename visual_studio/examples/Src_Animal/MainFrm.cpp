#include "stdafx.h"

#include "MainApp.h"
#include "Splash.h"

#include "MainFrm.h"
#include "MainView.h"
#include "RightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_RIGHTVIEW, OnViewRightview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RIGHTVIEW, OnUpdateViewRightview)
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_HELP_CONTENTS, OnHelpContents)
	ON_COMMAND(ID_HELP_WEB, OnHelpWeb)
	ON_COMMAND_EX(ID_VIEW_BOTTOMBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BOTTOMBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_LEFTBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LEFTBAR, OnUpdateControlBarMenu)
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
	m_bmBackground = NULL;
	m_Timer = 0;
	m_Activated=FALSE;
}

CMainFrame::~CMainFrame()
{
	if (m_bmBackground)	
		delete m_bmBackground;
}

CButtonPlacement leftButtons[] = 
{
	CButtonPlacement(0, ID_FILE_OPEN,          IDB_ORANGE,   FIRSTPLACE),
	CButtonPlacement(3, ID_NAVIGATION_WALK,    IDB_GREEN,    FIRSTPLACE),
	CButtonPlacement(4, ID_NAVIGATION_SLIDE,   IDB_GREEN,    FIRSTPLACE),
	CButtonPlacement(5, ID_NAVIGATION_ROTATEX, IDB_GREEN,    FIRSTPLACE),
	CButtonPlacement(6, ID_NAVIGATION_ROTATEY, IDB_GREEN,    FIRSTPLACE),
	CButtonPlacement(7, ID_NAVIGATION_ROTATEZ, IDB_GREEN,    FIRSTPLACE),
	CButtonPlacement(8, ID_NAVIGATION_EXAMINE, IDB_GREEN,  FIRSTPLACE),
	CButtonPlacement(0, ID_HELP_CONTENTS,      IDB_RED,      LAST),
};
int nLeftButtons = sizeof(leftButtons) / sizeof(CButtonPlacement);
CButtonPlacement bottomButtons[] = 
{
	CButtonPlacement(0, ID_HELP_WEB,      IDB_RED, FIRSTPLACE),
	CButtonPlacement(4, ID_VIEW_SOURCE,   IDB_BLUE, FIRSTPLACE),
	CButtonPlacement(5, ID_FILE_KILLALL,   IDB_BLUE, FIRSTPLACE),
	CButtonPlacement(6, ID_INSERT_INSERT,   IDB_BLUE, FIRSTPLACE),
	CButtonPlacement(7, ID_NAVIGATION_STRAIGHTEN,   IDB_BLUE, FIRSTPLACE),
	CButtonPlacement(9,  ID_VIEWPOINTS_PREV,   IDB_BLUE, FIRSTPLACE),
	CButtonPlacement(10, ID_VIEWPOINTS_LIST,   IDB_BLUE, FIRSTPLACE),
	CButtonPlacement(11, ID_VIEWPOINTS_NEXT,   IDB_BLUE, FIRSTPLACE),
	CButtonPlacement(0, ID_VIEW_INBROWSER,   IDB_ORANGE, LAST),
};
int nBottomButtons = sizeof(bottomButtons) / sizeof(CButtonPlacement);

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_pPalette = NULL;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_StatusBar.Create(this) ||
		!m_StatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	m_bmBackground = new CBitmap;
	m_bmBackground->LoadBitmap(IDB_BACKGROUND);

	if (!m_LeftBar.Create(this, IDD_LEFTBAR,
		CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
		ID_VIEW_LEFTBAR))
	{
		TRACE0("Failed to create dialog bar m_LeftBar\n");
		return -1;
	}

	if (!m_BottomBar.Create(this, IDD_BOTTOMBAR,
		CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
		ID_VIEW_BOTTOMBAR))
	{
		TRACE0("Failed to create dialog bar m_BottomBar\n");
		return -1;
	}

	m_LeftBar.SetParams  (nLeftButtons, leftButtons, m_bmBackground);
	m_BottomBar.SetParams(nBottomButtons, bottomButtons, m_bmBackground);

	if (AfxGetApp()->GetProfileInt("Debug", "ShowSplash", TRUE))
	{
		CSplashWnd::ShowSplashScreen(this);
		DWORD startTime = ::GetCurrentTime();
		while (::GetCurrentTime() - startTime < 2000)
			;
		CSplashWnd::c_pSplashWnd->HideSplashScreen();
	}

	// This timer keeps the idle processor pumping
	m_Timer = SetTimer(1001, 30, NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif

void CMainFrame::ActivateFrame(int nCmdShow) 
{
	CWnd           *pBar;
	BOOL            bStatus;
	UINT            flags = 0;
	WINDOWPLACEMENT placement;
  
	if (!m_Activated) 
	{
		CMainDoc *pDoc = GetDoc();
		ASSERT_VALID(pDoc);
		if (!pDoc->GetBrowser())
		{
			CMainView *a = (CMainView *)m_Splitter.GetPane(0,0);
			ASSERT(a);
			ASSERT(a->IsKindOf(RUNTIME_CLASS(CMainView)));
			pDoc->AttachBrowser(a->m_hWnd);
		}

  	CString text = AfxGetApp()->GetProfileString("Settings", "SizeRect", "");
  	CRect rect;
		if (!text.IsEmpty()) 
  	{
    		rect.left   = atoi((const char*) text);
    		rect.top    = atoi((const char*) text + 5); 
    		rect.right  = atoi((const char*) text + 10);
    		rect.bottom = atoi((const char*) text + 15);
  	} else 
  	{
   		int maxx = GetSystemMetrics(SM_CXFULLSCREEN);
   		int maxy = GetSystemMetrics(SM_CYFULLSCREEN);
			rect = CRect((long)(maxx*.1),(long)(maxy*.1),(long)(maxx*.9),(long)(maxy * .9));
  	}                           
  
  	BOOL bIconic    = AfxGetApp()->GetProfileInt("Settings", "Iconified" ,FALSE);
  	BOOL bMaximized = AfxGetApp()->GetProfileInt("Settings", "Maximized" ,FALSE);    
  	if (bIconic) 
  	{
    		nCmdShow = SW_SHOWMINNOACTIVE;
    		if (bMaximized) 
    		{
      		flags = WPF_RESTORETOMAXIMIZED;
    		}
  	} else 
  	{
    		if (bMaximized) 
    		{
      		nCmdShow = SW_SHOWMAXIMIZED;
      		flags = WPF_RESTORETOMAXIMIZED;
    		} else 
    		{
      		nCmdShow = SW_NORMAL;
      		flags = 0;
    		}
  	}                                                              
                   
  	placement.length  = sizeof(WINDOWPLACEMENT);
  	placement.showCmd = nCmdShow;
  	placement.flags   = flags;
  	placement.ptMinPosition = CPoint(0,0);                                                                  
  	placement.ptMaxPosition = CPoint(-::GetSystemMetrics(SM_CXBORDER),
                                     -::GetSystemMetrics(SM_CYBORDER));
  	placement.rcNormalPosition = rect;

  	bStatus = AfxGetApp()->GetProfileInt("Settings", "StatusBar", TRUE);
  	pBar = GetDescendantWindow(AFX_IDW_STATUS_BAR);
  	if (pBar) 
  	{
    		pBar->ShowWindow(bStatus);
  	}

    SetWindowPlacement(&placement);

  	m_Activated = TRUE;
 	}
	
	CFrameWnd::ActivateFrame(nCmdShow);
}

BOOL CMainFrame::DestroyWindow() 
{
	if (m_Timer)
		KillTimer(m_Timer);

  WINDOWPLACEMENT placement;
  placement.length = sizeof(WINDOWPLACEMENT);
  GetWindowPlacement(&placement);
  
  BOOL bIconic    = FALSE;
  BOOL bMaximized = FALSE;

  switch (placement.showCmd)
  {
  case SW_SHOWNORMAL:
    bIconic    = FALSE;
    bMaximized = FALSE;
    break;
  case SW_SHOWMAXIMIZED:
    bIconic    = FALSE;
    bMaximized = TRUE;
    break;
  case SW_SHOWMINIMIZED:
    bIconic = TRUE;
    if (placement.flags)
      bMaximized = TRUE;
    else
      bMaximized = FALSE;
  default:
    bIconic    = FALSE;
    bMaximized = FALSE;
  }    
     
  CRect r = placement.rcNormalPosition;
  CString text;
  text.Format("%04d %04d %04d %04d", r.left,  r.top, r.right, r.bottom);
        
  AfxGetApp()->WriteProfileString("Settings", "SizeRect", text);  
  AfxGetApp()->WriteProfileInt   ("Settings", "Iconified", bIconic);  
  AfxGetApp()->WriteProfileInt   ("Settings", "Maximized",  bMaximized);  
      
  CWnd *pBar = GetDescendantWindow(AFX_IDW_STATUS_BAR);
  if (pBar)
  {
    AfxGetApp()->WriteProfileInt("Settings", "StatusBar", (pBar->GetStyle() & WS_VISIBLE) != 0L);
  }                                                                                                                                                                                                                                   

	int x, xx;
	m_Splitter.GetColumnInfo(0, x, xx);
  AfxGetApp()->WriteProfileInt("Settings", "SplitterPos", x);

	return CFrameWnd::DestroyWindow();
}

BOOL CMainFrame::OnQueryNewPalette()
{
	if (m_pPalette == NULL)
		return FALSE;
	
	CClientDC dc(this);
	CPalette* pOldPalette = dc.SelectPalette(m_pPalette,
		GetCurrentMessage()->message == WM_PALETTECHANGED);
	UINT nChanged = dc.RealizePalette();
	dc.SelectPalette(pOldPalette, TRUE);

	if (nChanged == 0)
		return FALSE;
	
	Invalidate();
	
	return TRUE;
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd)
{
	if (pFocusWnd == this || IsChild(pFocusWnd))
		return;
	
	OnQueryNewPalette();
}

CPalette* CMainFrame::SetPalette(CPalette* pPalette)
{
	CPalette* pOldPalette = m_pPalette;
	m_pPalette = pPalette;
	OnQueryNewPalette();
	return pOldPalette;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (!m_Splitter.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create split bar ");
		return FALSE;
	}
	int initPos = AfxGetApp()->GetProfileInt("Settings", "SplitterPos", 3000);
	m_Splitter.CreateView(0, 0, RUNTIME_CLASS(CMainView),    CSize(initPos,300), pContext);
	m_Splitter.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(500,100),  pContext);
	m_LastSplitterPos = 0;

	return TRUE;
}

void CMainFrame::OnViewRightview() 
{
	CRightView *t = (CRightView *)m_Splitter.GetPane(0,1);

	CRect r;
	t->GetClientRect(r);
	
	if (r.Width())
	{
		// already displayed
		GetClientRect(r);
		int cx = r.Width();
		int x;
		m_Splitter.GetColumnInfo(0, m_LastSplitterPos, x);
		m_Splitter.SetColumnInfo(0, cx, 10);
		m_Splitter.RecalcLayout();
	} else
	{
		// not displayed
		GetClientRect(r);
		if (!m_LastSplitterPos)
			m_LastSplitterPos = (int)(r.Width() * .7);
		int cx = m_LastSplitterPos;
		m_Splitter.SetColumnInfo(0, cx, 10);
		m_Splitter.RecalcLayout();
	}
}

void CMainFrame::OnUpdateViewRightview(CCmdUI* pCmdUI) 
{
	CWnd *v = m_Splitter.GetPane(0,1);
	CRect r;
	v->GetClientRect(r);
	pCmdUI->SetCheck(r.Width());
}

void CMainFrame::OnHelpContents() 
{
	AfxGetApp()->WinHelp(0);	
}

void CMainFrame::OnHelpWeb() 
{
	HINSTANCE ret = ShellExecute(m_hWnd, "open", "http://www.greathill.com", "", "", SW_SHOWMAXIMIZED);
	if (ret < (HINSTANCE)32)
	{
		AfxMessageBox("No browser found.");
	}
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI)
{
#ifndef _DEBUG
  lpMMI->ptMinTrackSize.x = 790;
  lpMMI->ptMinTrackSize.y = 590;
#endif
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CFrameWnd::OnActivateApp(bActive, hTask);
	CMainDoc *doc = GetDoc();
	if (doc) doc->m_IsActive = bActive;
}

void CMainFrame::UpdateButtons(int cmdID, int checkState, int enableState)
{
	m_LeftBar.UpdateButtons(cmdID, checkState, enableState);
	m_BottomBar.UpdateButtons(cmdID, checkState, enableState);
}
