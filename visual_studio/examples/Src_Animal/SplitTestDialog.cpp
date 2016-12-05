#include "stdafx.h"

#include "SolidTests/Tests.h"
#include "SplitTestDialog.h"

CSplitTestDialog::CSplitTestDialog(CWnd* pParent) : CDialog(CSplitTestDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplitTestDialog)
	m_TestNum = 0;
	m_Iterations = 0;
	m_Ball = FALSE;
	m_Merge = FALSE;
	m_Auto = FALSE;
	m_MoveIn = FALSE;
	//}}AFX_DATA_INIT
}

void CSplitTestDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplitTestDialog)
	DDX_Text(pDX, IDC_TESTNUM, m_TestNum);
	DDV_MinMaxLong(pDX, m_TestNum, 0, 16);
	DDX_Text(pDX, IDC_ITERATIONS, m_Iterations);
	DDX_Check(pDX, IDC_BALL, m_Ball);
	DDX_Check(pDX, IDC_MERGE, m_Merge);
	DDX_Check(pDX, IDC_AUTO, m_Auto);
	DDX_Check(pDX, IDC_BALL2, m_MoveIn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSplitTestDialog, CDialog)
	//{{AFX_MSG_MAP(CSplitTestDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
