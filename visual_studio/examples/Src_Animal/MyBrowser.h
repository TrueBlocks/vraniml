#ifndef _MYBROWSER
#define _MYBROWSER

#define MOVEMODE_WALK    0
#define MOVEMODE_SLIDE   1
#define MOVEMODE_EXAMINE   2
#define MOVEMODE_ROTATEX 3
#define MOVEMODE_ROTATEY 4
#define MOVEMODE_ROTATEZ 5
#define MOVEMODE_NONE    6

class vrMyOGLTraverser : public vrOGLTraverser
{
public:
	vrMyOGLTraverser(vrBrowser *b, void *h) : vrOGLTraverser(b,h) {};
	vrMyOGLTraverser(const vrMyOGLTraverser& t) : vrOGLTraverser(t) {};
	virtual ~vrMyOGLTraverser()
		{
		};
	vrMyOGLTraverser& operator=(const vrMyOGLTraverser& t)
		{
			vrOGLTraverser::operator=(t);
			return *this;
		}
	virtual void PreTraverse(void);
};

class vrWindowsConsole : public vrConsole
{
public:
	HWND hWnd;
	vrWindowsConsole(HWND wnd=NULL) { hWnd = wnd; }
	void Error(const SFString& msg)
		{
 			MessageBox(hWnd, (const char *)msg, "Parse Error", MB_OK);
		}
};

class vrMyBrowser : public vrBrowser
{
	int  navMode;

public:
	HWND m_hWnd;
	vrMyBrowser(void *hWnd);
	virtual ~vrMyBrowser()
		{};
	SFBool ProcessUserMessage	(const vrUserMessage& msg);

	BOOL updateMatrix(void);

	void HandleMouse(int mode, const SFVec3f& pt);

	void SetNavigationMode(int mode);
	int GetNavigationMode(void) const;
};

#endif