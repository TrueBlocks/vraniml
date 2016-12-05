//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Cylinder.h"

IMPLEMENT_NODE(vrCylinder, vrGeometryNode);

//----------------------------------------------------------------------
vrCylinder::vrCylinder(void) : vrGeometryNode()
{
	m_Bottom             = TRUE;
	m_Height             = 2.0;
	m_Radius             = 1.0;
	m_Side               = TRUE;
	m_Top                = TRUE;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddField(SFFLOAT, VRML_RADIUS_STR);
		AddField(SFFLOAT, VRML_HEIGHT_STR);
		AddField(SFBOOL, VRML_SIDE_STR);
		AddField(SFBOOL, VRML_BOTTOM_STR);
		AddField(SFBOOL, VRML_TOP_STR);
	}
}

vrCylinder::vrCylinder(const vrCylinder& v) : vrGeometryNode(v)
{
	m_Bottom             = v.m_Bottom;
	m_Height             = v.m_Height;
	m_Radius             = v.m_Radius;
	m_Side               = v.m_Side;
	m_Top                = v.m_Top;
	GetRuntimeClass()->Reference();
}

vrCylinder::~vrCylinder(void)
{
	GetRuntimeClass()->Dereference();
}

vrCylinder& vrCylinder::operator=(const vrCylinder& v)
{
	vrGeometryNode::operator=(v);

	m_Bottom             = v.m_Bottom;
	m_Height             = v.m_Height;
	m_Radius             = v.m_Radius;
	m_Side               = v.m_Side;
	m_Top                = v.m_Top;

	return *this;
}

SFNode vrCylinder::Clone(void) const
{
	return new vrCylinder(*this);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
SFBool vrCylinder::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("bottom", m_Bottom, TRUE);
		//if (fieldName == "bottom")
		//	return (TRUE == m_Bottom);

		CHECK_FIELD("height", m_Height, (SFFloat)2.0);
		//if (fieldName == "height")
		//	return ((SFFloat)2.0 == m_Height);

		CHECK_FIELD("radius", m_Radius, (SFFloat)1.0);
		//if (fieldName == "radius")
		//	return ((SFFloat)1.0 == m_Radius);

		CHECK_FIELD("side", m_Side, TRUE);
		//if (fieldName == "side")
		//	return (TRUE == m_Side);

		CHECK_FIELD("top", m_Top, TRUE);
		//if (fieldName == "top")
		//	return (TRUE == m_Top);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("bottom")) return FALSE;
		if (!IsDefault("height")) return FALSE;
		if (!IsDefault("radius")) return FALSE;
		if (!IsDefault("side")) return FALSE;
		if (!IsDefault("top")) return FALSE;
	}

	return vrGeometryNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrCylinder::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "bottom")
	{
		SetBottom(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "height")
	{
		SetHeight(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "radius")
	{
		SetRadius(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "side")
	{
		SetSide(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "top")
	{
		SetTop(*((SFBool *)val));
		return TRUE;
	}

	return vrGeometryNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Cylinder.cxx"
