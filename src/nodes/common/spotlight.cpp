//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "SpotLight.h"

IMPLEMENT_NODE(vrSpotLight, vrLight);

//----------------------------------------------------------------------
vrSpotLight::vrSpotLight(void) : vrLight()
{
	m_BeamWidth          = 1.570796;
	m_CutOffAngle        = 0.785398;
	m_Direction          = -zAxis;
	m_Location           = origin;
	m_Radius             = 100 ;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFFLOAT, VRML_BEAMWIDTH_STR);
		AddExposedField(SFFLOAT, VRML_CUTOFFANGLE_STR);
		AddExposedField(SFVEC3F, VRML_DIRECTION_STR);
		AddExposedField(SFVEC3F, VRML_LOCATION_STR);
		AddExposedField(SFFLOAT, VRML_RADIUS_STR);
		AddExposedField(SFBOOL, VRML_ON_STR);
		AddExposedField(SFCOLOR, VRML_COLOR_STR);
		AddExposedField(SFFLOAT, VRML_INTENSITY_STR);
		AddExposedField(SFFLOAT, VRML_AMBIENTINTENSITY_STR);
		AddExposedField(SFVEC3F, VRML_ATTENUATION_STR);
	}
}

vrSpotLight::vrSpotLight(const vrSpotLight& v) : vrLight(v)
{
	m_BeamWidth          = v.m_BeamWidth;
	m_CutOffAngle        = v.m_CutOffAngle;
	m_Direction          = v.m_Direction;
	m_Location           = v.m_Location;
	m_Radius             = v.m_Radius;
	GetRuntimeClass()->Reference();
}

vrSpotLight::~vrSpotLight(void)
{
	GetRuntimeClass()->Dereference();
}

vrSpotLight& vrSpotLight::operator=(const vrSpotLight& v)
{
	vrLight::operator=(v);

	m_BeamWidth          = v.m_BeamWidth;
	m_CutOffAngle        = v.m_CutOffAngle;
	m_Direction          = v.m_Direction;
	m_Location           = v.m_Location;
	m_Radius             = v.m_Radius;

	return *this;
}

SFNode vrSpotLight::Clone(void) const
{
	return new vrSpotLight(*this);
}

//----------------------------------------------------------------------
void vrSpotLight::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_BEAMWIDTH_STR)
		{
			SetBeamWidth(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_BEAMWIDTH_STR, &m_BeamWidth);
		}
	else if (ev->m_FieldID == VRML_CUTOFFANGLE_STR)
		{
			SetCutOffAngle(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_CUTOFFANGLE_STR, &m_CutOffAngle);
		}
	else if (ev->m_FieldID == VRML_DIRECTION_STR)
		{
			SetDirection(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_DIRECTION_STR, &m_Direction);
		}
	else if (ev->m_FieldID == VRML_LOCATION_STR)
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
SFBool vrSpotLight::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("beamWidth", m_BeamWidth, (SFFloat)1.570796);
		//if (fieldName == "beamWidth")
		//	return ((SFFloat)1.570796 == m_BeamWidth);

		CHECK_FIELD("cutOffAngle", m_CutOffAngle, (SFFloat)0.785398);
		//if (fieldName == "cutOffAngle")
		//	return ((SFFloat)0.785398 == m_CutOffAngle);

		CHECK_FIELD("direction", m_Direction, -zAxis);
		//if (fieldName == "direction")
		//	return (-zAxis == m_Direction);

		CHECK_FIELD("location", m_Location, origin);
		//if (fieldName == "location")
		//	return (origin == m_Location);

		CHECK_FIELD("radius", m_Radius, (SFFloat)100);
		//if (fieldName == "radius")
		//	return ((SFFloat)100  == m_Radius);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("beamWidth")) return FALSE;
		if (!IsDefault("cutOffAngle")) return FALSE;
		if (!IsDefault("direction")) return FALSE;
		if (!IsDefault("location")) return FALSE;
		if (!IsDefault("radius")) return FALSE;
	}

	return vrLight::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrSpotLight::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "beamWidth")
	{
		SetBeamWidth(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "cutOffAngle")
	{
		SetCutOffAngle(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "direction")
	{
		SetDirection(*((SFVec3f *)val));
		return TRUE;
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
