#ifndef __WRITETRAVERSER_H3D
#define __WRITETRAVERSER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------

#include "Traverser.h"

/*----------------------------------------------------------------------
CLASS
	vrWriteTraverser

	A traverser to write the current scene graph out to a file.

DESCRIPTION
	<ul>
	This traverser writes the current scene graph out to a file
	using a vrDumpContext.  This class is very useful for writing
	VRML emitors and exporters.
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
class LIBInterface vrWriteTraverser : public vrTraverser
{
public:
	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] b: The browser to attach this traverser to.
	// [in] h: A window handle.
	//
	vrWriteTraverser(vrBrowser *b=NULL, void *h=NULL);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual     ~vrWriteTraverser(void)
		{ };

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

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrTextureTransform *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrBindable *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrBackground *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrFog *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrNavigationInfo *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrViewpoint *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrAudioClip *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrDirectionalLight *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrLight *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrPointLight *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrScript *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrShape *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSound *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSpotLight *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrWorldInfo *node);

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

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrColor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrCoordinate *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrNormal *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrTextureCoordinate *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrInterpolator *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrColorInterpolator *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrCoordinateInterpolator *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrNormalInterpolator *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrOrientationInterpolator *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrPositionInterpolator *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrScalarInterpolator *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrSensor *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrPointingDeviceSensor *node);

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
	// <dd>Traverse this node.
	//
	virtual void Traverse(const vrEvent *ev);

	//<doc>------------------------------------------------------------
	// <dd>Write the head out for this node.
	//
	virtual SFBool WriteHead(const vrNode *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse the grouping node's children.
	//
	virtual void TraverseChildren(const vrGroupingNode *node);

	//<doc>------------------------------------------------------------
	// <dd>Traverse an arbitry node type.
	//
	virtual void Traverse(const SFNode node);

	//<doc>------------------------------------------------------------
	// <dd>A chance to do something prior to the traversal.
	//
	virtual void PreTraverse();

	//<doc>------------------------------------------------------------
	// <dd>Set the filename into which to write (opens the file).
	//
	void SetFilename(const SFString& filename);

	//<doc>------------------------------------------------------------
	// <dd>Set tab stop and tab character.
	//
	void SetTabStop(int n, char c=' ');

	//<doc>------------------------------------------------------------
	// <dd>Set verbosity.
	//
	void SetVerbose(SFBool which);

	//<doc>------------------------------------------------------------
	// <dd>Set the number of digits to display for floating point numbers.
	//
	void SetDigits(SFInt32 n);

	DECLARE_NODE(vrWriteTraverser);

	void DumpRoutes(const vrGroupingNode* group, SFBool isProto);

private:
	vrDumpContext dc;
	SFInt32       m_Verbose;
	SFBool        skipit;

	void DumpField(const SFString& fieldName, const MFColor& val, int nPerRow=1);
	void DumpField(const SFString& fieldName, const MFFloat& val, int nPerRow=4);
	void DumpField(const SFString& fieldName, const MFInt32& val, int nPerRow=0);
	void DumpField(const SFString& fieldName, const MFString& val, int nPerRow=1);
	void DumpField(const SFString& fieldName, const MFVec2f& val, int nPerRow=1);
	void DumpField(const SFString& fieldName, const MFVec3f& val, int nPerRow=1);
	void DumpField(const SFString& fieldName, const MFRotation& val, int nPerRow=1);
	void DumpField(const SFString& fieldName, const MFNode& val);
	void DumpField(const SFString& fieldName, const vrAppearance* val);
	void DumpField(const SFString& fieldName, const vrAudioClip* val);
	void DumpField(const SFString& fieldName, const vrColor* val);
	void DumpField(const SFString& fieldName, const vrCoordinate* val);
	void DumpField(const SFString& fieldName, const vrFontStyle* val);
	void DumpField(const SFString& fieldName, const vrGeometryNode* val);
	void DumpField(const SFString& fieldName, const vrMaterial* val);
	void DumpField(const SFString& fieldName, const vrNormal* val);
	void DumpField(const SFString& fieldName, const vrPixelTexture* val);
	void DumpField(const SFString& fieldName, const vrTextureTransform* val);
	void DumpField(const SFString& fieldName, const vrTextureCoordinate* val);
	void DumpField(const SFString& fieldName, SFInt32 val);
	void DumpField(const SFString& fieldName, const SFNode val);
	void DumpField(const SFString& fieldName, SFBool val);
	void DumpField(const SFString& fieldName, const SFColor& val);
	void DumpField(const SFString& fieldName, const char *val);
	void DumpField(const SFString& fieldName, SFFloat val);
	void DumpField(const SFString& fieldName, const SFVec3f& val);
	void DumpField(const SFString& fieldName, const SFVec2f& val);
	void DumpField(const SFString& fieldName, const SFRotation& val);
	void DumpField(const SFString& fieldName, SFTime val);
	SFBool AddName(char *s);
};
#define ALL_FIELDS 0x1

inline void vrWriteTraverser::SetVerbose(SFBool which)
{
	m_Verbose = which;
}

inline void vrWriteTraverser::SetDigits(SFInt32 n)
{
	dc.m_nDigits = n;
}

//----------------------------------------------------------------------
#endif
