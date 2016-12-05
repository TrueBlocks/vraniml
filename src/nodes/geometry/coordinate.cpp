//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Coordinate.h"

IMPLEMENT_NODE(vrCoordinate, vrNode);

//----------------------------------------------------------------------
vrCoordinate::vrCoordinate(void) : vrNode()
{
	//m_Point              = array;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFVEC3F, VRML_POINT_STR);
		// undefined events -- to invalidate geometry nodes
		AddEventOut(SFBOOL, VRML_INVALIDATE_STR);
	}
}

vrCoordinate::vrCoordinate(const vrCoordinate& v) : vrNode(v)
{
	m_Point              = v.m_Point;
	GetRuntimeClass()->Reference();
}

vrCoordinate::~vrCoordinate(void)
{
	m_Point.Clear();
	GetRuntimeClass()->Dereference();
}

vrCoordinate& vrCoordinate::operator=(const vrCoordinate& v)
{
	vrNode::operator=(v);

	m_Point.Clear();
	m_Point              = v.m_Point;

	return *this;
}

SFNode vrCoordinate::Clone(void) const
{
	return new vrCoordinate(*this);
}

//----------------------------------------------------------------------
void vrCoordinate::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_POINT_STR)
	{
		SetPoint(*((MFVec3f *)ev->m_Value));
		SendEventOut(VRML_POINT_STR, &m_Point);
		SendEventOut(VRML_INVALIDATE_STR, NULL);
	}
}

//----------------------------------------------------------------------
SFBool vrCoordinate::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("point", GetNPoints(), m_Point, 0);
		//if (fieldName == "point")
		//	return (0 == GetNPoints()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("point")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrCoordinate::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "point")
	{
		SetPoint(*((MFVec3f *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
