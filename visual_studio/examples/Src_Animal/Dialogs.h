#ifndef __DIALOGS_H
#define __DIALOGS_H
 
#define MAKERGB(r, g, b)   ((COLORREF)(((b) << 16) | ((g) << 8) | (r)))
#define DEFAULT_Diffuse   MAKERGB(255, 255, 0)
#define DEFAULT_Specular  MAKERGB(255, 255, 255)
#define DEFAULT_Color1    MAKERGB(0, 255, 0)
#define DEFAULT_Color2    MAKERGB(0, 0, 255)
#define DEFAULT_Material  2
#define DEFAULT_Texture   0
#define DEFAULT_Behaviour 0
#define DEFAULT_CycleTime "3.0"

#define MAKERGB(r, g, b)   ((COLORREF)(((b) << 16) | ((g) << 8) | (r)))
inline COLORREF GetColor(COLORREF def)
{
  CColorDialog dlg;
  dlg.m_cc.Flags |= CC_FULLOPEN;

  if (dlg.DoModal() == IDOK)
  {
		return dlg.GetColor();
	}
  return def;
}

class CColorButton : public CBitmapButton
{
public:
	CColorButton();
	COLORREF m_Color;
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
};

/////////////////////////////////////////////////////////////////////////////
class CBoxPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBoxPage)

public:
	CBoxPage();
	~CBoxPage();

	void SaveState(void);
	void ResetState(void);
	void ReadState(void);

	//{{AFX_DATA(CBoxPage)
	enum { IDD = IDD_BOX };
	float	m_X;
	float	m_Y;
	float	m_Z;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CBoxPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CBoxPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
class CElevationGridPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CElevationGridPage)

public:
	CElevationGridPage();
	~CElevationGridPage();

	int m_FuncI;
	
	void SaveState(void);
	void ResetState(void);
	void ReadState(void);

	//{{AFX_DATA(CElevationGridPage)
	enum { IDD = IDD_ELEVATIONGRID };
	CComboBox	m_Func;
	BOOL	m_Colors;
	long	m_XDim;
	float	m_XSpace;
	long	m_ZDim;
	float	m_ZSpace;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CElevationGridPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CElevationGridPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
class CCylinderPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCylinderPage)

public:
	CCylinderPage();
	~CCylinderPage();

	void SaveState(void);
	void ResetState(void);
	void ReadState(void);

	//{{AFX_DATA(CCylinderPage)
	enum { IDD = IDD_CYLINDER };
	float	m_Height;
	float	m_Radius;
	BOOL	m_Bottom;
	BOOL	m_Side;
	BOOL	m_Top;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CCylinderPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CCylinderPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class CConePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CConePage)

public:
	CConePage();
	~CConePage();

	void SaveState(void);
	void ResetState(void);
	void ReadState(void);

	//{{AFX_DATA(CConePage)
	enum { IDD = IDD_CONE };
	float	m_Height;
	float	m_Radius;
	BOOL	m_Bottom;
	BOOL	m_Sides;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CConePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CConePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class CSpherePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSpherePage)

public:
	CSpherePage();
	~CSpherePage();

	void SaveState(void);
	void ResetState(void);
	void ReadState(void);

	//{{AFX_DATA(CSpherePage)
	enum { IDD = IDD_SPHERE };
	float	m_Radius;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CSpherePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CSpherePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class CMaterialPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMaterialPage)

public:
	CMaterialPage();
	~CMaterialPage();

	void SaveState(void);
	void ResetState(void);
	void ReadState(void);

	//{{AFX_DATA(CMaterialPage)
	enum { IDD = IDD_MATERIALS };
	CColorButton	m_SpecBtn;
	CColorButton	m_EmissiveBtn;
	CColorButton	m_DiffuseBtn;
	float	m_Ambient;
	float	m_Shininess;
	float	m_Transparent;
	BOOL	m_None;
	BOOL	m_Native;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CMaterialPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CMaterialPage)
	afx_msg void OnDiffuse();
	afx_msg void OnEmissive();
	afx_msg void OnSpec();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
class CTexturePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CTexturePage)

public:
	CTexturePage();
	~CTexturePage();

	int m_Which;
	
	CColorButton m_StopColorBtn;
	CColorButton m_StartColorBtn;

	void SaveState(void);
	void ResetState(void);
	void ReadState(void);

	//{{AFX_DATA(CTexturePage)
	enum { IDD = IDD_TEXTURE };
	BOOL	  m_Modulate;
	CButton m_CheckedBtn;
	CButton m_CircleBtn;
	CButton m_CrossesBtn;
	CButton m_NoneBtn;
	CButton m_RampBtn;
	CButton m_MandrillBtn;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CTexturePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CTexturePage)
	afx_msg void OnChecked();
	afx_msg void OnCircle();
	afx_msg void OnCrosses();
	afx_msg void OnNone();
	afx_msg void OnRamp();
	virtual BOOL OnInitDialog();
	afx_msg void OnStartcolor();
	afx_msg void OnStopcolor();
	afx_msg void OnMandrill();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
