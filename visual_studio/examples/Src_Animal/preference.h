#ifndef __PREFERENCE_H
#define __PREFERENCE_H
 
class CPreference : public CDialog
{
public:
	CPreference(CWnd* pParent = NULL);

	//{{AFX_DATA(CPreference)
	enum { IDD = IDD_PREFERENCES };
	CComboBox	m_NavMode;
	CComboBox	m_DrawMode;
	BOOL	m_AutoRotate;
	BOOL	m_HeadsUp;
	BOOL	m_SaveFile;
	BOOL	m_AllFields;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPreference)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPreference)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
