#error Should do a flush in PostTraverse

//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "WriteTraverser.h"
#include "Browser\Browser.h"
#include "Nodes\AllNodes.h"
#include "Browser\Route.h"

#include "WriteTraverser.cxx"

IMPLEMENT_NODE(vrWriteTraverser, vrTraverser);

void vrWriteTraverser::PreTraverse()
{
	dc << "#VRML V2.0 utf8\n\n";
	dc << "#\n";
	dc << "# Exported by VRaniML(tm) VRML 2.0 C++ Class Library v0.9.04\n";
	dc << "# Copyright (c) 1997-1999 by Great Hill Corporation\n";
	dc << "# website: www.greathill.com\n";
	dc << "# email:   info@greathill.com\n";
	dc << "# phone:   (800) 949-3334\n";
	dc << "#\n\n";
}	

vrWriteTraverser::vrWriteTraverser(vrBrowser *b, void *h) : vrTraverser(b, h)
{
	skipit=FALSE;
	m_Verbose = 0;
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrAppearance *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("material")) DumpField("material", node->GetMaterial());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texture")) DumpField("texture", node->GetTexture());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("textureTransform")) DumpField("textureTransform", node->GetTextureTransform());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrFontStyle *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("family")) DumpField("family", node->GetFamily());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("horizontal")) DumpField("horizontal", node->GetHorizontal());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("justify")) DumpField("justify", node->GetJustifyArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("language")) DumpField("language", node->GetLanguage());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("leftToRight")) DumpField("leftToRight", node->GetLeftToRight());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("size")) DumpField("size", node->GetSize());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("spacing")) DumpField("spacing", node->GetSpacing());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("style")) DumpField("style", node->GetStyle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("topToBottom")) DumpField("topToBottom", node->GetTopToBottom());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrImageTexture *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("repeatS")) DumpField("repeatS", node->GetRepeatS());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("repeatT")) DumpField("repeatT", node->GetRepeatT());
	//non-native field m_Format not written
	//non-native field m_ColorBuffer not written


	// dump class fields
	//non-native field m_OrigUrl not written
#ifdef FULL_VERSION // full version supports rendering
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("url")) DumpField("url", node->GetOrigUrlArray());
#else
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("url")) DumpField("url", node->GetUrlArray());
#endif

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrMaterial *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ambientIntensity")) DumpField("ambientIntensity", node->GetAmbientIntensity());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("diffuseColor")) DumpField("diffuseColor", node->GetDiffuseColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("emissiveColor")) DumpField("emissiveColor", node->GetEmissiveColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("shininess")) DumpField("shininess", node->GetShininess());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("specularColor")) DumpField("specularColor", node->GetSpecularColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("transparency")) DumpField("transparency", node->GetTransparency());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrMovieTexture *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("repeatS")) DumpField("repeatS", node->GetRepeatS());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("repeatT")) DumpField("repeatT", node->GetRepeatT());
	//non-native field m_Format not written
	//non-native field m_ColorBuffer not written


	// dump class fields
	//non-native field m_OrigUrl not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("loop")) DumpField("loop", node->GetLoop());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("speed")) DumpField("speed", node->GetSpeed());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("startTime")) DumpField("startTime", node->GetStartTime());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("stopTime")) DumpField("stopTime", node->GetStopTime());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("url")) DumpField("url", node->GetOrigUrlArray());
	//eventOut m_Duration not written
	//eventOut m_IsActive not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrPixelTexture *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("repeatS")) DumpField("repeatS", node->GetRepeatS());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("repeatT")) DumpField("repeatT", node->GetRepeatT());
	//non-native field m_Format not written
	//non-native field m_ColorBuffer not written

	if (TRUE) // assume its not default ((m_Verbose&ALL_FIELDS) || !node->IsDefault("image"))
	{
		dc << dc.Indent() << "image" << endl;
		dc.m_nIndents++;
#ifdef _DEBUG
	if (node->m_NodeType!=vrNode::normalNode)
		dc << "# nodeType: " << node->m_NodeType << endl;
#endif

		SFImage img;
		img.m_Width       = node->GetWidth();
		img.m_Height      = node->GetHeight();
		img.m_nComponents = node->GetNComponents();
		img.m_ColorData   = node->GetColorBuffer();
		dc << img;
		img.m_ColorData   = NULL;
		dc.m_nIndents--;
	}
/*
	long w = node->GetWidth();
	long h = node->GetHeight();
	dc << dc.Indent() << "image " << w << " " << h << node->GetNComponents() << "\n";
	if (node->GetColorBuffer())
	{	
		dc.m_nIndents++;
			for (int i=0;i<w;i++)
			{
				for (int j=0;j<h;j++)
				{
					long val = ((long *)node->GetColorBuffer())[i*w+j];
					dc << dc.Indent() << ((long)(void *)val) << " ";
				}
				dc << "\n";
			}
		dc.m_nIndents--;
	}
*/

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrTextureTransform *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("center")) DumpField("center", node->GetCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("rotation")) DumpField("rotation", node->GetRotation());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("scale")) DumpField("scale", node->GetScale());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("translation")) DumpField("translation", node->GetTranslation());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrBindable *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	//eventIn m_Bind not written
	//eventOut m_IsBound not written
	//non-native field m_BoundTo not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrBackground *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	//eventIn m_Bind not written
	//eventOut m_IsBound not written
	//non-native field m_BoundTo not written


	// dump class fields
	//non-native field m_OrigBackUrl not written
	//non-native field m_OrigBottomUrl not written
	//non-native field m_OrigFrontUrl not written
	//non-native field m_OrigLeftUrl not written
	//non-native field m_OrigRightUrl not written
	//non-native field m_OrigTopUrl not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("groundAngle")) DumpField("groundAngle", node->GetGroundAngleArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("groundColor")) DumpField("groundColor", node->GetGroundColorArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("backUrl")) DumpField("backUrl", node->GetOrigBackUrlArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bottomUrl")) DumpField("bottomUrl", node->GetOrigBottomUrlArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("frontUrl")) DumpField("frontUrl", node->GetOrigFrontUrlArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("leftUrl")) DumpField("leftUrl", node->GetOrigLeftUrlArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("rightUrl")) DumpField("rightUrl", node->GetOrigRightUrlArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("topUrl")) DumpField("topUrl", node->GetOrigTopUrlArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("skyAngle")) DumpField("skyAngle", node->GetSkyAngleArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("skyColor")) DumpField("skyColor", node->GetSkyColorArray());
	//non-native field m_BackgroundGroup not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrFog *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	//eventIn m_Bind not written
	//eventOut m_IsBound not written
	//non-native field m_BoundTo not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("fogType")) DumpField("fogType", node->GetFogType());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("visibilityRange")) DumpField("visibilityRange", node->GetVisibilityRange());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrNavigationInfo *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	//eventIn m_Bind not written
	//eventOut m_IsBound not written
	//non-native field m_BoundTo not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("avatarSize")) DumpField("avatarSize", node->GetAvatarSizeArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("headlight")) DumpField("headlight", node->GetHeadlight());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("speed")) DumpField("speed", node->GetSpeed());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("type")) DumpField("type", node->GetTypeArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("visibilityLimit")) DumpField("visibilityLimit", node->GetVisibilityLimit());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrViewpoint *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	//eventIn m_Bind not written
	//eventOut m_IsBound not written
	//non-native field m_BoundTo not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("fieldOfView")) DumpField("fieldOfView", node->GetFieldOfView());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("jump")) DumpField("jump", node->GetJump());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("orientation")) DumpField("orientation", node->GetOrientation());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("position")) DumpField("position", node->GetPosition());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("description")) DumpField("description", node->GetDescription());
	//eventOut m_BindTime not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrAudioClip *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	//non-native field m_OrigUrl not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("description")) DumpField("description", node->GetDescription());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("loop")) DumpField("loop", node->GetLoop());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("pitch")) DumpField("pitch", node->GetPitch());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("startTime")) DumpField("startTime", node->GetStartTime());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("stopTime")) DumpField("stopTime", node->GetStopTime());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("url")) DumpField("url", node->GetOrigUrlArray());
	//eventOut m_Duration not written
	//eventOut m_IsActive not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrDirectionalLight *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("on")) DumpField("on", node->GetOn());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("intensity")) DumpField("intensity", node->GetIntensity());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ambientIntensity")) DumpField("ambientIntensity", node->GetAmbientIntensity());
	//non-native field m_LightID not written
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("attenuation")) DumpField("attenuation", node->GetAttenuation());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("direction")) DumpField("direction", node->GetDirection());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrLight *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("on")) DumpField("on", node->GetOn());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("intensity")) DumpField("intensity", node->GetIntensity());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ambientIntensity")) DumpField("ambientIntensity", node->GetAmbientIntensity());
	//non-native field m_LightID not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("attenuation")) DumpField("attenuation", node->GetAttenuation());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrPointLight *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("on")) DumpField("on", node->GetOn());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("intensity")) DumpField("intensity", node->GetIntensity());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ambientIntensity")) DumpField("ambientIntensity", node->GetAmbientIntensity());
	//non-native field m_LightID not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("attenuation")) DumpField("attenuation", node->GetAttenuation());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("location")) DumpField("location", node->GetLocation());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("radius")) DumpField("radius", node->GetRadius());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrScript *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node, TRUE);
	
	// dump class fields
	//non-native field m_OrigUrl not written

	if (m_Verbose&ALL_FIELDS || !node->IsDefault("url")) DumpField("url", node->GetOrigUrlArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("directOutput")) DumpField("directOutput", node->GetDirectOutput());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("mustEvaluate")) DumpField("mustEvaluate", node->GetMustEvaluate());

	DumpFieldList(dc,node->GetFieldList(),FALSE,TRUE,node);

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrShape *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("appearance")) DumpField("appearance", node->GetAppearance());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("geometry")) DumpField("geometry", node->GetGeometry());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrSound *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("direction")) DumpField("direction", node->GetDirection());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("intensity")) DumpField("intensity", node->GetIntensity());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("location")) DumpField("location", node->GetLocation());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("maxBack")) DumpField("maxBack", node->GetMaxBack());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("maxFront")) DumpField("maxFront", node->GetMaxFront());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("minBack")) DumpField("minBack", node->GetMinBack());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("minFront")) DumpField("minFront", node->GetMinFront());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("priority")) DumpField("priority", node->GetPriority());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("source")) DumpField("source", node->GetSource());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("spatialize")) DumpField("spatialize", node->GetSpatialize());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrSpotLight *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("on")) DumpField("on", node->GetOn());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("intensity")) DumpField("intensity", node->GetIntensity());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ambientIntensity")) DumpField("ambientIntensity", node->GetAmbientIntensity());
	//non-native field m_LightID not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("attenuation")) DumpField("attenuation", node->GetAttenuation());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("beamWidth")) DumpField("beamWidth", node->GetBeamWidth());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("cutOffAngle")) DumpField("cutOffAngle", node->GetCutOffAngle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("direction")) DumpField("direction", node->GetDirection());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("location")) DumpField("location", node->GetLocation());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("radius")) DumpField("radius", node->GetRadius());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrWorldInfo *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("info")) DumpField("info", node->GetInfoArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("title")) DumpField("title", node->GetTitle());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrGroupingNode *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxCenter")) DumpField("bboxCenter", node->GetBboxCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxSize")) DumpField("bboxSize", node->GetBboxSize());

	TraverseChildren(node);

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrAnchor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxCenter")) DumpField("bboxCenter", node->GetBboxCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxSize")) DumpField("bboxSize", node->GetBboxSize());


	// dump class fields
	//non-native field m_OrigUrl not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("description")) DumpField("description", node->GetDescription());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("parameter")) DumpField("parameter", node->GetParameterArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("url")) DumpField("url", node->GetOrigUrlArray());

	TraverseChildren(node);

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrBillboard *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxCenter")) DumpField("bboxCenter", node->GetBboxCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxSize")) DumpField("bboxSize", node->GetBboxSize());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("axisOfRotation")) DumpField("axisOfRotation", node->GetAxisOfRotation());

	TraverseChildren(node);

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrCollision *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxCenter")) DumpField("bboxCenter", node->GetBboxCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxSize")) DumpField("bboxSize", node->GetBboxSize());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("collide")) DumpField("collide", node->GetCollide());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("proxy")) DumpField("proxy", node->GetProxy());
	//eventOut m_CollideTime not written

	TraverseChildren(node);

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrGroup *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxCenter")) DumpField("bboxCenter", node->GetBboxCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxSize")) DumpField("bboxSize", node->GetBboxSize());


	TraverseChildren(node);

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrTransform *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxCenter")) DumpField("bboxCenter", node->GetBboxCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxSize")) DumpField("bboxSize", node->GetBboxSize());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("center")) DumpField("center", node->GetCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("rotation")) DumpField("rotation", node->GetRotation());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("scale")) DumpField("scale", node->GetScale());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("scaleOrientation")) DumpField("scaleOrientation", node->GetScaleOrientation());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("translation")) DumpField("translation", node->GetTranslation());

	TraverseChildren(node);

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrInline *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxCenter")) DumpField("bboxCenter", node->GetBboxCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bboxSize")) DumpField("bboxSize", node->GetBboxSize());


	// dump class fields
	//non-native field m_OrigUrl not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("url")) DumpField("url", node->GetOrigUrlArray());

//	TraverseChildren(node);

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrLOD *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	//non-native field m_ActiveLevel not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("level")) DumpField("level", node->GetLevelArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("center")) DumpField("center", node->GetCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("range")) DumpField("range", node->GetRangeArray());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrSwitch *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("choice")) DumpField("choice", node->GetChoiceArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("whichChoice")) DumpField("whichChoice", node->GetWhichChoice());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrGeometryNode *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrBox *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("size")) DumpField("size", node->GetSize());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrCone *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bottomRadius")) DumpField("bottomRadius", node->GetBottomRadius());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("height")) DumpField("height", node->GetHeight());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("side")) DumpField("side", node->GetSide());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bottom")) DumpField("bottom", node->GetBottom());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrCylinder *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("bottom")) DumpField("bottom", node->GetBottom());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("height")) DumpField("height", node->GetHeight());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("radius")) DumpField("radius", node->GetRadius());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("side")) DumpField("side", node->GetSide());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("top")) DumpField("top", node->GetTop());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrExtrusion *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("beginCap")) DumpField("beginCap", node->GetBeginCap());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("crossSection")) DumpField("crossSection", node->GetCrossSectionArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("endCap")) DumpField("endCap", node->GetEndCap());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("orientation")) DumpField("orientation", node->GetOrientationArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("scale")) DumpField("scale", node->GetScaleArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("spine")) DumpField("spine", node->GetSpineArray());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrSphere *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("radius")) DumpField("radius", node->GetRadius());
	//non-native field m_Slices not written
	//non-native field m_Stacks not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrText *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("string")) DumpField("string", node->GetStringArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("fontStyle")) DumpField("fontStyle", node->GetFontStyle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("length")) DumpField("length", node->GetLengthArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("maxExtent")) DumpField("maxExtent", node->GetMaxExtent());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrDataSet *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorPerVertex")) DumpField("colorPerVertex", node->GetColorPerVertex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalPerVertex")) DumpField("normalPerVertex", node->GetNormalPerVertex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorIndex")) DumpField("colorIndex", node->GetColorIndexArray(), !node->GetColorPerVertex()*4);
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coordIndex")) DumpField("coordIndex", node->GetCoordIndexArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalIndex")) DumpField("normalIndex", node->GetNormalIndexArray(), !node->GetNormalPerVertex()*4);
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoordIndex")) DumpField("texCoordIndex", node->GetTexCoordIndexArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coord")) DumpField("coord", node->GetCoord());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normal")) DumpField("normal", node->GetNormal());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoord")) DumpField("texCoord", node->GetTexCoord());
	//eventIn m_ColorIndexEv not written
	//eventIn m_CoordIndexEv not written
	//eventIn m_NormalIndexEv not written
	//eventIn m_TexCoordIndexEv not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrElevationGrid *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorPerVertex")) DumpField("colorPerVertex", node->GetColorPerVertex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalPerVertex")) DumpField("normalPerVertex", node->GetNormalPerVertex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorIndex")) DumpField("colorIndex", node->GetColorIndexArray(), !node->GetColorPerVertex()*4);
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coordIndex")) DumpField("coordIndex", node->GetCoordIndexArray());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalIndex")) DumpField("normalIndex", node->GetNormalIndexArray(), !node->GetNormalPerVertex()*4);
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoordIndex")) DumpField("texCoordIndex", node->GetTexCoordIndexArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coord")) DumpField("coord", node->GetCoord());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normal")) DumpField("normal", node->GetNormal());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoord")) DumpField("texCoord", node->GetTexCoord());
	//eventIn m_ColorIndexEv not written
	//eventIn m_CoordIndexEv not written
	//eventIn m_NormalIndexEv not written
	//eventIn m_TexCoordIndexEv not written

	// dump grandparent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	// dump class fields
	//eventIn m_SetHeight not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("height")) DumpField("height", node->GetHeightArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("xDimension")) DumpField("xDimension", node->GetXDimension());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("xSpacing")) DumpField("xSpacing", node->GetXSpacing());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("zDimension")) DumpField("zDimension", node->GetZDimension());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("zSpacing")) DumpField("zSpacing", node->GetZSpacing());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrIndexedFaceSet *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorPerVertex")) DumpField("colorPerVertex", node->GetColorPerVertex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalPerVertex")) DumpField("normalPerVertex", node->GetNormalPerVertex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorIndex")) DumpField("colorIndex", node->GetColorIndexArray(), !node->GetColorPerVertex()*4);
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coordIndex")) DumpField("coordIndex", node->GetCoordIndexArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalIndex")) DumpField("normalIndex", node->GetNormalIndexArray(), !node->GetNormalPerVertex()*4);
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoordIndex")) DumpField("texCoordIndex", node->GetTexCoordIndexArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coord")) DumpField("coord", node->GetCoord());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normal")) DumpField("normal", node->GetNormal());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoord")) DumpField("texCoord", node->GetTexCoord());
	//eventIn m_ColorIndexEv not written
	//eventIn m_CoordIndexEv not written
	//eventIn m_NormalIndexEv not written
	//eventIn m_TexCoordIndexEv not written

	// dump grandparent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrIndexedLineSet *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorPerVertex")) DumpField("colorPerVertex", node->GetColorPerVertex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalPerVertex")) DumpField("normalPerVertex", node->GetNormalPerVertex());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorIndex")) DumpField("colorIndex", node->GetColorIndexArray(), !node->GetColorPerVertex()*4);
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coordIndex")) DumpField("coordIndex", node->GetCoordIndexArray());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalIndex")) DumpField("normalIndex", node->GetNormalIndexArray(), !node->GetNormalPerVertex()*4);
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoordIndex")) DumpField("texCoordIndex", node->GetTexCoordIndexArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coord")) DumpField("coord", node->GetCoord());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normal")) DumpField("normal", node->GetNormal());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoord")) DumpField("texCoord", node->GetTexCoord());
	//eventIn m_ColorIndexEv not written
	//eventIn m_CoordIndexEv not written
	//eventIn m_NormalIndexEv not written
	//eventIn m_TexCoordIndexEv not written

	// dump grandparent class fields
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrPointSet *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorPerVertex")) DumpField("colorPerVertex", node->GetColorPerVertex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalPerVertex")) DumpField("normalPerVertex", node->GetNormalPerVertex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("colorIndex")) DumpField("colorIndex", node->GetColorIndexArray(), !node->GetColorPerVertex()*4);
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coordIndex")) DumpField("coordIndex", node->GetCoordIndexArray());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normalIndex")) DumpField("normalIndex", node->GetNormalIndexArray(), !node->GetNormalPerVertex()*4);
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoordIndex")) DumpField("texCoordIndex", node->GetTexCoordIndexArray());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColor());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("coord")) DumpField("coord", node->GetCoord());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("normal")) DumpField("normal", node->GetNormal());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("texCoord")) DumpField("texCoord", node->GetTexCoord());
	//eventIn m_ColorIndexEv not written
	//eventIn m_CoordIndexEv not written
	//eventIn m_NormalIndexEv not written
	//eventIn m_TexCoordIndexEv not written

	// dump grandparent class fields
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("ccw")) DumpField("ccw", node->GetCcw());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("convex")) DumpField("convex", node->GetConvex());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("creaseAngle")) DumpField("creaseAngle", node->GetCreaseAngle());
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("solid")) DumpField("solid", node->GetSolid());
	//non-native field m_Geom not written
	//non-native field m_Native not written


	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrColor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("color")) DumpField("color", node->GetColorArray());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrCoordinate *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("point")) DumpField("point", node->GetPointArray());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrNormal *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("vector")) DumpField("vector", node->GetVectorArray());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrTextureCoordinate *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("point")) DumpField("point", node->GetPointArray());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrInterpolator *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("key")) DumpField("key", node->GetKeyArray());

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrColorInterpolator *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("key")) DumpField("key", node->GetKeyArray());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("keyValue")) DumpField("keyValue", node->GetKeyValueArray());
	//eventIn m_Fraction not written
	//eventOut m_Value not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrCoordinateInterpolator *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("key")) DumpField("key", node->GetKeyArray());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("keyValue")) DumpField("keyValue", node->GetKeyValueArray());
	//eventIn m_Fraction not written
	//eventOut m_Value not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrNormalInterpolator *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("key")) DumpField("key", node->GetKeyArray());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("keyValue")) DumpField("keyValue", node->GetKeyValueArray());
	//eventIn m_Fraction not written
	//eventOut m_Value not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrOrientationInterpolator *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("key")) DumpField("key", node->GetKeyArray());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("keyValue")) DumpField("keyValue", node->GetKeyValueArray());
	//eventIn m_Fraction not written
	//eventOut m_Value not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrPositionInterpolator *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("key")) DumpField("key", node->GetKeyArray());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("keyValue")) DumpField("keyValue", node->GetKeyValueArray());
	//eventIn m_Fraction not written
	//eventOut m_Value not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrScalarInterpolator *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("key")) DumpField("key", node->GetKeyArray());


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("keyValue")) DumpField("keyValue", node->GetKeyValueArray());
	//eventIn m_Fraction not written
	//eventOut m_Value not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrSensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrPointingDeviceSensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written


	// dump class fields
	//non-native field m_FirstPoint not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("autoOffset")) DumpField("autoOffset", node->GetAutoOffset());
	//eventOut m_TrackPoint not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrCylinderSensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	//non-native field m_FirstPoint not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("autoOffset")) DumpField("autoOffset", node->GetAutoOffset());
	//eventOut m_TrackPoint not written

	// dump grandparent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("offset")) DumpField("offset", node->GetOffset());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("diskAngle")) DumpField("diskAngle", node->GetDiskAngle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("maxAngle")) DumpField("maxAngle", node->GetMaxAngle());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("minAngle")) DumpField("minAngle", node->GetMinAngle());
	//eventOut m_Rotation not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrPlaneSensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	//non-native field m_FirstPoint not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("autoOffset")) DumpField("autoOffset", node->GetAutoOffset());
	//eventOut m_TrackPoint not written

	// dump grandparent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("offset")) DumpField("offset", node->GetOffset());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("maxPosition")) DumpField("maxPosition", node->GetMaxPosition());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("minPosition")) DumpField("minPosition", node->GetMinPosition());
	//eventOut m_Translation not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrProximitySensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("center")) DumpField("center", node->GetCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("size")) DumpField("size", node->GetSize());
	//eventOut m_Position not written
	//eventOut m_Orientation not written
	//eventOut m_EnterTime not written
	//eventOut m_ExitTime not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrSphereSensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	//non-native field m_FirstPoint not written
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("autoOffset")) DumpField("autoOffset", node->GetAutoOffset());
	//eventOut m_TrackPoint not written

	// dump grandparent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("offset")) DumpField("offset", node->GetOffset());
	//eventOut m_Rotation not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrTimeSensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("cycleInterval")) DumpField("cycleInterval", node->GetCycleInterval());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("loop")) DumpField("loop", node->GetLoop());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("startTime")) DumpField("startTime", node->GetStartTime());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("stopTime")) DumpField("stopTime", node->GetStopTime());
	//eventOut m_CycleTime not written
	//eventOut m_Fraction not written
	//eventOut m_Time not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrTouchSensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	//non-native field m_FirstPoint not written
//	if (m_Verbose&ALL_FIELDS || !node->IsDefault("autoOffset")) DumpField("autoOffset", node->GetAutoOffset());
	//eventOut m_TrackPoint not written

	// dump grandparent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written


	// dump class fields
	//eventOut m_HitNormal not written
	//eventOut m_HitPoint not written
	//eventOut m_HitTexCoord not written
	//eventOut m_IsOver not written
	//eventOut m_TouchTime not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

//-------------------------------------------------------------------
void vrWriteTraverser::Traverse(const vrVisibilitySensor *node)
{
	if (WriteHead(node)) return;
	dc.m_nIndents++;

	DumpIsMappings(dc, node);
	
	// dump parent class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("enabled")) DumpField("enabled", node->GetEnabled());
	//eventOut m_IsActive not written


	// dump class fields
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("center")) DumpField("center", node->GetCenter());
	if (m_Verbose&ALL_FIELDS || !node->IsDefault("size")) DumpField("size", node->GetSize());
	//eventOut m_EnterTime not written
	//eventOut m_ExitTime not written

	dc.m_nIndents--;
	dc << dc.Indent() << "}\n";
}

