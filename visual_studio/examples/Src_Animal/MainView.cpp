#include "stdafx.h"

#include "MainApp.h"
#include "MainFrm.h"
#include "MainDoc.h"
#include "MainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainView, CView)

BEGIN_MESSAGE_MAP(CMainView, CView)
	//{{AFX_MSG_MAP(CMainView)
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_MESSAGE(SENSOR_MESSAGE, OnOverSensor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainView::CMainView()
{
	m_isOver=FALSE;
}

CMainView::~CMainView()
{
}

BOOL CMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CMainView::OnDraw(CDC* pDC)
{
	if (GetDoc() && GetDoc()->GetBrowser())
		GetDoc()->GetBrowser()->Traverse();
}

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CView::AssertValid();
}

void CMainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif

void CMainView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
}

void CMainView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	if (GetDoc() && GetDoc()->GetBrowser())
	{
		vrRenderTraverser *rt = (vrRenderTraverser *)GetDoc()->GetBrowser()->GetTraverserByType(GETRUNTIME_CLASS(vrRenderTraverser));
		ASSERT(rt && rt->IsKindOf(GETRUNTIME_CLASS(vrRenderTraverser)));
		rt->SetViewport(0,0,cx,cy);
	}
}

void CMainView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnRButtonDown(nFlags, point);

 	CMenu menu;	
	menu.LoadMenu(IDR_RIGHTVIEWMENU);
 	CMenu *pPopUp = menu.GetSubMenu(0);

	ClientToScreen(&point);
	if (pPopUp)
	{
	 pPopUp->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

BOOL CMainView::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message==WM_MOUSEMOVE)
	{
		// If mouse moves in this window, then all buttons should turned off
		CPaintedButton::ButtonOff();
	}
	
	if (GetDoc() && GetDoc()->GetBrowser())
	{
		CPoint pt = pMsg->pt;
		ScreenToClient(&pt);
		vrUserMessage msg(pMsg->message, pMsg->wParam, pMsg->lParam, SFVec3f(pt.x, pt.y, 0.0));
		if (GetDoc()->GetBrowser()->ProcessUserMessage(msg))
			return TRUE; // Non-zero means ignore it
	}
	
	return CView::PreTranslateMessage(pMsg);
}


void CMainView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// If the mouse moves on this window then disable any existing colored buttons
	CPaintedButton::ButtonOff();
	
	CView::OnMouseMove(nFlags, point);
}

void CMainView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	InvalidateRect(NULL);
	UpdateWindow();
}

BOOL CMainView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_isOver)
	{
	  ::SetCursor(AfxGetApp()->LoadCursor(MAKEINTRESOURCE(IDC_SENSOR)));
		return FALSE;
	}
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CMainView::OnOverSensor(WPARAM wParam, LPARAM lParam)
{
	vrSensor *sensor = (vrSensor *)wParam;
	if (sensor)
		m_isOver = TRUE;
	else
		m_isOver = FALSE;
	return TRUE;
}
