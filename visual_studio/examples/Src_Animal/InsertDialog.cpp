#include "stdafx.h"

#include "mainapp.h"

#include "InsertDialog.h"
#include "Textures.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CInsertDialog::CInsertDialog(CWnd* pParent)
	: CDialog(CInsertDialog::IDD, pParent)
{
	pDoc=NULL;
	changed=FALSE;
	//{{AFX_DATA_INIT(CInsertDialog)
	//}}AFX_DATA_INIT
}


void CInsertDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertDialog)
	DDX_Control(pDX, IDC_GEOMETRYTYPE, m_GeomType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInsertDialog, CDialog)
	//{{AFX_MSG_MAP(CInsertDialog)
	ON_BN_CLICKED(IDC_INSERTGEOM, OnInsertgeom)
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const SFVec3f inserts[] =
{
	SFVec3f( 0.0,  0.0,  0.0),
	SFVec3f( 0.0,  0.0,  2.5),
	SFVec3f( 0.0,  2.5,  0.0),
	SFVec3f( 0.0,  2.5,  2.5),
	SFVec3f( 2.5,  0.0,  0.0),
	SFVec3f( 2.5,  0.0,  2.5),
	SFVec3f( 2.5,  2.5,  0.0),
	SFVec3f( 2.5,  2.5,  2.5),
	SFVec3f( 0.0,  0.0, -2.5),
	SFVec3f( 0.0, -2.5,  0.0),
	SFVec3f( 0.0, -2.5, -2.5),
	SFVec3f(-2.5,  0.0,  0.0),
	SFVec3f(-2.5,  0.0, -2.5),
	SFVec3f(-2.5, -2.5,  0.0),
	SFVec3f(-2.5, -2.5, -2.5),
};
const int N = sizeof(inserts) / sizeof(SFVec3f);

inline SFColor toColor(COLORREF col)
{
	unsigned char r  = GetRValue(col);
	unsigned char g  = GetGValue(col);
	unsigned char b  = GetBValue(col);
	SFFloat red = (SFFloat)r / (SFFloat)255.0;
	SFFloat green = (SFFloat)g / (SFFloat)255.0;
	SFFloat blue = (SFFloat)b / (SFFloat)255.0;
	return SFColor(red, green, blue);
}

vrAppearance *CInsertDialog::GetAppearance() 
{
	vrAppearance *app = new vrAppearance;

	vrMaterial *mat = NULL;
	
	if (!matPage.m_None)
	{
		mat = new vrMaterial;

		SFColor diffuseColor  = toColor(matPage.m_DiffuseBtn.m_Color);
		mat->SetDiffuseColor(diffuseColor);

		SFColor specularColor = toColor(matPage.m_SpecBtn.m_Color);
		mat->SetSpecularColor(specularColor);

		SFColor emissive = toColor(matPage.m_EmissiveBtn.m_Color);
		mat->SetEmissiveColor(emissive);

		mat->SetShininess(matPage.m_Shininess);
		mat->SetTransparency(matPage.m_Transparent);
		mat->SetAmbientIntensity(matPage.m_Ambient);
	}
	app->SetMaterial(mat);

	SFColor color1 = toColor(texPage.m_StartColorBtn.m_Color);
	SFColor color2 = toColor(texPage.m_StopColorBtn.m_Color);

	vrPixelTexture *tex = NULL;
	switch (texPage.m_Which)
	{
	case 1:
		{
			tex = new vrCheckedTexture(color1, color2);
			app->SetTexture(tex);
		}
		break;
	case 2:
		{
			tex = new vrCircleTexture(color1, color2);
			app->SetTexture(tex);
		}
		break;
	case 3:
		{
			tex = new vrCrossesTexture(color1, color2);
			app->SetTexture(tex);
		}
		break;
	case 4:
		{
			tex = new vrRampTexture(color1, color2);
			app->SetTexture(tex);
		}
		break;
	case 5:
		{
			tex = new vrImageTexture;
			CString file = GetProgramDir() + "\\tests\\textures\\mandrill.jpg";
			((vrImageTexture*)tex)->AddUrl((char *)(LPCTSTR)file);
			app->SetTexture(tex);
		}
		break;
	case 0:
	default:
		app->SetTexture(tex);
		break;
	}
	if (tex && !texPage.m_Modulate)
	{
		mat = NULL;
		app->SetMaterial(mat);
	}

	return app;
}

int m_LastInsert=0;
void CInsertDialog::Insert(vrNode *ob) 
{
	vrTransform *t = new vrTransform;
	t->SetTranslation(inserts[m_LastInsert]);

	if (ob->IsKindOf(GETRUNTIME_CLASS(vrGeometryNode)))
	{
		vrAppearance *app = GetAppearance();
		vrShape *shape = new vrShape;
		shape->SetAppearance(app);

		vrGeometryNode *n = (vrGeometryNode*)ob; 
		n->SetNative(matPage.m_Native);
		shape->SetGeometry(n);
		t->AddChild(shape);
	} else
	{
		t->AddChild(ob);
	}

	pDoc->GetBrowser()->AddChild(t);

	m_LastInsert = ((m_LastInsert + 1) % N);
	AfxGetApp()->WriteProfileInt("Settings", "LastInsert", m_LastInsert);
}

void CInsertDialog::Insert(const CString& fn) 
{
	SFString filename = fn;

	// Note: objects loaded from file are not given appearance or behaviour attributes
	vrTransform *t = new vrTransform;
	t->SetTranslation(inserts[m_LastInsert]);

	pDoc->GetBrowser()->ReadURL(filename, t);
	pDoc->GetBrowser()->AddChild(t);

	m_LastInsert = ((m_LastInsert + 1) % N);
	AfxGetApp()->WriteProfileInt("Settings", "LastInsert", m_LastInsert);

	pDoc->DoUpdateTitle(filename);
}

template<class T>
inline T RandomValue(T a, T b)
{
  T range = (T)fabs(a - b);
  return (rand() / RAND_MAX) * range + ((a < b) ? a : b);
}

void CInsertDialog::OnInsertgeom() 
{
	UpdateData(TRUE);
	
	changed=TRUE;

	ASSERT(pDoc);
	
	int sel = m_GeomType.GetCurSel();
	switch (sel)
	{
	case 0: // Box
		{
			vrBox *box = new vrBox;
			box->SetSize(SFVec3f(boxPage.m_X, boxPage.m_Y, boxPage.m_Z));
			Insert(box);
		}
		break;
	case 1: // Cone
		{
			vrCone *cone = new vrCone;
			cone->SetHeight(conePage.m_Height);
			cone->SetBottomRadius(conePage.m_Radius);
			cone->SetSide(conePage.m_Sides);
			cone->SetBottom(conePage.m_Bottom);
			Insert(cone);
		}
		break;
	case 2: // Cylinder
		{
			vrCylinder *cyl = new vrCylinder;
			cyl->SetHeight(cylinderPage.m_Height);
			cyl->SetRadius(cylinderPage.m_Radius);
			cyl->SetSide(cylinderPage.m_Side);
			cyl->SetBottom(cylinderPage.m_Bottom);
			cyl->SetTop(cylinderPage.m_Top);
			Insert(cyl);
		}
		break;
	case 3: // Sphere
		{
			vrSphere *s = new vrSphere;
			s->SetRadius(spherePage.m_Radius);
			Insert(s);
		}
		break;
	case 4: // Extrusion
		{
			extern vrTransform *MakeLogo(vrAppearance *app, vrBrowser *b);
			Insert(MakeLogo(GetAppearance(), pDoc->GetBrowser()));
		}
		break;
	case 5: // ElevationGrid
		{
			int nX = elevPage.m_XDim;
			int nZ = elevPage.m_ZDim;
			float sX = elevPage.m_XSpace;
			float sZ = elevPage.m_ZSpace;
			vrElevationGrid *grid = new vrElevationGrid;
			grid->SetXDimension(nX);
			grid->SetXSpacing(sX);
			grid->SetZDimension(nZ);
			grid->SetZSpacing(sZ);
			MFFloat heights;
			for (int i=0;i<nZ;i++) //elevPage.m_ZDim;i++)
			{
				for (int j=0;j<nX;j++) //elevPage.m_XDim;j++)
				{
					switch (elevPage.m_FuncI)
					{
					case 0:
						heights.AddValue(1.0);
						break;
					case 1:
						heights.AddValue(sin(i*sZ)-sin(j*sX));
						break;
					default:
					case 2:
						heights.AddValue(RandomValue(-1, 1));
						break;

					}
				}
			}
			grid->SetHeight(heights);
			vrTransform *t = new vrTransform;
			t->SetTranslation(SFVec3f(-(nX*sX)/2.0, 0, -(nZ*sZ)/2));
			vrShape *shape = new vrShape;
			vrGeometryNode *node = grid;
			vrAppearance *app = GetAppearance();
			shape->SetGeometry(node);
			shape->SetAppearance(app);
			t->AddChild(shape);
			Insert(t);
		}
		break;
	case 6: // PointSet
		Insert(GetProgramDir() + "\\Geometry\\PointSet1.wrl");
		break;
	case 7: // IndexedLineSet
		Insert(GetProgramDir() + "\\Geometry\\LineSet1.wrl");
		break;
	case 8: // IndexedFaceSet
		Insert(GetProgramDir() + "\\Geometry\\FaceSet1.wrl");
		break;
	case 9: // seperator --------
		return;
		break;
	case 10: // PointLight
		return;
		break;
	case 11: // DirectionalLight
		return;
		break;
	case 12: // SpotLight
		return;
		break;
	}

	// Close imeadiately upon insertion
	OnCancel();
}

void CInsertDialog::OnCancel() 
{
	UpdateData(TRUE);

	AfxGetApp()->WriteProfileInt("Settings", "GeomType",  m_GeomType.GetCurSel());
	
	if (changed)
		pDoc->UpdateAllViews(NULL);

	CDialog::OnCancel();
}

BOOL CInsertDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_GeomType.SetCurSel(AfxGetApp()->GetProfileInt("Settings", "GeomType", 0));
	
	m_LastInsert = AfxGetApp()->GetProfileInt("Settings", "LastInsert", 0);

	UpdateData(FALSE);
	
	return TRUE;
}

void CInsertDialog::OnProperties() 
{
	UpdateData(TRUE);
	
	int sel = m_GeomType.GetCurSel();
	CPropertySheet sheet("Node Insert Properties");

	switch (sel)
	{
	case 0:
		sheet.AddPage(&boxPage);
		break;
	case 1:
		sheet.AddPage(&conePage);
		break;
	case 2:
		sheet.AddPage(&cylinderPage);
		break;
	case 3:
		sheet.AddPage(&spherePage);
		break;
	case 5:
		sheet.AddPage(&elevPage);
		break;
	}
	sheet.AddPage(&matPage);
	sheet.AddPage(&texPage);
	if (sheet.DoModal()==IDOK)
	{
		switch (sel)
		{
		case 0:
			boxPage.SaveState();
			break;
		case 1:
			conePage.SaveState();
			break;
		case 2:
			cylinderPage.SaveState();
			break;
		case 3:
			spherePage.SaveState();
			break;
		case 5:
			elevPage.SaveState();
			break;
		}
		matPage.SaveState();
		texPage.SaveState();
	}
}
 
void CInsertDialog::OnReset() 
{
	m_GeomType.SetCurSel(0);
	AfxGetApp()->WriteProfileInt("Settings", "GeomType",  m_GeomType.GetCurSel());

	boxPage.ResetState();
	conePage.ResetState();
	cylinderPage.ResetState();
	spherePage.ResetState();
	elevPage.ResetState();
	matPage.ResetState();
	texPage.ResetState();
}
