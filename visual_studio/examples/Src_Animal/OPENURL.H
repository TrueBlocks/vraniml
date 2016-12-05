#ifndef _OPENURL_H
#define _OPENURL_H

class COpenURL : public CDialog
{
public:
	COpenURL(CWnd* pParent = NULL);

	SFBool m_QuickOpen;

	//{{AFX_DATA(COpenURL)
	enum { IDD = IDD_OPENURL };
	CButton	m_OkButton;
	CString	m_URL;
	BOOL	m_Preserve;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(COpenURL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(COpenURL)
	afx_msg void OnBrowse();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif