//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "ValidateTraverser.h"
#include "Browser\Browser.h"
#include "Nodes\AllNodes.h"

#pragma warning(disable:4189)

IMPLEMENT_NODE(vrValidateTraverser, vrTraverser);

inline SFBool inColorRange(SFColor val, SFColor start, SFColor stop)
{
	return 
		(((start.x <= val.x) && (stop.x >= val.x)) && 
		 ((start.y <= val.y) && (stop.y >= val.y)) && 
		 ((start.z <= val.z) && (stop.z >= val.z)) && 
		 ((start.a <= val.a) && (stop.a >= val.a)));
}

vrValidateTraverser::vrValidateTraverser(vrBrowser *b, void *h) : vrTraverser(b, h)
{
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrAppearance *node)
{
	//
	// The value for each of the fields can be NULL, however if the
	// field is non-NULL then it must contain one node of the correct type
	//
	vrMaterial *mat = node->GetMaterial();
	ASSERT(!mat || mat->IsKindOf(GETRUNTIME_CLASS(vrMaterial)));

	vrPixelTexture *texture = node->GetTexture();
	ASSERT(!texture || texture->IsKindOf(GETRUNTIME_CLASS(vrPixelTexture)));

	vrTextureTransform *trans = node->GetTextureTransform();
	ASSERT(!trans || trans->IsKindOf(GETRUNTIME_CLASS(vrTextureTransform)));
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrFontStyle *node)
{
	//VRTRACE("Traversing: FontStyle\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrImageTexture *node)
{
	//VRTRACE("Traversing: ImageTexture\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrMaterial *node)
{
	ASSERT(vrInRange(node->GetAmbientIntensity(), 0.0f, 1.0f));
	ASSERT(vrInRange(node->GetShininess(), 0.0f, 1.0f));
	ASSERT(vrInRange(node->GetTransparency(), 0.0f, 1.0f));
	ASSERT(inColorRange(node->GetDiffuseColor(), vrBlack, vrWhite));
	ASSERT(inColorRange(node->GetEmissiveColor(), vrBlack, vrWhite));
	ASSERT(inColorRange(node->GetSpecularColor(), vrBlack, vrWhite));
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrMovieTexture *node)
{
	//VRTRACE("Traversing: MovieTexture\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrPixelTexture *node)
{
	//VRTRACE("Traversing: PixelTexture\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrTextureTransform *node)
{
	//VRTRACE("Traversing: TextureTransform\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrBackground *node)
{
	//VRTRACE("Traversing: Background\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrFog *node)
{
	//VRTRACE("Traversing: Fog\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrNavigationInfo *node)
{
	//VRTRACE("Traversing: NavigationInfo\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrViewpoint *node)
{
	//VRTRACE("Traversing: Viewpoint\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrAudioClip *node)
{
	//VRTRACE("Traversing: AudioClip\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrDirectionalLight *node)
{
	//VRTRACE("Traversing: DirectionalLight\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrLight *node)
{
	//VRTRACE("Traversing: Light\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrPointLight *node)
{
	//VRTRACE("Traversing: PointLight\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrScript *node)
{
	//VRTRACE("Traversing: Script\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrShape *node)
{
	//VRTRACE("Traversing: Shape\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrSound *node)
{
	//VRTRACE("Traversing: Sound\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrSpotLight *node)
{
	ASSERT(node->GetRadius()>=0.0);
	ASSERT(node->GetBeamWidth()>=0.0 && node->GetBeamWidth()<M_PI/2.);
	ASSERT(node->GetCutOffAngle()>=0.0 && node->GetCutOffAngle()<M_PI/2.);

	//VRTRACE("Traversing: SpotLight\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrWorldInfo *node)
{
	//VRTRACE("Traversing: WorldInfo\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrGroupingNode *node)
{
	//VRTRACE("Traversing: GroupingNode\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrAnchor *node)
{
	//VRTRACE("Traversing: Anchor\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrBillboard *node)
{
	//VRTRACE("Traversing: Billboard\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrCollision *node)
{
	//VRTRACE("Traversing: Collision\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrGroup *node)
{
	//VRTRACE("Traversing: Group\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrTransform *node)
{
	//VRTRACE("Traversing: Transform\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrInline *node)
{
	//VRTRACE("Traversing: Inline\n");
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrLOD *node)
{
	//VRTRACE("Traversing: LOD\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrSwitch *node)
{
	//VRTRACE("Traversing: Switch\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrGeometryNode *node)
{
	//VRTRACE("Traversing: GeometryNode\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrBox *node)
{
	// Size must be greater than 0.0
	ASSERT(node->GetSize().x > 0.0);
	ASSERT(node->GetSize().y > 0.0);
	ASSERT(node->GetSize().z > 0.0);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrCone *node)
{
	// Both bottomRadius and height must be greater than 0.0
	ASSERT(node->GetBottomRadius()>0.0);
	ASSERT(node->GetHeight()>0.0);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrCylinder *node)
{
	// Both radius and height must be greater than 0.0
	ASSERT(node->GetRadius()>0.0);
	ASSERT(node->GetHeight()>0.0);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrExtrusion *node)
{
	//VRTRACE("Traversing: Extrusion\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrSphere *node)
{
	// radius must be greater than 0.0
	ASSERT(node->GetRadius()>0.0);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrText *node)
{
	//VRTRACE("Traversing: Text\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrDataSet *node)
{
	//VRTRACE("Traversing: DataSet\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrElevationGrid *node)
{
	ASSERT(node->GetXDimension() >= 1);
	ASSERT(node->GetZDimension() >= 1);
	ASSERT(node->GetXSpacing() >= 0.0);
	ASSERT(node->GetZSpacing() >= 0.0);

	SFInt32 nVerts = node->GetXDimension() * node->GetZDimension();
	ASSERT(node->GetNHeights() >= nVerts);

	vrTextureCoordinate *texCoords = node->GetTexCoord();
	ASSERT(!texCoords || texCoords->IsKindOf(GETRUNTIME_CLASS(vrTextureCoordinate)));
	if (texCoords)
	{
		ASSERT(texCoords->GetNPoints() <= nVerts);
	}
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrIndexedFaceSet *node)
{
	// Coordinate and Color nodes and thier counts
	vrCoordinate *coords  = node->GetCoord();
	vrColor   *colors  = node->GetColor();

	SFInt32       nCoords = ((coords) ? coords->GetNPoints() : 0);
	SFInt32       nColors = ((colors) ? colors->GetNColors() : 0);

	// CoordinateIndex and ColorIndex arrays and thier counts
	const MFInt32& coordIndexArray = node->GetCoordIndexArray();
	SFInt32  nCoordIndicies  = coordIndexArray.GetCount();
	if (!nCoordIndicies)
		return;
	const MFInt32& colorIndexArray = node->GetColorIndexArray();
	SFInt32  nColorIndicies  = colorIndexArray.GetCount();

	if (!coords || !nCoords)
		return;

	ASSERT(!coords || coords->IsKindOf(GETRUNTIME_CLASS(vrCoordinate)));
	ASSERT(!colors || colors->IsKindOf(GETRUNTIME_CLASS(vrColor)));

	// Count number of line segments
	SFInt32 nLines=0;
	for (int i=0;i<nCoordIndicies;i++)
	{
		if (coordIndexArray[i] == -1)
			nLines++;
	}
	if (coordIndexArray[nCoordIndicies-1] != -1)
		nLines++;
	
	// Find largest coordinate and color indicies
	SFInt32 largestCoordIndex = -1;
	for (i=0;i<nCoordIndicies;i++)
	{
		SFInt32 index = coordIndexArray[i];
		ASSERT(index>=0);
		largestCoordIndex = MAX(index, largestCoordIndex);
	}
	SFInt32 largestColorIndex = -1;
	for (i=0;i<nColorIndicies;i++)
	{
		SFInt32 index = colorIndexArray[i];
		ASSERT(index>=0);
		largestColorIndex = MAX(index, largestColorIndex);
	}

	if (!node->GetColorPerVertex())
	{
		// Color per line
		if (nColorIndicies)
		{
			ASSERT(nColorIndicies >= nLines);
			ASSERT(largestColorIndex < nColors);
		} else
		{
			ASSERT(nColors >= nLines);
		}
	} else
	{
		// Color per vertex
		if (nColorIndicies)
		{
			ASSERT(nColorIndicies >= nCoordIndicies);
			ASSERT(largestColorIndex < nColors);
			for (int i=0;i<nCoordIndicies;i++)
			{
				SFInt32 coordIndex = coordIndexArray[i];
				SFInt32 colorIndex = colorIndexArray[i];
				ASSERT( ((coordIndex == -1) && (colorIndex == -1)) ||
									((coordIndex != -1) && (colorIndex != -1)));
			}
		} else
		{
			ASSERT(largestCoordIndex < nColors);
		}
	}
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrIndexedLineSet *node)
{
	//VRTRACE("Traversing: IndexedLineSet\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrPointSet *node)
{
	ASSERT(!node->GetCoord() || node->GetCoord()->IsKindOf(GETRUNTIME_CLASS(vrCoordinate)));
	if (node->GetNCoords())
	{
		if (node->GetColor())
		{
			ASSERT(node->GetColor()->IsKindOf(GETRUNTIME_CLASS(vrColor)));
			SFInt32 nCoords = node->GetNCoords();
			SFInt32 nColors = node->GetNColors();
			ASSERT(nCoords >= nColors);
		}
	}
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrColor *node)
{
	//VRTRACE("Traversing: Color\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrCoordinate *node)
{
	//VRTRACE("Traversing: Coordinate\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrNormal *node)
{
	//VRTRACE("Traversing: Normal\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrTextureCoordinate *node)
{
	//VRTRACE("Traversing: TextureCoordinate\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrInterpolator *node)
{
	//VRTRACE("Traversing: Interpolator\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrColorInterpolator *node)
{
	// Number of keyvalues must be the same as the number of keys
	ASSERT(node->GetNKeyValues() == node->GetNKeys());
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrCoordinateInterpolator *node)
{
	// Number of keyvalues must be an integer multiple of the number of keys
	ASSERT((node->GetNKeyValues()%node->GetNKeys()) == 0);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrNormalInterpolator *node)
{
	// Number of keyvalues must be an integer multiple of the number of keys
	ASSERT((node->GetNKeyValues()%node->GetNKeys()) == 0);
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrOrientationInterpolator *node)
{
	// Number of keyvalues must be the same as the number of keys
	ASSERT(node->GetNKeyValues() == node->GetNKeys());
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrPositionInterpolator *node)
{
	// Number of keyvalues must be the same as the number of keys
	ASSERT(node->GetNKeyValues() == node->GetNKeys());
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrScalarInterpolator *node)
{
	// Number of keyvalues must be the same as the number of keys
	ASSERT(node->GetNKeyValues() == node->GetNKeys());
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrSensor *node)
{
	//VRTRACE("Traversing: Sensor\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrCylinderSensor *node)
{
	//VRTRACE("Traversing: CylinderSensor\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrPlaneSensor *node)
{
	//VRTRACE("Traversing: PlaneSensor\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrProximitySensor *node)
{
	//VRTRACE("Traversing: ProximitySensor\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrSphereSensor *node)
{
	//VRTRACE("Traversing: SphereSensor\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrTimeSensor *node)
{
	//VRTRACE("Traversing: TimeSensor\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrTouchSensor *node)
{
	//VRTRACE("Traversing: TouchSensor\n");
}

//-------------------------------------------------------------------
void vrValidateTraverser::Traverse(const vrVisibilitySensor *node)
{
	//VRTRACE("Traversing: VisibilitySensor\n");
}

void vrValidateTraverser::Traverse(const vrBrowser *node)
{
	//VRTRACE("Traversing: Browser\n");
	TraverseChildren(node);
}

void vrValidateTraverser::Traverse(const vrBindable* node)
{
}

void vrValidateTraverser::Traverse(const vrPointingDeviceSensor* node)
{
}
