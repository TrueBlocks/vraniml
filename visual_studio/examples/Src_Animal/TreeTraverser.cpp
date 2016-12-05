//-------------------------------------------------------------------------
// Copyright (c) 1997 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Stdafx.h"

#include "TreeTraverser.h"

#include <afxcmn.h>

IMPLEMENT_NODE(vrTreeTraverser, vrTraverser);

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
vrTreeTraverser::vrTreeTraverser(vrBrowser *b, CTreeCtrl *t) : vrTraverser(b, t->m_hWnd)
{
	tos   = 0;
	tree  = t;
	tree->DeleteAllItems();
}

void vrTreeTraverser::PreTraverse()
{
}	

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
char *GetName(const vrNode *node)
{
	static char ss[256];
	vrRuntimeClass *pClass = node->GetRuntimeClass();
	char *s = pClass->m_ClassName;
	if (strlen(s)>3)
	{
		s++; s++;
	}
	if (!node->GetName())
	{
		sprintf(ss, "%s", s);
	} else
	{
		sprintf(ss, "%s (%s)", s, (char*)node->GetName());
	}
	return ss;
}

SFBool vrTreeTraverser::WriteHead(const vrNode *node)
{
	itemStack[tos+1] = tree->InsertItem(GetName(node), itemStack[tos]);
	return 1;
}

//----------------------------------------------------------------------------------------------------------------------
void vrTreeTraverser::TraverseChildren(const vrGroupingNode *node)
{
	itemStack[tos+1] = tree->InsertItem("children", itemStack[tos]);

	if (node->GetChildren())
	{
		tos++;
		LISTPOS pos = node->GetChildren()->GetHeadPosition();
		while (pos)
		{
			SFNode ob = node->GetChildren()->GetNext(pos);
			ob->Traverse(this);
		}
		tos--;
	}
}

void vrTreeTraverser::DumpRoutes(const vrBrowser* browser)
{
/*
	if (!browser->m_RouteMap.GetCount())
	{
		itemStack[tos+1] = tree->InsertItem("ROUTES: None", TVI_ROOT);
	} else
	{
		itemStack[tos+1] = tree->InsertItem("ROUTES", TVI_ROOT);

		tos++;
		
		LISTPOS pos = browser->m_RouteMap.GetHeadPosition();
		while (pos)
		{
			SFNode ob;
			vrRouteList *list=NULL;
			browser->m_RouteMap.GetNext(pos, ob, list);
			if (list)
			{
				LISTPOS ppos = list->GetHeadPosition();
				while (ppos)
				{
					vrRoute *route = list->GetNext(ppos);
					if (route && !route->m_Internal)
					{
						char str[500];
						sprintf(str, "%s.%s TO %s.%s", 
							((route->m_SourceNode) ? route->m_SourceNode->GetName() : NULL),
							route->GetFieldName(0),
							((route->m_DestNode) ? route->m_DestNode->GetName() : NULL),
							route->GetFieldName(1));
						tree->InsertItem(str, itemStack[tos]);
					}
				}
			}
		}
		tos++;
	}
*/
}

void vrTreeTraverser::Traverse(const vrBrowser *node)
{
	itemStack[tos] = tree->InsertItem("Scene Graph", TVI_ROOT);

//	WriteHead(node);

	TraverseChildren(node);

	DumpRoutes(node);

	tree->Expand(itemStack[0], TVE_EXPAND);
	tree->SelectItem(itemStack[0]);
}

void vrTreeTraverser::DumpField(char *fieldName, const MFColor& val, int nPerRow)
{
	char str[256];
	sprintf(str, "%s: %d items", fieldName, val.GetCount());
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const MFFloat& val, int nPerRow)
{
	char str[256];
	sprintf(str, "%s: %d items", fieldName, val.GetCount());
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const MFInt32& val, int nPerRow)
{
	char str[256];
	sprintf(str, "%s: %d items", fieldName, val.GetCount());
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const MFString& val, int nPerRow)
{
	char str[256];
	sprintf(str, "%s: %d items", fieldName, val.GetCount());
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const MFVec2f& val, int nPerRow)
{
	char str[256];
	sprintf(str, "%s: %d items", fieldName, val.GetCount());
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const MFVec3f& val, int nPerRow)
{
	char str[256];
	sprintf(str, "%s: %d items", fieldName, val.GetCount());
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const MFRotation& val, int nPerRow)
{
	char str[256];
	sprintf(str, "%s: %d items", fieldName, val.GetCount());
	tree->InsertItem(str, itemStack[tos]);
}

void vrTreeTraverser::DO_NODE(char *fieldName, const vrNode *node)
{
	if (node)
	{
		char str[256];
		sprintf(str, "%s", fieldName);
		itemStack[tos+1] = tree->InsertItem(str, itemStack[tos]);
		tos++;
		node->Traverse(this);
		tos--;
	} else
	{
		char str[256];
		sprintf(str, "%s NULL", fieldName);
		itemStack[tos+1] = tree->InsertItem(str, itemStack[tos]);
	}
}

void vrTreeTraverser::DumpField(char *fieldName, const MFNode& val)
{
	//DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrAppearance* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrAudioClip* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrColor* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrCoordinate* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrFontStyle* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrGeometryNode* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrMaterial* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrNormal* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrPixelTexture* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrTextureTransform* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const vrTextureCoordinate* val)
{
	DO_NODE(fieldName, val);
}
void vrTreeTraverser::DumpField(char *fieldName, const SFNode val)
{
	DO_NODE(fieldName, val);
}

void vrTreeTraverser::DumpField(char *fieldName, SFInt32 val)
{
	char str[256];
	sprintf(str, "%s: %d", fieldName, val);
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, SFBool val)
{
	char str[256];
	sprintf(str, "%s: %s", fieldName, ((val) ? "TRUE" : "FALSE"));
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const SFColor& val)
{
	char str[256];
	sprintf(str, "%s: %f %f %f", fieldName, val.x, val.y, val.z);
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const char *val)
{
	char str[256];
	sprintf(str, "%s: %s", fieldName, ((val) ? val : "NULL"));
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, SFFloat val)
{
	char str[256];
	sprintf(str, "%s: %f", fieldName, val);
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const SFVec3f& val)
{
	char str[256];
	sprintf(str, "%s: %f %f %f", fieldName, val.x, val.y, val.z);
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const SFVec2f& val)
{
	char str[256];
	sprintf(str, "%s: %f %f", fieldName, val.x, val.y);
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, const SFRotation& val)
{
	char str[256];
	sprintf(str, "%s: %f %f %f %f", fieldName, val.x, val.y, val.z, val.w);
	tree->InsertItem(str, itemStack[tos]);
}
void vrTreeTraverser::DumpField(char *fieldName, SFTime val)
{
	char str[256];
	sprintf(str, "%s: %f", fieldName, val);
	tree->InsertItem(str, itemStack[tos]);
}

void vrTreeTraverser::Traverse(const vrEvent *node)
{
}

void vrTreeTraverser::Traverse(const vrNode *node)
{
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrAppearance *node)
{
	WriteHead(node);

	tos++;

	DumpField("material", node->GetMaterial());
	DumpField("texture", node->GetTexture());
	DumpField("textureTransform", node->GetTextureTransform());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrFontStyle *node)
{
	WriteHead(node);

	tos++;

	DumpField("family", node->GetFamily());
	DumpField("horizontal", node->GetHorizontal());
	DumpField("justify", node->GetJustifyArray());
	DumpField("language", node->GetLanguage());
	DumpField("leftToRight", node->GetLeftToRight());
	DumpField("size", node->GetSize());
	DumpField("spacing", node->GetSpacing());
	DumpField("style", node->GetStyle());
	DumpField("topToBottom", node->GetTopToBottom());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrImageTexture *node)
{
	WriteHead(node);

	tos++;

	DumpField("repeatS", node->GetRepeatS());
	DumpField("repeatT", node->GetRepeatT());
	DumpField("url", node->GetOrigUrlArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrMaterial *node)
{
	WriteHead(node);

	tos++;

	DumpField("ambientIntensity", node->GetAmbientIntensity());
	DumpField("diffuseColor", node->GetDiffuseColor());
	DumpField("emissiveColor", node->GetEmissiveColor());
	DumpField("shininess", node->GetShininess());
	DumpField("specularColor", node->GetSpecularColor());
	DumpField("transparency", node->GetTransparency());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrMovieTexture *node)
{
	WriteHead(node);

	tos++;

	DumpField("repeatS", node->GetRepeatS());
	DumpField("repeatT", node->GetRepeatT());
	DumpField("loop", node->GetLoop());
	DumpField("speed", node->GetSpeed());
	DumpField("startTime", node->GetStartTime());
	DumpField("stopTime", node->GetStopTime());
	DumpField("url", node->GetOrigUrlArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrPixelTexture *node)
{
	WriteHead(node);

	tos++;

	DumpField("repeatS", node->GetRepeatS());
	DumpField("repeatT", node->GetRepeatT());

//	long w = node->GetWidth();
//	long h = node->GetHeight();
//	dc << tos() << "image " << w << " " << h << node->GetNComponents() << "\n";

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrTextureTransform *node)
{
	WriteHead(node);

	tos++;

	DumpField("center", node->GetCenter());
	DumpField("rotation", node->GetRotation());
	DumpField("scale", node->GetScale());
	DumpField("translation", node->GetTranslation());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrBindable *node)
{
	WriteHead(node);

	tos++;
	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrBackground *node)
{
	WriteHead(node);

	tos++;

	DumpField("groundAngle", node->GetGroundAngleArray());
	DumpField("groundColor", node->GetGroundColorArray());
	DumpField("backUrl", node->GetOrigBackUrlArray());
	DumpField("bottomUrl", node->GetOrigBottomUrlArray());
	DumpField("frontUrl", node->GetOrigFrontUrlArray());
	DumpField("leftUrl", node->GetOrigLeftUrlArray());
	DumpField("rightUrl", node->GetOrigRightUrlArray());
	DumpField("topUrl", node->GetOrigTopUrlArray());
	DumpField("skyAngle", node->GetSkyAngleArray());
	DumpField("skyColor", node->GetSkyColorArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrFog *node)
{
	WriteHead(node);

	tos++;

	DumpField("color", node->GetColor());
	DumpField("fogType", node->GetFogType());
	DumpField("visibilityRange", node->GetVisibilityRange());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrNavigationInfo *node)
{
	// Don't write the browser created navigation info
	if (node->GetName() && !strcmp(node->GetName(), "_?BROWSER_NAV")) return;

	WriteHead(node);

	tos++;

	DumpField("avatarSize", node->GetAvatarSizeArray());
	DumpField("headlight", node->GetHeadlight());
	DumpField("speed", node->GetSpeed());
	DumpField("type", node->GetTypeArray());
	DumpField("visibilityLimit", node->GetVisibilityLimit());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrViewpoint *node)
{
	// Don't write the browser created viewpoint
	if (node->GetName() && !strcmp(node->GetName(), "_?BROWSER_VP")) return;

	WriteHead(node);

	tos++;

	DumpField("fieldOfView", node->GetFieldOfView());
	DumpField("jump", node->GetJump());
	DumpField("orientation", node->GetOrientation());
	DumpField("position", node->GetPosition());
	DumpField("description", node->GetDescription());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrAudioClip *node)
{
	WriteHead(node);

	tos++;

	DumpField("description", node->GetDescription());
	DumpField("loop", node->GetLoop());
	DumpField("pitch", node->GetPitch());
	DumpField("startTime", node->GetStartTime());
	DumpField("stopTime", node->GetStopTime());
	DumpField("url", node->GetOrigUrlArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrDirectionalLight *node)
{
	WriteHead(node);

	tos++;

	DumpField("on", node->GetOn());
	DumpField("color", node->GetColor());
	DumpField("intensity", node->GetIntensity());
	DumpField("ambientIntensity", node->GetAmbientIntensity());
	DumpField("direction", node->GetDirection());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrLight *node)
{
	WriteHead(node);

	tos++;

	DumpField("on", node->GetOn());
	DumpField("color", node->GetColor());
	DumpField("intensity", node->GetIntensity());
	DumpField("ambientIntensity", node->GetAmbientIntensity());
	DumpField("attenuation", node->GetAttenuation());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrPointLight *node)
{
	WriteHead(node);

	tos++;

	DumpField("on", node->GetOn());
	DumpField("color", node->GetColor());
	DumpField("intensity", node->GetIntensity());
	DumpField("ambientIntensity", node->GetAmbientIntensity());
	DumpField("attenuation", node->GetAttenuation());
	DumpField("location", node->GetLocation());
	DumpField("radius", node->GetRadius());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrScript *node)
{
	WriteHead(node);

	tos++;

	DumpField("url", node->GetUrlArray());
	DumpField("directOutput", node->GetDirectOutput());
	DumpField("mustEvaluate", node->GetMustEvaluate());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrShape *node)
{
	WriteHead(node);

	tos++;

	DumpField("appearance", node->GetAppearance());
	DumpField("geometry", node->GetGeometry());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrSound *node)
{
	WriteHead(node);

	tos++;

	DumpField("direction", node->GetDirection());
	DumpField("intensity", node->GetIntensity());
	DumpField("location", node->GetLocation());
	DumpField("maxBack", node->GetMaxBack());
	DumpField("maxFront", node->GetMaxFront());
	DumpField("minBack", node->GetMinBack());
	DumpField("minFront", node->GetMinFront());
	DumpField("priority", node->GetPriority());
	DumpField("source", node->GetSource());
	DumpField("spatialize", node->GetSpatialize());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrSpotLight *node)
{
	WriteHead(node);

	tos++;

	DumpField("on", node->GetOn());
	DumpField("color", node->GetColor());
	DumpField("intensity", node->GetIntensity());
	DumpField("ambientIntensity", node->GetAmbientIntensity());
	DumpField("attenuation", node->GetAttenuation());
	DumpField("beamWidth", node->GetBeamWidth());
	DumpField("cutOffAngle", node->GetCutOffAngle());
	DumpField("direction", node->GetDirection());
	DumpField("location", node->GetLocation());
	DumpField("radius", node->GetRadius());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrWorldInfo *node)
{
	WriteHead(node);

	tos++;

	DumpField("info", node->GetInfoArray());
	DumpField("title", node->GetTitle());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrGroupingNode *node)
{
	WriteHead(node);

	tos++;

	DumpField("bboxCenter", node->GetBboxCenter());
	DumpField("bboxSize", node->GetBboxSize());

	TraverseChildren(node);

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrAnchor *node)
{
	WriteHead(node);

	tos++;

	DumpField("bboxCenter", node->GetBboxCenter());
	DumpField("bboxSize", node->GetBboxSize());

	DumpField("description", node->GetDescription());
	DumpField("parameter", node->GetParameterArray());
	DumpField("url", node->GetOrigUrlArray());

	TraverseChildren(node);

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrBillboard *node)
{
	WriteHead(node);

	tos++;

	DumpField("bboxCenter", node->GetBboxCenter());
	DumpField("bboxSize", node->GetBboxSize());
	DumpField("axisOfRotation", node->GetAxisOfRotation());

	TraverseChildren(node);

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrCollision *node)
{
	WriteHead(node);

	tos++;

	DumpField("bboxCenter", node->GetBboxCenter());
	DumpField("bboxSize", node->GetBboxSize());
	DumpField("collide", node->GetCollide());
	DumpField("proxy", node->GetProxy());

	TraverseChildren(node);

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrGroup *node)
{
	WriteHead(node);

	tos++;

	DumpField("bboxCenter", node->GetBboxCenter());
	DumpField("bboxSize", node->GetBboxSize());

	TraverseChildren(node);

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrTransform *node)
{
	WriteHead(node);

	tos++;

	DumpField("bboxCenter", node->GetBboxCenter());
	DumpField("bboxSize", node->GetBboxSize());
	DumpField("center", node->GetCenter());
	DumpField("rotation", node->GetRotation());
	DumpField("scale", node->GetScale());
	DumpField("scaleOrientation", node->GetScaleOrientation());
	DumpField("translation", node->GetTranslation());

	TraverseChildren(node);

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrInline *node)
{
	WriteHead(node);

	tos++;

	DumpField("bboxCenter", node->GetBboxCenter());
	DumpField("bboxSize", node->GetBboxSize());
	DumpField("url", node->GetOrigUrlArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrLOD *node)
{
	WriteHead(node);

	tos++;

	DumpField("level", node->GetLevelArray());
	DumpField("center", node->GetCenter());
	DumpField("range", node->GetRangeArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrSwitch *node)
{
	WriteHead(node);

	tos++;

	DumpField("choice", node->GetChoiceArray());
	DumpField("whichChoice", node->GetWhichChoice());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrGeometryNode *node)
{
	WriteHead(node);

	tos++;

	DumpField("ccw", node->GetCcw());
	DumpField("convex", node->GetConvex());
	DumpField("creaseAngle", node->GetCreaseAngle());
	DumpField("solid", node->GetSolid());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrBox *node)
{
	WriteHead(node);

	tos++;

	DumpField("size", node->GetSize());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrCone *node)
{
	WriteHead(node);

	tos++;

	DumpField("bottomRadius", node->GetBottomRadius());
	DumpField("height", node->GetHeight());
	DumpField("side", node->GetSide());
	DumpField("bottom", node->GetBottom());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrCylinder *node)
{
	WriteHead(node);

	tos++;

	DumpField("bottom", node->GetBottom());
	DumpField("height", node->GetHeight());
	DumpField("radius", node->GetRadius());
	DumpField("side", node->GetSide());
	DumpField("top", node->GetTop());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrExtrusion *node)
{
	WriteHead(node);

	tos++;

	DumpField("ccw", node->GetCcw());
	DumpField("convex", node->GetConvex());
	DumpField("creaseAngle", node->GetCreaseAngle());
	DumpField("solid", node->GetSolid());
	DumpField("beginCap", node->GetBeginCap());
	DumpField("crossSection", node->GetCrossSectionArray());
	DumpField("endCap", node->GetEndCap());
	DumpField("orientation", node->GetOrientationArray());
	DumpField("scale", node->GetScaleArray());
	DumpField("spine", node->GetSpineArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrSphere *node)
{
	WriteHead(node);

	tos++;

	DumpField("radius", node->GetRadius());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrText *node)
{
	WriteHead(node);

	tos++;

	DumpField("string", node->GetStringArray());
	DumpField("fontStyle", node->GetFontStyle());
	DumpField("length", node->GetLengthArray());
	DumpField("maxExtent", node->GetMaxExtent());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrDataSet *node)
{
	WriteHead(node);

	tos++;

	DumpField("ccw", node->GetCcw());
	DumpField("convex", node->GetConvex());
	DumpField("creaseAngle", node->GetCreaseAngle());
	DumpField("solid", node->GetSolid());
	DumpField("colorPerVertex", node->GetColorPerVertex());
	DumpField("normalPerVertex", node->GetNormalPerVertex());
	DumpField("colorIndex", node->GetColorIndexArray(), !node->GetColorPerVertex()*4);
	DumpField("coordIndex", node->GetCoordIndexArray());
	DumpField("normalIndex", node->GetNormalIndexArray(), !node->GetNormalPerVertex()*4);
	DumpField("texCoordIndex", node->GetTexCoordIndexArray());
	DumpField("color", node->GetColor());
	DumpField("coord", node->GetCoord());
	DumpField("normal", node->GetNormal());
	DumpField("texCoord", node->GetTexCoord());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrElevationGrid *node)
{
	WriteHead(node);

	tos++;

	DumpField("colorPerVertex", node->GetColorPerVertex());
	DumpField("normalPerVertex", node->GetNormalPerVertex());
	DumpField("color", node->GetColor());
	DumpField("normal", node->GetNormal());
	DumpField("texCoord", node->GetTexCoord());
	DumpField("ccw", node->GetCcw());
	DumpField("creaseAngle", node->GetCreaseAngle());
	DumpField("solid", node->GetSolid());
	DumpField("height", node->GetHeightArray());
	DumpField("xDimension", node->GetXDimension());
	DumpField("xSpacing", node->GetXSpacing());
	DumpField("zDimension", node->GetZDimension());
	DumpField("zSpacing", node->GetZSpacing());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrIndexedFaceSet *node)
{
	WriteHead(node);

	tos++;

	DumpField("colorPerVertex", node->GetColorPerVertex());
	DumpField("normalPerVertex", node->GetNormalPerVertex());
	DumpField("colorIndex", node->GetColorIndexArray(), !node->GetColorPerVertex()*4);
	DumpField("coordIndex", node->GetCoordIndexArray());
	DumpField("normalIndex", node->GetNormalIndexArray(), !node->GetNormalPerVertex()*4);
	DumpField("texCoordIndex", node->GetTexCoordIndexArray());
	DumpField("color", node->GetColor());
	DumpField("coord", node->GetCoord());
	DumpField("normal", node->GetNormal());
	DumpField("texCoord", node->GetTexCoord());
	DumpField("ccw", node->GetCcw());
	DumpField("convex", node->GetConvex());
	DumpField("creaseAngle", node->GetCreaseAngle());
	DumpField("solid", node->GetSolid());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrIndexedLineSet *node)
{
	WriteHead(node);

	tos++;

	DumpField("colorPerVertex", node->GetColorPerVertex());
	DumpField("colorIndex", node->GetColorIndexArray(), !node->GetColorPerVertex()*4);
	DumpField("coordIndex", node->GetCoordIndexArray());
	DumpField("color", node->GetColor());
	DumpField("coord", node->GetCoord());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrPointSet *node)
{
	WriteHead(node);

	tos++;

	DumpField("color", node->GetColor());
	DumpField("coord", node->GetCoord());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrColor *node)
{
	WriteHead(node);

	tos++;

	DumpField("color", node->GetColorArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrCoordinate *node)
{
	WriteHead(node);

	tos++;

	DumpField("point", node->GetPointArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrNormal *node)
{
	WriteHead(node);

	tos++;

	DumpField("vector", node->GetVectorArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrTextureCoordinate *node)
{
	WriteHead(node);

	tos++;

	DumpField("point", node->GetPointArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrInterpolator *node)
{
	WriteHead(node);

	tos++;

	DumpField("key", node->GetKeyArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrColorInterpolator *node)
{
	WriteHead(node);

	tos++;

	DumpField("key", node->GetKeyArray());
	DumpField("keyValue", node->GetKeyValueArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrCoordinateInterpolator *node)
{
	WriteHead(node);

	tos++;

	DumpField("key", node->GetKeyArray());
	DumpField("keyValue", node->GetKeyValueArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrNormalInterpolator *node)
{
	WriteHead(node);

	tos++;

	DumpField("key", node->GetKeyArray());
	DumpField("keyValue", node->GetKeyValueArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrOrientationInterpolator *node)
{
	WriteHead(node);

	tos++;

	DumpField("key", node->GetKeyArray());
	DumpField("keyValue", node->GetKeyValueArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrPositionInterpolator *node)
{
	WriteHead(node);

	tos++;

	DumpField("key", node->GetKeyArray());
	DumpField("keyValue", node->GetKeyValueArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrScalarInterpolator *node)
{
	WriteHead(node);

	tos++;

	DumpField("key", node->GetKeyArray());
	DumpField("keyValue", node->GetKeyValueArray());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrSensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("enabled", node->GetEnabled());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrPointingDeviceSensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("enabled", node->GetEnabled());
	DumpField("autoOffset", node->GetAutoOffset());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrCylinderSensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("autoOffset", node->GetAutoOffset());
	DumpField("enabled", node->GetEnabled());
	DumpField("offset", node->GetOffset());
	DumpField("diskAngle", node->GetDiskAngle());
	DumpField("maxAngle", node->GetMaxAngle());
	DumpField("minAngle", node->GetMinAngle());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrPlaneSensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("autoOffset", node->GetAutoOffset());
	DumpField("enabled", node->GetEnabled());
	DumpField("offset", node->GetOffset());
	DumpField("maxPosition", node->GetMaxPosition());
	DumpField("minPosition", node->GetMinPosition());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrProximitySensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("enabled", node->GetEnabled());
	DumpField("center", node->GetCenter());
	DumpField("size", node->GetSize());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrSphereSensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("autoOffset", node->GetAutoOffset());
	DumpField("enabled", node->GetEnabled());
	DumpField("offset", node->GetOffset());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrTimeSensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("enabled", node->GetEnabled());
	DumpField("cycleInterval", node->GetCycleInterval());
	DumpField("loop", node->GetLoop());
	DumpField("startTime", node->GetStartTime());
	DumpField("stopTime", node->GetStopTime());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrTouchSensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("enabled", node->GetEnabled());

	tos--;
}

//-------------------------------------------------------------------
void vrTreeTraverser::Traverse(const vrVisibilitySensor *node)
{
	WriteHead(node);

	tos++;

	DumpField("enabled", node->GetEnabled());
	DumpField("center", node->GetCenter());
	DumpField("size", node->GetSize());

	tos--;
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
//-------------------------------------------------------------------
