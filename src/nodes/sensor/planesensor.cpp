//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "PlaneSensor.h"

IMPLEMENT_NODE(vrPlaneSensor, vrPointingDeviceSensor);

//----------------------------------------------------------------------
vrPlaneSensor::vrPlaneSensor(void) : vrPointingDeviceSensor()
{
	m_Offset             = origin;
	m_MaxPosition        = xy1*-1;
	m_MinPosition        = origin2;
	m_Translation        = origin;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFVEC3F, VRML_OFFSET_STR);
		AddExposedField(SFVEC2F, VRML_MAXPOSITION_STR);
		AddExposedField(SFVEC2F, VRML_MINPOSITION_STR);
		AddEventOut(SFVEC3F, VRML_TRANSLATION_CHANGED_STR);
		AddExposedField(SFBOOL, VRML_AUTOOFFSET_STR);
		AddEventOut(SFVEC3F, VRML_TRACKPOINT_CHANGED_STR);
		AddExposedField(SFBOOL, VRML_ENABLED_STR);
		AddEventOut(SFBOOL, VRML_ISACTIVE_STR);
	}
}

vrPlaneSensor::vrPlaneSensor(const vrPlaneSensor& v) : vrPointingDeviceSensor(v)
{
	m_Offset             = v.m_Offset;
	m_MaxPosition        = v.m_MaxPosition;
	m_MinPosition        = v.m_MinPosition;
	m_Translation        = v.m_Translation;
	GetRuntimeClass()->Reference();
}

vrPlaneSensor::~vrPlaneSensor(void)
{
	GetRuntimeClass()->Dereference();
}

vrPlaneSensor& vrPlaneSensor::operator=(const vrPlaneSensor& v)
{
	vrPointingDeviceSensor::operator=(v);

	m_Offset             = v.m_Offset;
	m_MaxPosition        = v.m_MaxPosition;
	m_MinPosition        = v.m_MinPosition;
	m_Translation        = v.m_Translation;

	return *this;
}

SFNode vrPlaneSensor::Clone(void) const
{
	return new vrPlaneSensor(*this);
}

//----------------------------------------------------------------------
void vrPlaneSensor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_OFFSET_STR)
		{
			SetOffset(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_OFFSET_STR, &m_Offset);
		}
	else if (ev->m_FieldID == VRML_MAXPOSITION_STR)
		{
			SetMaxPosition(*((SFVec2f *)ev->m_Value));
			SendEventOut(VRML_MAXPOSITION_STR, &m_MaxPosition);
		}
	else if (ev->m_FieldID == VRML_MINPOSITION_STR)
		{
			SetMinPosition(*((SFVec2f *)ev->m_Value));
			SendEventOut(VRML_MINPOSITION_STR, &m_MinPosition);
		}
	else
		{
			vrPointingDeviceSensor::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrPlaneSensor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("offset", m_Offset, origin);
		//if (fieldName == "offset")
		//	return (origin == m_Offset);

		CHECK_FIELD("maxPosition", m_MaxPosition, xy1*-1);
		//if (fieldName == "maxPosition")
		//	return (xy1*-1 == m_MaxPosition);

		CHECK_FIELD("minPosition", m_MinPosition, origin2);
		//if (fieldName == "minPosition")
		//	return (origin2 == m_MinPosition);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("offset")) return FALSE;
		if (!IsDefault("maxPosition")) return FALSE;
		if (!IsDefault("minPosition")) return FALSE;
	}

	return vrPointingDeviceSensor::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrPlaneSensor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "offset")
	{
		SetOffset(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "maxPosition")
	{
		SetMaxPosition(*((SFVec2f *)val));
		return TRUE;
	} else if (fieldName == "minPosition")
	{
		SetMinPosition(*((SFVec2f *)val));
		return TRUE;
	}
	
	return vrPointingDeviceSensor::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "PlaneSensor.cxx"
