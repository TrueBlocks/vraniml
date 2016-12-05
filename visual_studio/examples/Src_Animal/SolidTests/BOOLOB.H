#ifndef _BOOLOB
#define _BOOLOB

class DLLInterface CBoolObDlg : public CDialog
{
public:
	CBoolObDlg(CWnd* pParent = NULL);

	//{{AFX_DATA(CBoolObDlg)
	enum { IDD = IDD_BOOLTESTS2 };
	CComboBox	m_ObjectCtrl;
	BOOL	m_Merge;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CBoolObDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CBoolObDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif