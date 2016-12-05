//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "ProximitySensor.h"

IMPLEMENT_NODE(vrProximitySensor, vrSensor);

//----------------------------------------------------------------------
vrProximitySensor::vrProximitySensor(void) : vrSensor()
{
	m_Center             = origin;
	m_Size               = origin;
	m_Position           = origin;
	m_Orientation        = defRotation;
	m_EnterTime          = 0.0;
	m_ExitTime           = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFVEC3F, VRML_CENTER_STR);
		AddExposedField(SFVEC3F, VRML_SIZE_STR);
		AddEventOut(SFVEC3F, VRML_POSITION_CHANGED_STR);
		AddEventOut(SFROTATION, VRML_ORIENTATION_CHANGED_STR);
		AddEventOut(SFTIME, VRML_ENTERTIME_STR);
		AddEventOut(SFTIME, VRML_EXITTIME_STR);
		AddExposedField(SFBOOL, VRML_ENABLED_STR);
		AddEventOut(SFBOOL, VRML_ISACTIVE_STR);
	}
}

vrProximitySensor::vrProximitySensor(const vrProximitySensor& v) : vrSensor(v)
{
	m_Center             = v.m_Center;
	m_Size               = v.m_Size;
	m_Position           = v.m_Position;
	m_Orientation        = v.m_Orientation;
	m_EnterTime          = v.m_EnterTime;
	m_ExitTime           = v.m_ExitTime;
	GetRuntimeClass()->Reference();
}

vrProximitySensor::~vrProximitySensor(void)
{
	GetRuntimeClass()->Dereference();
}

vrProximitySensor& vrProximitySensor::operator=(const vrProximitySensor& v)
{
	vrSensor::operator=(v);

	m_Center             = v.m_Center;
	m_Size               = v.m_Size;
	m_Position           = v.m_Position;
	m_Orientation        = v.m_Orientation;
	m_EnterTime          = v.m_EnterTime;
	m_ExitTime           = v.m_ExitTime;

	return *this;
}

SFNode vrProximitySensor::Clone(void) const
{
	return new vrProximitySensor(*this);
}

//----------------------------------------------------------------------
void vrProximitySensor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_CENTER_STR)
		{
			SetCenter(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_CENTER_STR, &m_Center);
		}
	else if (ev->m_FieldID == VRML_SIZE_STR)
		{
			SetSize(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_SIZE_STR, &m_Size);
		}
	else
		{
			vrSensor::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrProximitySensor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("center", m_Center, origin);
		//if (fieldName == "center")
		//	return (origin == m_Center);

		CHECK_FIELD("size", m_Size, origin);
		//if (fieldName == "size")
		//	return (origin == m_Size);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("center")) return FALSE;
		if (!IsDefault("size")) return FALSE;
	}

	return vrSensor::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrProximitySensor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "center")
	{
		SetCenter(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "size")
	{
		SetSize(*((SFVec3f *)val));
		return TRUE;
	}
	
	return vrSensor::SetFieldValue(fieldName, val);
}
