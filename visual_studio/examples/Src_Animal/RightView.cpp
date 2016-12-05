#include "stdafx.h"

#include "MainApp.h"
#include "MainFrm.h"
#include "MainDoc.h"
#include "RightView.h"

#include "TreeTraverser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CRightView, CTreeView)

vrTreeTraverser *tt=NULL;
CRightView::CRightView()
{
}

CRightView::~CRightView()
{
	if (tt)
		delete tt;
}

BEGIN_MESSAGE_MAP(CRightView, CTreeView)
	//{{AFX_MSG_MAP(CRightView)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CRightView::OnDraw(CDC* pDC)
{
}

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CRightView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif

void CRightView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
}

void CRightView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (GetDoc()->IsModified() && GetDoc()->GetBrowser())
	{
		CTreeCtrl& t = GetTreeCtrl();
		if (GetDoc()->GetBrowser()->GetChildren())
		{
			if (tt)
				delete tt;
			tt = new vrTreeTraverser(GetDoc()->GetBrowser(), &t);
			tt->Traverse(GetDoc()->GetBrowser());
		} else
		{
			t.DeleteAllItems();
			t.InsertItem("None");
		}
	}

	CTreeView::OnUpdate(pSender, lHint, pHint);
}

BOOL CRightView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= (TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS|TVS_SHOWSELALWAYS|TVS_DISABLEDRAGDROP);
	
	return CTreeView::PreCreateWindow(cs);
}

void CRightView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// If the mouse moves on this window then disable any existing colored buttons
	CPaintedButton::ButtonOff();

	CTreeView::OnMouseMove(nFlags, point);
}

void CRightView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CTreeView::OnRButtonDown(nFlags, point);

 	CMenu menu;	
	menu.LoadMenu(IDR_RIGHTVIEWMENU);
 	CMenu *pPopUp = menu.GetSubMenu(0);

	ClientToScreen(&point);
	if (pPopUp)
	{
		pPopUp->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}

