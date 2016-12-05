// sample3View.cpp : implementation of the CSample3View class
//

#include "stdafx.h"
#include "sample3.h"

#include "sample3Doc.h"
#include "sample3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSample3View

IMPLEMENT_DYNCREATE(CSample3View, CView)

BEGIN_MESSAGE_MAP(CSample3View, CView)
	//{{AFX_MSG_MAP(CSample3View)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSample3View construction/destruction

CSample3View::CSample3View()
{
	// TODO: add construction code here

}

CSample3View::~CSample3View()
{
}

BOOL CSample3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSample3View drawing

void CSample3View::OnDraw(CDC* pDC)
{
	CSample3Doc *pDoc = (CSample3Doc *)GetDocument();
	ASSERT(pDoc);

	// If the browser exists...
	if (pDoc->browser)
	   // ...draw it
	   pDoc->browser->Traverse();
}

/////////////////////////////////////////////////////////////////////////////
// CSample3View printing

BOOL CSample3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSample3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSample3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSample3View diagnostics

#ifdef _DEBUG
void CSample3View::AssertValid() const
{
	CView::AssertValid();
}

void CSample3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSample3Doc* CSample3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSample3Doc)));
	return (CSample3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSample3View message handlers

void CSample3View::OnInitialUpdate() 
{
	// Call the base class's OnInitialUpdate function
	CView::OnInitialUpdate();

	// Get the document
	CSample3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc->browser)
	{
	   // Create the browser and associate it to this window
	   pDoc->browser = new vrBrowser(m_hWnd);
   
	   // Create a default box
	   vrBox *box = new vrBox;

	   // Create a shape in which we can hold the box
	   vrShape *shape = new vrShape;
   
	   // Now add the box to the shape and the shape to the browser
	   shape->SetGeometry(box);
	   pDoc->browser->AddChild(shape);

	   SetTimer(1001, 30, NULL);
	}
}

void CSample3View::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	CSample3Doc *pDoc = (CSample3Doc *)GetDocument();
	ASSERT(pDoc);

	// If the browser exists...
	if (pDoc->browser)
	{
		vrRenderTraverser *rt = (vrRenderTraverser *)pDoc->browser->GetTraverserByType(GETRUNTIME_CLASS(vrRenderTraverser));
		ASSERT(rt && rt->IsKindOf(GETRUNTIME_CLASS(vrRenderTraverser)));
		rt->SetViewport(0,0,cx,cy);
	}
}

void CSample3View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// Get the document
	CSample3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// Draw the scene
	if (pDoc->browser)
		pDoc->browser->Traverse();     
}
