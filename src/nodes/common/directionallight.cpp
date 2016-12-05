//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "DirectionalLight.h"

IMPLEMENT_NODE(vrDirectionalLight, vrLight);

//----------------------------------------------------------------------
vrDirectionalLight::vrDirectionalLight(void) : vrLight()
{
	m_Direction          = -zAxis;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFVEC3F, VRML_DIRECTION_STR);
		AddExposedField(SFBOOL, VRML_ON_STR);
		AddExposedField(SFCOLOR, VRML_COLOR_STR);
		AddExposedField(SFFLOAT, VRML_INTENSITY_STR);
		AddExposedField(SFFLOAT, VRML_AMBIENTINTENSITY_STR);
	}
}

vrDirectionalLight::vrDirectionalLight(const vrDirectionalLight& v) : vrLight(v)
{
	m_Direction          = v.m_Direction;
	GetRuntimeClass()->Reference();
}

vrDirectionalLight::~vrDirectionalLight(void)
{
	GetRuntimeClass()->Dereference();
}

vrDirectionalLight& vrDirectionalLight::operator=(const vrDirectionalLight& v)
{
	vrLight::operator=(v);

	m_Direction          = v.m_Direction;

	return *this;
}

SFNode vrDirectionalLight::Clone(void) const
{
	return new vrDirectionalLight(*this);
}

//----------------------------------------------------------------------
void vrDirectionalLight::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_DIRECTION_STR)
		{
			SetDirection(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_DIRECTION_STR, &m_Direction);
		}
	else
		{
			vrLight::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrDirectionalLight::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("direction", m_Direction, -zAxis);
		//if (fieldName == "direction")
		//	return (-zAxis == m_Direction);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("direction")) return FALSE;
	}

	return vrLight::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrDirectionalLight::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "direction")
	{
		SetDirection(*((SFVec3f *)val));
		return TRUE;
	}
	
	return vrLight::SetFieldValue(fieldName, val);
}
