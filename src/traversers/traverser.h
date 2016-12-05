#ifndef __TRAVERSER_H3D
#define __TRAVERSER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

#include "Browser\UserMessage.h"

/*----------------------------------------------------------------------
CLASS
	vrTraverser

	The base class for all Traversers.

DESCRIPTION
	<ul>
	This is the base class for all traversers.  It implements functionality
	that is common to all traversers (such as traversing grouping node's children).
	This class also maintains a stack of grouping nodes that represent the
	parentage of a given node in the traversal.
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
class LIBInterface vrTraverser : public vrBaseNode
{
public:
	//<doc>------------------------------------------------------------
	// <dd>The browser which contains the scene graph to traverse.
	//
	// [default] NA
	//
	vrBrowser  *m_Browser;

	//<doc>------------------------------------------------------------
	// <dd>The window into which to draw the scene graph.
	//
	// [default] NA
	//
	void       *m_hWnd;

	//<nodoc>------------------------------------------------------------
	// <dd>The mouse location of the current mouse event.
	//
	SFVec3f m_CurrMouse;

	//<nodoc>------------------------------------------------------------
	// <dd>The mouse location of the previous mouse event.
	//
	SFVec3f m_LastMouse;

	//<nodoc>------------------------------------------------------------
	// <dd>The rectangular size of the window.
	//
	vrRect2D  m_Viewport;

	//<doc>------------------------------------------------------------
	// <dd>The parentage of the current node being traversed (the branch of the scene graph that is currently being traversed).
	//
	vrNodeStack<vrGroupingNode *> parentStack;

	//<doc>------------------------------------------------------------
	// <dd>Constructor (don't use this).
	//
	vrTraverser()
		{ ASSERT(0); };

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] b: The browser to attach this traverser to.
	// [in] h: A window handle.
	//
	vrTraverser(vrBrowser *b, void *h);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual     ~vrTraverser(void)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrAppearance *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrFontStyle *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrImageTexture *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrMaterial *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrMovieTexture *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrPixelTexture *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrTextureTransform *node)
		{ };

	//<nodoc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	// virtual void Traverse(const vrBindable *node) {};

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrBackground *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrFog *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrNavigationInfo *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrViewpoint *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrAudioClip *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrDirectionalLight *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrLight *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrPointLight *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrScript *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrShape *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrSound *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrSpotLight *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrWorldInfo *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrGroupingNode *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrAnchor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrBillboard *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrCollision *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrGroup *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrTransform *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrInline *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrLOD *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSwitch *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrGeometryNode *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrBox *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrCone *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrCylinder *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrExtrusion *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrSphere *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrText *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrDataSet *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrElevationGrid *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrIndexedFaceSet *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrIndexedLineSet *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrPointSet *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrColor *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrCoordinate *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrNormal *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrTextureCoordinate *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrInterpolator *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrColorInterpolator *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrCoordinateInterpolator *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrNormalInterpolator *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrOrientationInterpolator *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrPositionInterpolator *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrScalarInterpolator *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrSensor *node)
		{ };

	//<nodoc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	//	virtual void Traverse(const vrPointingDeviceSensor *node)
	//		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrCylinderSensor *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrPlaneSensor *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrProximitySensor *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrSphereSensor *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrTimeSensor *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrTouchSensor *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrVisibilitySensor *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node (does nothing).
	//
	virtual void Traverse(const vrBrowser *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse the children of the given grouping node.
	//
	// [in] node: The grouping node to traverse the children of.
	//
	virtual void TraverseChildren(const vrGroupingNode *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse an arbitrary node type.
	// <dd>Probably never called.
	//
	virtual void Traverse(const vrNode *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse a bounding box (unknown use) - not documented.
	//
	virtual void Traverse(const vrBoundingBox *node);

	//<doc>------------------------------------------------------------
	// <dd>A chance to do something just prior to a traversal.  (Does nothing).
	//
	virtual void PreTraverse()
		{ };

	//<doc>------------------------------------------------------------
	// <dd>A chance to do something just after a traversal.  (Does nothing).
	//
	virtual void PostTraverse()
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Respond to a user generated event. (Does nothing).
	//
	// [in] msg: The vrUserMessage event.
	//
	virtual SFBool ProcessUserMessage(const vrUserMessage& msg)
		{ return FALSE; };

	//<doc>------------------------------------------------------------
	// <dd>Reset the traverser.
	//
	virtual void Reset(void);

	//<doc>------------------------------------------------------------
	// <dd>Clear the traverser.
	//
	virtual void Clear(void);

	//<doc>------------------------------------------------------------
	// <dd>Initialize the traverser (called by constructor).
	//
	virtual void Init(void);

	//<doc>------------------------------------------------------------
	// <dd>Returns the total transformation matrix represented by the currently traversed branch of the scene graph.
	//
	vrMatrix GetTotalTransformation(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Set the current mouse position (and copy the last mouse position to previous mouse position).
	//
	void    SetMousePos(SFVec3f pos);

	//<doc>------------------------------------------------------------
	// <dd>Get the current and previous mouse positions.
	//
	// [out] cur: Memory location for the current mouse position.
	// [out] prev: Memory location for the previous mouse position.
	//
	void    GetMousePos(SFVec3f& cur, SFVec3f& prev) const;

	//<doc>------------------------------------------------------------
	// <dd>Get the current and previous mouse positions.
	//
	SFVec3f GetMousePos(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Get the viewport.
	//
	vrRect2D          GetViewport					(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Set the viewport.
	//
	// [in] x,y: The top-left of the window.
	// [in] w,h: The width and height of the window.
	//
	virtual void      SetViewport					(long x, long y, long w, long h);

	//<doc>------------------------------------------------------------
	// <dd>Get the window handle.
	//
	void             *GetWindowHandle			(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Set the window handle.
	//
	// [in] hWnd: The handle.
	//
	void              SetWindowHandle			(void *hWnd);

	//<doc>------------------------------------------------------------
	// <dd>Return a unique identifier for a given node based on the node's
	// <dd>parentage.  The string returned is a concatenation of the
	// <dd>current parent stack.
	//
	SFString GetUniqueID(const vrNode *node) const;

	//<doc>------------------------------------------------------------
	// <dd>Declare that this class may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrTraverser);
};
typedef vrList<vrTraverser *> vrTraverserList;

inline void vrTraverser::Reset(void)
{
	Clear();
	Init();
}

inline void vrTraverser::Clear(void)
{
}

inline void vrTraverser::Init(void)
{
}

inline void *vrTraverser::GetWindowHandle(void) const
{
	return m_hWnd;
}

inline void vrTraverser::SetWindowHandle(void *hWnd)
{
	m_hWnd = hWnd;
}

inline vrRect2D vrTraverser::GetViewport(void) const
{
	return m_Viewport;
}

inline void vrTraverser::SetMousePos(SFVec3f pos)
{
	m_LastMouse = m_CurrMouse;
	m_CurrMouse = SFVec3f(pos.x, pos.y, pos.z);
}

inline void vrTraverser::GetMousePos(SFVec3f& cur, SFVec3f& prev) const
{
	cur = m_CurrMouse;
	prev = m_LastMouse;
}

inline SFVec3f vrTraverser::GetMousePos(void) const
{
	return m_CurrMouse;
}

//----------------------------------------------------------------------
#endif
