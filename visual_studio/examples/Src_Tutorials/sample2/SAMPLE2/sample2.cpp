#include "windows.h"

#include "vraniml.h"

LRESULT APIENTRY WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND InitWindow(HINSTANCE hCurrentInst, char *className, char *windowName)
{
	WNDCLASS wndClass;
	HWND hWnd;

	/* register window class */
	wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc   = WindowProc;
	wndClass.cbClsExtra    = 0;
	wndClass.cbWndExtra    = 0;
	wndClass.hInstance     = hCurrentInst;
	wndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName  = NULL;
	wndClass.lpszClassName = className;
	RegisterClass(&wndClass);

	/* create window */
	hWnd = CreateWindow(className, 
				windowName,
				WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
				0, 0, 640, 480,
				NULL, NULL, hCurrentInst, NULL);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return hWnd;
}

//
// Create a shape object of the given color using the given geometry
//
vrShape *BuildShape(const SFColor& color, vrGeometryNode *node)
{
	vrShape *shape = new vrShape;
	vrAppearance *app = new vrAppearance;
	vrMaterial *mat = new vrMaterial;
	mat->SetDiffuseColor(color);
	app->SetMaterial(mat);
	shape->SetAppearance(app);
	shape->SetGeometry(node);
	return shape;
}


//
// Return an animated transform that spins the given shape about it's own axis
//
vrTransform *BuildSpinner(vrBrowser *browser, vrShape *shape)
{
	vrTransform *spinner = new vrTransform;
	spinner->AddChild(shape);

	// Notice that we make the TimeSensor and the OrientationInterpolator
	// children of the Transform.  In this way the entire sub-assembly
	// (from the Transform down) can be viewed as a single object.
	vrTimeSensor *timer = new vrTimeSensor;
	timer->SetLoop(TRUE);
	spinner->AddChild(timer);

	vrOrientationInterpolator *ori = new vrOrientationInterpolator;
	ori->AddKey(0.00); ori->AddKeyValue(SFRotation(zAxis, vrDeg2Rad(  0.0)));
	ori->AddKey(0.25); ori->AddKeyValue(SFRotation(zAxis, vrDeg2Rad( 90.0)));
	ori->AddKey(0.50); ori->AddKeyValue(SFRotation(zAxis, vrDeg2Rad(180.0)));
	ori->AddKey(0.75); ori->AddKeyValue(SFRotation(zAxis, vrDeg2Rad(270.0)));
	ori->AddKey(1.00); ori->AddKeyValue(SFRotation(zAxis, vrDeg2Rad(360.0)));
	spinner->AddChild(ori);

	// Now we ROUTE the timer to the interpolator to the transform to
	// create the animation
	timer->AddRoute("fraction_changed", ori,      "set_fraction");
	ori->AddRoute("value_changed",    spinner,  "set_rotation");

	return spinner;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd = InitWindow(hInstance, "VRaniML", "VRaniML Sample Program 2");

	vrBrowser *browser = new vrBrowser(hWnd);

	vrTransform *spinner;

	// Note that the original Transforms are still used to
	// separate the objects in space.  After building this
	// scene graph we will have two top level Transforms each
	// with a 'spinner' child.  The 'spinner' children each have
	// a Shape, TimeSensor and Interpolator as children of their own,
	// demonstrating the ability of VRML to encapsulate whole behaviors
	// under a scene graph hierarchy.
	vrTransform *t = new vrTransform;
	t->SetTranslation(SFVec3f(-1.0, 0.0, 0.0));     // move over in X

	// Add a spinning red cone
	spinner = BuildSpinner(browser, BuildShape(vrRed, new vrCone));
	t->AddChild(spinner);
	browser->AddChild(t);

	t = new vrTransform;
	t->SetTranslation(SFVec3f(1.0, 0.0, 0.0));      // move over the other way in X
	// Add a spinning green cylinder
	spinner = BuildSpinner(browser, BuildShape(vrGreen, new vrCylinder));
	t->AddChild(spinner);
	browser->AddChild(t);

	while (1)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0) != TRUE)
			{
				delete browser;
				return msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else
		{
			if (browser->Tick())
				browser->Traverse();
		}
	}

	delete browser;
	return FALSE;
}