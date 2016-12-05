//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "PointLight.h"

IMPLEMENT_NODE(vrPointLight, vrLight);

//----------------------------------------------------------------------
vrPointLight::vrPointLight(void) : vrLight()
{
	m_Location           = origin;
	m_Radius             = 100.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFVEC3F, VRML_LOCATION_STR);
		AddExposedField(SFFLOAT, VRML_RADIUS_STR);
		AddExposedField(SFBOOL, VRML_ON_STR);
		AddExposedField(SFCOLOR, VRML_COLOR_STR);
		AddExposedField(SFFLOAT, VRML_INTENSITY_STR);
		AddExposedField(SFFLOAT, VRML_AMBIENTINTENSITY_STR);
		AddExposedField(SFVEC3F, VRML_ATTENUATION_STR);
	}
}

vrPointLight::vrPointLight(const vrPointLight& v) : vrLight(v)
{
	m_Location           = v.m_Location;
	m_Radius             = v.m_Radius;
	GetRuntimeClass()->Reference();
}

vrPointLight::~vrPointLight(void)
{
	GetRuntimeClass()->Dereference();
}

vrPointLight& vrPointLight::operator=(const vrPointLight& v)
{
	vrLight::operator=(v);

	m_Location           = v.m_Location;
	m_Radius             = v.m_Radius;

	return *this;
}

SFNode vrPointLight::Clone(void) const
{
	return new vrPointLight(*this);
}

//----------------------------------------------------------------------
void vrPointLight::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_LOCATION_STR)
		{
			SetLocation(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_LOCATION_STR, &m_Location);
		}
	else if (ev->m_FieldID == VRML_RADIUS_STR)
		{
			SetRadius(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_RADIUS_STR, &m_Radius);
		}
	else
		{
			vrLight::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrPointLight::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("location", m_Location, origin);
		//if (fieldName == "location")
		//	return (origin == m_Location);

		CHECK_FIELD("radius", m_Radius, (SFFloat)100.0);
		//if (fieldName == "radius")
		//	return ((SFFloat)100.0 == m_Radius);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("location")) return FALSE;
		if (!IsDefault("radius")) return FALSE;
	}

	return vrLight::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrPointLight::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "location")
	{
		SetLocation(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "radius")
	{
		SetRadius(*((SFFloat *)val));
		return TRUE;
	}
	
	return vrLight::SetFieldValue(fieldName, val);
}
