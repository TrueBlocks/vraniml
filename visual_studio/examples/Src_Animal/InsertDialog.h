#ifndef __INSERT_DIALOG_H
#define __INSERT_DIALOG_H
 
#include "MainDoc.h"

#include "Dialogs.h"

class CInsertDialog : public CDialog
{
public:
	CBoxPage boxPage;
	CConePage conePage;
	CCylinderPage cylinderPage;
	CSpherePage spherePage;
	CElevationGridPage elevPage;
	CMaterialPage matPage;
	CTexturePage texPage;

	CMainDoc *pDoc;
	BOOL changed;

	CInsertDialog(CWnd* pParent = NULL);

	vrAppearance *GetAppearance();
	void Insert(vrNode *node);
	void Insert(const CString& fn);

	void Reset();

	//{{AFX_DATA(CInsertDialog)
	enum { IDD = IDD_INSERTDIALOG };
	CComboBox	m_GeomType;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CInsertDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CInsertDialog)
	afx_msg void OnInsertgeom();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnProperties();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
