#include "stdafx.h"

#include "MainApp.h"
#include "OpenURL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

COpenURL::COpenURL(CWnd* pParent) : CDialog(COpenURL::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenURL)
	m_URL = _T("");
	m_Preserve = FALSE;
	//}}AFX_DATA_INIT
	m_QuickOpen=FALSE;
}

void COpenURL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenURL)
	DDX_Control(pDX, IDOK, m_OkButton);
	DDX_Text(pDX, IDC_URL, m_URL);
	DDX_Check(pDX, IDC_PRESERVE, m_Preserve);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COpenURL, CDialog)
	//{{AFX_MSG_MAP(COpenURL)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFilename fn;
void COpenURL::OnBrowse() 
{
	UpdateData(TRUE);

	CString type = "wrl";
	CString dir = AfxGetApp()->GetProfileString("Settings", "LastOpenDir", GetProgramDir() + "\\..\\Sample Worlds");
	
	CFileDialogInfo data(TRUE, type, "VRML 2.0 Files|*.wrl|All Files|*.*||", "Open World", CString(CFilename(dir)));

	if (GetFileName(&data, fn))
	{
		AfxGetApp()->WriteProfileString("Settings", "LastOpenDir", fn.GetPath());
		m_URL = "file://" + CString(fn);
		UpdateData(FALSE);
		OnOK();
		return;
	}

	if (m_QuickOpen)
	{
		OnCancel();
		return;
	}

	UpdateData(FALSE);

	m_OkButton.SetFocus();
}

void COpenURL::OnOK() 
{
	UpdateData(TRUE);

	AfxGetApp()->WriteProfileInt("Settings", "PreserveFilename", m_Preserve);

	if (m_Preserve)
	{
		AfxGetApp()->WriteProfileString("Settings", "Filename", CString(fn));
	}

	CDialog::OnOK();
}

BOOL COpenURL::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_Preserve = AfxGetApp()->GetProfileInt("Settings", "PreserveFilename", FALSE);

	UpdateData(FALSE);

	if (m_QuickOpen)
	{
		OnBrowse();
		return FALSE;
	}
		
	return TRUE;
}
