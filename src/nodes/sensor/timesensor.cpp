//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "TimeSensor.h"

IMPLEMENT_NODE(vrTimeSensor, vrSensor);

//----------------------------------------------------------------------
vrTimeSensor::vrTimeSensor(void) : vrSensor()
{
	m_CycleInterval      = 1.0;
	m_Loop               = FALSE;
	m_StartTime          = 0.0;
	m_StopTime           = 0.0;
	m_CycleTime          = 0.0;
	m_Fraction           = 0.0;
	m_Time               = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFTIME, VRML_CYCLEINTERVAL_STR);
		AddExposedField(SFBOOL, VRML_LOOP_STR);
		AddExposedField(SFTIME, VRML_STARTTIME_STR);
		AddExposedField(SFTIME, VRML_STOPTIME_STR);
		AddEventOut(SFTIME, VRML_CYCLETIME_STR);
		AddEventOut(SFFLOAT, VRML_FRACTION_CHANGED_STR);
		AddEventOut(SFTIME, VRML_TIME_STR);
		AddExposedField(SFBOOL, VRML_ENABLED_STR);
		AddEventOut(SFBOOL, VRML_ISACTIVE_STR);
	}
}

vrTimeSensor::vrTimeSensor(const vrTimeSensor& v) : vrSensor(v)
{
	m_CycleInterval      = v.m_CycleInterval;
	m_Loop               = v.m_Loop;
	m_StartTime          = v.m_StartTime;
	m_StopTime           = v.m_StopTime;
	m_CycleTime          = v.m_CycleTime;
	m_Fraction           = v.m_Fraction;
	m_Time               = v.m_Time;
	GetRuntimeClass()->Reference();
}

vrTimeSensor::~vrTimeSensor(void)
{
	GetRuntimeClass()->Dereference();
}

vrTimeSensor& vrTimeSensor::operator=(const vrTimeSensor& v)
{
	vrSensor::operator=(v);

	m_CycleInterval      = v.m_CycleInterval;
	m_Loop               = v.m_Loop;
	m_StartTime          = v.m_StartTime;
	m_StopTime           = v.m_StopTime;
	m_CycleTime          = v.m_CycleTime;
	m_Fraction           = v.m_Fraction;
	m_Time               = v.m_Time;

	return *this;
}

SFNode vrTimeSensor::Clone(void) const
{
	return new vrTimeSensor(*this);
}

//----------------------------------------------------------------------
/*
void vrTimeSensor::ReceiveEventIn(vrEvent *ev)
{
}
*/

//----------------------------------------------------------------------
SFBool vrTimeSensor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("cycleInterval", m_CycleInterval, 1.0);
		//if (fieldName == "cycleInterval")
		//	return (1.0 == m_CycleInterval);

		CHECK_FIELD("loop", m_Loop, FALSE);
		//if (fieldName == "loop")
		//	return (FALSE == m_Loop);

		CHECK_FIELD("startTime", m_StartTime, 0.0);
		//if (fieldName == "startTime")
		//	return (0.0 == m_StartTime);

		CHECK_FIELD("stopTime", m_StopTime, 0.0);
		//if (fieldName == "stopTime")
		//	return (0.0 == m_StopTime);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("cycleInterval")) return FALSE;
		if (!IsDefault("loop")) return FALSE;
		if (!IsDefault("startTime")) return FALSE;
		if (!IsDefault("stopTime")) return FALSE;
	}

	return vrSensor::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrTimeSensor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "cycleInterval")
	{
		SetCycleInterval(*((SFTime *)val));
		return TRUE;
	} else if (fieldName == "loop")
	{
		SetLoop(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "startTime")
	{
		SetStartTime(*((SFTime *)val));
		return TRUE;
	} else if (fieldName == "stopTime")
	{
		SetStopTime(*((SFTime *)val));
		return TRUE;
	}
	
	return vrSensor::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "TimeSensor.cxx"
