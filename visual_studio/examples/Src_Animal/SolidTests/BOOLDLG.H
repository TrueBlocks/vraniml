#ifndef BOOLDLG_H
#define BOOLDLG_H

#include "Resource.h"

class DLLInterface vrBoolTestRecord
{
public:
	BOOL center;
	BOOL rotate;
	BOOL wide;
	long op;
	long group;
	long testId;

	vrBoolTestRecord(void)
		{
			center = rotate = wide = FALSE ;
			op = group = testId = 0;
		}
};

class DLLInterface CBoolDlg : public CDialog
{
public:
	CBoolDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(CBoolDlg)
	enum { IDD = IDD_BOOLTESTS };
	CComboBox	m_Operation;
	CComboBox	m_Group;
	BOOL	    m_Auto;
	long	    m_TestID;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CBoolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CBoolDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif