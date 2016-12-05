#ifndef __RIGHTVIEW_H
#define __RIGHTVIEW_H
 
#include "MainDoc.h"

class CRightView : public CTreeView
{
protected:
	CRightView();
	DECLARE_DYNCREATE(CRightView)

public:
	//{{AFX_VIRTUAL(CRightView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	virtual ~CRightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CRightView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
