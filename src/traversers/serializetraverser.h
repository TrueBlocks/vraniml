#ifndef __SERIALIZETRAVERSER_H3D
#define __SERIALIZETRAVERSER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------

#include "Traverser.h"

class LIBInterface vrSerializeTraverser : public vrTraverser
{
public:
	             vrSerializeTraverser(vrBrowser *b=NULL, void *h=NULL);
	virtual     ~vrSerializeTraverser(void) {};

	DECLARE_NODE(vrSerializeTraverser);

	virtual void Traverse(const vrAppearance *node);
	virtual void Traverse(const vrFontStyle *node);
	virtual void Traverse(const vrImageTexture *node);
	virtual void Traverse(const vrMaterial *node);
	virtual void Traverse(const vrMovieTexture *node);
	virtual void Traverse(const vrPixelTexture *node);
	virtual void Traverse(const vrTextureTransform *node);
	virtual void Traverse(const vrBindable *node);
	virtual void Traverse(const vrBackground *node);
	virtual void Traverse(const vrFog *node);
	virtual void Traverse(const vrNavigationInfo *node);
	virtual void Traverse(const vrViewpoint *node);
	virtual void Traverse(const vrAudioClip *node);
	virtual void Traverse(const vrDirectionalLight *node);
	virtual void Traverse(const vrLight *node);
	virtual void Traverse(const vrPointLight *node);
	virtual void Traverse(const vrScript *node);
	virtual void Traverse(const vrShape *node);
	virtual void Traverse(const vrSound *node);
	virtual void Traverse(const vrSpotLight *node);
	virtual void Traverse(const vrWorldInfo *node);
	virtual void Traverse(const vrGroupingNode *node);
	virtual void Traverse(const vrAnchor *node);
	virtual void Traverse(const vrBillboard *node);
	virtual void Traverse(const vrCollision *node);
	virtual void Traverse(const vrGroup *node);
	virtual void Traverse(const vrTransform *node);
	virtual void Traverse(const vrInline *node);
	virtual void Traverse(const vrLOD *node);
	virtual void Traverse(const vrSwitch *node);
	virtual void Traverse(const vrGeometryNode *node);
	virtual void Traverse(const vrBox *node);
	virtual void Traverse(const vrCone *node);
	virtual void Traverse(const vrCylinder *node);
	virtual void Traverse(const vrExtrusion *node);
	virtual void Traverse(const vrSphere *node);
	virtual void Traverse(const vrText *node);
	virtual void Traverse(const vrDataSet *node);
	virtual void Traverse(const vrElevationGrid *node);
	virtual void Traverse(const vrIndexedFaceSet *node);
	virtual void Traverse(const vrIndexedLineSet *node);
	virtual void Traverse(const vrPointSet *node);
	virtual void Traverse(const vrColor *node);
	virtual void Traverse(const vrCoordinate *node);
	virtual void Traverse(const vrNormal *node);
	virtual void Traverse(const vrTextureCoordinate *node);
	virtual void Traverse(const vrInterpolator *node);
	virtual void Traverse(const vrColorInterpolator *node);
	virtual void Traverse(const vrCoordinateInterpolator *node);
	virtual void Traverse(const vrNormalInterpolator *node);
	virtual void Traverse(const vrOrientationInterpolator *node);
	virtual void Traverse(const vrPositionInterpolator *node);
	virtual void Traverse(const vrScalarInterpolator *node);
	virtual void Traverse(const vrSensor *node);
	virtual void Traverse(const vrPointingDeviceSensor *node);
	virtual void Traverse(const vrCylinderSensor *node);
	virtual void Traverse(const vrPlaneSensor *node);
	virtual void Traverse(const vrProximitySensor *node);
	virtual void Traverse(const vrSphereSensor *node);
	virtual void Traverse(const vrTimeSensor *node);
	virtual void Traverse(const vrTouchSensor *node);
	virtual void Traverse(const vrVisibilitySensor *node);

	virtual void Traverse(const vrBrowser *node);

protected:
	//CArchive ar;

};

//----------------------------------------------------------------------
#endif
