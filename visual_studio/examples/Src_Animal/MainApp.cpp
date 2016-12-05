#include "stdafx.h"

#include "MainApp.h"
#include "MainFrm.h"
#include "MainDoc.h"
#include "MainView.h"

#include "AfxDisp.h"

#include "Splash.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMainApp, CWinApp)
	//{{AFX_MSG_MAP(CMainApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP_CONTENTS_HELP, OnHelpContentsHelp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CMainApp::CMainApp()
{
}

CMainApp theApp;

BOOL CMainApp::InitInstance()
{
	SetRegistryKey(_T("Great Hill Corporation"));

#ifndef _DEBUG
	if (!GetProfileInt("Settings", "ProperExit", FALSE))
	{
		WriteProfileString("Settings", "Filename", GetProgramDir() + "/logo.wrl");
	}
	WriteProfileInt("Settings", "ProperExit", FALSE);
#endif

	CSplashWnd::EnableSplashScreen(TRUE);

	{
		CCommandLineInfo cmdInfo;
		ParseCommandLine(cmdInfo);

		if (cmdInfo.m_strFileName!="")
			WriteProfileString("Settings", "Filename", cmdInfo.m_strFileName);
	}

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	AfxEnableControlContainer();

	LoadStdProfileSettings(0);

	CSingleDocTemplate* pDocTemplate;
#undef new
	pDocTemplate = new CSingleDocTemplate(
						IDR_MAINFRAME,
						RUNTIME_CLASS(CMainDoc),
						RUNTIME_CLASS(CMainFrame),
						RUNTIME_CLASS(CMainView));
	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

#include "About.h"
void CMainApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

BOOL CMainApp::OnIdle(LONG lCount)
{
	BOOL bBaseIdle = CWinApp::OnIdle(lCount);

	BOOL bMoreIdle = TRUE;
	if (lCount == 0)
	{
		// For continuously updated rendering do this:
		CMainDoc *doc = GetDoc();
		doc->Redraw();
	} else if (lCount == 100)
	{
	} else if (lCount == 1000)
	{
		bMoreIdle = bBaseIdle;
	}

	return bMoreIdle;
}

BOOL CMainApp::PreTranslateMessage(MSG* pMsg)
{
	return CWinApp::PreTranslateMessage(pMsg);
}

void CMainApp::OnHelpContentsHelp() 
{
	CFilename filename(GetProgramDir()+"/../Documentation/browserman.htm");
	if (filename.Exists())
	{
		CDirectoryPreserver d(GetProgramDir());
		{
			CDirectoryPreserver d("..\\Documentation");
			CString cmd("runme.exe browser");
			WinExec(cmd, SW_SHOW);
		}
	} else
	{
		SFString msg = "Please download the VRaniML help file documentation available at http://www.greathill.com/vrml.htm";
		AfxMessageBox((char *)msg);
	}
}
