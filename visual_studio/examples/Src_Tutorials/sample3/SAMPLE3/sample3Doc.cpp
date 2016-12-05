// sample3Doc.cpp : implementation of the CSample3Doc class
//

#include "stdafx.h"
#include "sample3.h"

#include "sample3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSample3Doc

IMPLEMENT_DYNCREATE(CSample3Doc, CDocument)

BEGIN_MESSAGE_MAP(CSample3Doc, CDocument)
	//{{AFX_MSG_MAP(CSample3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSample3Doc construction/destruction

CSample3Doc::CSample3Doc()
{
	// TODO: add one-time construction code here
	browser = NULL;
}

CSample3Doc::~CSample3Doc()
{
	if (browser)
		delete browser;
}

BOOL CSample3Doc::OnNewDocument()
{
	// Call the base class's OnNewDocument function
	if (!CDocument::OnNewDocument())
	   return FALSE;

	// Read the file (note: we hardcode the filename here for ease of instruction).
	if (browser)
	   browser->ReadURL("c:/program files/great hill corporation/vraniml/sample browser/logo.wrl");

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSample3Doc serialization

void CSample3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSample3Doc diagnostics

#ifdef _DEBUG
void CSample3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSample3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSample3Doc commands
