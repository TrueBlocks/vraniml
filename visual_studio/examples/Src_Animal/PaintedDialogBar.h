#ifndef __PAINTEDDIALOGBAR_H
#define __PAINTEDDIALOGBAR_H

#include "PaintedButton.h"

//---------------------------------------------------------------------
class CPaintedDialogBar : public CDialogBar
{
private:
	int                  m_nButs;
	int                  m_Placement;
	CPaintedButtonArray  m_ButtonArray;
	CBitmap             *m_Background;

public:
	CPaintedDialogBar();

	DECLARE_DYNCREATE(CPaintedDialogBar)

	BOOL Create(CWnd *pParentWnd, UINT nID, DWORD dwStyle, UINT nID2);

	void SetParams(int n, CButtonPlacement placements[], CBitmap *back);
	void Clear(void);

public:
	//{{AFX_VIRTUAL(CPaintedDialogBar)
	//}}AFX_VIRTUAL

public:
	void UpdateButtons(int cmdID, int checkState, int enableState=-1);
	virtual ~CPaintedDialogBar();

protected:
	//{{AFX_MSG(CPaintedDialogBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
