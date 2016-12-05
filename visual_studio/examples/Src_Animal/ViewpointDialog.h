#ifndef __VIEWPOINTDIALOG_H
#define __VIEWPOINTDIALOG_H
 
class CViewpointDialog : public CDialog
{
public:
	vrBrowser *browser;

	CViewpointDialog(CWnd* pParent = NULL);

	//{{AFX_DATA(CViewpointDialog)
	enum { IDD = IDD_VIEWPOINTS };
	CListBox	m_ListCtrl;
	CString	m_List;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CViewpointDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CViewpointDialog)
	afx_msg void OnDoubleClick();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

SFInt32 CountViewpoints(vrBrowser *browser);
void BindViewpoint(vrBrowser *m_Browser, int sel);

#endif
