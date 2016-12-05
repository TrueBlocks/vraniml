//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Transform.h"

IMPLEMENT_NODE(vrTransform, vrGroupingNode);

//----------------------------------------------------------------------
vrTransform::vrTransform(void) : vrGroupingNode()
{
	m_Center             = origin;
	m_Rotation           = defRotation;
	m_Scale              = xyz1;
	m_ScaleOrientation   = defRotation;
	m_Translation        = origin;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventIn(MFNODE, VRML_ADDCHILDREN_STR);
		AddEventIn(MFNODE, VRML_REMOVECHILDREN_STR);
		AddExposedField(MFNODE, VRML_CHILDREN_STR);
		AddExposedField(SFVEC3F, VRML_CENTER_STR);
		AddExposedField(SFROTATION, VRML_ROTATION_STR);
		AddExposedField(SFVEC3F, VRML_SCALE_STR);
		AddExposedField(SFROTATION, VRML_SCALEORIENTATION_STR);
		AddExposedField(SFVEC3F, VRML_TRANSLATION_STR);
		AddField(SFVEC3F, VRML_BBOXCENTER_STR);
		AddField(SFVEC3F, VRML_BBOXSIZE_STR);
	}
}

vrTransform::vrTransform(const vrTransform& v) : vrGroupingNode(v)
{
	m_Center             = v.m_Center;
	m_Rotation           = v.m_Rotation;
	m_Scale              = v.m_Scale;
	m_ScaleOrientation   = v.m_ScaleOrientation;
	m_Translation        = v.m_Translation;
	GetRuntimeClass()->Reference();
}

vrTransform::~vrTransform(void)
{
	GetRuntimeClass()->Dereference();
}

vrTransform& vrTransform::operator=(const vrTransform& v)
{
	vrGroupingNode::operator=(v);

	m_Center             = v.m_Center;
	m_Rotation           = v.m_Rotation;
	m_Scale              = v.m_Scale;
	m_ScaleOrientation   = v.m_ScaleOrientation;
	m_Translation        = v.m_Translation;

	return *this;
}

SFNode vrTransform::Clone(void) const
{
	return new vrTransform(*this);
}

//----------------------------------------------------------------------
void vrTransform::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_CENTER_STR)
		{
			SetCenter(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_CENTER_STR, &m_Center);
		}
	else if (ev->m_FieldID == VRML_ROTATION_STR)
		{
			SetRotation(*((SFRotation *)ev->m_Value));
			SendEventOut(VRML_ROTATION_STR, &m_Rotation);
		}
	else if (ev->m_FieldID == VRML_SCALE_STR)
		{
			SetScale(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_SCALE_STR, &m_Scale);
		}
	else if (ev->m_FieldID == VRML_SCALEORIENTATION_STR)
		{
			SetScaleOrientation(*((SFRotation *)ev->m_Value));
			SendEventOut(VRML_SCALEORIENTATION_STR, &m_ScaleOrientation);
		}
	else if (ev->m_FieldID == VRML_TRANSLATION_STR)
		{
			SetTranslation(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_TRANSLATION_STR, &m_Translation);
		}
	else
		{
			vrGroupingNode::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrTransform::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("center", m_Center, origin);
		//if (fieldName == "center")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_Center);
		//	return (origin == m_Center);
		//}

		CHECK_FIELD("rotation", m_Rotation, defRotation);
		//if (fieldName == "rotation")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_Rotation);
		//	return (defRotation == m_Rotation);
		//}

		CHECK_FIELD("scale", m_Scale, xyz1);
		//if (fieldName == "scale")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_Scale);
		//	return (xyz1 == m_Scale);
		//}

		CHECK_FIELD("scaleOrientation", m_ScaleOrientation, defRotation);
		//if (fieldName == "scaleOrientation")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_ScaleOrientation);
		//	return (defRotation == m_ScaleOrientation);
		//}

		CHECK_FIELD("translation", m_Translation, origin);
		//if (fieldName == "translation")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_Translation);
		//	return (origin == m_Translation);
		//}

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("center")) return FALSE;
		if (!IsDefault("rotation")) return FALSE;
		if (!IsDefault("scale")) return FALSE;
		if (!IsDefault("scaleOrientation")) return FALSE;
		if (!IsDefault("translation")) return FALSE;
	}

	return vrGroupingNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrTransform::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "center")
	{
		SetCenter(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "rotation")
	{
		SetRotation(*((SFRotation *)val));
		return TRUE;
	} else if (fieldName == "scale")
	{
		SetScale(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "scaleOrientation")
	{
		SetScaleOrientation(*((SFRotation *)val));
		return TRUE;
	} else if (fieldName == "translation")
	{
		SetTranslation(*((SFVec3f *)val));
		return TRUE;
	}
	
	return vrGroupingNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Transform.cxx"
