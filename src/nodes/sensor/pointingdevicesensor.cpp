//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "PointingDeviceSensor.h"

IMPLEMENT_NODE(vrPointingDeviceSensor, vrSensor);

//----------------------------------------------------------------------
vrPointingDeviceSensor::vrPointingDeviceSensor(void) : vrSensor()
{
	m_FirstPoint         = origin;
	m_AutoOffset         = TRUE;
	m_TrackPoint         = origin;
}

vrPointingDeviceSensor::vrPointingDeviceSensor(const vrPointingDeviceSensor& v) : vrSensor(v)
{
	m_FirstPoint         = v.m_FirstPoint;
	m_AutoOffset         = v.m_AutoOffset;
	m_TrackPoint         = v.m_TrackPoint;
}

vrPointingDeviceSensor::~vrPointingDeviceSensor(void)
{
}

vrPointingDeviceSensor& vrPointingDeviceSensor::operator=(const vrPointingDeviceSensor& v)
{
	vrSensor::operator=(v);

	m_FirstPoint         = v.m_FirstPoint;
	m_AutoOffset         = v.m_AutoOffset;
	m_TrackPoint         = v.m_TrackPoint;

	return *this;
}

SFNode vrPointingDeviceSensor::Clone(void) const
{
	return new vrPointingDeviceSensor(*this);
}

//----------------------------------------------------------------------
void vrPointingDeviceSensor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_AUTOOFFSET_STR)
		{
			SetAutoOffset(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_AUTOOFFSET_STR, &m_AutoOffset);
		}
	else
		{
			vrSensor::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrPointingDeviceSensor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("autoOffset", m_AutoOffset, TRUE);
		//if (fieldName == "autoOffset")
		//	return (TRUE == m_AutoOffset);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("autoOffset")) return FALSE;
	}

	return vrSensor::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrPointingDeviceSensor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "autoOffset")
	{
		SetAutoOffset(*((SFBool *)val));
		return TRUE;
	}
	
	return vrSensor::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "PointingDeviceSensor.cxx"
