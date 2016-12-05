#ifndef __ACTIONTRAVERSER_H3D
#define __ACTIONTRAVERSER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------

#include "Traverser.h"

/*----------------------------------------------------------------------
CLASS
	vrActionTraverser

	A traverser that generate any actions initiating event cascades.

DESCRIPTION
	<ul>
	A traverser that generate any actions initiating event cascades.
	This includes both user generated events (mouse events) and 
	Sensor events.
	</ul>

NOTES
	<ul>
	<li>Most node types are handled by the base class vrTraverser.  This class
	only handles the nodes that can initiate event cascades.  For example,
	the geometry and interpolator nodes never initiate event cascades (even
	though they may participate in an event cascade).</li>
	<li>Like all traversers this class has a single method called Traverse for
	each of the built-in nodes types (although some Traverse functions may actually
	be defined in the base class).  These Traverse methods handle each node
	seperatly and in an appropriate way.  These seperate methods are not
	documented.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrActionTraverser : public vrTraverser
{
public:
	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] b: The browser to attach this traverser to.
	// [in] h: A window handle.
	//
  vrActionTraverser(vrBrowser *b=NULL, void *h=NULL);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	//
	virtual     ~vrActionTraverser(void)
		{ };

//	virtual void Traverse(const vrAppearance *node);
//	virtual void Traverse(const vrFontStyle *node);
//	virtual void Traverse(const vrImageTexture *node);
//	virtual void Traverse(const vrMaterial *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrMovieTexture *node);

//	virtual void Traverse(const vrPixelTexture *node);
//	virtual void Traverse(const vrTextureTransform *node);
//	virtual void Traverse(const vrBackground *node);
//	virtual void Traverse(const vrFog *node);
//	virtual void Traverse(const vrNavigationInfo *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrViewpoint *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrAudioClip *node);

//	virtual void Traverse(const vrDirectionalLight *node);
//	virtual void Traverse(const vrLight *node);
//	virtual void Traverse(const vrPointLight *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrScript *node);

//	virtual void Traverse(const vrShape *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSound *node);

//	virtual void Traverse(const vrSpotLight *node);
//	virtual void Traverse(const vrWorldInfo *node);

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

//	virtual void Traverse(const vrGeometryNode *node);
//	virtual void Traverse(const vrBox *node);
//	virtual void Traverse(const vrCone *node);
//	virtual void Traverse(const vrCylinder *node);
//	virtual void Traverse(const vrExtrusion *node);
//	virtual void Traverse(const vrSphere *node);
//	virtual void Traverse(const vrText *node);
//	virtual void Traverse(const vrDataSet *node);
//	virtual void Traverse(const vrElevationGrid *node);
//	virtual void Traverse(const vrIndexedFaceSet *node);
//	virtual void Traverse(const vrIndexedLineSet *node);
//	virtual void Traverse(const vrPointSet *node);
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

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrCylinderSensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrPlaneSensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrProximitySensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSphereSensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrTimeSensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrTouchSensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrVisibilitySensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrBrowser *node);

	//<doc>------------------------------------------------------------
	// <dd>A chance to do something just prior to a traversal.
	//
	virtual void PreTraverse();

	//<doc>------------------------------------------------------------
	// <dd>A chance to do something just after a traversal.
	//
	virtual void PostTraverse();

	//<doc>------------------------------------------------------------
	// <dd>Respond to a user generated event.
	//
	// [in] msg: The vrUserMessage event.
	//
	virtual SFBool ProcessUserMessage(const vrUserMessage& msg);

	//<doc>------------------------------------------------------------
	// <dd>Declare that this class may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrActionTraverser);

protected:
	//<doc>------------------------------------------------------------
	// <dd>TRUE if the most recent traversal encountered any sensors in the scene graph.
	//
	// [default] FALSE
	//
	SFBool hasSensor;

	//<nodoc>------------------------------------------------------------
	// <dd>Initiate a picking event on the browser.
	//
	void Pick(const vrBrowser *browser);
};

#endif
