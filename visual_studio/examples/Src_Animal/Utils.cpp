#include "Stdafx.h"

#ifdef _DEBUG
//#include "MainFrm.h"
#define DEBUGBLT(xxx,ddc) \
	{ \
		dDC.BitBlt((xxx), (size.y/2), size.x, size.y, (ddc), 0, 0, SRCCOPY); \
	}
//	CView *theView = GetFrame()->GetActiveView();
//	CClientDC dDC(theView);
#else
#define DEBUGBLT(x,ddc)
#endif
#undef DEBUGBLT
#define DEBUGBLT(x,ddc)

void DrawTransparentBitmap(CDC *dc, CBitmap *bitmap, CPoint tl, CPoint offset, CPoint sourceTL)
{
	if (!dc)
		return;
	if (!bitmap)
		return;

	// Create some DC's
	CDC tempDC;
	tempDC.CreateCompatibleDC(dc);

	CDC backDC;
	backDC.CreateCompatibleDC(dc);

	CDC objectDC;
	objectDC.CreateCompatibleDC(dc);

	CDC memDC;
	memDC.CreateCompatibleDC(dc);

	CDC saveDC;
	saveDC.CreateCompatibleDC(dc);

	tempDC.SelectObject(bitmap);
	BITMAP bm;
	bitmap->GetBitmap(&bm);
	CPoint size(bm.bmWidth, bm.bmHeight);
	tempDC.DPtoLP(&size, 1);

	// Create matching bitmaps
	CBitmap andBackBmp;
	andBackBmp.CreateBitmap(size.x, size.y, 1, 1, NULL);

	CBitmap andObjectBmp;
	andObjectBmp.CreateBitmap(size.x, size.y, 1, 1, NULL);

	CBitmap andMemBmp;
	andMemBmp.CreateCompatibleBitmap(dc, size.x, size.y);
	
	CBitmap saveBmp;
	saveBmp.CreateCompatibleBitmap(dc, size.x, size.y);

	// Each DC must select a bitmap object to store pixel data.
#pragma warning(disable:4189)
	CBitmap *oldBack   = backDC.SelectObject(&andBackBmp);
	CBitmap *oldObject = objectDC.SelectObject(&andObjectBmp);
	CBitmap *oldMem    = memDC.SelectObject(&andMemBmp);
	CBitmap *oldSave   = saveDC.SelectObject(&saveBmp);

	// Set proper mapping mode.
	tempDC.SetMapMode(dc->GetMapMode());

	// Save the bitmap sent here, because it will be overwritten.
	saveDC.BitBlt(0, 0, size.x, size.y, &tempDC, 0, 0, SRCCOPY);
DEBUGBLT(0*size.x, &saveDC);

#define RRGGBB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	COLORREF c = RRGGBB(0,255,255);
	COLORREF cColor = tempDC.SetBkColor(c);

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	objectDC.BitBlt(0, 0, size.x, size.y, &tempDC, sourceTL.x, sourceTL.y, SRCCOPY);
DEBUGBLT(1*size.x, &objectDC);

	// Set the background color of the source DC back to the original
	// color.
	tempDC.SetBkColor(cColor);

	// Create the inverse of the object mask.
	backDC.BitBlt(0, 0, size.x, size.y, &objectDC, 0, 0, NOTSRCCOPY);
DEBUGBLT(2*size.x, &backDC);

	// Copy the background of the main DC to the destination.
	memDC.BitBlt(0, 0, size.x, size.y, dc, 0, 0, SRCCOPY);
DEBUGBLT(3*size.x, &memDC);

	// Mask out the places where the bitmap will be placed.
	memDC.BitBlt(0, 0, size.x, size.y, &objectDC, 0, 0, SRCAND);
DEBUGBLT(4*size.x, &memDC);

	// Mask out the transparent colored pixels on the bitmap.
	tempDC.BitBlt(sourceTL.x, sourceTL.y, size.x, size.y, &backDC, 0, 0, SRCAND);
DEBUGBLT(5*size.x, &tempDC);

	// XOR the bitmap with the background on the destination DC.
	memDC.BitBlt(0, 0, size.x, size.y, &tempDC, sourceTL.x, sourceTL.y, SRCPAINT);
DEBUGBLT(6*size.x, &memDC);

	// Copy the destination to the screen.
	dc->BitBlt(tl.x+offset.x, tl.y+offset.y, size.x/2, size.y, &memDC, 0, 0, SRCCOPY);
DEBUGBLT(7*size.x, dc);

	// Place the original bitmap back into the bitmap sent here.
	tempDC.BitBlt(0, 0, size.x, size.y, &saveDC, 0, 0, SRCCOPY);
DEBUGBLT(8*size.x, &tempDC);

	// all DC's and BM are released automatically
}

CString GetProgramDir(void)
{
	CString commandLine(GetCommandLine());
	
	commandLine.MakeLower();

	//ASSERT(Contains(commandLine, ".exe"));

	if (commandLine[0] == '\"')
	{
		commandLine = commandLine.Mid(1);
	}

	commandLine = commandLine.Left(commandLine.Find(".exe"));
	
	int f = commandLine.ReverseFind('\\');
	if (f != -1)
	{
		commandLine = commandLine.Left(f);
	}
	commandLine.MakeLower();
	
	return commandLine;
}

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CFileCenteredDlg::CFileCenteredDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt,
		                                        LPCTSTR lpszFileName, DWORD dwFlags,
		                                        LPCTSTR lpszFilter, CWnd* pParentWnd)
: CFileDialog(bOpenFileDialog, lpszDefExt,lpszFileName,dwFlags,lpszFilter ,pParentWnd)
{
}              

BEGIN_MESSAGE_MAP(CFileCenteredDlg, CFileDialog)
	//{{AFX_MSG_MAP(CFileCenteredDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CFileCenteredDlg::OnInitDialog()
{
  BOOL tmp = CFileDialog::OnInitDialog();
  CenterWindow(AfxGetMainWnd());
  return tmp;
}

#undef new
IMPLEMENT_SERIAL(CFilename, CObject, 1001);

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFilename::operator CString() const
{
	return CString(m_Filename);
}

CFileDialogInfo::~CFileDialogInfo()
{
}

BOOL GetFileName(CFileDialogInfo *data, CFilename &filename)
{
  CString fn = filename;

  long flags = (OFN_HIDEREADONLY | OFN_NOCHANGEDIR);
  if (data->open)
  {
    flags |= OFN_FILEMUSTEXIST;
    flags |= OFN_PATHMUSTEXIST;
  } else
  {
    flags |= OFN_OVERWRITEPROMPT;
  }

  if (filename.GetTitle()=="")
  {
			fn = CString("*.") + data->ext;
  }

  CFileCenteredDlg dlg(data->open, data->ext, CString(fn), flags, data->mask);

  int ret;
  {
    CDirectoryPreserver d(data->dir);
		//dlg.SetWindowText(data->wndTitle);
		ret = dlg.DoModal();
  }

  if (ret==IDOK)
  {
    filename = dlg.GetPathName();
    return TRUE;
  }
  return FALSE;
}

//----------------------------------------------------------------------
CFilename::CFilename()
{
}

CFilename::CFilename(const CFilename& fn)
{
	m_Filename = fn.m_Filename;
}

CFilename& CFilename::operator=(const CFilename& fn)
{
	m_Filename = fn.m_Filename;
	ExpandPath();
	return *this;
}

//----------------------------------------------------------------------
CFilename::CFilename(const CString& str)
{ 
	m_Filename = str;
	ExpandPath();
};

CFilename& CFilename::operator=(const CString& str)
{
	m_Filename = str;
	ExpandPath();
	return *this;
}

//----------------------------------------------------------------------
void CFilename::Serialize(CArchive& archive)
{
  CObject::Serialize(archive);

	if (archive.IsStoring())
	{
		archive << m_Filename;
	} else
	{
		archive >> m_Filename;
	}
}

BOOL CFilename::operator==(const CFilename& fn) const
{
	return (m_Filename == fn.m_Filename);
}

BOOL CFilename::operator!=(const CFilename& fn) const
{
	return !operator==(fn);
}

//----------------------------------------------------------------------
CString CFilename::GetPath(void) const
{
	CString name = GetName();
	int i = m_Filename.Find(name);
	ASSERT(i!=-1);
	CString str = m_Filename;
	ASSERT(i!=0);
	str = str.Left(i);
	return str;
}

CString CFilename::GetTitle(void) const
{
	CString str('.', _MAX_PATH);
	LPTSTR buf = str.GetBuffer(_MAX_PATH);
	AfxGetFileName(m_Filename, buf, _MAX_PATH);
	str.ReleaseBuffer();

	int i = str.ReverseFind('.');
  if (i!=-1)
  {
    str = str.Left(i);
  }
  return str;
}

CString CFilename::GetName(void) const
{
	CString str('.', _MAX_PATH);
	LPTSTR buf = str.GetBuffer(_MAX_PATH);
	AfxGetFileName(m_Filename, buf, _MAX_PATH);
	str.ReleaseBuffer();
	return str;
}

CString CFilename::GetType(void) const
{
	CString name = GetName();
	int i = name.ReverseFind('.');
	if (i!=-1)
	{
		ASSERT(i!=0);
		i+=1;
		return name.Right(name.GetLength()-i);
	} else
	{
		return "";
	}
}

void Replace(CString& Modify, LPCTSTR What, LPCTSTR With)
{
	int i = Modify.Find(What);
	
	if (i >= 0) {
		Modify = Modify.Left(i) + 
		          With + 
		            Modify.Mid(i+lstrlen(What));
	}
}


CString CFilename::Relativize(const CString& wrtPath) const
{
  CString str = m_Filename;

	int i = str.Find(wrtPath);
	if (i!=-1)
	{
		CString rep = (wrtPath.Right(1) == "\\") ? ".\\" : ".";
		Replace(str, wrtPath, rep);
	}
	return str;
}

void CFilename::ExpandPath(void)
{
	CString str = m_Filename;
	if (str != "")
	{
		LPTSTR buf = m_Filename.GetBuffer(_MAX_PATH);
		GetFullPathName(str, _MAX_PATH, buf, NULL);
		m_Filename.ReleaseBuffer();
	}
}

BOOL CFilename::IsDirectory(void) const
{
	if (!Exists()) return FALSE;
	
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = FindFirstFile(m_Filename, &findFileData);
 	ASSERT(!(hFind == (HANDLE)-1));
	BOOL ret = (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
 	FindClose(hFind);
	return ret;
}
