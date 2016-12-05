#include "stdafx.h"

#include "MainApp.h"

#include "PaintedDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
IMPLEMENT_DYNCREATE(CPaintedDialogBar, CDialogBar)

BEGIN_MESSAGE_MAP(CPaintedDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(CPaintedDialogBar)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPaintedDialogBar::CPaintedDialogBar()
{
	m_Placement = -1;
	m_nButs = 0;
	m_Background = NULL;
}

CPaintedDialogBar::~CPaintedDialogBar()
{
	Clear();
}

void CPaintedDialogBar::Clear(void)
{
	for (int i=0;i<m_nButs;i++)
	{
		CPaintedButton *but = m_ButtonArray.GetAt(i);
		delete but;
	}
	m_ButtonArray.RemoveAll();
	m_nButs=0;
}

void CPaintedDialogBar::SetParams(int n, CButtonPlacement placements[], CBitmap *back)
{
	Clear();

	m_nButs = 0;
	while (m_nButs < n)
	{
		CPaintedButton *but = NULL;
		if (placements[m_nButs].msgID)
		{
			but = new CPaintedButton(&placements[m_nButs]);
			but->Create(this, placements[m_nButs].msgID,  placements[m_nButs].iconID);
			but->m_Background = back;
		}
		m_ButtonArray.SetAtGrow(m_nButs++, but);
	}

	m_Background = back;
}

BOOL CPaintedDialogBar::OnEraseBkgnd(CDC* pDC)
{
	CRect r;
	GetClientRect(r);

	if (m_Background)
	{
		BITMAP bmInfo;
		m_Background->GetBitmap(&bmInfo);

		// Tile the given background image on the dialog bar
		int rows = (int)((((double)r.Height() / bmInfo.bmHeight) + 0.5) + 1);
		int cols = (int)((((double)r.Width() / bmInfo.bmWidth) + 0.5) + 1);

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		CBitmap *oldBM = memDC.SelectObject(m_Background);
		for (int i=0;i<rows;i++)
		{
			for (int j=0;j<cols;j++)
			{
				int x = j * bmInfo.bmWidth;
				int y = i * bmInfo.bmHeight;
				pDC->BitBlt(x, y, bmInfo.bmWidth, bmInfo.bmHeight, &memDC, 0, 0, SRCCOPY);
			}
		}
		memDC.SelectObject(oldBM);
		return FALSE;
	}

	return CDialogBar::OnEraseBkgnd(pDC);
}

void CPaintedDialogBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	// If the mouse moves on this window then disable any existing colored buttons
	CPaintedButton::ButtonOff();
	CDialogBar::OnMouseMove(nFlags, point);
}


BOOL CPaintedDialogBar::Create(CWnd *pParentWnd, UINT nID, DWORD dwStyle, UINT nID2)
{
	BOOL ret = CDialogBar::Create(pParentWnd, nID, dwStyle, nID2);

	if (dwStyle & CBRS_TOP)
	{
		m_Placement = CBRS_TOP;
	} else if (dwStyle & CBRS_BOTTOM)
	{
		m_Placement = CBRS_BOTTOM;
	} else if (dwStyle & CBRS_RIGHT)
	{
		m_Placement = CBRS_RIGHT;
	} else
	{
		m_Placement = CBRS_LEFT;
	}
	return ret;
}

void CPaintedDialogBar::OnSize(UINT nType, int cx, int cy) 
{
	CDialogBar::OnSize(nType, cx, cy);

	if (m_nButs)
	{
		CRect r;
		GetClientRect(r);

		int w = r.Width();
		int h = r.Height();

#define B 4
#define S (B*2)

		for (int i=0;i<m_nButs;i++)
		{
			CPaintedButton *b = m_ButtonArray.GetAt(i);
			if (b)
			{
				int num = b->m_Placement.num;
				int align = b->m_Placement.align;

				if (m_Placement == CBRS_TOP || m_Placement == CBRS_BOTTOM)
				{
					int y1 = B;
					int y2 = h-B;

					int bw = h-S; // button width (also button height)

					int x1=0, x2=0;

					if (align==FIRSTPLACE)
					{
						x1 = (num*(S+bw))+6; x2 = ((num+1)*(S+bw)); 
					}
					if (align==LAST)
					{
						x1 = w-((num+1)*(S+bw)); x2 = w-(num*(S+bw)+S); 
					}
					if (align==CENTER)
					{
						ASSERT(0);
						x1 = (b->m_Placement.num*(S+bw))+6; x2 = ((b->m_Placement.num+1)*(S+bw)); 
					}
					b->MoveWindow(CRect( x1, y1, x2, y2));
				} else
				{
					ASSERT(m_Placement == CBRS_LEFT || m_Placement == CBRS_RIGHT);
					int x1 = B;
					int x2 = w-B;

					int bw = w-S; // button width (also button height)

					int y1=0, y2=0;

					int num = b->m_Placement.num;
					int align = b->m_Placement.align;
					if (align==FIRSTPLACE)
					{
						y1 = (num*(S+bw))+6; y2 = ((num+1)*(S+bw)); 
					}
					if (align==LAST)
					{
						y1 = h-((num+1)*(S+bw)); y2 = h-(num*(S+bw)+S); 
					}
					if (align==CENTER)
					{
						ASSERT(0);
						x1 = (num*(S+bw))+6; x2 = ((b->m_Placement.num+1)*(S+bw)); 
					}
					b->MoveWindow(CRect( x1, y1+4, x2, y2+4));
				}
			}
		}
	}
}

void CPaintedDialogBar::UpdateButtons(int cmdID, int checkState, int enableState)
{
	for (int i=0;i<m_nButs;i++)
	{
		CPaintedButton *b = m_ButtonArray.GetAt(i);
		if (b->m_CmdID == cmdID)
		{
			if (checkState!=-1)
				b->SetCheck(checkState);
//			if (enableState!=-1)
//				b->SetEnabled(enableState);
		}
	}
}
