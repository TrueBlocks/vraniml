#include "stdafx.h"

#include "MyBrowser.h"
#include "MainDoc.h"
#include "MainView.h"

#include "GL\gl.h"

SFBool autoAnimate=FALSE;
SFRotation orientation(0,1,1,10);
BOOL isActive = TRUE;

SFVec3f lastPos, firstPos;
SFVec3f delta(0);
SFVec3f vec;

SFVec3f firstDown, currPt;
SFBool drawRubber = FALSE;
SFBool drawCrossHair = FALSE;
SFVec3f ProjectToSphere(const vrRect2D& viewport, const SFVec3f& mouseLoc, SFFloat sensitivity=1.0)
{
	// vec is a normalized vector centered in the viewport
	vec = SFVec3f((2.0*mouseLoc.x - viewport.Width()) / viewport.Width(), (viewport.Height() - 2.0*mouseLoc.y) / viewport.Height(), 0);;
	vec *= sensitivity;

	// Distance of vec from center of window
	float dist = Length(vec);

  // This projects the point onto the hemi-sphere
	vec.z = ((dist < 1.0) ? cos((M_PI/2.0) * dist) : 0.0);

	vec = Normalize(vec);
	return vec;
}

SFVec3f Project(int navMode, const vrRect2D& viewport, const SFVec3f& mouseLoc)
{
	SFVec3f vec;

	switch (navMode)
	{
	case MOVEMODE_ROTATEX:
		vec = ProjectToSphere(viewport, mouseLoc);
		vec.x = 0;
		return vec;
	case MOVEMODE_ROTATEY:
		vec = ProjectToSphere(viewport, mouseLoc);
		vec.y = 0;
		return vec;
	case MOVEMODE_ROTATEZ:
		vec = ProjectToSphere(viewport, mouseLoc);
		vec.z = 0;
		return vec;

	case MOVEMODE_SLIDE:
		return ProjectToSphere(viewport, mouseLoc, .25);

	case MOVEMODE_WALK:
		{
			// a normalized point centered around the center of the window
			vec = SFVec3f((2.0*mouseLoc.x - viewport.Width()) / viewport.Width(), (2.0*mouseLoc.y - viewport.Height()) / viewport.Height(), 0);;
			return vec;
		}
		break;

	case MOVEMODE_EXAMINE:
		return ProjectToSphere(viewport, mouseLoc);
	}
	return mouseLoc;
}

vrRect2D tovrRect(CRect r)
{
	return vrRect2D(r.left, r.top, r.right, r.bottom);
}

void vrMyBrowser::HandleMouse(int action, const SFVec3f& mouseLoc)
{
	static SFVec3f start;

	switch (action)
	{
	case WM_MOUSEMOVE:
		{
			if (isActive)
			{
				CRect viewport;
				GetWindowRect(m_hWnd, viewport);
				SFVec3f curPos = Project(GetNavigationMode(), tovrRect(viewport), mouseLoc);
				delta = curPos - lastPos;
				orientation = SFRotation(CrossProduct(lastPos, curPos), 90.0F * Length(delta));
				delta = curPos - firstPos;
				lastPos = curPos;
				updateMatrix();
			}
			currPt = mouseLoc;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			autoAnimate = TRUE;
			isActive = TRUE;
			start = mouseLoc;
			CRect viewport;
			GetWindowRect(m_hWnd, viewport);
			firstPos = lastPos = Project(GetNavigationMode(), tovrRect(viewport), mouseLoc);
			delta = 0.0;
		}
		currPt = mouseLoc;
		firstDown = mouseLoc;
		drawRubber = TRUE;
		drawCrossHair = TRUE;
		break;
	case WM_LBUTTONUP:
		{
			isActive = FALSE;
			SFBool val = AfxGetApp()->GetProfileInt("Settings", "AutoAnimate", TRUE);
			if ((!val) || !(start != mouseLoc) || GetNavigationMode() == MOVEMODE_SLIDE || GetNavigationMode() == MOVEMODE_WALK)
			{
				orientation.w = 0.0;
				autoAnimate = FALSE;
			}
		}
		drawCrossHair = FALSE;
		drawRubber = FALSE;
		break;
	}
}

BOOL vrMyBrowser::updateMatrix(void)
{
	if (autoAnimate && delta!=0.0)
	{
		vrViewpoint *vp = GetViewpoint();
		if (vp)
		{
			if (GetNavigationMode() == MOVEMODE_WALK)
			{
				vp->SetPosition(vp->GetPosition() + SFVec3f(delta.x, 0, delta.y));
			} else if (GetNavigationMode() == MOVEMODE_SLIDE)
			{
				vp->SetPosition(vp->GetPosition() + SFVec3f(delta.x, delta.y, 0));
			} else
			{
				glPushMatrix();
				glLoadIdentity();
				glRotatef(orientation.w, orientation.x, orientation.y, orientation.z);
				glMultMatrixf((GLfloat*)&matrix.vals[0][0]);
				glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)&matrix.vals[0][0]);
				glPopMatrix();
				drawRubber = FALSE;
			}
		}

		return TRUE;
	}

	return FALSE;
}

SFBool vrMyBrowser::ProcessUserMessage(const vrUserMessage& msg)
{
	if (vrBrowser::ProcessUserMessage(msg)) return TRUE;
	
	switch (msg.message_id)
	{
	case WM_LBUTTONDOWN:
		{
			SetCapture(m_hWnd);
			HandleMouse(WM_LBUTTONDOWN, msg.point);
		}
		return TRUE;

	case WM_LBUTTONUP:
		{
			ReleaseCapture();
			HandleMouse(WM_LBUTTONUP, msg.point);
		}
		return TRUE;

	case WM_MOUSEMOVE:
	  if (isActive)
		{
			HandleMouse(WM_MOUSEMOVE, msg.point);
			// This gives smooth animation of interpolators and such while moving
			// mouse, may not be needed when navigation is part of vraniml.dll
			Tick();
			Traverse();
			return TRUE;
		}
	}
	return FALSE;
}

int vrMyBrowser::GetNavigationMode(void) const
{
	return navMode;
}

void vrMyBrowser::SetNavigationMode(int mode)
{
	navMode = mode;
	autoAnimate = FALSE;
	AfxGetApp()->WriteProfileInt("Settings", "NavMode", mode);
}

void vrMyOGLTraverser::PreTraverse(void)
{
	vrOGLTraverser::PreTraverse();
	int dmode = AfxGetApp()->GetProfileInt("Settings", "DrawMode", 0);
	if (dmode == 2)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	else if (dmode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	HWND hWnd = (HWND)m_hWnd;
	HDC hDC = GetDC(hWnd);
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(255,255,255));
	HPEN old = (HPEN)SelectObject(hDC, pen);
	if (drawRubber)
	{
		MoveToEx(hDC, firstDown.x, firstDown.y, NULL);
		LineTo(hDC, currPt.x, currPt.y);
	}
	if (drawCrossHair)
	{
		MoveToEx(hDC, firstDown.x-6, firstDown.y, NULL);
		LineTo(hDC, firstDown.x+7, firstDown.y);
		MoveToEx(hDC, firstDown.x, firstDown.y-6, NULL);
		LineTo(hDC, firstDown.x, firstDown.y+7);
	}
	SelectObject(hDC, old);
	DeleteObject(pen);
	if (drawCrossHair)
	{
		SetPixel(hDC, firstDown.x, firstDown.y, 0);
		SetPixel(hDC, firstDown.x-1, firstDown.y, 0);
		SetPixel(hDC, firstDown.x+1, firstDown.y, 0);
		SetPixel(hDC, firstDown.x, firstDown.y-1, 0);
		SetPixel(hDC, firstDown.x, firstDown.y+1, 0);
		SetPixel(hDC, currPt.x,   currPt.y,   RGB(255,255,255));
		SetPixel(hDC, currPt.x-1, currPt.y,   RGB(255,255,255));
		SetPixel(hDC, currPt.x+1, currPt.y,   RGB(255,255,255));
		SetPixel(hDC, currPt.x,   currPt.y-1, RGB(255,255,255));
		SetPixel(hDC, currPt.x,   currPt.y+1, RGB(255,255,255));
	}

	SFBool headsUp = AfxGetApp()->GetProfileInt("Settings", "HeadsUpDisplay", FALSE);
	if (headsUp)
	{
		char str[256];
		SFVec3f l;
		SFRotation r;
		vrViewpoint *vp = m_Browser->GetViewpoint();
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255,255,0));
		l = (vp) ? vp->GetPosition() : SFVec3f(0,0,0);
		sprintf(str, "vp pos: %f %f %f", l.x, l.y, l.z);
		TextOut(hDC, 400, 10, str, strlen(str));

		r = (vp) ? vp->GetOrientation() : SFRotation(0,0,1,0);
		sprintf(str, "vp ori: %f %f %f %f", r.x, r.y, r.z, r.w);
		TextOut(hDC, 400, 30, str, strlen(str));
	}

	ReleaseDC(hWnd, hDC);
}

vrWindowsConsole console;
vrMyBrowser::vrMyBrowser(void *hWnd) : vrBrowser(hWnd)
{
	m_Console = &console;
#ifdef _DEBUG
	navMode = AfxGetApp()->GetProfileInt("Settings", "NavMode", MOVEMODE_EXAMINE);
#else
	navMode = MOVEMODE_EXAMINE;
#endif
	
	ASSERT(GetTraverserByNumber(1) && GetTraverserByNumber(1)->IsKindOf(GETRUNTIME_CLASS(vrRenderTraverser)));
	// Replace the rendering traverser
	vrMyOGLTraverser *t = new vrMyOGLTraverser(this, hWnd);
	vrTraverser *old = SetTraverser(t, 1, FALSE);
	delete old;
	m_hWnd = (HWND)hWnd;
};

