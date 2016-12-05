#include "Kramer.h"

#include "AllNodes.h"

//-----------------------------------------------------------------------
// Picks the runtime node creation function for the node
//-----------------------------------------------------------------------
SFNode CreateAppearance(void)
{
	return new vrAppearance;
}

SFNode CreateAnchor(void)
{
	return new vrAnchor;
}

SFNode CreateAudioClip(void)
{
	return new vrAudioClip;
}

SFNode CreateBackground(void)
{
	return new vrBackground;
}

SFNode CreateBillboard(void)
{
	return new vrBillboard;
}

SFNode CreateBox(void)
{
	return new vrBox;
}

SFNode CreateColor(void)
{
	return new vrColor;
}

SFNode CreateCoordinate(void)
{
	return new vrCoordinate;
}

SFNode CreateCone(void)
{
	return new vrCone;
}

SFNode CreateColorInterpolator(void)
{
	return new vrColorInterpolator;
}

SFNode CreateCoordinateInterpolator(void)
{
	return new vrCoordinateInterpolator;
}

SFNode CreateCollision(void)
{
	return new vrCollision;
}

SFNode CreateCylinder(void)
{
	return new vrCylinder;
}

SFNode CreateCylinderSensor(void)
{
	return new vrCylinderSensor;
}

SFNode CreateDirectionalLight(void)
{
	return new vrDirectionalLight;
}

SFNode CreateExtrusion(void)
{
	return new vrExtrusion;
}

SFNode CreateElevationGrid(void)
{
	return new vrElevationGrid;
}

SFNode CreateFontStyle(void)
{
	return new vrFontStyle;
}

SFNode CreateFog(void)
{
	return new vrFog;
}

SFNode CreateGroup(void)
{
	return new vrGroup;
}

SFNode CreateIndexedFaceSet(void)
{
	return new vrIndexedFaceSet;
}

SFNode CreateIndexedLineSet(void)
{
	return new vrIndexedLineSet;
}

SFNode CreateInline(void)
{
	return new vrInline;
}

SFNode CreateImageTexture(void)
{
	return new vrImageTexture;
}

SFNode CreateLOD(void)
{
	return new vrLOD;
}

SFNode CreateMaterial(void)
{
	return new vrMaterial;
}

SFNode CreateMovieTexture(void)
{
	return new vrMovieTexture;
}

SFNode CreateNormal(void)
{
	return new vrNormal;
}

SFNode CreateNavigationInfo(void)
{
	return new vrNavigationInfo;
}

SFNode CreateNormalInterpolator(void)
{
	return new vrNormalInterpolator;
}

SFNode CreateOrientationInterpolator(void)
{
	return new vrOrientationInterpolator;
}

SFNode CreatePointLight(void)
{
	return new vrPointLight;
}

SFNode CreatePixelTexture(void)
{
	return new vrPixelTexture;
}

SFNode CreatePositionInterpolator(void)
{
	return new vrPositionInterpolator;
}

SFNode CreatePointSet(void)
{
	return new vrPointSet;
}

SFNode CreatePlaneSensor(void)
{
	return new vrPlaneSensor;
}

SFNode CreateProximitySensor(void)
{
	return new vrProximitySensor;
}

SFNode CreateShape(void)
{
	return new vrShape;
}

SFNode CreateScript(void)
{
	return new vrScript;
}

SFNode CreateSphere(void)
{
	return new vrSphere;
}

SFNode CreateSwitch(void)
{
	return new vrSwitch;
}

SFNode CreateSpotLight(void)
{
	return new vrSpotLight;
}

SFNode CreateScalarInterpolator(void)
{
	return new vrScalarInterpolator;
}

SFNode CreateSphereSensor(void)
{
	return new vrSphereSensor;
}

SFNode CreateSound(void)
{
	return new vrSound;
}

SFNode CreateTransform(void)
{
	return new vrTransform;
}

SFNode CreateTimeSensor(void)
{
	return new vrTimeSensor;
}

SFNode CreateTouchSensor(void)
{
	return new vrTouchSensor;
}

SFNode CreateTextureCoordinate(void)
{
	return new vrTextureCoordinate;
}

SFNode CreateText(void)
{
	return new vrText;
}

SFNode CreateTextureTransform(void)
{
	return new vrTextureTransform;
}

SFNode CreateViewpoint(void)
{
	return new vrViewpoint;
}

SFNode CreateVisibilitySensor(void)
{
	return new vrVisibilitySensor;
}

SFNode CreateWorldInfo(void)
{
	return new vrWorldInfo;
}

PFNNV FindCreateFunc(char *protoName)
{
	switch (protoName[0])
	{
		case 'A':
			{
				if (!strcmp(protoName, "Appearance"))
				{
					return CreateAppearance;
				} else if (!strcmp(protoName, "Anchor"))
				{
					return CreateAnchor;
				} else if (!strcmp(protoName, "AudioClip"))
				{
					return CreateAudioClip;
				}
			}
			break;
		case 'B':
			{
				if (!strcmp(protoName, "Background"))
				{
					return CreateBackground;
				} else if (!strcmp(protoName, "Billboard"))
				{
					return CreateBillboard;
				} else if (!strcmp(protoName, "Box"))
				{
					return CreateBox;
				}
			}
			break;
		case 'C':
			{
				switch (protoName[1])
				{
					case 'o':
						{
							if (!strcmp(protoName, "Color"))
							{
								return CreateColor;
							} else if (!strcmp(protoName, "Coordinate"))
							{
								return CreateCoordinate;
							} else if (!strcmp(protoName, "Cone"))
							{
								return CreateCone;
							} else if (!strcmp(protoName, "ColorInterpolator"))
							{
								return CreateColorInterpolator;
							} else if (!strcmp(protoName, "CoordinateInterpolator"))
							{
								return CreateCoordinateInterpolator;
							} else if (!strcmp(protoName, "Collision"))
							{
								return CreateCollision;
							}
						}
						break;
					case 'y':
						{
							if (!strcmp(protoName, "Cylinder"))
							{
								return CreateCylinder;
							} else if (!strcmp(protoName, "CylinderSensor"))
							{
								return CreateCylinderSensor;
							}
						}
				}
			}
			break;
		case 'D':
			{
				if (!strcmp(protoName, "DirectionalLight"))
				{
					return CreateDirectionalLight;
				}
			}
			break;
		case 'E':
			{
				if (!strcmp(protoName, "Extrusion"))
				{
					return CreateExtrusion;
				} else if (!strcmp(protoName, "ElevationGrid"))
				{
					return CreateElevationGrid;
				}
			}
			break;
		case 'F':
			{
				if (!strcmp(protoName, "FontStyle"))
				{
					return CreateFontStyle;
				} else if (!strcmp(protoName, "Fog"))
				{
					return CreateFog;
				}
			}
			break;
		case 'G':
			{
				if (!strcmp(protoName, "Group"))
				{
					return CreateGroup;
				}
			}
			break;
		case 'I':
			{
				if (!strcmp(protoName, "IndexedFaceSet"))
				{
					return CreateIndexedFaceSet;
				} else if (!strcmp(protoName, "IndexedLineSet"))
				{
					return CreateIndexedLineSet;
				} else if (!strcmp(protoName, "Inline"))
				{
					return CreateInline;
				} else if (!strcmp(protoName, "ImageTexture"))
				{
					return CreateImageTexture;
				}
			}
			break;
		case 'L':
			{
				if (!strcmp(protoName, "LOD"))
				{
					return CreateLOD;
				}
			}
			break;
		case 'M':
			{
				if (!strcmp(protoName, "Material"))
				{
					return CreateMaterial;
				} else if (!strcmp(protoName, "MovieTexture"))
				{
					return CreateMovieTexture;
				}
			}
			break;
		case 'N':
			{
				if (!strcmp(protoName, "Normal"))
				{
					return CreateNormal;
				} else if (!strcmp(protoName, "NavigationInfo"))
				{
					return CreateNavigationInfo;
				} else if (!strcmp(protoName, "NormalInterpolator"))
				{
					return CreateNormalInterpolator;
				}
			}
			break;
		case 'O':
			{
				if (!strcmp(protoName, "OrientationInterpolator"))
				{
					return CreateOrientationInterpolator;
				}
			}
			break;
		case 'P':
			{
				if (!strcmp(protoName, "PointLight"))
				{
					return CreatePointLight;
				} else if (!strcmp(protoName, "PixelTexture"))
				{
					return CreatePixelTexture;
				} else if (!strcmp(protoName, "PositionInterpolator"))
				{
					return CreatePositionInterpolator;
				} else if (!strcmp(protoName, "PointSet"))
				{
					return CreatePointSet;
				} else if (!strcmp(protoName, "PlaneSensor"))
				{
					return CreatePlaneSensor;
				} else if (!strcmp(protoName, "ProximitySensor"))
				{
					return CreateProximitySensor;
				}
			}
			break;
		case 'S':
			{
				if (!strcmp(protoName, "Shape"))
				{
					return CreateShape;
				} else if (!strcmp(protoName, "Script"))
				{
					return CreateScript;
				} else if (!strcmp(protoName, "Sphere"))
				{
					return CreateSphere;
				} else if (!strcmp(protoName, "Switch"))
				{
					return CreateSwitch;
				} else if (!strcmp(protoName, "SpotLight"))
				{
					return CreateSpotLight;
				} else if (!strcmp(protoName, "ScalarInterpolator"))
				{
					return CreateScalarInterpolator;
				} else if (!strcmp(protoName, "SphereSensor"))
				{
					return CreateSphereSensor;
				} else if (!strcmp(protoName, "Sound"))
				{
					return CreateSound;
				}
			}
			break;
		case 'T':
			{
				if (!strcmp(protoName, "Transform"))
				{
					return CreateTransform;
				} else if (!strcmp(protoName, "TimeSensor"))
				{
					return CreateTimeSensor;
				} else if (!strcmp(protoName, "TouchSensor"))
				{
					return CreateTouchSensor;
				} else if (!strcmp(protoName, "TextureCoordinate"))
				{
					return CreateTextureCoordinate;
				} else if (!strcmp(protoName, "Text"))
				{
					return CreateText;
				} else if (!strcmp(protoName, "TextureTransform"))
				{
					return CreateTextureTransform;
				}
			}
			break;
		case 'V':
			{
				if (!strcmp(protoName, "Viewpoint"))
				{
					return CreateViewpoint;
				} else if (!strcmp(protoName, "VisibilitySensor"))
				{
					return CreateVisibilitySensor;
				}
			}
			break;
		case 'W':
			{
				if (!strcmp(protoName, "WorldInfo"))
				{
					return CreateWorldInfo;
				}
			}
			break;
	}
	return NULL;
}

