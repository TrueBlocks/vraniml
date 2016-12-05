#ifndef __MAINFRAME_H
#define __MAINFRAME_H

#include "PaintedDialogBar.h"
#include "Splitter.h"

class CMainFrame : public CFrameWnd
{
protected:
	CStatusBar         m_StatusBar;
	CSplitter          m_Splitter;
	CPaintedDialogBar  m_BottomBar;
	CPaintedDialogBar  m_LeftBar;
	CPalette          *m_pPalette;
	int m_Timer; // this timer keeps the idle processor pumping -- don't remove it.

	int                m_LastSplitterPos;

public:
	BOOL m_Activated;

	CBitmap           *m_bmBackground;

	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
	void UpdateButtons(int cmdID, int checkState, int enableState=-1);
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void ActivateFrame(int nCmdShow = -1);
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

	virtual ~CMainFrame();

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	        CPalette* SetPalette(CPalette* pPalette);
	
	//{{AFX_MSG(CMainFrame)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewRightview();
	afx_msg void OnUpdateViewRightview(CCmdUI* pCmdUI);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnHelpContents();
	afx_msg void OnHelpWeb();
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

inline CMainFrame *GetFrame() { return (CMainFrame*)AfxGetApp()->m_pMainWnd; }
#endif
