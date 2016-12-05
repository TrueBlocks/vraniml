// sample3.h : main header file for the SAMPLE3 application
//

#if !defined(AFX_SAMPLE3_H__306F9E9B_7593_11D1_9AFF_004005341B72__INCLUDED_)
#define AFX_SAMPLE3_H__306F9E9B_7593_11D1_9AFF_004005341B72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSample3App:
// See sample3.cpp for the implementation of this class
//

class CSample3App : public CWinApp
{
public:
	CSample3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSample3App)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSample3App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLE3_H__306F9E9B_7593_11D1_9AFF_004005341B72__INCLUDED_)
