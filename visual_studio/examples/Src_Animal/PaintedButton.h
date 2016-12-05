#ifndef __PAINTEDBUTTON_H
#define __PAINTEDBUTTON_H

#undef NORMAL
#define NORMAL 1
#define ACTIVE 2

#define FIRSTPLACE 1
#define CENTER 2
#define LAST 3
// Used by painted button class to position the buttons on a painted button bar
class CButtonPlacement
{
public:
	int num;
	int msgID;
	int iconID;
	int align;
	CButtonPlacement() { num=-1;}
	CButtonPlacement(int n, int msg, int icon, int a)
		{
			num = n; msgID = msg; iconID = icon; align = a;
		}
	CButtonPlacement(const CButtonPlacement& place)
		{
			num = place.num; msgID = place.msgID; iconID = place.iconID; align = place.align;
		}
	CButtonPlacement& operator=(const CButtonPlacement& place)
		{
			num = place.num; msgID = place.msgID; iconID = place.iconID; align = place.align; return *this;
		}
};

class CPaintedButton : public CBitmapButton
{
private:
	         CPaintedButton() {};

	CBitmap          *m_Icon;
	int               m_IsActive;
	CBitmap          *m_Background;
	CButtonPlacement  m_Placement;
	int               m_Checked;
	int               m_CmdID;

public:
	void SetCheck(int state);

	static void ButtonOff(void);
	static CPaintedButton *m_ActiveButtonPtr;

	         CPaintedButton(CButtonPlacement *bp);
	virtual ~CPaintedButton();

	BOOL Create(CWnd *pParent, UINT msgID, UINT iconID=0);

	DECLARE_DYNCREATE(CPaintedButton)

private:
	void SetIsActive(BOOL isActive);
	
	//{{AFX_VIRTUAL(CPaintedButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CPaintedButton)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	friend class CPaintedDialogBar;

};

typedef CTypedPtrArray<CPtrArray,  CPaintedButton*> CPaintedButtonArray;

#endif
