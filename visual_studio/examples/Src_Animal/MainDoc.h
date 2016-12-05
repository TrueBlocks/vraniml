#ifndef __MAINDOC_H
#define __MAINDOC_H

#include "MyBrowser.h"
class CMainDoc : public CDocument
{
protected:
	CMainDoc();
	DECLARE_DYNCREATE(CMainDoc)

	vrMyBrowser *m_Browser;
	SFBool m_IsActive;
	SFBool     m_Loaded;

public:
	vrMyBrowser *GetBrowser() { return m_Browser; }
	void AttachBrowser(HWND hWnd);
	void Redraw(void);
#define GetDoc CMainDoc::GetDoc
	static CMainDoc *GetDoc(void);

	void DoOpenFile(const SFString& filename);
	void DoUpdateTitle(const SFString& filename);
	void Import(CString filename);

	void UpdateUI(CCmdUI *pCmdUI, SFBool checkState, SFBool enableState);

	//{{AFX_VIRTUAL(CMainDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	virtual void SetPathName(LPCTSTR lpszPathName, BOOL bAddToMRU = TRUE);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

public:
	virtual ~CMainDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CMainDoc)
	afx_msg void OnFileOpen();
	afx_msg void OnFileKillAll();
	afx_msg void OnUpdateFileKillAll(CCmdUI* pCmdUI);
	afx_msg void OnNavigationSlide();
	afx_msg void OnUpdateNavigationSlide(CCmdUI* pCmdUI);
	afx_msg void OnNavigationRotateZ();
	afx_msg void OnUpdateNavigationRotateZ(CCmdUI* pCmdUI);
	afx_msg void OnNavigationExamine();
	afx_msg void OnUpdateNavigationExamine(CCmdUI* pCmdUI);
	afx_msg void OnNavigationRotateX();
	afx_msg void OnUpdateNavigationRotateX(CCmdUI* pCmdUI);
	afx_msg void OnNavigationWalk();
	afx_msg void OnUpdateNavigationWalk(CCmdUI* pCmdUI);
	afx_msg void OnViewSource();
	afx_msg void OnUpdateViewSource(CCmdUI* pCmdUI);
	afx_msg void OnViewBackground();
	afx_msg void OnUpdateViewBackground(CCmdUI* pCmdUI);
	afx_msg void OnInsert();
	afx_msg void OnUpdateInsert(CCmdUI* pCmdUI);
	afx_msg void OnViewDrawmodePolygons();
	afx_msg void OnViewDrawmodeLines();
	afx_msg void OnViewDrawmodePoints();
	afx_msg void OnUpdateViewDrawmodeLines(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDrawmodePoints(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewDrawmodePolygons(CCmdUI* pCmdUI);
	afx_msg void OnViewLights();
	afx_msg void OnUpdateViewLights(CCmdUI* pCmdUI);
	afx_msg void OnFileReload();
	afx_msg void OnFileImport();
	afx_msg void OnViewCenterobjects();
	afx_msg void OnUpdateViewCenterobjects(CCmdUI* pCmdUI);
	afx_msg void OnViewBoundingboxes();
	afx_msg void OnUpdateViewBoundingboxes(CCmdUI* pCmdUI);
	afx_msg void OnFileExport();
	afx_msg void OnUpdateFileExport(CCmdUI* pCmdUI);
	afx_msg void OnViewHeadsupdisplay();
	afx_msg void OnUpdateViewHeadsupdisplay(CCmdUI* pCmdUI);
	afx_msg void OnNavigationRotateY();
	afx_msg void OnUpdateNavigationRotateY(CCmdUI* pCmdUI);
	afx_msg void OnNavigationAutoanimate();
	afx_msg void OnUpdateNavigationAutoanimate(CCmdUI* pCmdUI);
	afx_msg void OnNavigationStraighten();
	afx_msg void OnUpdateNavigationStraighten(CCmdUI* pCmdUI);
	afx_msg void OnViewInbrowser();
	afx_msg void OnUpdateViewInbrowser(CCmdUI* pCmdUI);
	afx_msg void OnHiddenQuickopen();
	afx_msg void OnFilePreferences();
	afx_msg void OnHelpContents();
	afx_msg void OnViewpointsList();
	afx_msg void OnUpdateViewpointsList(CCmdUI* pCmdUI);
	afx_msg void OnViewpointsNext();
	afx_msg void OnUpdateViewpointsNext(CCmdUI* pCmdUI);
	afx_msg void OnViewpointsPrev();
	afx_msg void OnUpdateViewpointsPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpContents(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileImport(CCmdUI* pCmdUI);
	afx_msg void On0Testing();
	afx_msg void OnUpdate0Testing(CCmdUI* pCmdUI);
	afx_msg void OnSolidmodelProperties();
	afx_msg void OnUpdateSolidmodelProperties(CCmdUI* pCmdUI);
	afx_msg void OnSolidmodelObjectsBall();
	afx_msg void OnSolidmodelObjectsCar();
	afx_msg void OnSolidmodelObjectsPedro();
	afx_msg void OnSolidmodelObjectsPlant();
	afx_msg void OnSolidmodelObjectsTwist();
	afx_msg void OnInsertSolidobjectsTwist2();
	afx_msg void OnInsertSolidalgorithmsTranslationalsweep();
	afx_msg void OnInsertSolidalgorithmsRotationalsweep();
	afx_msg void OnSolidmodelSplitplaneTest1();
	afx_msg void OnInsertSolidboolean();
	afx_msg void OnInsertBooltests2Factorypart();
	afx_msg void OnInsertBooltests2Table();
	afx_msg void On0Autotest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
