//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "TouchSensor.h"

IMPLEMENT_NODE(vrTouchSensor, vrPointingDeviceSensor);

//----------------------------------------------------------------------
vrTouchSensor::vrTouchSensor(void) : vrPointingDeviceSensor()
{
	m_HitNormal          = origin;
	m_HitPoint           = origin;
	m_HitTexCoord        = origin2;
	m_IsOver             = FALSE;
	m_TouchTime          = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventOut(SFVEC3F, VRML_HITNORMAL_CHANGED_STR);
		AddEventOut(SFVEC3F, VRML_HITPOINT_CHANGED_STR);
		AddEventOut(SFVEC2F, VRML_HITTEXCOORD_CHANGED_STR);
		AddEventOut(SFBOOL, VRML_ISOVER_STR);
		AddEventOut(SFTIME, VRML_TOUCHTIME_STR);
		AddExposedField(SFBOOL, VRML_ENABLED_STR);
		AddEventOut(SFBOOL, VRML_ISACTIVE_STR);
	}
}

vrTouchSensor::vrTouchSensor(const vrTouchSensor& v) : vrPointingDeviceSensor(v)
{
	m_HitNormal          = v.m_HitNormal;
	m_HitPoint           = v.m_HitPoint;
	m_HitTexCoord        = v.m_HitTexCoord;
	m_IsOver             = v.m_IsOver;
	m_TouchTime          = v.m_TouchTime;
	GetRuntimeClass()->Reference();
}

vrTouchSensor::~vrTouchSensor(void)
{
	GetRuntimeClass()->Dereference();
}

vrTouchSensor& vrTouchSensor::operator=(const vrTouchSensor& v)
{
	vrPointingDeviceSensor::operator=(v);

	m_HitNormal          = v.m_HitNormal;
	m_HitPoint           = v.m_HitPoint;
	m_HitTexCoord        = v.m_HitTexCoord;
	m_IsOver             = v.m_IsOver;
	m_TouchTime          = v.m_TouchTime;

	return *this;
}

SFNode vrTouchSensor::Clone(void) const
{
	return new vrTouchSensor(*this);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
SFBool vrTouchSensor::IsDefault(const SFString& fieldName, vrField *field) const
{
	return vrPointingDeviceSensor::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrTouchSensor::SetFieldValue(const SFString& fieldName, void *val)
{
	return vrPointingDeviceSensor::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "TouchSensor.cxx"
