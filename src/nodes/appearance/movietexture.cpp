//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "MovieTexture.h"

IMPLEMENT_NODE(vrMovieTexture, vrPixelTexture);

//----------------------------------------------------------------------
vrMovieTexture::vrMovieTexture(void) : vrPixelTexture()
{
	//m_OrigUrl            = array;
	m_Loop               = FALSE;
	m_Speed              = 1.0;
	m_StartTime          = 0.0;
	m_StopTime           = 0.0;
	//m_Url                = array;
	m_Duration           = 0.0;
	m_IsActive           = FALSE;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFBOOL, VRML_LOOP_STR);
		AddExposedField(SFFLOAT, VRML_SPEED_STR);
		AddExposedField(SFTIME, VRML_STARTTIME_STR);
		AddExposedField(SFTIME, VRML_STOPTIME_STR);
		AddExposedField(MFSTRING, VRML_URL_STR);
		AddEventOut(SFFLOAT, VRML_DURATION_CHANGED_STR);
		AddEventOut(SFBOOL, VRML_ISACTIVE_STR);
		AddField(SFBOOL, VRML_REPEATS_STR);
		AddField(SFBOOL, VRML_REPEATT_STR);
	}
}

vrMovieTexture::vrMovieTexture(const vrMovieTexture& v) : vrPixelTexture(v)
{
	m_OrigUrl            = v.m_OrigUrl;
	m_Loop               = v.m_Loop;
	m_Speed              = v.m_Speed;
	m_StartTime          = v.m_StartTime;
	m_StopTime           = v.m_StopTime;
	m_Url                = v.m_Url;
	m_Duration           = v.m_Duration;
	m_IsActive           = v.m_IsActive;
	GetRuntimeClass()->Reference();
}

vrMovieTexture::~vrMovieTexture(void)
{
	m_OrigUrl.Clear();
	m_Url.Clear();
	GetRuntimeClass()->Dereference();
}

vrMovieTexture& vrMovieTexture::operator=(const vrMovieTexture& v)
{
	vrPixelTexture::operator=(v);

	m_OrigUrl.Clear();
	m_OrigUrl            = v.m_OrigUrl;
	m_Loop               = v.m_Loop;
	m_Speed              = v.m_Speed;
	m_StartTime          = v.m_StartTime;
	m_StopTime           = v.m_StopTime;
	m_Url.Clear();
	m_Url                = v.m_Url;
	m_Duration           = v.m_Duration;
	m_IsActive           = v.m_IsActive;

	return *this;
}

SFNode vrMovieTexture::Clone(void) const
{
	return new vrMovieTexture(*this);
}

//----------------------------------------------------------------------
/*
void vrMovieTexture::ReceiveEventIn(vrEvent *ev)
{
}
*/

//----------------------------------------------------------------------
SFBool vrMovieTexture::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("loop", m_Loop, FALSE);
		//if (fieldName == "loop")
		//	return (FALSE == m_Loop);

		CHECK_FIELD("speed", m_Speed, (SFFloat)1.0);
		//if (fieldName == "speed")
		//	return ((SFFloat)1.0 == m_Speed);

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
		if (!IsDefault("loop")) return FALSE;
		if (!IsDefault("speed")) return FALSE;
		if (!IsDefault("startTime")) return FALSE;
		if (!IsDefault("stopTime")) return FALSE;
		if (!IsDefault("url")) return FALSE;
	}

	return vrPixelTexture::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrMovieTexture::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "loop")
	{
		SetLoop(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "speed")
	{
		SetSpeed(*((SFFloat *)val));
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
	
	return vrPixelTexture::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "MovieTexture.cxx"
