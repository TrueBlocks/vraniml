#include "stdafx.h"

#include "MainApp.h"

#include "PaintedButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CPaintedButton, CBitmapButton)

CPaintedButton::CPaintedButton(CButtonPlacement *bp)
{
	m_Icon       = NULL;
	m_IsActive   = NORMAL;
	m_Checked    = FALSE;
	m_CmdID      = -1;

	if (bp)
	{
		m_Placement = *bp;
	}
	m_Background = NULL;
}

CPaintedButton::~CPaintedButton()
{
	if (m_Icon)
		delete m_Icon;
	if (m_ActiveButtonPtr == this)
	{
		m_ActiveButtonPtr=NULL;
	}
}

// The single active button that gets the highlight
CPaintedButton *CPaintedButton::m_ActiveButtonPtr = NULL;
void CPaintedButton::ButtonOff()
{
	if (m_ActiveButtonPtr)
	{
		m_ActiveButtonPtr->SetIsActive(NORMAL);
	}
}

void CPaintedButton::SetIsActive(BOOL val)
{
	m_IsActive = val;
	InvalidateRect(NULL);
	UpdateWindow();
	if (val==NORMAL)
	{
		m_ActiveButtonPtr=NULL;
	} else
	{
		ASSERT(val==ACTIVE);
		m_ActiveButtonPtr=this;
	}
}

BEGIN_MESSAGE_MAP(CPaintedButton, CBitmapButton)
	//{{AFX_MSG_MAP(CPaintedButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPaintedButton::Create(CWnd *pParent, UINT id, UINT iconID) 
{
	if (iconID)
	{
		m_Icon = new CBitmap;
		m_Icon->LoadBitmap(iconID);
	}
	
	m_CmdID = id;

	return CBitmapButton::Create("", BS_OWNERDRAW|WS_CHILD|WS_VISIBLE, CRect(0,0,0,0), pParent, id);
}

void DrawTransparentBitmap(CDC *dc, CBitmap *bitmap, CPoint tl, CPoint offset=CPoint(0,0), CPoint source=CPoint(0,0));

void CPaintedButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	int   action = lpDrawItemStruct->itemAction;
	int   bstate = lpDrawItemStruct->itemState;
	CRect r      = lpDrawItemStruct->rcItem;
	CRect orig   = lpDrawItemStruct->rcItem;

	CDC *dc = CDC::FromHandle(lpDrawItemStruct->hDC);

	CPoint tl(0,0);
	CPoint offset(0,0);
	if (m_Icon)
	{
		BITMAP bh;
		m_Icon->GetBitmap(&bh);

#if 0
		int w = r.Width();
		int h = r.Height();
		int bW = bh.bmWidth;
		int bH = bh.bmHeight;
#endif
	}

	if (action & ODA_DRAWENTIRE)
	{
		if (bstate & ODS_DISABLED)
		{
			if (m_ActiveButtonPtr == this)
			{
				SetIsActive(NORMAL);
			}
			DrawTransparentBitmap(dc, m_Icon, tl, offset, CPoint(120,0));
		} else
		{
			if (m_Checked)
			{
				DrawTransparentBitmap(dc, m_Icon, tl, offset, CPoint(80,0));
			} else if (m_IsActive!=ACTIVE)
			{
				DrawTransparentBitmap(dc, m_Icon, tl, offset);
			} else
			{
				DrawTransparentBitmap(dc, m_Icon, tl, offset, CPoint(40,0));
			}
		}
		return;
	} else if (action & ODA_SELECT)
	{
		if (bstate & ODS_SELECTED)
		{
			offset=CPoint(2,2);
		}
		OnEraseBkgnd(dc);
		if (m_Checked)
		{
			DrawTransparentBitmap(dc, m_Icon, tl, offset, CPoint(80,0));
		} else if (m_IsActive!=ACTIVE)
		{
			DrawTransparentBitmap(dc, m_Icon, tl, offset);
		} else
		{
			DrawTransparentBitmap(dc, m_Icon, tl, offset, CPoint(40,0));
		}
	}
}

BOOL CPaintedButton::OnEraseBkgnd(CDC* pDC) 
{
	CRect r;
	GetClientRect(r);

	// Draw the underlying bmp to clean up
	if (m_Background)
	{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap *oldBM = memDC.SelectObject(m_Background);
		pDC->BitBlt(0, 0, r.Width(), r.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(oldBM);
		return FALSE;
	} else
	{
		return CBitmapButton::OnEraseBkgnd(pDC);
	}
}

void CPaintedButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_IsActive!=ACTIVE)
	{
		ButtonOff();
		SetIsActive(ACTIVE);
	}

	CBitmapButton::OnMouseMove(nFlags, point);
}

void CPaintedButton::SetCheck(int state)
{
	if (state != m_Checked)
	{
		m_Checked = state;
		InvalidateRect(NULL);
		UpdateWindow();
	}
}
