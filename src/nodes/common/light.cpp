//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Light.h"

IMPLEMENT_NODE(vrLight, vrNode);

//----------------------------------------------------------------------
vrLight::vrLight(void) : vrNode()
{
	m_On                 = TRUE ;
	m_Color              = vrWhite;
	m_Intensity          = 1.0;
	m_AmbientIntensity   = 0.0;
	m_LightID            = AllocateLightID();
	m_Attenuation        = xAxis;
}

vrLight::vrLight(const vrLight& v) : vrNode(v)
{
	m_On                 = v.m_On;
	m_Color              = v.m_Color;
	m_Intensity          = v.m_Intensity;
	m_AmbientIntensity   = v.m_AmbientIntensity;
	m_LightID            = AllocateLightID();
	m_Attenuation        = v.m_Attenuation;
}

vrLight::~vrLight(void)
{
	FreeLightID(m_LightID);
	m_LightID=-1;
}

vrLight& vrLight::operator=(const vrLight& v)
{
	vrNode::operator=(v);

	m_On                 = v.m_On;
	m_Color              = v.m_Color;
	m_Intensity          = v.m_Intensity;
	m_AmbientIntensity   = v.m_AmbientIntensity;
	m_LightID            = AllocateLightID();
	m_Attenuation        = v.m_Attenuation;

	return *this;
}

SFNode vrLight::Clone(void) const
{
	return new vrLight(*this);
}

//----------------------------------------------------------------------
void vrLight::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_ON_STR)
		{
			SetOn(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_ON_STR, &m_On);
		}
	else if (ev->m_FieldID == VRML_COLOR_STR)
		{
			SetColor(*((SFColor *)ev->m_Value));
			SendEventOut(VRML_COLOR_STR, &m_Color);
		}
	else if (ev->m_FieldID == VRML_INTENSITY_STR)
		{
			SetIntensity(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_INTENSITY_STR, &m_Intensity);
		}
	else if (ev->m_FieldID == VRML_AMBIENTINTENSITY_STR)
		{
			SetAmbientIntensity(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_AMBIENTINTENSITY_STR, &m_AmbientIntensity);
		}
	else if (ev->m_FieldID == VRML_ATTENUATION_STR)
		{
			SetAttenuation(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_ATTENUATION_STR, &m_Attenuation);
		}
}

//----------------------------------------------------------------------
SFBool vrLight::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("on", m_On, TRUE);
		//if (fieldName == "on")
		//	return (TRUE  == m_On);

		CHECK_FIELD("color", m_Color, vrWhite);
		//if (fieldName == "color")
		//	return (vrWhite == m_Color);

		CHECK_FIELD("intensity", m_Intensity, (SFFloat)1.0);
		//if (fieldName == "intensity")
		//	return ((SFFloat)1.0 == m_Intensity);

		CHECK_FIELD("ambientIntensity", m_AmbientIntensity, (SFFloat)0.0);
		//if (fieldName == "ambientIntensity")
		//	return ((SFFloat)0.0 == m_AmbientIntensity);

		CHECK_FIELD("attenuation", m_Attenuation, xAxis);
		//if (fieldName == "attenuation")
		//	return (xAxis == m_Attenuation);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("on")) return FALSE;
		if (!IsDefault("color")) return FALSE;
		if (!IsDefault("intensity")) return FALSE;
		if (!IsDefault("ambientIntensity")) return FALSE;
		if (!IsDefault("attenuation")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrLight::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "on")
	{
		SetOn(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "color")
	{
		SetColor(*((SFColor *)val));
		return TRUE;
	} else if (fieldName == "intensity")
	{
		SetIntensity(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "ambientIntensity")
	{
		SetAmbientIntensity(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "attenuation")
	{
		SetAttenuation(*((SFVec3f *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

//----------------------------------------------------------------------
#include "Light.cxx"
