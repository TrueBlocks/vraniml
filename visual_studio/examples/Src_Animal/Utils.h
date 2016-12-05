#ifndef __UTILS_H
#define __UTILS_H

extern void DrawTransparentBitmap(CDC *dc, CBitmap *bitmap, CPoint tl, CPoint offset, CPoint sourceTL);
extern CString GetProgramDir(void);

// When this is declared as a temporary variable it will save the
// current directory and when it goes out of scope it will return
// the directory to this saved value.  For use when opening file dialogs.
class CDirectoryPreserver
{
	char curDir[FILENAME_MAX];

public:
	CDirectoryPreserver(const CString& str)
		{
			GetCurrentDirectory(FILENAME_MAX,(LPTSTR)curDir);
			SetCurrentDirectory(str);
		};
	~CDirectoryPreserver(void)
		{
			SetCurrentDirectory(curDir);
		}
};

class CFileCenteredDlg : public CFileDialog
{
public:                            
  CFileCenteredDlg(
          BOOL bOpenFileDialog, 
      		LPCTSTR lpszDefExt = NULL,
		      LPCTSTR lpszFileName = NULL,
      		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		      LPCTSTR lpszFilter = NULL,
      		CWnd* pParentWnd = NULL);

	// Generated message map functions
	//{{AFX_MSG(CFileCenteredDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define DLLInterface 
//------------------------------------------------------------
class DLLInterface CFilename : public CObject
{
	DECLARE_SERIAL(CFilename);
	CString m_Filename;
	
public:
							CFilename				(void);
							CFilename				(const CFilename& fn);
							CFilename				(const CString& str);
	CFilename&	operator=				(const CFilename& fn);
	CFilename&	operator=				(const CString& str);
							operator CString() const;

	BOOL        operator==      (const CFilename& pt) const;
	BOOL        operator!=      (const CFilename& pt) const;

	void				Serialize				(CArchive& archive);

	CString			GetPath					(void) const;
	CString			GetTitle				(void) const;
	CString			GetName					(void) const;
	CString			GetType					(void) const;

	BOOL				Exists					(void) const;
	BOOL				IsDirectory     (void) const;
	CString			Relativize			(const CString& wrtPath) const;

private:
	void				ExpandPath			(void);
};

UINT AFXAPI AfxGetFileTitle(LPCTSTR lpszPathName, LPTSTR lpszTitle, UINT nMax);
UINT AFXAPI AfxGetFileName(LPCTSTR lpszPathName, LPTSTR lpszTitle, UINT nMax);

inline BOOL CFilename::Exists(void) const
{
	CFileStatus fs;
	return (CFile::GetStatus(m_Filename, fs));
}

//------------------------------------------------------------
class DLLInterface CFileDialogInfo
{
public:
  BOOL open;
  CString ext;
  CString mask;
	CString wndTitle;
  CString dir;
  CFileDialogInfo(BOOL o, const CString& e, const CString& m, const CString& wndT, const CString& d)
    {
	    open = o;
      ext = e;
      mask = m;
    	wndTitle = wndT;
      dir = d;
    }
  ~CFileDialogInfo();
};

extern BOOL      DLLInterface GetFileName        (CFileDialogInfo *data, CFilename& filename);
extern CFile*    DLLInterface GetFile            (LPCTSTR lpszFileName, UINT nOpenFlags, CFileException* pError);
#endif