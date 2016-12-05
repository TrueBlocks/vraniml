#ifndef __SPLITTER_H
#define __SPLITTER_H

class CSplitter : public CSplitterWnd
{
	BOOL lastCx;

public:
	         CSplitter();
	virtual ~CSplitter();

	DECLARE_DYNCREATE(CSplitter)

private:
	
	//{{AFX_VIRTUAL(CSplitter)
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CSplitter)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif
