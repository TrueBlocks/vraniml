#ifndef BOOLDLG_H
#define BOOLDLG_H

#include "Resource.h"

class vrBoolTestRecord
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

class CBoolTestDialog : public CDialog
{
public:
	CBoolTestDialog(CWnd* pParent = NULL);

	//{{AFX_DATA(CBoolTestDialog)
	enum { IDD = IDD_BOOLTESTS };
	CComboBox	m_Operation;
	CComboBox	m_Group;
	BOOL	    m_Auto;
	long	    m_TestID;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CBoolTestDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CBoolTestDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif