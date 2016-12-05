#ifndef __MAINAPP_H
#define __MAINAPP_H

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"

class CMainApp : public CWinApp
{
public:
	CMainApp();

	//{{AFX_VIRTUAL(CMainApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMainApp)
	afx_msg void OnAppAbout();
	afx_msg void OnHelpContentsHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
