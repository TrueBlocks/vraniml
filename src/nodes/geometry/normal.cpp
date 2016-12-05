//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Normal.h"

IMPLEMENT_NODE(vrNormal, vrNode);

//----------------------------------------------------------------------
vrNormal::vrNormal(void) : vrNode()
{
	//m_Vector             = array;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFVEC3F, VRML_VECTOR_STR);
		// undefined events -- to invalidate geometry nodes
		AddEventOut(SFBOOL, VRML_INVALIDATE_STR);
	}
}

vrNormal::vrNormal(const vrNormal& v) : vrNode(v)
{
	m_Vector             = v.m_Vector;
	GetRuntimeClass()->Reference();
}

vrNormal::~vrNormal(void)
{
	m_Vector.Clear();
	GetRuntimeClass()->Dereference();
}

vrNormal& vrNormal::operator=(const vrNormal& v)
{
	vrNode::operator=(v);

	m_Vector.Clear();
	m_Vector             = v.m_Vector;

	return *this;
}

SFNode vrNormal::Clone(void) const
{
	return new vrNormal(*this);
}

//----------------------------------------------------------------------
void vrNormal::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_VECTOR_STR)
		{
			SetVector(*((MFVec3f *)ev->m_Value));
			SendEventOut(VRML_VECTOR_STR, &m_Vector);
			SendEventOut(VRML_INVALIDATE_STR, NULL);
		}
}

//----------------------------------------------------------------------
SFBool vrNormal::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("vector", GetNVectors(), m_Vector, 0);
		//if (fieldName == "vector")
		//	return (0 == GetNVectors()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("vector")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrNormal::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "vector")
	{
		SetVector(*((MFVec3f *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
