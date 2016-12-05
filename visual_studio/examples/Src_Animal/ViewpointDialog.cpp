#include "stdafx.h"
#include "mainapp.h"

#include "ViewpointDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CViewpointDialog::CViewpointDialog(CWnd* pParent) : CDialog(CViewpointDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewpointDialog)
	m_List = _T("");
	//}}AFX_DATA_INIT
}

void CViewpointDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewpointDialog)
	DDX_Control(pDX, IDC_VIEWPOINTLIST, m_ListCtrl);
	DDX_LBString(pDX, IDC_VIEWPOINTLIST, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CViewpointDialog, CDialog)
	//{{AFX_MSG_MAP(CViewpointDialog)
	ON_LBN_DBLCLK(IDC_VIEWPOINTLIST, OnDoubleClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CViewpointDialog::OnDoubleClick() 
{
	UpdateData(TRUE);

	if (m_List.Find("**") == -1)
	{
		EndDialog(m_ListCtrl.GetCurSel()+100);
		return;
	}
	EndDialog(IDCANCEL);
}

int cnt=0;
SFBool LoadViewpointNames(vrNode *node, void *data)
{
	CListBox *lb = (CListBox *)data;
	if (node->IsKindOf(GETRUNTIME_CLASS(vrViewpoint)))
	{
		vrViewpoint *vp = (vrViewpoint *)node;
		CString s;
		if (vp->GetDescription())
		{
			s = vp->GetDescription();
		} else
		{
			CString str;
			str.Format("Unnamed %d", ++cnt);
			s = str;
		}
		if (vp->IsBound())
			s += "**";
		lb->AddString(s);
	}
	return TRUE;
}

BOOL CViewpointDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(browser);

	cnt=0;
	browser->ForEvery(LoadViewpointNames, &m_ListCtrl);

	UpdateData(FALSE);

	return TRUE;
}

//---------------------------------------------------------------------------
SFBool Accumulate(vrNode *node, void *data)
{
	if (node->IsKindOf(GETRUNTIME_CLASS(vrViewpoint)))
	{
		MFNode *array = (MFNode *)data;
		array->AddValue(node);
	}
	return TRUE;
}

SFInt32 CountViewpoints(vrBrowser *b)
{
	if (!b) return 0;

	MFNode array;
	b->ForEvery(Accumulate, &array);
	return array.GetCount();
}

void BindViewpoint(vrBrowser *b, int sel)
{
	if (b)
	{
		MFNode array;
		b->ForEvery(Accumulate, &array);

		vrViewpoint *curr = b->GetViewpoint();
		ASSERT(curr);

		if (sel < 0)
		{
			// Find the current vp...
			for (int i=0;i<array.GetCount();i++)
			{
				if (curr == array[i]) //.GetValue(i))
					break;
			}
			
			// increment or decrement
			if (sel == -1)
				sel = ((i == array.GetCount()-1) ?  0 : i+1);
			else if (sel == -2)
				sel = ((i == 0) ? array.GetCount()-1 : i-1);
		}

		ASSERT(sel>=0);
		vrViewpoint *vp = (vrViewpoint*)array[sel]; //.GetValue(sel);
		ASSERT(vp->IsKindOf(GETRUNTIME_CLASS(vrViewpoint)));

		b->ChangeViewpoint(vp);
	}
	return;
}

