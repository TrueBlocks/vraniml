//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Color.h"

IMPLEMENT_NODE(vrColor, vrNode);

//----------------------------------------------------------------------
vrColor::vrColor(void) : vrNode()
{
	//m_Color              = array;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFCOLOR, VRML_COLOR_STR);
		// undefined events -- to invalidate geometry nodes
		AddEventOut(SFBOOL, VRML_INVALIDATE_STR);
	}
}

vrColor::vrColor(const vrColor& v) : vrNode(v)
{
	m_Color              = v.m_Color;
	GetRuntimeClass()->Reference();
}

vrColor::~vrColor(void)
{
	m_Color.Clear();
	GetRuntimeClass()->Dereference();
}

vrColor& vrColor::operator=(const vrColor& v)
{
	vrNode::operator=(v);

	m_Color.Clear();
	m_Color              = v.m_Color;

	return *this;
}

SFNode vrColor::Clone(void) const
{
	return new vrColor(*this);
}

//----------------------------------------------------------------------
void vrColor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_COLOR_STR)
	{
		SetColor(*((MFColor *)ev->m_Value));
		SendEventOut(VRML_COLOR_STR, &m_Color);
		SendEventOut(VRML_INVALIDATE_STR, NULL);
	}
}

//----------------------------------------------------------------------
SFBool vrColor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("color", GetNColors(), m_Color, 0);
		//if (fieldName == "color")
		//	return (0 == GetNColors()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("color")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrColor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "color")
	{
		SetColor(*((MFColor *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
