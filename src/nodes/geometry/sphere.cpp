//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Sphere.h"

IMPLEMENT_NODE(vrSphere, vrGeometryNode);

//----------------------------------------------------------------------
vrSphere::vrSphere(void) : vrGeometryNode()
{
	m_Radius             = 1;
	m_Slices             = 16;
	m_Stacks             = 16;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddField(SFFLOAT, VRML_RADIUS_STR);
	}
}

vrSphere::vrSphere(const vrSphere& v) : vrGeometryNode(v)
{
	m_Radius             = v.m_Radius;
	m_Slices             = v.m_Slices;
	m_Stacks             = v.m_Stacks;
	GetRuntimeClass()->Reference();
}

vrSphere::~vrSphere(void)
{
	GetRuntimeClass()->Dereference();
}

vrSphere& vrSphere::operator=(const vrSphere& v)
{
	vrGeometryNode::operator=(v);

	m_Radius             = v.m_Radius;
	m_Slices             = v.m_Slices;
	m_Stacks             = v.m_Stacks;

	return *this;
}

SFNode vrSphere::Clone(void) const
{
	return new vrSphere(*this);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
SFBool vrSphere::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("radius", m_Radius, (SFFloat)1);
		//if (fieldName == "radius")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_Radius);
		//	if (IsIsMapped(fieldName))
		//		return TRUE;
		//	return ((SFFloat)1 == m_Radius);
		//}


		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("radius")) return FALSE;
	}

	return vrGeometryNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrSphere::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "radius")
	{
		SetRadius(*((SFFloat *)val));
		return TRUE;
	}

	return vrGeometryNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Sphere.cxx"
