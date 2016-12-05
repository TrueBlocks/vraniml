//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "SphereSensor.h"

IMPLEMENT_NODE(vrSphereSensor, vrPointingDeviceSensor);

//----------------------------------------------------------------------
vrSphereSensor::vrSphereSensor(void) : vrPointingDeviceSensor()
{
	m_Offset             = SFRotation(0,1,0,0);
	m_Rotation           = defRotation;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFROTATION, VRML_OFFSET_STR);
		AddEventOut(SFROTATION, VRML_ROTATION_CHANGED_STR);
		AddExposedField(SFBOOL, VRML_AUTOOFFSET_STR);
		AddEventOut(SFVEC3F, VRML_TRACKPOINT_CHANGED_STR);
		AddExposedField(SFBOOL, VRML_ENABLED_STR);
		AddEventOut(SFBOOL, VRML_ISACTIVE_STR);
	}
}

vrSphereSensor::vrSphereSensor(const vrSphereSensor& v) : vrPointingDeviceSensor(v)
{
	m_Offset             = v.m_Offset;
	m_Rotation           = v.m_Rotation;
	GetRuntimeClass()->Reference();
}

vrSphereSensor::~vrSphereSensor(void)
{
	GetRuntimeClass()->Dereference();
}

vrSphereSensor& vrSphereSensor::operator=(const vrSphereSensor& v)
{
	vrPointingDeviceSensor::operator=(v);

	m_Offset             = v.m_Offset;
	m_Rotation           = v.m_Rotation;

	return *this;
}

SFNode vrSphereSensor::Clone(void) const
{
	return new vrSphereSensor(*this);
}

//----------------------------------------------------------------------
void vrSphereSensor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_OFFSET_STR)
		{
			SetOffset(*((SFRotation *)ev->m_Value));
			SendEventOut(VRML_OFFSET_STR, &m_Offset);
		}
	else
		{
			vrPointingDeviceSensor::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrSphereSensor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("offset", m_Offset, SFRotation(0,1,0,0));
		//if (fieldName == "offset")
		//	return (SFRotation(0,1,0,0) == m_Offset);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("offset")) return FALSE;
	}

	return vrPointingDeviceSensor::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrSphereSensor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "offset")
	{
		SetOffset(*((SFRotation *)val));
		return TRUE;
	}
	
	return vrPointingDeviceSensor::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "SphereSensor.cxx"
