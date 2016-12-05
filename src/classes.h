#ifndef __CLASSES_H3D
#define __CLASSES_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

// Predeclare important classes to ease compile

// Basic Nodes
class vrNode;
class vrBrowser;
class vrEvent;
class vrRoute;

// Appearance Nodes
class vrAppearance;
class vrFontStyle;
class vrMaterial;
class vrImageTexture;
class vrMovieTexture;
class vrPixelTexture;
class vrTextureTransform;

// Bindable Nodes
class vrBindable;
class vrBackground;
class vrFog;
class vrNavigationInfo;
class vrViewpoint;

// Common Nodes
class vrAudioClip;
class vrLight;
class vrPointLight;
class vrDirectionalLight;
class vrSpotLight;
class vrScript;
class vrShape;
class vrSound;
class vrWorldInfo;

// Geometry Nodes
class vrGeometryNode;
class vrBox;
class vrCone;
class vrCylinder;
class vrElevationGrid;
class vrExtrusion;
class vrIndexedFaceSet;
class vrIndexedLineSet;
class vrPointSet;
class vrSphere;
class vrText;
class vrDataSet;
class vrColor;
class vrCoordinate;
class vrNormal;
class vrTextureCoordinate;

// Geometry Support
class vrSolid;
class vrFace;
class vrLoop;
class vrEdge;
class vrHalfEdge;
class vrVertex;

// Grouping Nodes
class vrGroupingNode;
class vrAnchor;
class vrBillboard;
class vrCollision;
class vrGroup;
class vrInline;
class vrLOD;
class vrSwitch;
class vrTransform;

// Interpolator Nodes
class vrInterpolator;
class vrColorInterpolator;
class vrCoordinateInterpolator;
class vrNormalInterpolator;
class vrOrientationInterpolator;
class vrPositionInterpolator;
class vrScalarInterpolator;

// Sensor Nodes
class vrSensor;
class vrPointingDeviceSensor;
class vrCylinderSensor;
class vrPlaneSensor;
class vrProximitySensor;
class vrSphereSensor;
class vrTimeSensor;
class vrTouchSensor;
class vrVisibilitySensor;

#endif
