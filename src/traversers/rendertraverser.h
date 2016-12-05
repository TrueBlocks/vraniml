#ifndef __RENDERTRAVERSER_H3D
#define __RENDERTRAVERSER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------

#include "Traverser.h"

/*----------------------------------------------------------------------
CLASS
	vrRenderTraverser

	The base class for traversers that render to a window.

DESCRIPTION
	<ul>
	This class is the base class for traversers that render to the
	window (for example an OGL or D3D traverser).  This class handles
	nodes common to all rendering traversers.  This class stores a
	pointer to the device context into which to draw the scene graph.
	</ul>

NOTES
	<ul>
	<li>Methods documented with 'does nothing' provide interfaces only.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrRenderTraverser : public vrTraverser
{
protected:
	//<doc>------------------------------------------------------------
	// <dd>The device context into which to render.
	//
	// [default] hWnd->hDC
	//
	void    *m_hDC;

	//<doc>------------------------------------------------------------
	// <dd>The device context into which to render.
	//
	// [default] hWnd->hDC
	//
	vrMatrix m_TextureCoordTransform;

	//<nodoc>------------------------------------------------------------
	// <dd>TRUE if lights should be drawn (mostly for debugging).
	//
	// [default] FALSE
	//
	SFBool   m_DrawLights;

#ifdef SOUND1
	// Sound is disabled
	LPDIRECTSOUND            lpDS;
	LPDIRECTSOUNDBUFFER      primaryBuffer;
	LPDIRECTSOUND3DLISTENER  listener;
#endif

public:
	//<doc>------------------------------------------------------------
	// <dd>The most recently encountered vrMaterial node used for default rendering of vrGeometry nodes.
	//
	// [default] NULL
	//
	const vrMaterial *currMaterial;

	//<doc>------------------------------------------------------------
	// <dd>TRUE if the current traversal if for purposes of picking the scene.
	//
	// [default] FALSE
	//
	SFBool          m_isPicking;

	//<doc>------------------------------------------------------------
	// <dd>Constructor (don't use).
	//
  vrRenderTraverser()
		{ ASSERT(0); };

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] b: The browser to attach this traverser to.
	// [in] h: A window handle.
	//
  vrRenderTraverser(vrBrowser *b, void *h);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual     ~vrRenderTraverser(void);

public:
	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrImageTexture *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrTextureTransform *node);

//	virtual void Traverse(const vrNavigationInfo *node);
//	virtual void Traverse(const vrViewpoint *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrAudioClip *node);

//	virtual void Traverse(const vrLight *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrScript *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSound *node);

//	virtual void Traverse(const vrWorldInfo *node);
//	virtual void Traverse(const vrGroupingNode *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrAnchor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrGroup *node);

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
	// <dd>Traverse a vrSolid (does nothing).
	//
	virtual void Traverse(const vrSolid *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse a vrFace (does nothing).
	//
	virtual void Traverse(const vrFace *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse a complex (with holes) vrFace (does nothing).
	//
	virtual void DrawComplexFace(const vrFace *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Traverse a simple (no holes) vrFace (does nothing).
	//
	virtual void DrawSimpleFace(const vrFace *node)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Modify the given texture coordinate by the current texture transform matrix.
	//
  SFVec2f TransformTexCoord(const SFVec2f& t) const;

	//<doc>------------------------------------------------------------
	// <dd>Clear the traverser.
	//
	virtual void Clear(void);

	//<doc>------------------------------------------------------------
	// <dd>Initialize the traverser.
	//
	virtual void Init(void);

	//<doc>------------------------------------------------------------
	// <dd>Declare that this class may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrRenderTraverser);
};

#endif
