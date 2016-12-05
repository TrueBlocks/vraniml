//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Material.h"

IMPLEMENT_NODE(vrMaterial, vrNode);

//----------------------------------------------------------------------
vrMaterial::vrMaterial(void) : vrNode()
{
	m_AmbientIntensity   = 0.2;
	m_DiffuseColor       = vrWhite*0.8;
	m_EmissiveColor      = vrBlack;
	m_Shininess          = 0.2;
	m_SpecularColor      = vrBlack;
	m_Transparency       = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFFLOAT, VRML_AMBIENTINTENSITY_STR);
		AddExposedField(SFCOLOR, VRML_DIFFUSECOLOR_STR);
		AddExposedField(SFCOLOR, VRML_EMISSIVECOLOR_STR);
		AddExposedField(SFFLOAT, VRML_SHININESS_STR);
		AddExposedField(SFCOLOR, VRML_SPECULARCOLOR_STR);
		AddExposedField(SFFLOAT, VRML_TRANSPARENCY_STR);
	}
}

vrMaterial::vrMaterial(const vrMaterial& v) : vrNode(v)
{
	m_AmbientIntensity   = v.m_AmbientIntensity;
	m_DiffuseColor       = v.m_DiffuseColor;
	m_EmissiveColor      = v.m_EmissiveColor;
	m_Shininess          = v.m_Shininess;
	m_SpecularColor      = v.m_SpecularColor;
	m_Transparency       = v.m_Transparency;
	GetRuntimeClass()->Reference();
}

vrMaterial::~vrMaterial(void)
{
	GetRuntimeClass()->Dereference();
}

vrMaterial& vrMaterial::operator=(const vrMaterial& v)
{
	vrNode::operator=(v);

	m_AmbientIntensity   = v.m_AmbientIntensity;
	m_DiffuseColor       = v.m_DiffuseColor;
	m_EmissiveColor      = v.m_EmissiveColor;
	m_Shininess          = v.m_Shininess;
	m_SpecularColor      = v.m_SpecularColor;
	m_Transparency       = v.m_Transparency;

	return *this;
}

SFNode vrMaterial::Clone(void) const
{
	return new vrMaterial(*this);
}

//----------------------------------------------------------------------
void vrMaterial::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_AMBIENTINTENSITY_STR)
		{
			SetAmbientIntensity(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_AMBIENTINTENSITY_STR, &m_AmbientIntensity);
		}
	else if (ev->m_FieldID == VRML_DIFFUSECOLOR_STR)
		{
			SetDiffuseColor(*((SFColor *)ev->m_Value));
			SendEventOut(VRML_DIFFUSECOLOR_STR, &m_DiffuseColor);
		}
	else if (ev->m_FieldID == VRML_EMISSIVECOLOR_STR)
		{
			SetEmissiveColor(*((SFColor *)ev->m_Value));
			SendEventOut(VRML_EMISSIVECOLOR_STR, &m_EmissiveColor);
		}
	else if (ev->m_FieldID == VRML_SHININESS_STR)
		{
			SetShininess(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_SHININESS_STR, &m_Shininess);
		}
	else if (ev->m_FieldID == VRML_SPECULARCOLOR_STR)
		{
			SetSpecularColor(*((SFColor *)ev->m_Value));
			SendEventOut(VRML_SPECULARCOLOR_STR, &m_SpecularColor);
		}
	else if (ev->m_FieldID == VRML_TRANSPARENCY_STR)
		{
			SetTransparency(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_TRANSPARENCY_STR, &m_Transparency);
		}
}

//----------------------------------------------------------------------
SFBool vrMaterial::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("ambientIntensity", m_AmbientIntensity, (SFFloat)0.2);
//		if (fieldName == "ambientIntensity")
//		{
//			if (field)
//			  SetValEx(field, (void*)&m_AmbientIntensity);
//			if (IsIsMapped(fieldName))
//				return TRUE;
//			return ((SFFloat)0.2 == m_AmbientIntensity);
//		}

		CHECK_FIELD("diffuseColor", m_DiffuseColor, vrWhite*0.8);
//		if (fieldName == "diffuseColor")
//		{
//			if (field)
//			  SetValEx(field, (void*)&m_DiffuseColor);
//			if (IsIsMapped(fieldName))
//				return TRUE;
//			return (vrWhite*0.8 == m_DiffuseColor);
//		}

		CHECK_FIELD("emissiveColor", m_EmissiveColor, vrBlack);
//		if (fieldName == "emissiveColor")
//		{
//			if (field)
//			  SetValEx(field, (void*)&m_EmissiveColor);
//			if (IsIsMapped(fieldName))
//				return TRUE;
//			return (vrBlack == m_EmissiveColor);
//		}

		CHECK_FIELD("shininess", m_Shininess, (SFFloat)0.2);
//		if (fieldName == "shininess")
//		{
//			if (field)
//			  SetValEx(field, (void*)&m_Shininess);
//			if (IsIsMapped(fieldName))
//				return TRUE;
//			return ((SFFloat)0.2 == m_Shininess);
//		}

		CHECK_FIELD("specularColor", m_SpecularColor, vrBlack);
//		if (fieldName == "specularColor")
//		{
//			if (field)
//			  SetValEx(field, (void*)&m_SpecularColor);
//			if (IsIsMapped(fieldName))
//				return TRUE;
//			return (vrBlack == m_SpecularColor);
//		}

		CHECK_FIELD("transparency", m_Transparency, (SFFloat)0.0);
//		if (fieldName == "transparency")
//		{
//			if (field)
//			  SetValEx(field, (void*)&m_Transparency);
//			if (IsIsMapped(fieldName))
//				return TRUE;
//			return ((SFFloat)0.0 == m_Transparency);
//		}

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("ambientIntensity")) return FALSE;
		if (!IsDefault("diffuseColor")) return FALSE;
		if (!IsDefault("emissiveColor")) return FALSE;
		if (!IsDefault("shininess")) return FALSE;
		if (!IsDefault("specularColor")) return FALSE;
		if (!IsDefault("transparency")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrMaterial::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "ambientIntensity")
	{
		SetAmbientIntensity(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "diffuseColor")
	{
		SetDiffuseColor(*((SFColor *)val));
		return TRUE;
	} else if (fieldName == "emissiveColor")
	{
		SetEmissiveColor(*((SFColor *)val));
		return TRUE;
	} else if (fieldName == "shininess")
	{
		SetShininess(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "specularColor")
	{
		SetSpecularColor(*((SFColor *)val));
		return TRUE;
	} else if (fieldName == "transparency")
	{
		SetTransparency(*((SFFloat *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

//----------------------------------------------------------------------
#include "Material.cxx"
