//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Sensor.h"

IMPLEMENT_NODE(vrSensor, vrNode);

//----------------------------------------------------------------------
vrSensor::vrSensor(void) : vrNode()
{
	m_Enabled            = TRUE;
	m_IsActive           = FALSE;
}

vrSensor::vrSensor(const vrSensor& v) : vrNode(v)
{
	m_Enabled            = v.m_Enabled;
	m_IsActive           = v.m_IsActive;
}

vrSensor::~vrSensor(void)
{
}

vrSensor& vrSensor::operator=(const vrSensor& v)
{
	vrNode::operator=(v);

	m_Enabled            = v.m_Enabled;
	m_IsActive           = v.m_IsActive;

	return *this;
}

SFNode vrSensor::Clone(void) const
{
	return new vrSensor(*this);
}

//----------------------------------------------------------------------
void vrSensor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_ENABLED_STR)
		{
			SetEnabled(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_ENABLED_STR, &m_Enabled);

			// If Enabled receives a FALSE event while the sensor is active
			// then the sensor should evaluate and send all relevant 
			// outputs, send a FALSE value for isActiveOut, and disable itself
			if (!m_Enabled && IsActive())
			{
				Deactivate();
			}	 
		}
}

//----------------------------------------------------------------------
SFBool vrSensor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("enabled", m_Enabled, TRUE);
		//if (fieldName == "enabled")
		//	return (TRUE == m_Enabled);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("enabled")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrSensor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "enabled")
	{
		SetEnabled(*((SFBool *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

//----------------------------------------------------------------------
#include "Sensor.cxx"
