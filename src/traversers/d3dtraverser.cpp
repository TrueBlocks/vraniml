//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "D3DTraverser.h"
#include "Browser\Browser.h"
#include "Nodes\AllNodes.h"

IMPLEMENT_NODE(vrD3DTraverser, vrRenderTraverser);

vrD3DTraverser::vrD3DTraverser(vrBrowser *b, void *h) : vrRenderTraverser(b, h)
{
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrAppearance *node)
{
	//VRTRACE("Traversing: Appearance\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrFontStyle *node)
{
	//VRTRACE("Traversing: FontStyle\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrImageTexture *node)
{
	//VRTRACE("Traversing: ImageTexture\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrMaterial *node)
{
	//VRTRACE("Traversing: Material\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrMovieTexture *node)
{
	//VRTRACE("Traversing: MovieTexture\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrPixelTexture *node)
{
	//VRTRACE("Traversing: PixelTexture\n");
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrTextureTransform *node)
{
	//VRTRACE("Traversing: TextureTransform\n");
}
*/

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrBackground *node)
{
	//VRTRACE("Traversing: Background\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrFog *node)
{
	//VRTRACE("Traversing: Fog\n");
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrNavigationInfo *node)
{
	//VRTRACE("Traversing: NavigationInfo\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrViewpoint *node)
{
	//VRTRACE("Traversing: Viewpoint\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrAudioClip *node)
{
	//VRTRACE("Traversing: AudioClip\n");
}
*/

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrDirectionalLight *node)
{
	//VRTRACE("Traversing: DirectionalLight\n");
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrLight *node)
{
	//VRTRACE("Traversing: Light\n");
}
*/

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrPointLight *node)
{
	//VRTRACE("Traversing: PointLight\n");
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrScript *node)
{
	//VRTRACE("Traversing: Script\n");
}
*/

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrShape *node)
{
	//VRTRACE("Traversing: Shape\n");
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrSound *node)
{
	//VRTRACE("Traversing: Sound\n");
}
*/

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrSpotLight *node)
{
	//VRTRACE("Traversing: SpotLight\n");
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrWorldInfo *node)
{
	//VRTRACE("Traversing: WorldInfo\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrGroupingNode *node)
{
	//VRTRACE("Traversing: GroupingNode\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrAnchor *node)
{
	//VRTRACE("Traversing: Anchor\n");
	TraverseChildren(node);
}
*/

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrBillboard *node)
{
	//VRTRACE("Traversing: Billboard\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrCollision *node)
{
	//VRTRACE("Traversing: Collision\n");
	TraverseChildren(node);
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrGroup *node)
{
	//VRTRACE("Traversing: Group\n");
	TraverseChildren(node);
}
*/

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrTransform *node)
{
	//VRTRACE("Traversing: Transform\n");
	TraverseChildren(node);
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrInline *node)
{
	//VRTRACE("Traversing: Inline\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrLOD *node)
{
	//VRTRACE("Traversing: LOD\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrSwitch *node)
{
	//VRTRACE("Traversing: Switch\n");
}
*/

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrGeometryNode *node)
{
	//VRTRACE("Traversing: GeometryNode\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrBox *node)
{
	//VRTRACE("Traversing: Box\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrCone *node)
{
	//VRTRACE("Traversing: Cone\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrCylinder *node)
{
	//VRTRACE("Traversing: Cylinder\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrExtrusion *node)
{
	//VRTRACE("Traversing: Extrusion\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrSphere *node)
{
	//VRTRACE("Traversing: Sphere\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrText *node)
{
	//VRTRACE("Traversing: Text\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrDataSet *node)
{
	//VRTRACE("Traversing: DataSet\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrElevationGrid *node)
{
	//VRTRACE("Traversing: ElevationGrid\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrIndexedFaceSet *node)
{
	//VRTRACE("Traversing: IndexedFaceSet\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrIndexedLineSet *node)
{
	//VRTRACE("Traversing: IndexedLineSet\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrPointSet *node)
{
	//VRTRACE("Traversing: PointSet\n");
}

/*
//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrColor *node)
{
	//VRTRACE("Traversing: Color\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrCoordinate *node)
{
	//VRTRACE("Traversing: Coordinate\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrNormal *node)
{
	//VRTRACE("Traversing: Normal\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrTextureCoordinate *node)
{
	//VRTRACE("Traversing: TextureCoordinate\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrInterpolator *node)
{
	//VRTRACE("Traversing: Interpolator\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrColorInterpolator *node)
{
	//VRTRACE("Traversing: ColorInterpolator\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrCoordinateInterpolator *node)
{
	//VRTRACE("Traversing: CoordinateInterpolator\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrNormalInterpolator *node)
{
	//VRTRACE("Traversing: NormalInterpolator\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrOrientationInterpolator *node)
{
	//VRTRACE("Traversing: OrientationInterpolator\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrPositionInterpolator *node)
{
	//VRTRACE("Traversing: PositionInterpolator\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrScalarInterpolator *node)
{
	//VRTRACE("Traversing: ScalarInterpolator\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrSensor *node)
{
	//VRTRACE("Traversing: Sensor\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrCylinderSensor *node)
{
	//VRTRACE("Traversing: CylinderSensor\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrPlaneSensor *node)
{
	//VRTRACE("Traversing: PlaneSensor\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrProximitySensor *node)
{
	//VRTRACE("Traversing: ProximitySensor\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrSphereSensor *node)
{
	//VRTRACE("Traversing: SphereSensor\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrTimeSensor *node)
{
	//VRTRACE("Traversing: TimeSensor\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrTouchSensor *node)
{
	//VRTRACE("Traversing: TouchSensor\n");
}

//-------------------------------------------------------------------
void vrD3DTraverser::Traverse(const vrVisibilitySensor *node)
{
	//VRTRACE("Traversing: VisibilitySensor\n");
}
*/

void vrD3DTraverser::Traverse(const vrBrowser *node)
{
	//VRTRACE("Traversing: Browser\n");
	TraverseChildren(node);
}

