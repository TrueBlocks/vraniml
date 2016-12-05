#ifndef __OGLTRAVERSER_H3D
#define __OGLTRAVERSER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------

#include "RenderTraverser.h"

/*----------------------------------------------------------------------
CLASS
	vrOGLTraverser

	A rendering traverser that uses OpenGL for rendering.

DESCRIPTION
	<ul>
	Implements only those parts of a traversal that are accomplished
	by the underlying graphics library -- in this case OpenGL.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrOGLTraverser : public vrRenderTraverser
{
protected:
	//<doc>------------------------------------------------------------
	// <dd>Handle to the OpenGL rendering context.
	//
	// [default] NULL
	//
	void *m_hGLRC;

public:
	//<doc>------------------------------------------------------------
	// <dd>Constructor (don't use).
	//
	vrOGLTraverser()
		{ ASSERT(0); };

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] b: The browser to attach this traverser to.
	// [in] h: A window handle.
	//
	vrOGLTraverser(vrBrowser *b, void *h);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual     ~vrOGLTraverser(void);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrAppearance *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrFontStyle *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrImageTexture *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrMaterial *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrMovieTexture *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrPixelTexture *node);

//	virtual void Traverse(const vrTextureTransform *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrBackground *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrFog *node);

//	virtual void Traverse(const vrNavigationInfo *node);
//	virtual void Traverse(const vrViewpoint *node);
//	virtual void Traverse(const vrAudioClip *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrDirectionalLight *node);

//	virtual void Traverse(const vrLight *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrPointLight *node);

//	virtual void Traverse(const vrScript *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrShape *node);

//	virtual void Traverse(const vrSound *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSpotLight *node);

//	virtual void Traverse(const vrWorldInfo *node);
//	virtual void Traverse(const vrGroupingNode *node);
//	virtual void Traverse(const vrAnchor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrBillboard *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrCollision *node);

//	virtual void Traverse(const vrGroup *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrTransform *node);

//	virtual void Traverse(const vrInline *node);
//	virtual void Traverse(const vrLOD *node);
//	virtual void Traverse(const vrSwitch *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrGeometryNode *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrBox *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrCone *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrCylinder *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrExtrusion *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSphere *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrText *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrDataSet *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrElevationGrid *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrIndexedFaceSet *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrIndexedLineSet *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrPointSet *node);

//	virtual void Traverse(const vrColor *node);
//	virtual void Traverse(const vrCoordinate *node);
//	virtual void Traverse(const vrNormal *node);
//	virtual void Traverse(const vrTextureCoordinate *node);
//	virtual void Traverse(const vrInterpolator *node);
//	virtual void Traverse(const vrColorInterpolator *node);
//	virtual void Traverse(const vrCoordinateInterpolator *node);
//	virtual void Traverse(const vrNormalInterpolator *node);
//	virtual void Traverse(const vrOrientationInterpolator *node);
//	virtual void Traverse(const vrPositionInterpolator *node);
//	virtual void Traverse(const vrScalarInterpolator *node);
//	virtual void Traverse(const vrSensor *node);
//	virtual void Traverse(const vrCylinderSensor *node);
//	virtual void Traverse(const vrPlaneSensor *node);
//	virtual void Traverse(const vrProximitySensor *node);
//	virtual void Traverse(const vrSphereSensor *node);
//	virtual void Traverse(const vrTimeSensor *node);
//	virtual void Traverse(const vrTouchSensor *node);
//	virtual void Traverse(const vrVisibilitySensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrBrowser *node);

	//<doc>------------------------------------------------------------
	// <dd>A chance to do something just prior to a traversal.
	//
	virtual void PreTraverse(void);

	//<doc>------------------------------------------------------------
	// <dd>A chance to do something just after a traversal.
	//
	virtual void PostTraverse(void);

	//<doc>------------------------------------------------------------
	// <dd>Render a vrSolid.
	//
	virtual void Traverse(const vrSolid *node);

	//<doc>------------------------------------------------------------
	// <dd>Render a vrFace.
	//
	virtual void Traverse(const vrFace *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse the children of the given grouping node.
	//
	// [in] node: The grouping node to traverse the children of.
	//
	virtual void TraverseChildren(const vrGroupingNode *node);

	//<doc>------------------------------------------------------------
	// <dd>Set the viewport.
	//
	// [in] x,y: The top-left of the window.
	// [in] w,h: The width and height of the window.
	//
	virtual void SetViewport(long x, long y, long w, long h);

	//<doc>------------------------------------------------------------
	// <dd>Declare that this class may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrOGLTraverser);

private:
	        void SetupPalette(void);
	        void SetupDC(void);

	virtual void DrawComplexFace(const vrFace *node);
	virtual void DrawSimpleFace(const vrFace *node);

	virtual void Clear(void);
	virtual void Init(void);
};

// Some debugging help
#undef VCHECK
#ifdef _DEBUG
#include "ValidateTraverser.h"
#define VCHECK(a) { vrValidateTraverser _vt(m_Browser,m_hWnd); (a)->Traverse(&_vt); }
#define OGLCHECK(a) glCheck(a)
#else
#define VCHECK(a)
#define OGLCHECK(a)
#endif
#undef OGLCHECK
#define OGLCHECK(a)
//void ShowDSError(HWND hWnd, HRESULT hr);
//#define CHECKDS(a) ShowDSError(m_hWnd, a);
#define CHECKDS(a)

//----------------------------------------------------------------------
#endif

