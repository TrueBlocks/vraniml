#ifndef __TREETRAVERSER_H3D
#define __TREETRAVERSER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

class CTreeCtrl;
class vrTreeTraverser : public vrTraverser
{
public:
							 vrTreeTraverser(vrBrowser *b=NULL, CTreeCtrl *t=NULL);
	virtual     ~vrTreeTraverser(void) {};

	DECLARE_NODE(vrTreeTraverser);

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
	virtual void Traverse(const vrEvent *ev);
	virtual SFBool WriteHead(const vrNode *node);

	virtual void TraverseChildren(const vrGroupingNode *node);
	virtual void Traverse(const vrNode *node);
	virtual void PreTraverse();

public:
typedef vrArrayBase<SFNode> MFNode;
	void DumpField(char *fieldName, const MFColor& val, int nPerRow=1);
	void DumpField(char *fieldName, const MFFloat& val, int nPerRow=4);
	void DumpField(char *fieldName, const MFInt32& val, int nPerRow=0);
	void DumpField(char *fieldName, const MFString& val, int nPerRow=1);
	void DumpField(char *fieldName, const MFVec2f& val, int nPerRow=1);
	void DumpField(char *fieldName, const MFVec3f& val, int nPerRow=1);
	void DumpField(char *fieldName, const MFRotation& val, int nPerRow=1);
	void DumpField(char *fieldName, const MFNode& val);
	void DumpField(char *fieldName, const vrAppearance* val);
	void DumpField(char *fieldName, const vrAudioClip* val);
	void DumpField(char *fieldName, const vrColor* val);
	void DumpField(char *fieldName, const vrCoordinate* val);
	void DumpField(char *fieldName, const vrFontStyle* val);
	void DumpField(char *fieldName, const vrGeometryNode* val);
	void DumpField(char *fieldName, const vrMaterial* val);
	void DumpField(char *fieldName, const vrNormal* val);
	void DumpField(char *fieldName, const vrPixelTexture* val);
	void DumpField(char *fieldName, const vrTextureTransform* val);
	void DumpField(char *fieldName, const vrTextureCoordinate* val);
	void DumpField(char *fieldName, SFInt32 val);
	void DumpField(char *fieldName, const SFNode val);
	void DumpField(char *fieldName, SFBool val);
	void DumpField(char *fieldName, const SFColor& val);
	void DumpField(char *fieldName, const char *val);
	void DumpField(char *fieldName, SFFloat val);
	void DumpField(char *fieldName, const SFVec3f& val);
	void DumpField(char *fieldName, const SFVec2f& val);
	void DumpField(char *fieldName, const SFRotation& val);
	void DumpField(char *fieldName, SFTime val);

	void DumpRoutes(const vrBrowser* browser);
	void DO_NODE(char *fieldName, const vrNode *node);

	CTreeCtrl *tree;
	HTREEITEM itemStack[100];
	int tos;
};

//----------------------------------------------------------------------
#endif
