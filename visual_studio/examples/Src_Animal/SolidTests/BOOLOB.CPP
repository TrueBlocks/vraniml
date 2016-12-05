#include "..\stdafx.h"

#include "Tests.h"
#include "BoolOb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBoolObDlg::CBoolObDlg(CWnd* pParent) : CDialog(CBoolObDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoolObDlg)
	m_Merge = FALSE;
	//}}AFX_DATA_INIT
}

void CBoolObDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoolObDlg)
	DDX_Control(pDX, IDC_OBJECT, m_ObjectCtrl);
	DDX_Check(pDX, IDC_MERGE, m_Merge);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBoolObDlg, CDialog)
	//{{AFX_MSG_MAP(CBoolObDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBoolObDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ObjectCtrl.SetCurSel(AfxGetApp()->GetProfileInt("Tests", "LastOb", 0));
	m_Merge = AfxGetApp()->GetProfileInt("Tests", "LastObMerge", FALSE);
	
	UpdateData(FALSE);
	
	return TRUE;
}

void CBoolObDlg::OnOK() 
{
	UpdateData(TRUE);

	AfxGetApp()->WriteProfileInt("Tests", "LastOb", m_ObjectCtrl.GetCurSel());
	AfxGetApp()->WriteProfileInt("Tests", "LastObMerge", m_Merge);

	CDialog::OnOK();
}
