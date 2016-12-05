//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "PixelTexture.h"

IMPLEMENT_NODE(vrPixelTexture, vrNode);

//----------------------------------------------------------------------
vrPixelTexture::vrPixelTexture(void) : vrNode()
{
	m_RepeatS            = TRUE;
	m_RepeatT            = TRUE;
	m_Width              = 0;
	m_Height             = 0;
	m_NComponents        = 0;
	m_Format             = 0x1908; // do not change this it is an OpenGL #define
	m_ColorBuffer        = NULL;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFIMAGE, VRML_IMAGE_STR);
		AddField(SFBOOL, VRML_REPEATS_STR);
		AddField(SFBOOL, VRML_REPEATT_STR);
	}
}

vrPixelTexture::vrPixelTexture(const vrPixelTexture& v) : vrNode(v)
{
	m_RepeatS            = v.m_RepeatS;
	m_RepeatT            = v.m_RepeatT;
	m_Width              = v.m_Width;
	m_Height             = v.m_Height;
	m_NComponents        = v.m_NComponents;
	m_Format             = v.m_Format;
	m_ColorBuffer        = NULL;

	long size = m_Width * m_Height * m_NComponents;
	if (v.m_ColorBuffer && size)
	{
		m_ColorBuffer = (char *)malloc(size);
		memcpy(m_ColorBuffer, v.m_ColorBuffer, size);
	}
	GetRuntimeClass()->Reference();
}

vrPixelTexture::~vrPixelTexture(void)
{
	if (m_ColorBuffer)
		free(m_ColorBuffer);
	m_ColorBuffer = NULL;
	GetRuntimeClass()->Dereference();
}

vrPixelTexture& vrPixelTexture::operator=(const vrPixelTexture& v)
{
	vrNode::operator=(v);

	m_RepeatS            = v.m_RepeatS;
	m_RepeatT            = v.m_RepeatT;
	m_Width              = v.m_Width;
	m_Height             = v.m_Height;
	m_NComponents        = v.m_NComponents;
	m_Format             = v.m_Format;

	if (m_ColorBuffer)
		free(m_ColorBuffer);
	m_ColorBuffer = NULL;

	long size = m_Width * m_Height * m_NComponents;
	if (v.m_ColorBuffer && size)
	{
		m_ColorBuffer = (char *)malloc(size);
		memcpy(m_ColorBuffer, v.m_ColorBuffer, size);
	}

	return *this;
}

SFNode vrPixelTexture::Clone(void) const
{
	return new vrPixelTexture(*this);
}

//----------------------------------------------------------------------
void vrPixelTexture::SetColorBuffer(const SFImage& data)
{
	if (m_ColorBuffer)
		free(m_ColorBuffer);
	m_ColorBuffer = NULL;

	m_Width = data.m_Width;
	m_Height = data.m_Height;
	m_NComponents = data.m_nComponents;

	long size = m_Width * m_Height * m_NComponents;
	if (data.m_ColorData && size)
	{
		m_ColorBuffer = (char *)malloc(size);
		memcpy(m_ColorBuffer, (char *)data.m_ColorData, size);
	}
}

//----------------------------------------------------------------------
SFBool vrPixelTexture::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("repeatS", m_RepeatS, TRUE);
		//if (fieldName == "repeatS")
		//	return (TRUE == m_RepeatS);

		CHECK_FIELD("repeatT", m_RepeatT, TRUE);
		//if (fieldName == "repeatT")
		//	return (TRUE == m_RepeatT);

		CHECK_FIELD("width", m_Width, 0);
		//if (fieldName == "width")
		//	return (0 == m_Width);

		CHECK_FIELD("height", m_Height, 0);
		//if (fieldName == "height")
		//	return (0 == m_Height);

		CHECK_FIELD("nComponents", m_NComponents, 0);
		//if (fieldName == "nComponents")
		//	return (0 == m_NComponents);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("repeatS")) return FALSE;
		if (!IsDefault("repeatT")) return FALSE;
		if (!IsDefault("width")) return FALSE;
		if (!IsDefault("height")) return FALSE;
		if (!IsDefault("nComponents")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrPixelTexture::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "repeatS")
	{
		SetRepeatS(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "repeatT")
	{
		SetRepeatT(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "width")
	{
		SetWidth(*((SFInt32 *)val));
		return TRUE;
	} else if (fieldName == "height")
	{
		SetHeight(*((SFInt32 *)val));
		return TRUE;
	} else if (fieldName == "nComponents")
	{
		SetNComponents(*((SFInt32 *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

//----------------------------------------------------------------------
#include "PixelTexture.cxx"
