#include "stdafx.h"

#include "Solidtests/Tests.h"
#include "BoolTestDialog.h"

CBoolTestDialog::CBoolTestDialog(CWnd* pParent) : CDialog(CBoolTestDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoolTestDialog)
	m_Auto = FALSE;
	m_TestID = 0;
	//}}AFX_DATA_INIT
}

void CBoolTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoolTestDialog)
	DDX_Control(pDX, IDC_OPERATION, m_Operation);
	DDX_Control(pDX, IDC_GROUP, m_Group);
	DDX_Check(pDX, IDC_AUTO, m_Auto);
	DDX_Text(pDX, IDC_TESTNUM, m_TestID);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBoolTestDialog, CDialog)
	//{{AFX_MSG_MAP(CBoolTestDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBoolTestDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_TestID   = AfxGetApp()->GetProfileInt("Tests", "BoolLastTest", 7);
	m_Auto     = AfxGetApp()->GetProfileInt("Tests", "BoolAutoTest", FALSE);

	m_Operation.SetCurSel(AfxGetApp()->GetProfileInt("Tests", "BoolLastOperation", 4));
	m_Group.SetCurSel(AfxGetApp()->GetProfileInt("Tests", "BoolLastGroup", 0));

	UpdateData(FALSE);

	return TRUE;
}

void CBoolTestDialog::OnOK() 
{
	UpdateData(TRUE);
	
	AfxGetApp()->WriteProfileInt("Tests", "BoolLastOperation", m_Operation.GetCurSel());
	AfxGetApp()->WriteProfileInt("Tests", "BoolLastGroup",     m_Group.GetCurSel());
	AfxGetApp()->WriteProfileInt("Tests", "BoolLastTest",      m_TestID);
	AfxGetApp()->WriteProfileInt("Tests", "BoolAutoTest",      m_Auto);

	CDialog::OnOK();
}
