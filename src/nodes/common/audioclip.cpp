//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "AudioClip.h"

IMPLEMENT_NODE(vrAudioClip, vrNode);

//----------------------------------------------------------------------
vrAudioClip::vrAudioClip(void) : vrNode()
{
	//m_OrigUrl            = array;
  //m_Description        = NULL;
	m_Loop               = FALSE;
	m_Pitch              = 1.0;
	m_StartTime          = 0.0;
	m_StopTime           = 0.0;
	//m_Url                = array;
	m_Duration           = 0.0;
	m_IsActive           = FALSE;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFSTRING, VRML_DESCRIPTION_STR);
		AddExposedField(SFBOOL, VRML_LOOP_STR);
		AddExposedField(SFFLOAT, VRML_PITCH_STR);
		AddExposedField(SFTIME, VRML_STARTTIME_STR);
		AddExposedField(SFTIME, VRML_STOPTIME_STR);
		AddExposedField(MFSTRING, VRML_URL_STR);
		AddEventOut(SFTIME, VRML_DURATION_CHANGED_STR);
		AddEventOut(SFBOOL, VRML_ISACTIVE_STR);
	}
}

vrAudioClip::vrAudioClip(const vrAudioClip& v) : vrNode(v)
{
	m_OrigUrl            = v.m_OrigUrl;
	m_Description        = v.m_Description;
	m_Loop               = v.m_Loop;
	m_Pitch              = v.m_Pitch;
	m_StartTime          = v.m_StartTime;
	m_StopTime           = v.m_StopTime;
	m_Url                = v.m_Url;
	m_Duration           = v.m_Duration;
	m_IsActive           = v.m_IsActive;
	GetRuntimeClass()->Reference();
}

vrAudioClip::~vrAudioClip(void)
{
	m_OrigUrl.Clear();
	m_Url.Clear();
	GetRuntimeClass()->Dereference();
}

vrAudioClip& vrAudioClip::operator=(const vrAudioClip& v)
{
	vrNode::operator=(v);

	m_OrigUrl.Clear();
	m_OrigUrl            = v.m_OrigUrl;
	m_Description        = v.m_Description;
	m_Loop               = v.m_Loop;
	m_Pitch              = v.m_Pitch;
	m_StartTime          = v.m_StartTime;
	m_StopTime           = v.m_StopTime;
	m_Url.Clear();
	m_Url                = v.m_Url;
	m_Duration           = v.m_Duration;
	m_IsActive           = v.m_IsActive;

	return *this;
}

SFNode vrAudioClip::Clone(void) const
{
	return new vrAudioClip(*this);
}

//----------------------------------------------------------------------
void vrAudioClip::SetDescription(const SFString& description)
{
	m_Description = description;
}

/*
void vrAudioClip::ReceiveEventIn(vrEvent *ev)
{
}
*/

//----------------------------------------------------------------------
SFBool vrAudioClip::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_STRING_FIELD("description", m_Description);
		//if (fieldName == "description")
		//	return m_Description.Empty();

		CHECK_FIELD("loop", m_Loop, FALSE);
		//if (fieldName == "loop")
		//	return (FALSE == m_Loop);

		CHECK_FIELD("pitch", m_Pitch, (SFFloat)1.0);
		//if (fieldName == "pitch")
		//	return ((SFFloat)1.0 == m_Pitch);

		CHECK_FIELD("startTime", m_StartTime, 0.0);
		//if (fieldName == "startTime")
		//	return (0.0 == m_StartTime);

		CHECK_FIELD("stopTime", m_StopTime, 0.0);
		//if (fieldName == "stopTime")
		//	return (0.0 == m_StopTime);

		CHECK_ARRAY_FIELD("url", GetNUrls(), m_Url, 0);
		//if (fieldName == "url")
		//	return (0 == GetNUrls()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("description")) return FALSE;
		if (!IsDefault("loop")) return FALSE;
		if (!IsDefault("pitch")) return FALSE;
		if (!IsDefault("startTime")) return FALSE;
		if (!IsDefault("stopTime")) return FALSE;
		if (!IsDefault("url")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrAudioClip::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "description")
	{
		SetDescription(((char *)val));
		return TRUE;
	} else if (fieldName == "loop")
	{
		SetLoop(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "pitch")
	{
		SetPitch(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "startTime")
	{
		SetStartTime(*((SFTime *)val));
		return TRUE;
	} else if (fieldName == "stopTime")
	{
		SetStopTime(*((SFTime *)val));
		return TRUE;
	} else if (fieldName == "url")
	{
		SetOrigUrl(*((MFString *)val));
		MFString s;
		for (int i=0;i<((MFString *)val)->GetCount();i++)
			s.AddValue(vrExpandPath(GetOrigUrl(i)));
		SetUrl(s);
		s.Clear();
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

//----------------------------------------------------------------------
#include "AudioClip.cxx"
