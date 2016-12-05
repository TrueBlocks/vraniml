//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Sound.h"
#include "AudioClip.h"

IMPLEMENT_NODE(vrSound, vrNode);

//----------------------------------------------------------------------
vrSound::vrSound(void) : vrNode()
{
	m_Direction          = zAxis;
	m_Intensity          = 1.0;
	m_Location           = origin;
	m_MaxBack            = 10.0;
	m_MaxFront           = 10.0;
	m_MinBack            = 1.0;
	m_MinFront           = 1.0;
	m_Priority           = 0.0;
	m_Source             = NULL;
	m_Spatialize         = TRUE;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFVEC3F, VRML_DIRECTION_STR);
		AddExposedField(SFFLOAT, VRML_INTENSITY_STR);
		AddExposedField(SFVEC3F, VRML_LOCATION_STR);
		AddExposedField(SFFLOAT, VRML_MAXBACK_STR);
		AddExposedField(SFFLOAT, VRML_MAXFRONT_STR);
		AddExposedField(SFFLOAT, VRML_MINBACK_STR);
		AddExposedField(SFFLOAT, VRML_MINFRONT_STR);
		AddExposedField(SFFLOAT, VRML_PRIORITY_STR);
		AddExposedField(SFNODE, VRML_SOURCE_STR);
	  AddField(SFBOOL, VRML_SPATIALIZE_STR);
	}
}

vrSound::vrSound(const vrSound& v) : vrNode(v)
{
	m_Direction          = v.m_Direction;
	m_Intensity          = v.m_Intensity;
	m_Location           = v.m_Location;
	m_MaxBack            = v.m_MaxBack;
	m_MaxFront           = v.m_MaxFront;
	m_MinBack            = v.m_MinBack;
	m_MinFront           = v.m_MinFront;
	m_Priority           = v.m_Priority;
	m_Source=NULL;
	SetSource(((v.m_Source) ? (vrAudioClip*)v.m_Source->Clone() : NULL));
	m_Spatialize         = v.m_Spatialize;
	GetRuntimeClass()->Reference();
}

vrSound::~vrSound(void)
{
	vrDELETE(m_Source);
	GetRuntimeClass()->Dereference();
}

vrSound& vrSound::operator=(const vrSound& v)
{
	vrNode::operator=(v);

	m_Direction          = v.m_Direction;
	m_Intensity          = v.m_Intensity;
	m_Location           = v.m_Location;
	m_MaxBack            = v.m_MaxBack;
	m_MaxFront           = v.m_MaxFront;
	m_MinBack            = v.m_MinBack;
	m_MinFront           = v.m_MinFront;
	m_Priority           = v.m_Priority;
	vrDELETE(m_Source);
	SetSource(((v.m_Source) ? (vrAudioClip*)v.m_Source->Clone() : NULL));
	m_Spatialize         = v.m_Spatialize;

	return *this;
}

SFNode vrSound::Clone(void) const
{
	return new vrSound(*this);
}

//----------------------------------------------------------------------
void vrSound::SetSource(const vrAudioClip* source)
{
	vrDELETE(m_Source);
	m_Source = (vrAudioClip*)source; //((source) ? (vrAudioClip*)source->Clone() : NULL);
	if (m_Source)
		m_Source->Reference();
}

void vrSound::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_DIRECTION_STR)
		{
			SetDirection(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_DIRECTION_STR, &m_Direction);
		}
	else if (ev->m_FieldID == VRML_INTENSITY_STR)
		{
			SetIntensity(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_INTENSITY_STR, &m_Intensity);
		}
	else if (ev->m_FieldID == VRML_LOCATION_STR)
		{
			SetLocation(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_LOCATION_STR, &m_Location);
		}
	else if (ev->m_FieldID == VRML_MAXBACK_STR)
		{
			SetMaxBack(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_MAXBACK_STR, &m_MaxBack);
		}
	else if (ev->m_FieldID == VRML_MAXFRONT_STR)
		{
			SetMaxFront(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_MAXFRONT_STR, &m_MaxFront);
		}
	else if (ev->m_FieldID == VRML_MINBACK_STR)
		{
			SetMinBack(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_MINBACK_STR, &m_MinBack);
		}
	else if (ev->m_FieldID == VRML_MINFRONT_STR)
		{
			SetMinFront(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_MINFRONT_STR, &m_MinFront);
		}
	else if (ev->m_FieldID == VRML_PRIORITY_STR)
		{
			SetPriority(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_PRIORITY_STR, &m_Priority);
		}
	else if (ev->m_FieldID == VRML_SOURCE_STR)
		{
			SetSource(*((vrAudioClip* *)ev->m_Value));
			SendEventOut(VRML_SOURCE_STR, &m_Source);
		}
}

//----------------------------------------------------------------------
SFNode vrSound::FindByType(vrRuntimeClass *pClass) const
{
	if (m_Source && m_Source->IsKindOf(pClass))
		return ((SFNode)m_Source);

	return vrNode::FindByType(pClass);
}

SFNode vrSound::FindByName(const SFString& nodeName) const
{
	SFNode node = NULL;

	if (m_Source && ((node = m_Source->FindByName(nodeName)) != NULL))
		return (node);

	return vrNode::FindByName(nodeName);
}

SFBool vrSound::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	if (m_Source)
		m_Source->ForEvery(userFn, userData, afterFn);

	return vrNode::ForEvery(userFn, userData, afterFn);
}


//----------------------------------------------------------------------
SFBool vrSound::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("direction", m_Direction, zAxis);
		//if (fieldName == "direction")
		//	return (zAxis == m_Direction);

		CHECK_FIELD("intensity", m_Intensity, (SFFloat)1.0);
		//if (fieldName == "intensity")
		//	return ((SFFloat)1.0 == m_Intensity);

		CHECK_FIELD("location", m_Location, origin);
		//if (fieldName == "location")
		//	return (origin == m_Location);

		CHECK_FIELD("maxBack", m_MaxBack, (SFFloat)10.0);
		//if (fieldName == "maxBack")
		//	return ((SFFloat)10.0 == m_MaxBack);

		CHECK_FIELD("maxFront", m_MaxFront, (SFFloat)10.0);
		//if (fieldName == "maxFront")
		//	return ((SFFloat)10.0 == m_MaxFront);

		CHECK_FIELD("minBack", m_MinBack, (SFFloat)1.0);
		//if (fieldName == "minBack")
		//	return ((SFFloat)1.0 == m_MinBack);

		CHECK_FIELD("minFront", m_MinFront, (SFFloat)1.0);
		//if (fieldName == "minFront")
		//	return ((SFFloat)1.0 == m_MinFront);

		CHECK_FIELD("priority", m_Priority, (SFFloat)0.0);
		//if (fieldName == "priority")
		//	return ((SFFloat)0.0 == m_Priority);

		CHECK_FIELD("source", m_Source, NULL);
		//if (fieldName == "source")
		//	return (NULL == m_Source);

		CHECK_FIELD("spatialize", m_Spatialize, TRUE);
		//if (fieldName == "spatialize")
		//	return (TRUE == m_Spatialize);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("direction")) return FALSE;
		if (!IsDefault("intensity")) return FALSE;
		if (!IsDefault("location")) return FALSE;
		if (!IsDefault("maxBack")) return FALSE;
		if (!IsDefault("maxFront")) return FALSE;
		if (!IsDefault("minBack")) return FALSE;
		if (!IsDefault("minFront")) return FALSE;
		if (!IsDefault("priority")) return FALSE;
		if (!IsDefault("source")) return FALSE;
		if (!IsDefault("spatialize")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

void vrSound::AddChild(SFNode node)
{
	ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrAudioClip)));
	SetSource((vrAudioClip*)node);
}

//----------------------------------------------------------------------
SFBool vrSound::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "direction")
	{
		SetDirection(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "intensity")
	{
		SetIntensity(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "location")
	{
		SetLocation(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "maxBack")
	{
		SetMaxBack(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "maxFront")
	{
		SetMaxFront(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "minBack")
	{
		SetMinBack(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "minFront")
	{
		SetMinFront(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "priority")
	{
		SetPriority(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "source")
	{
		AddChild((SFNode)val);
		return TRUE;
	} else if (fieldName == "spatialize")
	{
		SetSpatialize(*((SFBool *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
