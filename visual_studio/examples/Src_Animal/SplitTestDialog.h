#ifndef _H_SPLITTEST
#define _H_SPLITTEST

#include "resource.h"

class CSplitTestDialog : public CDialog
{
public:
	CSplitTestDialog(CWnd* pParent = NULL);

	//{{AFX_DATA(CSplitTestDialog)
	enum { IDD = IDD_SPLITTESTS };
	long	m_TestNum;
	long	m_Iterations;
	BOOL	m_Ball;
	BOOL	m_Merge;
	BOOL	m_Auto;
	BOOL	m_MoveIn;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CSplitTestDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CSplitTestDialog)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif