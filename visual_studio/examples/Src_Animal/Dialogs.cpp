#include "stdafx.h"
#include "mainapp.h"

#include "Dialogs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
#undef new
IMPLEMENT_DYNCREATE(CBoxPage, CPropertyPage)

CBoxPage::CBoxPage() : CPropertyPage(CBoxPage::IDD)
{
	//{{AFX_DATA_INIT(CBoxPage)
	//}}AFX_DATA_INIT
	ReadState();
}

CBoxPage::~CBoxPage()
{
}

void CBoxPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoxPage)
	DDX_Text(pDX, IDC_BOXX, m_X);
	DDV_MinMaxFloat(pDX, m_X, 0.1f, 100.f);
	DDX_Text(pDX, IDC_BOXY, m_Y);
	DDV_MinMaxFloat(pDX, m_Y, 0.1f, 100.f);
	DDX_Text(pDX, IDC_BOXZ, m_Z);
	DDV_MinMaxFloat(pDX, m_Z, 0.1f, 100.f);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBoxPage, CPropertyPage)
	//{{AFX_MSG_MAP(CBoxPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBoxPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ReadState();

	UpdateData(FALSE);
	
	return TRUE;
}

void CBoxPage::SaveState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "BoxX", m_X*10000);
	AfxGetApp()->WriteProfileInt("Insert", "BoxY", m_Y*10000);
	AfxGetApp()->WriteProfileInt("Insert", "BoxZ", m_Z*10000);
}

void CBoxPage::ResetState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "BoxX", 20000);
	AfxGetApp()->WriteProfileInt("Insert", "BoxY", 20000);
	AfxGetApp()->WriteProfileInt("Insert", "BoxZ", 20000);
	ReadState();
}

void CBoxPage::ReadState() 
{
	m_X = AfxGetApp()->GetProfileInt("Insert", "BoxX", 20000) / 10000.;
	m_Y = AfxGetApp()->GetProfileInt("Insert", "BoxY", 20000) / 10000.;
	m_Z = AfxGetApp()->GetProfileInt("Insert", "BoxZ", 20000) / 10000.;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CSpherePage, CPropertyPage)

CSpherePage::CSpherePage() : CPropertyPage(CSpherePage::IDD)
{
	//{{AFX_DATA_INIT(CSpherePage)
	//}}AFX_DATA_INIT
	ReadState();
}

CSpherePage::~CSpherePage()
{
}

void CSpherePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpherePage)
	DDX_Text(pDX, IDC_SPHERERAD, m_Radius);
	DDV_MinMaxFloat(pDX, m_Radius, 0.1f, 100.f);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpherePage, CPropertyPage)
	//{{AFX_MSG_MAP(CSpherePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSpherePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ReadState();

	UpdateData(FALSE);

	return TRUE;
}

void CSpherePage::SaveState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "SphereRadius", m_Radius*10000);
}

void CSpherePage::ResetState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "SphereRadius", 20000);
	ReadState();
}

void CSpherePage::ReadState() 
{
	m_Radius = AfxGetApp()->GetProfileInt("Insert", "SphereRadius", 20000) / 10000.;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CElevationGridPage, CPropertyPage)

CElevationGridPage::CElevationGridPage() : CPropertyPage(CElevationGridPage::IDD)
{
	//{{AFX_DATA_INIT(CElevationGridPage)
	//}}AFX_DATA_INIT
	ReadState();
}

CElevationGridPage::~CElevationGridPage()
{
}

void CElevationGridPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElevationGridPage)
	DDX_Control(pDX, IDC_HEIGHTFUNC, m_Func);
	DDX_Check(pDX, IDC_COLORS, m_Colors);
	DDX_Text(pDX, IDC_XDIM, m_XDim);
	DDX_Text(pDX, IDC_XSPACE, m_XSpace);
	DDX_Text(pDX, IDC_ZDIM, m_ZDim);
	DDX_Text(pDX, IDC_ZSPACE, m_ZSpace);
	//}}AFX_DATA_MAP
	if (IsWindow(m_Func.m_hWnd))
		m_FuncI=m_Func.GetCurSel();
}

BEGIN_MESSAGE_MAP(CElevationGridPage, CPropertyPage)
	//{{AFX_MSG_MAP(CElevationGridPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CElevationGridPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ReadState();
	m_Func.SetCurSel(m_FuncI);

	UpdateData(FALSE);
	
	return TRUE;
}

void CElevationGridPage::SaveState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "ElevFunc",   m_FuncI);
	AfxGetApp()->WriteProfileInt("Insert", "ElevColors", m_Colors);
	AfxGetApp()->WriteProfileInt("Insert", "ElevXDim",   m_XDim);
	AfxGetApp()->WriteProfileInt("Insert", "ElevXSpace", m_XSpace*10000);
	AfxGetApp()->WriteProfileInt("Insert", "ElevZDim",   m_ZDim);
	AfxGetApp()->WriteProfileInt("Insert", "ElevZSpace", m_ZSpace*10000);
}

void CElevationGridPage::ResetState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "ElevFunc",   1);
	AfxGetApp()->WriteProfileInt("Insert", "ElevColors", TRUE);
	AfxGetApp()->WriteProfileInt("Insert", "ElevXDim",   30);
	AfxGetApp()->WriteProfileInt("Insert", "ElevXSpace", 2000);
	AfxGetApp()->WriteProfileInt("Insert", "ElevZDim",   30);
	AfxGetApp()->WriteProfileInt("Insert", "ElevZSpace", 2000);
	ReadState();
}

void CElevationGridPage::ReadState() 
{
	m_FuncI  = AfxGetApp()->GetProfileInt("Insert", "ElevFunc", 1);
	m_Colors = AfxGetApp()->GetProfileInt("Insert", "ElevColors", TRUE);
	m_XDim   = AfxGetApp()->GetProfileInt("Insert", "ElevXDim", 30);
	m_XSpace = AfxGetApp()->GetProfileInt("Insert", "ElevXSpace", 2000) / 10000.;
	m_ZDim   = AfxGetApp()->GetProfileInt("Insert", "ElevZDim", 30);
	m_ZSpace = AfxGetApp()->GetProfileInt("Insert", "ElevZSpace", 2000) / 10000.;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CCylinderPage, CPropertyPage)

CCylinderPage::CCylinderPage() : CPropertyPage(CCylinderPage::IDD)
{
	//{{AFX_DATA_INIT(CCylinderPage)
	//}}AFX_DATA_INIT
	ReadState();
}

CCylinderPage::~CCylinderPage()
{
}

void CCylinderPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCylinderPage)
	DDX_Text(pDX, IDC_CONEHEIGHT, m_Height);
	DDX_Text(pDX, IDC_CONERAD, m_Radius);
	DDX_Check(pDX, IDC_CONESHOWBOTTOM, m_Bottom);
	DDX_Check(pDX, IDC_CONESHOWSIDES, m_Side);
	DDX_Check(pDX, IDC_CONESHOWTOP, m_Top);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCylinderPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCylinderPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CCylinderPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ReadState();

	UpdateData(FALSE);

	return TRUE;
}

void CCylinderPage::SaveState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "CylinderHeight", m_Height*10000);
	AfxGetApp()->WriteProfileInt("Insert", "CylinderRadius", m_Radius*10000);
	AfxGetApp()->WriteProfileInt("Insert", "CylinderBottom", m_Bottom);
	AfxGetApp()->WriteProfileInt("Insert", "CylinderTop",    m_Top);
	AfxGetApp()->WriteProfileInt("Insert", "CylinderSides",  m_Side);
}

void CCylinderPage::ResetState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "CylinderHeight", 20000);
	AfxGetApp()->WriteProfileInt("Insert", "CylinderRadius", 10000);
	AfxGetApp()->WriteProfileInt("Insert", "CylinderBottom", TRUE);
	AfxGetApp()->WriteProfileInt("Insert", "CylinderTop",    TRUE);
	AfxGetApp()->WriteProfileInt("Insert", "CylinderSides",  TRUE);
	ReadState();
}

void CCylinderPage::ReadState() 
{
	m_Height = AfxGetApp()->GetProfileInt("Insert", "CylinderHeight", 20000) / 10000.;
	m_Radius = AfxGetApp()->GetProfileInt("Insert", "CylinderRadius", 10000) / 10000.;
	m_Bottom = AfxGetApp()->GetProfileInt("Insert", "CylinderBottom", TRUE);
	m_Top    = AfxGetApp()->GetProfileInt("Insert", "CylinderTop", TRUE);
	m_Side   = AfxGetApp()->GetProfileInt("Insert", "CylinderSides",  TRUE);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CConePage, CPropertyPage)

CConePage::CConePage() : CPropertyPage(CConePage::IDD)
{
	//{{AFX_DATA_INIT(CConePage)
	//}}AFX_DATA_INIT
	ReadState();
}

CConePage::~CConePage()
{
}

void CConePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConePage)
	DDX_Text(pDX, IDC_CONEHEIGHT, m_Height);
	DDX_Text(pDX, IDC_CONERAD, m_Radius);
	DDX_Check(pDX, IDC_CONESHOWBOTTOM, m_Bottom);
	DDX_Check(pDX, IDC_CONESHOWSIDES, m_Sides);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConePage, CPropertyPage)
	//{{AFX_MSG_MAP(CConePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CConePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ReadState();

	UpdateData(FALSE);

	return TRUE;
}

void CConePage::SaveState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "ConeHeight", 20000);
	AfxGetApp()->WriteProfileInt("Insert", "ConeRadius", 10000);
	AfxGetApp()->WriteProfileInt("Insert", "ConeBottom", TRUE);
	AfxGetApp()->WriteProfileInt("Insert", "ConeSides",  TRUE);
}

void CConePage::ResetState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "ConeHeight", m_Height*10000);
	AfxGetApp()->WriteProfileInt("Insert", "ConeRadius", m_Radius*10000);
	AfxGetApp()->WriteProfileInt("Insert", "ConeBottom", m_Bottom);
	AfxGetApp()->WriteProfileInt("Insert", "ConeSides",  m_Sides);
	ReadState();
}

void CConePage::ReadState() 
{
	m_Height = AfxGetApp()->GetProfileInt("Insert", "ConeHeight", 20000) / 10000.;
	m_Radius = AfxGetApp()->GetProfileInt("Insert", "ConeRadius", 10000) / 10000.;
	m_Bottom = AfxGetApp()->GetProfileInt("Insert", "ConeBottom", TRUE);
	m_Sides  = AfxGetApp()->GetProfileInt("Insert", "ConeSides",  TRUE);
}

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CTexturePage, CPropertyPage)

CTexturePage::CTexturePage() : CPropertyPage(CTexturePage::IDD)
{
	//{{AFX_DATA_INIT(CTexturePage)
	//}}AFX_DATA_INIT
	ReadState();
}

CTexturePage::~CTexturePage()
{
}

void CTexturePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTexturePage)
	DDX_Control(pDX, IDC_CHECKED, m_CheckedBtn);
	DDX_Control(pDX, IDC_CIRCLE, m_CircleBtn);
	DDX_Control(pDX, IDC_CROSSES, m_CrossesBtn);
	DDX_Control(pDX, IDC_NONE, m_NoneBtn);
	DDX_Control(pDX, IDC_RAMP, m_RampBtn);
	DDX_Control(pDX, IDC_MANDRILL, m_MandrillBtn);
	DDX_Control(pDX, IDC_STOPCOLOR, m_StopColorBtn);
	DDX_Control(pDX, IDC_STARTCOLOR, m_StartColorBtn);
	DDX_Check(pDX, IDC_MODULATES, m_Modulate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTexturePage, CPropertyPage)
	//{{AFX_MSG_MAP(CTexturePage)
	ON_BN_CLICKED(IDC_CHECKED, OnChecked)
	ON_BN_CLICKED(IDC_CIRCLE, OnCircle)
	ON_BN_CLICKED(IDC_CROSSES, OnCrosses)
	ON_BN_CLICKED(IDC_NONE, OnNone)
	ON_BN_CLICKED(IDC_RAMP, OnRamp)
	ON_BN_CLICKED(IDC_STARTCOLOR, OnStartcolor)
	ON_BN_CLICKED(IDC_STOPCOLOR, OnStopcolor)
	ON_BN_CLICKED(IDC_MANDRILL, OnMandrill)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CTexturePage::OnChecked() 
{
	m_Which = 1;	
}

void CTexturePage::OnCircle() 
{
	m_Which = 2;	
}

void CTexturePage::OnCrosses() 
{
	m_Which = 3;	
}

void CTexturePage::OnNone() 
{
	m_Which = 0;
}

void CTexturePage::OnRamp() 
{
	m_Which = 4;
}

void CTexturePage::OnMandrill() 
{
	m_Which = 5;
}

BOOL CTexturePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ReadState();

	m_CheckedBtn.SetCheck(FALSE);
	m_CheckedBtn.SetCheck(FALSE);
	m_CircleBtn.SetCheck(FALSE);
	m_CrossesBtn.SetCheck(FALSE);
	m_RampBtn.SetCheck(FALSE);
	m_MandrillBtn.SetCheck(FALSE);

	switch (m_Which)
	{
	case 0:
		m_NoneBtn.SetCheck(TRUE); break;
	case 1:
		m_CheckedBtn.SetCheck(TRUE); break;
	case 2:
		m_CircleBtn.SetCheck(TRUE); break;
	case 3:
		m_CrossesBtn.SetCheck(TRUE); break;
	case 4:
		m_RampBtn.SetCheck(TRUE); break;
	case 5:
		m_MandrillBtn.SetCheck(TRUE); break;
	default:
		ASSERT(0);
	}

	UpdateData(FALSE);
	
	return TRUE;
}

void CTexturePage::SaveState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "TextureWhich",      m_Which);
	AfxGetApp()->WriteProfileInt("Insert", "TextureStartColor", m_StartColorBtn.m_Color);
	AfxGetApp()->WriteProfileInt("Insert", "TextureStopColor",  m_StopColorBtn.m_Color);
	AfxGetApp()->WriteProfileInt("Insert", "TextureModulate",   m_Modulate);
}

void CTexturePage::ResetState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "TextureWhich",      0);
	AfxGetApp()->WriteProfileInt("Insert", "TextureStartColor", DEFAULT_Color1);
	AfxGetApp()->WriteProfileInt("Insert", "TextureStopColor",  DEFAULT_Color2);
	AfxGetApp()->WriteProfileInt("Insert", "TextureModulate",   FALSE);
	ReadState();
}

void CTexturePage::ReadState() 
{
	m_Which                 = AfxGetApp()->GetProfileInt("Insert", "TextureWhich", 0);
	m_StartColorBtn.m_Color = AfxGetApp()->GetProfileInt("Insert", "TextureStartColor", DEFAULT_Color1);
	m_StopColorBtn.m_Color  = AfxGetApp()->GetProfileInt("Insert", "TextureStopColor", DEFAULT_Color2);
	m_Modulate              = AfxGetApp()->GetProfileInt("Insert", "TextureModulate", FALSE);
}

void CTexturePage::OnStartcolor() 
{
	m_StartColorBtn.m_Color = GetColor(m_StartColorBtn.m_Color);
	Invalidate(NULL);
	UpdateWindow();
}

void CTexturePage::OnStopcolor() 
{
	m_StopColorBtn.m_Color = GetColor(m_StopColorBtn.m_Color);
	Invalidate(NULL);
	UpdateWindow();
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CMaterialPage, CPropertyPage)

CMaterialPage::CMaterialPage() : CPropertyPage(CMaterialPage::IDD)
{
	//{{AFX_DATA_INIT(CMaterialPage)
	m_Native = FALSE;
	//}}AFX_DATA_INIT
	ReadState();
}

CMaterialPage::~CMaterialPage()
{
}

void CMaterialPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMaterialPage)
	DDX_Control(pDX, IDC_SPEC, m_SpecBtn);
	DDX_Control(pDX, IDC_EMISSIVE, m_EmissiveBtn);
	DDX_Control(pDX, IDC_DIFFUSE, m_DiffuseBtn);
	DDX_Text(pDX, IDC_AMBIENT, m_Ambient);
	DDV_MinMaxFloat(pDX, m_Ambient, 0.f, 1.f);
	DDX_Text(pDX, IDC_SHININESS, m_Shininess);
	DDV_MinMaxFloat(pDX, m_Shininess, 0.f, 1.f);
	DDX_Text(pDX, IDC_TRANSPARENT, m_Transparent);
	DDV_MinMaxFloat(pDX, m_Transparent, 0.f, 1.f);
	DDX_Check(pDX, IDC_NONE, m_None);
	DDX_Check(pDX, IDC_NATIVE, m_Native);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMaterialPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMaterialPage)
	ON_BN_CLICKED(IDC_DIFFUSE, OnDiffuse)
	ON_BN_CLICKED(IDC_EMISSIVE, OnEmissive)
	ON_BN_CLICKED(IDC_SPEC, OnSpec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMaterialPage::OnDiffuse() 
{
	m_DiffuseBtn.m_Color = GetColor(m_DiffuseBtn.m_Color);
	Invalidate(NULL);
	UpdateWindow();
}

void CMaterialPage::OnEmissive() 
{
	m_EmissiveBtn.m_Color = GetColor(m_EmissiveBtn.m_Color);
	Invalidate(NULL);
	UpdateWindow();
}

void CMaterialPage::OnSpec() 
{
	m_SpecBtn.m_Color = GetColor(m_SpecBtn.m_Color);
	Invalidate(NULL);
	UpdateWindow();
}

BOOL CMaterialPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	ReadState();

	UpdateData(FALSE);

	return TRUE;
}

void CMaterialPage::SaveState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "MaterialSpec", m_SpecBtn.m_Color);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialEmissive", m_EmissiveBtn.m_Color);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialDiffuse", m_DiffuseBtn.m_Color);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialAmbient", m_Ambient*10000);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialTransparent", m_Transparent*10000);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialShininess", m_Shininess*10000);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialNone", m_None);
	AfxGetApp()->WriteProfileInt("Insert", "Native", m_Native);
}

void CMaterialPage::ResetState() 
{
	AfxGetApp()->WriteProfileInt("Insert", "MaterialSpec", DEFAULT_Specular);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialEmissive", MAKERGB(0,0,0));
	AfxGetApp()->WriteProfileInt("Insert", "MaterialDiffuse", DEFAULT_Diffuse);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialAmbient", 2000);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialTransparent", 0);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialShininess", 3000);
	AfxGetApp()->WriteProfileInt("Insert", "MaterialNone", FALSE);
	AfxGetApp()->WriteProfileInt("Insert", "Native", TRUE);
	ReadState();
}

void CMaterialPage::ReadState() 
{
	m_SpecBtn.m_Color     = AfxGetApp()->GetProfileInt("Insert", "MaterialSpec", DEFAULT_Specular);
	m_EmissiveBtn.m_Color = AfxGetApp()->GetProfileInt("Insert", "MaterialEmissive", MAKERGB(0,0,0));
	m_DiffuseBtn.m_Color  = AfxGetApp()->GetProfileInt("Insert", "MaterialDiffuse", DEFAULT_Diffuse);
	m_Ambient             = AfxGetApp()->GetProfileInt("Insert", "MaterialAmbient", 2000) / 10000.;
	m_Transparent         = AfxGetApp()->GetProfileInt("Insert", "MaterialTransparent", 0) / 10000.;
	m_Shininess           = AfxGetApp()->GetProfileInt("Insert", "MaterialShinines", 3000) / 10000.;
	m_None                = AfxGetApp()->GetProfileInt("Insert", "MaterialNone", FALSE);
	m_Native              = AfxGetApp()->GetProfileInt("Insert", "Native", TRUE);
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
CColorButton::CColorButton(void)
{
}

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
  CRect rect = lpDIS->rcItem;
  //long id    = lpDIS->itemID;
	UINT state = lpDIS->itemState;
 
	if (state & ODS_DISABLED)
	{
		CClientDC dc(this);

		CBrush brush, *oldBrush;
		brush.CreateSolidBrush(MAKERGB(191, 191, 191));
		oldBrush = dc.SelectObject(&brush);

		dc.Rectangle(rect);

		dc.SelectObject(oldBrush);
		brush.DeleteObject();

	} else if (state & ODS_SELECTED || state & ODS_FOCUS)
	{
		CClientDC dc(this);

		CBrush brush, *oldBrush;
		brush.CreateSolidBrush(MAKERGB(255, 212, 0));
		oldBrush = dc.SelectObject(&brush);

		dc.Rectangle(rect);

		dc.SelectObject(oldBrush);
		brush.DeleteObject();

		brush.CreateSolidBrush(m_Color);
		oldBrush = dc.SelectObject(&brush);

		rect.InflateRect(-3, -3);
		dc.Rectangle(rect);

		dc.SelectObject(oldBrush);
		brush.DeleteObject();

	} else
	{
		CClientDC dc(this);

		CBrush brush, *oldBrush;
		brush.CreateSolidBrush(m_Color);
		oldBrush = dc.SelectObject(&brush);

		dc.Rectangle(rect);

		dc.SelectObject(oldBrush);
		brush.DeleteObject();
	}
}

