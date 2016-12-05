//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "CylinderSensor.h"

IMPLEMENT_NODE(vrCylinderSensor, vrPointingDeviceSensor);

//----------------------------------------------------------------------
vrCylinderSensor::vrCylinderSensor(void) : vrPointingDeviceSensor()
{
	m_Offset             = 0.0;
	m_DiskAngle          = 0.262;
	m_MaxAngle           = -1.0;
	m_MinAngle           = 0.0;
	m_Rotation           = defRotation;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFFLOAT, VRML_OFFSET_STR);
		AddExposedField(SFFLOAT, VRML_DISKANGLE_STR);
		AddExposedField(SFFLOAT, VRML_MAXANGLE_STR);
		AddExposedField(SFFLOAT, VRML_MINANGLE_STR);
		AddEventOut(SFROTATION, VRML_ROTATION_CHANGED_STR);
		AddExposedField(SFBOOL, VRML_AUTOOFFSET_STR);
		AddEventOut(SFVEC3F, VRML_TRACKPOINT_CHANGED_STR);
		AddExposedField(SFBOOL, VRML_ENABLED_STR);
		AddEventOut(SFBOOL, VRML_ISACTIVE_STR);
	}
}

vrCylinderSensor::vrCylinderSensor(const vrCylinderSensor& v) : vrPointingDeviceSensor(v)
{
	m_Offset             = v.m_Offset;
	m_DiskAngle          = v.m_DiskAngle;
	m_MaxAngle           = v.m_MaxAngle;
	m_MinAngle           = v.m_MinAngle;
	m_Rotation           = v.m_Rotation;
	GetRuntimeClass()->Reference();
}

vrCylinderSensor::~vrCylinderSensor(void)
{
	GetRuntimeClass()->Dereference();
}

vrCylinderSensor& vrCylinderSensor::operator=(const vrCylinderSensor& v)
{
	vrPointingDeviceSensor::operator=(v);

	m_Offset             = v.m_Offset;
	m_DiskAngle          = v.m_DiskAngle;
	m_MaxAngle           = v.m_MaxAngle;
	m_MinAngle           = v.m_MinAngle;
	m_Rotation           = v.m_Rotation;

	return *this;
}

SFNode vrCylinderSensor::Clone(void) const
{
	return new vrCylinderSensor(*this);
}

//----------------------------------------------------------------------
void vrCylinderSensor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_OFFSET_STR)
		{
			SetOffset(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_OFFSET_STR, &m_Offset);
		}
	else if (ev->m_FieldID == VRML_DISKANGLE_STR)
		{
			SetDiskAngle(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_DISKANGLE_STR, &m_DiskAngle);
		}
	else if (ev->m_FieldID == VRML_MAXANGLE_STR)
		{
			SetMaxAngle(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_MAXANGLE_STR, &m_MaxAngle);
		}
	else if (ev->m_FieldID == VRML_MINANGLE_STR)
		{
			SetMinAngle(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_MINANGLE_STR, &m_MinAngle);
		}
	else
		{
			vrPointingDeviceSensor::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrCylinderSensor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("offset", m_Offset, (SFFloat)0.0);
		//if (fieldName == "offset")
		//	return ((SFFloat)0.0 == m_Offset);

		CHECK_FIELD("diskAngle", m_DiskAngle, (SFFloat)0.262);
		//if (fieldName == "diskAngle")
		//	return ((SFFloat)0.262 == m_DiskAngle);

		CHECK_FIELD("maxAngle", m_MaxAngle, (SFFloat)-1.0);
		//if (fieldName == "maxAngle")
		//	return ((SFFloat)-1.0 == m_MaxAngle);

		CHECK_FIELD("minAngle", m_MinAngle, (SFFloat)0.0);
		//if (fieldName == "minAngle")
		//	return ((SFFloat)0.0 == m_MinAngle);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("offset")) return FALSE;
		if (!IsDefault("diskAngle")) return FALSE;
		if (!IsDefault("maxAngle")) return FALSE;
		if (!IsDefault("minAngle")) return FALSE;
	}

	return vrPointingDeviceSensor::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrCylinderSensor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "offset")
	{
		SetOffset(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "diskAngle")
	{
		SetDiskAngle(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "maxAngle")
	{
		SetMaxAngle(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "minAngle")
	{
		SetMinAngle(*((SFFloat *)val));
		return TRUE;
	}

	return vrPointingDeviceSensor::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "CylinderSensor.cxx"
