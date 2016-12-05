#include "stdafx.h"
#include "mainapp.h"
#include "Preference.h"

#include "MyBrowser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPreference::CPreference(CWnd* pParent) : CDialog(CPreference::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreference)
	m_AutoRotate = FALSE;
	m_HeadsUp = FALSE;
	m_SaveFile = FALSE;
	m_AllFields = FALSE;
	//}}AFX_DATA_INIT
}

void CPreference::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreference)
	DDX_Control(pDX, IDC_NAVMODE, m_NavMode);
	DDX_Control(pDX, IDC_COMBO1, m_DrawMode);
	DDX_Check(pDX, IDC_AUTOROTATE, m_AutoRotate);
	DDX_Check(pDX, IDC_HEADSUPDISPLAY, m_HeadsUp);
	DDX_Check(pDX, IDC_SAVEFILENAMEONLOAD, m_SaveFile);
	DDX_Check(pDX, IDC_EXPORTALLFIELDS, m_AllFields);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPreference, CDialog)
	//{{AFX_MSG_MAP(CPreference)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPreference::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_AutoRotate = AfxGetApp()->GetProfileInt("Settings", "AutoAnimate", TRUE);
	m_SaveFile = AfxGetApp()->GetProfileInt("Settings", "PreserveFilename", FALSE);
	m_HeadsUp = AfxGetApp()->GetProfileInt("Settings", "HeadsUpDisplay", FALSE);
	m_AllFields = AfxGetApp()->GetProfileInt("Settings", "AllFields", FALSE);
	m_DrawMode.SetCurSel(AfxGetApp()->GetProfileInt("Settings", "DrawMode", 0));
	m_NavMode.SetCurSel(AfxGetApp()->GetProfileInt("Settings", "NavMode", MOVEMODE_WALK));
	
	UpdateData(FALSE);
	return TRUE;
}

void CPreference::OnOK() 
{
	UpdateData(TRUE);
	
	AfxGetApp()->WriteProfileInt("Settings", "AutoAnimate", m_AutoRotate);
	AfxGetApp()->WriteProfileInt("Settings", "PreserveFilename", m_SaveFile);
	AfxGetApp()->WriteProfileInt("Settings", "HeadsUpDisplay", m_HeadsUp);
	AfxGetApp()->WriteProfileInt("Settings", "AllFields", m_AllFields);
	AfxGetApp()->WriteProfileInt("Settings", "DrawMode", m_DrawMode.GetCurSel());
	AfxGetApp()->WriteProfileInt("Settings", "NavMode", m_NavMode.GetCurSel());

	CDialog::OnOK();
}
