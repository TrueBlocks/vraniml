//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "ImageTexture.h"

IMPLEMENT_NODE(vrImageTexture, vrPixelTexture);

//----------------------------------------------------------------------
vrImageTexture::vrImageTexture(void) : vrPixelTexture()
{
	//m_OrigUrl            = array;
	//m_Url                = array;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFSTRING, VRML_URL_STR);
		AddField(SFBOOL, VRML_REPEATS_STR);
		AddField(SFBOOL, VRML_REPEATT_STR);
	}
}

vrImageTexture::vrImageTexture(const vrImageTexture& v) : vrPixelTexture(v)
{
	m_OrigUrl            = v.m_OrigUrl;
	m_Url                = v.m_Url;
	GetRuntimeClass()->Reference();
}

vrImageTexture::~vrImageTexture(void)
{
	m_OrigUrl.Clear();
	m_Url.Clear();
	GetRuntimeClass()->Dereference();
}

vrImageTexture& vrImageTexture::operator=(const vrImageTexture& v)
{
	vrPixelTexture::operator=(v);

	m_OrigUrl.Clear();
	m_OrigUrl            = v.m_OrigUrl;
	m_Url.Clear();
	m_Url                = v.m_Url;

	return *this;
}

SFNode vrImageTexture::Clone(void) const
{
	return new vrImageTexture(*this);
}

//----------------------------------------------------------------------
void vrImageTexture::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_URL_STR)
		{
			SetUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_URL_STR, &m_Url);
		}
	else
		{
			vrPixelTexture::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrImageTexture::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("url", GetNUrls(), m_Url, 0);
		//if (fieldName == "url")
		//	return (0 == GetNUrls()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("url")) return FALSE;
	}

	return vrPixelTexture::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrImageTexture::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
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
