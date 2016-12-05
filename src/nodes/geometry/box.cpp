//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Box.h"

IMPLEMENT_NODE(vrBox, vrGeometryNode);

//----------------------------------------------------------------------
vrBox::vrBox(void) : vrGeometryNode()
{
	m_Size               = xyz1*2;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddField(SFVEC3F, VRML_SIZE_STR);
	}
}

vrBox::vrBox(const vrBox& v) : vrGeometryNode(v)
{
	m_Size               = v.m_Size;
	GetRuntimeClass()->Reference();
}

vrBox::~vrBox(void)
{
	GetRuntimeClass()->Dereference();
}

vrBox& vrBox::operator=(const vrBox& v)
{
	vrGeometryNode::operator=(v);

	m_Size               = v.m_Size;

	return *this;
}

SFNode vrBox::Clone(void) const
{
	return new vrBox(*this);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
SFBool vrBox::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("size", m_Size, (xyz1*2));
		//if (fieldName == "size")
		//	return (xyz1*2 == m_Size);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("size")) return FALSE;
	}

	return vrGeometryNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrBox::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "size")
	{
		SetSize(*((SFVec3f *)val));
		return TRUE;
	}

	return vrGeometryNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Box.cxx"
