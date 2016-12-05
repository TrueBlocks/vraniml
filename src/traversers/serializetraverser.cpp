//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "SerializeTraverser.h"

/*

IMPLEMENT_NODE(vrSerializeTraverser, vrTraverser);

//---------------------
void vrSerializeTraverser::Traverse(const vrAppearance *node)
{
	vrNode::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_Material
			<< m_TextureTrans
			<< m_Texture;
	}
	else
	{
		archive
			>> m_Material
			>> m_TextureTrans
			>> m_Texture;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrFontStyle *node)
{
	vrNode::Serialize(archive);

	m_Justifys.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_Size
			<< m_Spacing
			<< m_Family
			<< m_Style
			<< m_Language
			<< m_Horizontal
			<< m_LeftToRight
			<< m_TopToBottom;
	}
	else
	{
		archive
			>> m_Size
			>> m_Spacing
			>> m_Family
			>> m_Style
			>> m_Language
			>> m_Horizontal
			>> m_LeftToRight
			>> m_TopToBottom;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrBackground *node)
{
	vrNode::Serialize(archive);

	m_GroundColors.Serialize(archive);
	m_SkyColors.Serialize(archive);
	m_GroundAngles.Serialize(archive);
	m_SkyAngles.Serialize(archive);
	m_BackURLs.Serialize(archive);
	m_BottomURLs.Serialize(archive);
	m_FrontURLs.Serialize(archive);
	m_LeftURLs.Serialize(archive);
	m_RightURLs.Serialize(archive);
	m_TopURLs.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrFog *node)
{
	vrNode::Serialize(archive);

	m_Color.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_FogType
			<< m_VisibilityRange;
	}
	else
	{
		archive
			>> m_FogType
			>> m_VisibilityRange;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrNavigationInfo *node)
{
	vrNode::Serialize(archive);

	m_AvatarSize.Serialize(archive);
	m_Type.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_HeadLight
			<< m_Speed
			<< m_VisibilityLimit;
	}
	else
	{
		archive
			>> m_HeadLight
			>> m_Speed
			>> m_VisibilityLimit;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrViewpoint *node)
{
	vrNode::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_FieldOfView
			<< m_Jump
			<< m_Rotation
			<< m_Position
			<< m_Description;
	}
	else
	{
		archive
			>> m_FieldOfView
			>> m_Jump
			>> m_Rotation
			>> m_Position
			>> m_Description;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrAudioClip *node)
{
	vrNode::Serialize(archive);

	m_URLs.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_Pitch
			<< m_Loop
			<< m_StartTime
			<< m_StopTime
			<< m_Description;
	}
	else
	{
		archive
			>> m_Pitch
			>> m_Loop
			>> m_StartTime
			>> m_StopTime
			>> m_Description;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrScript *node)
{
	vrNode::Serialize(archive);

	m_Scripts.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_MustEvaluate
			<< m_DirectOutput;
	}
	else
	{
		archive
			>> m_MustEvaluate
			>> m_DirectOutput;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrSound *node)
{
	vrNode::Serialize(archive);


	if (archive.IsStoring())
	{
		archive
			<< m_Intensity
			<< m_Priority
			<< m_Location
			<< m_Direction
			<< m_MinFront
			<< m_MaxFront
			<< m_MinBack
			<< m_MaxBack
			<< m_Spatialize;
	}
	else
	{
		archive
			>> m_Intensity
			>> m_Priority
			>> m_Location
			>> m_Direction
			>> m_MinFront
			>> m_MaxFront
			>> m_MinBack
			>> m_MaxBack
			>> m_Spatialize;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrWorldInfo *node)
{
	vrNode::Serialize(archive);

	m_Infos.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_Title;
	}
	else
	{
		archive
			>> m_Title;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrAxis *node)
{
	vrIndexedFaceSet::Serialize(archive);
}

//---------------------
void vrSerializeTraverser::Traverse(const vrTorus *node)
{
	CMesh::Serialize(archive);


	if (archive.IsStoring())
	{
		archive
			<< m_Major
			<< m_Minor
			<< m_InRad
			<< m_OutRad;
	}
	else
	{
		archive
			>> m_Major
			>> m_Minor
			>> m_InRad
			>> m_OutRad;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrBox *node)
{
	CMesh::Serialize(archive);


	if (archive.IsStoring())
	{
		archive
			<< m_Size;
	}
	else
	{
		archive
			>> m_Size;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrColor *node)
{
	vrNode::Serialize(archive);

	m_Colors.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrCone *node)
{
	vrCylinder::Serialize(archive);
}

//---------------------
void vrSerializeTraverser::Traverse(const vrCoordinate *node)
{
	vrNode::Serialize(archive);

	m_Coords.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrCylinder *node)
{
	vrNode::Serialize(archive);
}

//---------------------
void vrSerializeTraverser::Traverse(const vrDataSet *node)
{
	vrNode::Serialize(archive);

	m_ColorIndexs.Serialize(archive);
	m_CoordIndexs.Serialize(archive);
	m_NormalIndexs.Serialize(archive);
	m_TextureIndexs.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_ColorPerVertex
			<< m_NormalPerVertex;
	}
	else
	{
		archive
			>> m_ColorPerVertex
			>> m_NormalPerVertex;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrElevationGrid *node)
{
	vrDataSet::Serialize(archive);

	m_Heights.Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_xDimension
			<< m_xSpacing
			<< m_zDimension
			<< m_zSpacing;
	}
	else
	{
		archive
			>> m_xDimension
			>> m_xSpacing
			>> m_zDimension
			>> m_zSpacing;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrExtrusion *node)
{
	vrNode::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_Spines
			<< m_CrossSections
			<< m_Scales
			<< m_Orientations
			<< m_BeginCap
			<< m_EndCap;
	}
	else
	{
		archive
			>> m_Spines
			>> m_CrossSections
			>> m_Scales
			>> m_Orientations
			>> m_BeginCap
			>> m_EndCap;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrIndexedFaceSet *node)
{
	vrDataSet::Serialize(archive);

	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrIndexedLineSet *node)
{
	vrDataSet::Serialize(archive);

	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrNormal *node)
{
	vrNode::Serialize(archive);

	m_Normals.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrPointSet *node)
{
	vrDataSet::Serialize(archive);
}

//---------------------
void vrSerializeTraverser::Traverse(const vrSphere *node)
{
	CMesh::Serialize(archive);


	if (archive.IsStoring())
	{
		archive
			<< m_Radius
			<< m_Slices
			<< m_Stacks;
	}
	else
	{
		archive
			>> m_Radius
			>> m_Slices
			>> m_Stacks;
	}
}

*/
/*

//---------------------
void vrSerializeTraverser::Traverse(const vrText *node)
{
	vrNode::Serialize(archive);

	m_Lengths.Serialize(archive);
	m_Strings.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_MaxExtent;
	}
	else
	{
		archive
			>> m_MaxExtent;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrTextureCoordinate *node)
{
	vrNode::Serialize(archive);

	m_TexCoords.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrAnchor *node)
{
	vrGroupingNode::Serialize(archive);

	m_Parameters.Serialize(archive);
	m_URLs.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_Description;
	}
	else
	{
		archive
			>> m_Description;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrBillboard *node)
{
	vrGroupingNode::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_AxisOfRotation;
	}
	else
	{
		archive
			>> m_AxisOfRotation;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrCollision *node)
{
	vrGroupingNode::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_Collide;
	}
	else
	{
		archive
			>> m_Collide;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrGroup *node)
{
	vrGroupingNode::Serialize(archive);
}

//---------------------
void vrSerializeTraverser::Traverse(const vrGroupingNode *node)
{
	vrNode::Serialize(archive);

	m_Bounds.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrInline *node)
{
	vrGroupingNode::Serialize(archive);

	m_URLs.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrLOD *node)
{
	vrNode::Serialize(archive);

	m_Ranges.Serialize(archive);
	if (archive.IsStoring())
	{
		archive
			<< m_Center;
	}
	else
	{
		archive
			>> m_Center;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrSwitch *node)
{
	vrNode::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_Which;
	}
	else
	{
		archive
			>> m_Which;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrTransform *node)
{
	vrGroupingNode::Serialize(archive);


	if (archive.IsStoring())
	{
		archive
			<< m_Translation
			<< m_Scale
			<< m_Center
			<< m_Rotation
			<< m_Orient;
	}
	else
	{
		archive
			>> m_Translation
			>> m_Scale
			>> m_Center
			>> m_Rotation
			>> m_Orient;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrColorInterpolator *node)
{
	vrInterpolator::Serialize(archive);


	m_KeyValues.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrCoordinateInterpolator *node)
{
	vrInterpolator::Serialize(archive);


	m_KeyValues.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrInterpolator *node)
{
	vrNode::Serialize(archive);


	m_Keys.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrNormalInterpolator *node)
{
	vrInterpolator::Serialize(archive);


	m_KeyValues.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrOrientationInterpolator *node)
{
	vrInterpolator::Serialize(archive);


	m_KeyValues.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrPositionInterpolator *node)
{
	vrInterpolator::Serialize(archive);


	m_KeyValues.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrScalarInterpolator *node)
{
	vrInterpolator::Serialize(archive);


	m_KeyValues.Serialize(archive);
	if (archive.IsStoring())
	{
	}
	else
	{
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrCylinderSensor *node)
{
	vrSensor::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_MinAngle
			<< m_MaxAngle
			<< m_DiskAngle
			<< m_Offset;
	}
	else
	{
		archive
			>> m_MinAngle
			>> m_MaxAngle
			>> m_DiskAngle
			>> m_Offset;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrPlaneSensor *node)
{
	vrSensor::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_MaxPosition
			<< m_MinPosition
			<< m_Offset;
	}
	else
	{
		archive
			>> m_MaxPosition
			>> m_MinPosition
			>> m_Offset;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrProximitySensor *node)
{
	vrSensor::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_Center
			<< m_Size;
	}
	else
	{
		archive
			>> m_Center
			>> m_Size;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrSensor *node)
{
	vrNode::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_Enabled
			<< m_AutoOffset;
	}
	else
	{
		archive
			>> m_Enabled
			>> m_AutoOffset;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrSphereSensor *node)
{
	vrSensor::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_Offset;
	}
	else
	{
		archive
			>> m_Offset;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrTimeSensor *node)
{
	vrSensor::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_StartTime
			<< m_StopTime
			<< m_CycleInterval
			<< m_Loop;
	}
	else
	{
		archive
			>> m_StartTime
			>> m_StopTime
			>> m_CycleInterval
			>> m_Loop;
	}
}

//---------------------
void vrSerializeTraverser::Traverse(const vrTouchSensor *node)
{
	vrSensor::Serialize(archive);
}

//---------------------
void vrSerializeTraverser::Traverse(const vrVisibilitySensor *node)
{
	vrSensor::Serialize(archive);

	if (archive.IsStoring())
	{
		archive
			<< m_Center
			<< m_Size;
	}
	else
	{
		archive
			>> m_Center
			>> m_Size;
	}
}
*/