//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Interpolator.h"

IMPLEMENT_NODE(vrInterpolator, vrNode);

//----------------------------------------------------------------------
vrInterpolator::vrInterpolator(void) : vrNode()
{
	//m_Key                = array;
}

vrInterpolator::vrInterpolator(const vrInterpolator& v) : vrNode(v)
{
	m_Key                = v.m_Key;
}

vrInterpolator::~vrInterpolator(void)
{
	m_Key.Clear();
}

vrInterpolator& vrInterpolator::operator=(const vrInterpolator& v)
{
	vrNode::operator=(v);

	m_Key.Clear();
	m_Key                = v.m_Key;

	return *this;
}

SFNode vrInterpolator::Clone(void) const
{
	return new vrInterpolator(*this);
}

//----------------------------------------------------------------------
void vrInterpolator::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_KEY_STR)
		{
			SetKey(*((MFFloat *)ev->m_Value));
			SendEventOut(VRML_KEY_STR, &m_Key);
		}
}

//----------------------------------------------------------------------
SFBool vrInterpolator::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("key", GetNKeys(), m_Key, 0);
		//if (fieldName == "key")
		//	return (0 == GetNKeys()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("key")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrInterpolator::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "key")
	{
		SetKey(*((MFFloat *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
