//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "TextureCoordinate.h"

IMPLEMENT_NODE(vrTextureCoordinate, vrNode);

//----------------------------------------------------------------------
vrTextureCoordinate::vrTextureCoordinate(void) : vrNode()
{
	//m_Point              = array;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFVEC2F, VRML_POINT_STR);
		// undefined events -- to invalidate geometry nodes
		AddEventOut(SFBOOL, VRML_INVALIDATE_STR);
	}
}

vrTextureCoordinate::vrTextureCoordinate(const vrTextureCoordinate& v) : vrNode(v)
{
	m_Point              = v.m_Point;
	GetRuntimeClass()->Reference();
}

vrTextureCoordinate::~vrTextureCoordinate(void)
{
	m_Point.Clear();
	GetRuntimeClass()->Dereference();
}

vrTextureCoordinate& vrTextureCoordinate::operator=(const vrTextureCoordinate& v)
{
	vrNode::operator=(v);

	m_Point.Clear();
	m_Point              = v.m_Point;

	return *this;
}

SFNode vrTextureCoordinate::Clone(void) const
{
	return new vrTextureCoordinate(*this);
}

//----------------------------------------------------------------------
void vrTextureCoordinate::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_POINT_STR)
		{
			SetPoint(*((MFVec2f *)ev->m_Value));
			SendEventOut(VRML_POINT_STR, &m_Point);
			SendEventOut(VRML_INVALIDATE_STR, NULL);
		}
}

//----------------------------------------------------------------------
SFBool vrTextureCoordinate::IsDefault(const SFString& fieldName, vrField *field) const
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
SFBool vrTextureCoordinate::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "point")
	{
		SetPoint(*((MFVec2f *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
