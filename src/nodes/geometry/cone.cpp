//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Cone.h"

IMPLEMENT_NODE(vrCone, vrGeometryNode);

//----------------------------------------------------------------------
vrCone::vrCone(void) : vrGeometryNode()
{
	m_BottomRadius       = 1.0;
	m_Height             = 2.0;
	m_Side               = TRUE;
	m_Bottom             = TRUE;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddField(SFFLOAT, VRML_BOTTOMRADIUS_STR);
		AddField(SFFLOAT, VRML_HEIGHT_STR);
		AddField(SFBOOL, VRML_SIDE_STR);
		AddField(SFBOOL, VRML_BOTTOM_STR);
	}
}

vrCone::vrCone(const vrCone& v) : vrGeometryNode(v)
{
	m_BottomRadius       = v.m_BottomRadius;
	m_Height             = v.m_Height;
	m_Side               = v.m_Side;
	m_Bottom             = v.m_Bottom;
	GetRuntimeClass()->Reference();
}

vrCone::~vrCone(void)
{
	GetRuntimeClass()->Dereference();
}

vrCone& vrCone::operator=(const vrCone& v)
{
	vrGeometryNode::operator=(v);

	m_BottomRadius       = v.m_BottomRadius;
	m_Height             = v.m_Height;
	m_Side               = v.m_Side;
	m_Bottom             = v.m_Bottom;

	return *this;
}

SFNode vrCone::Clone(void) const
{
	return new vrCone(*this);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
SFBool vrCone::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("bottomRadius", m_BottomRadius, (SFFloat)1.0);
		//if (fieldName == "bottomRadius")
		//	return ((SFFloat)1.0 == m_BottomRadius);

		CHECK_FIELD("height", m_Height, (SFFloat)2.0);
		//if (fieldName == "height")
		//	return ((SFFloat)2.0 == m_Height);

		CHECK_FIELD("side", m_Side, TRUE);
		//if (fieldName == "side")
		//	return (TRUE == m_Side);

		CHECK_FIELD("bottom", m_Bottom, TRUE);
		//if (fieldName == "bottom")
		//	return (TRUE == m_Bottom);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("bottomRadius")) return FALSE;
		if (!IsDefault("height")) return FALSE;
		if (!IsDefault("side")) return FALSE;
		if (!IsDefault("bottom")) return FALSE;
	}

	return vrGeometryNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrCone::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "bottomRadius")
	{
		SetBottomRadius(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "height")
	{
		SetHeight(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "side")
	{
		SetSide(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "bottom")
	{
		SetBottom(*((SFBool *)val));
		return TRUE;
	}

	return vrGeometryNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Cone.cxx"
