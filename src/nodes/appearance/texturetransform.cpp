//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "TextureTransform.h"

IMPLEMENT_NODE(vrTextureTransform, vrNode);

//----------------------------------------------------------------------
vrTextureTransform::vrTextureTransform(void) : vrNode()
{
	m_Center             = origin2;
	m_Rotation           = 0.0;
	m_Scale              = xy1;
	m_Translation        = origin2;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFVEC2F, VRML_CENTER_STR);
		AddExposedField(SFFLOAT, VRML_ROTATION_STR);
		AddExposedField(SFVEC2F, VRML_SCALE_STR);
		AddExposedField(SFVEC2F, VRML_TRANSLATION_STR);
	}
}

vrTextureTransform::vrTextureTransform(const vrTextureTransform& v) : vrNode(v)
{
	m_Center             = v.m_Center;
	m_Rotation           = v.m_Rotation;
	m_Scale              = v.m_Scale;
	m_Translation        = v.m_Translation;
	GetRuntimeClass()->Reference();
}

vrTextureTransform::~vrTextureTransform(void)
{
	GetRuntimeClass()->Dereference();
}

vrTextureTransform& vrTextureTransform::operator=(const vrTextureTransform& v)
{
	vrNode::operator=(v);

	m_Center             = v.m_Center;
	m_Rotation           = v.m_Rotation;
	m_Scale              = v.m_Scale;
	m_Translation        = v.m_Translation;

	return *this;
}

SFNode vrTextureTransform::Clone(void) const
{
	return new vrTextureTransform(*this);
}

//----------------------------------------------------------------------
void vrTextureTransform::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_CENTER_STR)
		{
			SetCenter(*((SFVec2f *)ev->m_Value));
			SendEventOut(VRML_CENTER_STR, &m_Center);
		}
	else if (ev->m_FieldID == VRML_ROTATION_STR)
		{
			SetRotation(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_ROTATION_STR, &m_Rotation);
		}
	else if (ev->m_FieldID == VRML_SCALE_STR)
		{
			SetScale(*((SFVec2f *)ev->m_Value));
			SendEventOut(VRML_SCALE_STR, &m_Scale);
		}
	else if (ev->m_FieldID == VRML_TRANSLATION_STR)
		{
			SetTranslation(*((SFVec2f *)ev->m_Value));
			SendEventOut(VRML_TRANSLATION_STR, &m_Translation);
		}
}

//----------------------------------------------------------------------
SFBool vrTextureTransform::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("center", m_Center, origin2);
		//if (fieldName == "center")
		//	return (origin2 == m_Center);

		CHECK_FIELD("rotation", m_Rotation, (SFFloat)0.0);
		//if (fieldName == "rotation")
		//	return ((SFFloat)0.0 == m_Rotation);

		CHECK_FIELD("scale", m_Scale, xy1);
		//if (fieldName == "scale")
		//	return (xy1 == m_Scale);

		CHECK_FIELD("translation", m_Translation, origin2);
		//if (fieldName == "translation")
		//	return (origin2 == m_Translation);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("center")) return FALSE;
		if (!IsDefault("rotation")) return FALSE;
		if (!IsDefault("scale")) return FALSE;
		if (!IsDefault("translation")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrTextureTransform::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "center")
	{
		SetCenter(*((SFVec2f *)val));
		return TRUE;
	} else if (fieldName == "rotation")
	{
		SetRotation(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "scale")
	{
		SetScale(*((SFVec2f *)val));
		return TRUE;
	} else if (fieldName == "translation")
	{
		SetTranslation(*((SFVec2f *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
