//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "DataSet.h"
#include "Color.h"
#include "Coordinate.h"
#include "Normal.h"
#include "TextureCoordinate.h"

IMPLEMENT_NODE(vrDataSet, vrGeometryNode);

//----------------------------------------------------------------------
vrDataSet::vrDataSet(void) : vrGeometryNode()
{
	m_ColorPerVertex     = TRUE;
	m_NormalPerVertex    = TRUE;
	//m_ColorIndex         = array;
	//m_CoordIndex         = array;
	//m_NormalIndex        = array;
	//m_TexCoordIndex      = array;
	m_Color              = NULL   ;
	m_Coord              = NULL   ;
	m_Normal             = NULL   ;
	m_TexCoord           = NULL   ;
	m_ColorIndexEv       = 0;
	m_CoordIndexEv       = 0;
	m_NormalIndexEv      = 0;
	m_TexCoordIndexEv    = 0;
}

vrDataSet::vrDataSet(const vrDataSet& v) : vrGeometryNode(v)
{
	m_ColorPerVertex     = v.m_ColorPerVertex;
	m_NormalPerVertex    = v.m_NormalPerVertex;
	m_ColorIndex         = v.m_ColorIndex;
	m_CoordIndex         = v.m_CoordIndex;
	m_NormalIndex        = v.m_NormalIndex;
	m_TexCoordIndex      = v.m_TexCoordIndex;
	m_Color=NULL;
	SetColor(((v.m_Color) ? (vrColor*)v.m_Color->Clone() : NULL));
	m_Coord=NULL;
	SetCoord(((v.m_Coord) ? (vrCoordinate*)v.m_Coord->Clone() : NULL));
	m_Normal=NULL;
	SetNormal(((v.m_Normal) ? (vrNormal*)v.m_Normal->Clone() : NULL));
	m_TexCoord=NULL;
	SetTexCoord(((v.m_TexCoord) ? (vrTextureCoordinate*)v.m_TexCoord->Clone() : NULL));
	m_ColorIndexEv       = v.m_ColorIndexEv;
	m_CoordIndexEv       = v.m_CoordIndexEv;
	m_NormalIndexEv      = v.m_NormalIndexEv;
	m_TexCoordIndexEv    = v.m_TexCoordIndexEv;
}

vrDataSet::~vrDataSet(void)
{
	m_ColorIndex.Clear();
	m_CoordIndex.Clear();
	m_NormalIndex.Clear();
	m_TexCoordIndex.Clear();
	vrDELETE(m_Color);
	vrDELETE(m_Coord);
	vrDELETE(m_Normal);
	vrDELETE(m_TexCoord);
}

vrDataSet& vrDataSet::operator=(const vrDataSet& v)
{
	vrGeometryNode::operator=(v);

	m_ColorPerVertex     = v.m_ColorPerVertex;
	m_NormalPerVertex    = v.m_NormalPerVertex;
	m_ColorIndex.Clear();
	m_ColorIndex         = v.m_ColorIndex;
	m_CoordIndex.Clear();
	m_CoordIndex         = v.m_CoordIndex;
	m_NormalIndex.Clear();
	m_NormalIndex        = v.m_NormalIndex;
	m_TexCoordIndex.Clear();
	m_TexCoordIndex      = v.m_TexCoordIndex;
	vrDELETE(m_Color);
	SetColor(((v.m_Color) ? (vrColor*)v.m_Color->Clone() : NULL));
	vrDELETE(m_Coord);
	SetCoord(((v.m_Coord) ? (vrCoordinate*)v.m_Coord->Clone() : NULL));
	vrDELETE(m_Normal);
	SetNormal(((v.m_Normal) ? (vrNormal*)v.m_Normal->Clone() : NULL));
	vrDELETE(m_TexCoord);
	SetTexCoord(((v.m_TexCoord) ? (vrTextureCoordinate*)v.m_TexCoord->Clone() : NULL));
	m_ColorIndexEv       = v.m_ColorIndexEv;
	m_CoordIndexEv       = v.m_CoordIndexEv;
	m_NormalIndexEv      = v.m_NormalIndexEv;
	m_TexCoordIndexEv    = v.m_TexCoordIndexEv;

	return *this;
}

SFNode vrDataSet::Clone(void) const
{
	return new vrDataSet(*this);
}

//----------------------------------------------------------------------
void vrDataSet::SetColor(const vrColor* color)
{
	vrDELETE(m_Color);

	m_Color = (vrColor*)color; //((color) ? (vrColor*)color->Clone() : NULL);
	if (m_Color)
		m_Color->Reference();
}

void vrDataSet::SetCoord(const vrCoordinate* coord)
{
	vrDELETE(m_Coord);

	m_Coord = (vrCoordinate*)coord; //((coord) ? (vrCoordinate*)coord->Clone() : NULL);
	if (m_Coord)
		m_Coord->Reference();
}

void vrDataSet::SetNormal(const vrNormal* normal)
{
	vrDELETE(m_Normal);

	m_Normal = (vrNormal*)normal; //((normal) ? (vrNormal*)normal->Clone() : NULL);
	if (m_Normal)
		m_Normal->Reference();
}

void vrDataSet::SetTexCoord(const vrTextureCoordinate* texcoord)
{
	vrDELETE(m_TexCoord);

	m_TexCoord = (vrTextureCoordinate*)texcoord; //((texcoord) ? (vrTextureCoordinate*)texcoord->Clone() : NULL);
	if (m_TexCoord)
		m_TexCoord->Reference();
}

void vrDataSet::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_SET_COLORINDEX_STR)
		{
			// not implemented
		}
	else if (ev->m_FieldID == VRML_SET_COORDINDEX_STR)
		{
			// not implemented
		}
	else if (ev->m_FieldID == VRML_SET_NORMALINDEX_STR)
		{
			// not implemented
		}
	else if (ev->m_FieldID == VRML_SET_TEXCOORDINDEX_STR)
		{
			// not implemented
		}
	else if (ev->m_FieldID == VRML_COORD_STR)
		{
			// Note: I think there are a ton of copies going on here.  It should
			//       probably not do this, instead just pass on the pointer, but we will
			//       fix this when it becomes a problem.
			// So the solid gets re-built -- this is also quite inefficient
			SetGeom(NULL);
			vrCoordinate *coords = GetCoord();
			ASSERT(coords);
			coords->SetPoint(*((MFVec3f *)ev->m_Value));
			MFVec3f array = coords->GetPointArray();
			SendEventOut(VRML_COORD_STR, &array);
		}
	else if (ev->m_FieldID == VRML_INVALIDATE_STR)
		{
			SetGeom(NULL);
		}
}

//----------------------------------------------------------------------
SFNode vrDataSet::FindByType(vrRuntimeClass *pClass) const
{
	if (m_Color && m_Color->IsKindOf(pClass))
		return ((SFNode)m_Color);

	if (m_Coord && m_Coord->IsKindOf(pClass))
		return ((SFNode)m_Coord);

	if (m_Normal && m_Normal->IsKindOf(pClass))
		return ((SFNode)m_Normal);

	if (m_TexCoord && m_TexCoord->IsKindOf(pClass))
		return ((SFNode)m_TexCoord);

	return vrGeometryNode::FindByType(pClass);
}

SFNode vrDataSet::FindByName(const SFString& nodeName) const
{
	SFNode node = NULL;

	if (m_Color && ((node = m_Color->FindByName(nodeName)) != NULL))
		return (node);

	if (m_Coord && ((node = m_Coord->FindByName(nodeName)) != NULL))
		return (node);

	if (m_Normal && ((node = m_Normal->FindByName(nodeName)) != NULL))
		return (node);

	if (m_TexCoord && ((node = m_TexCoord->FindByName(nodeName)) != NULL))
		return (node);

	return vrGeometryNode::FindByName(nodeName);
}

SFBool vrDataSet::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	if (m_Color)
		m_Color->ForEvery(userFn, userData, afterFn);

	if (m_Coord)
		m_Coord->ForEvery(userFn, userData, afterFn);

	if (m_Normal)
		m_Normal->ForEvery(userFn, userData, afterFn);

	if (m_TexCoord)
		m_TexCoord->ForEvery(userFn, userData, afterFn);

	return vrGeometryNode::ForEvery(userFn, userData, afterFn);
}


//----------------------------------------------------------------------
SFBool vrDataSet::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("colorPerVertex", m_ColorPerVertex, TRUE);
		//if (fieldName == "colorPerVertex")
		//	return (TRUE == m_ColorPerVertex);

		CHECK_FIELD("normalPerVertex", m_NormalPerVertex, TRUE);
		//if (fieldName == "normalPerVertex")
		//	return (TRUE == m_NormalPerVertex);

		CHECK_ARRAY_FIELD("colorIndex", GetNColorIndexs(), m_ColorIndex, 0);
		//if (fieldName == "colorIndex")
		//	return (0 == GetNColorIndexs()); // default: []

		CHECK_ARRAY_FIELD("coordIndex", GetNCoordIndexs(), m_CoordIndex, 0);
		//if (fieldName == "coordIndex")
		//	return (0 == GetNCoordIndexs()); // default: []

		CHECK_ARRAY_FIELD("normalIndex", GetNNormalIndexs(), m_NormalIndex, 0);
		//if (fieldName == "normalIndex")
		//	return (0 == GetNNormalIndexs()); // default: []

		CHECK_ARRAY_FIELD("texCoordIndex", GetNTexCoordIndexs(), m_TexCoordIndex, 0);
		//if (fieldName == "texCoordIndex")
		//	return (0 == GetNTexCoordIndexs()); // default: []

		CHECK_FIELD("color", m_Color, NULL);
		//if (fieldName == "color")
		//	return (NULL    == m_Color);

		CHECK_FIELD("coord", m_Coord, NULL);
		//if (fieldName == "coord")
		//	return (NULL    == m_Coord);

		CHECK_FIELD("normal", m_Normal, NULL);
		//if (fieldName == "normal")
		//	return (NULL    == m_Normal);

		CHECK_FIELD("texCoord", m_TexCoord, NULL);
		//if (fieldName == "texCoord")
		//	return (NULL    == m_TexCoord);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("colorPerVertex")) return FALSE;
		if (!IsDefault("normalPerVertex")) return FALSE;
		if (!IsDefault("colorIndex")) return FALSE;
		if (!IsDefault("coordIndex")) return FALSE;
		if (!IsDefault("normalIndex")) return FALSE;
		if (!IsDefault("texCoordIndex")) return FALSE;
		if (!IsDefault("color")) return FALSE;
		if (!IsDefault("coord")) return FALSE;
		if (!IsDefault("normal")) return FALSE;
		if (!IsDefault("texCoord")) return FALSE;
	}

	return vrGeometryNode::IsDefault(fieldName, field);
}

void vrDataSet::AddChild(SFNode node)
{
	if (node->IsKindOf(GETRUNTIME_CLASS(vrColor)))
	{
		SetColor((vrColor*)node);
	} else if (node->IsKindOf(GETRUNTIME_CLASS(vrCoordinate)))
	{
		SetCoord((vrCoordinate*)node);
	} else if (node->IsKindOf(GETRUNTIME_CLASS(vrNormal)))
	{
		SetNormal((vrNormal*)node);
	} else 
	{
		ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrTextureCoordinate)));
		SetTexCoord((vrTextureCoordinate*)node);
	}

	node->RemoveRoute(node->FindRoute("invalidate", this, "invalidate"));
	node->AddRoute("invalidate", this, "invalidate", TRUE);
}

//----------------------------------------------------------------------
SFBool vrDataSet::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "colorPerVertex")
	{
		SetColorPerVertex(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "normalPerVertex")
	{
		SetNormalPerVertex(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "colorIndex")
	{
		SetColorIndex(*((MFInt32 *)val));
		return TRUE;
	} else if (fieldName == "coordIndex")
	{
		SetCoordIndex(*((MFInt32 *)val));
		return TRUE;
	} else if (fieldName == "normalIndex")
	{
		SetNormalIndex(*((MFInt32 *)val));
		return TRUE;
	} else if (fieldName == "texCoordIndex")
	{
		SetTexCoordIndex(*((MFInt32 *)val));
		return TRUE;
	} else if (fieldName == "color")
	{
		AddChild((SFNode)val);
		return TRUE;
	} else if (fieldName == "coord")
	{
		AddChild((SFNode)val);
		return TRUE;
	} else if (fieldName == "normal")
	{
		AddChild((SFNode)val);
		return TRUE;
	} else if (fieldName == "texCoord")
	{
		AddChild((SFNode)val);
		return TRUE;
	}
	
	return vrGeometryNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "DataSet.cxx"
