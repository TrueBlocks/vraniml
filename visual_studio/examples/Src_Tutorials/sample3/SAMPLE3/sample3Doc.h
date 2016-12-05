// sample3Doc.h : interface of the CSample3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMPLE3DOC_H__306F9EA1_7593_11D1_9AFF_004005341B72__INCLUDED_)
#define AFX_SAMPLE3DOC_H__306F9EA1_7593_11D1_9AFF_004005341B72__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSample3Doc : public CDocument
{
protected: // create from serialization only
	CSample3Doc();
	DECLARE_DYNCREATE(CSample3Doc)

// Attributes
public:
	vrBrowser *browser;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSample3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSample3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSample3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLE3DOC_H__306F9EA1_7593_11D1_9AFF_004005341B72__INCLUDED_)
