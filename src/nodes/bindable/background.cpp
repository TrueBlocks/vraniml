//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Background.h"
#include "Browser\Browser.h"
#include "Solid\Solid.h"

IMPLEMENT_NODE(vrBackground, vrBindable);

//----------------------------------------------------------------------
vrBackground::vrBackground(void) : vrBindable()
{
	//m_OrigBackUrl        = array;
	//m_OrigBottomUrl      = array;
	//m_OrigFrontUrl       = array;
	//m_OrigLeftUrl        = array;
	//m_OrigRightUrl       = array;
	//m_OrigTopUrl         = array;
	//m_GroundAngle        = array;
	//m_GroundColor        = array;
	//m_BackUrl            = array;
	//m_BottomUrl          = array;
	//m_FrontUrl           = array;
	//m_LeftUrl            = array;
	//m_RightUrl           = array;
	//m_TopUrl             = array;
	//m_SkyAngle           = array;
	//m_SkyColor           = array;
	m_BackgroundGroup    = NULL;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFFLOAT, VRML_GROUNDANGLE_STR);
		AddExposedField(MFCOLOR, VRML_GROUNDCOLOR_STR);
		AddExposedField(MFSTRING, VRML_BACKURL_STR);
		AddExposedField(MFSTRING, VRML_BOTTOMURL_STR);
		AddExposedField(MFSTRING, VRML_FRONTURL_STR);
		AddExposedField(MFSTRING, VRML_LEFTURL_STR);
		AddExposedField(MFSTRING, VRML_RIGHTURL_STR);
		AddExposedField(MFSTRING, VRML_TOPURL_STR);
		AddExposedField(MFFLOAT, VRML_SKYANGLE_STR);
		AddExposedField(MFCOLOR, VRML_SKYCOLOR_STR);
		AddEventIn(SFBOOL, VRML_SET_BIND_STR);
		AddEventOut(SFBOOL, VRML_ISBOUND_STR);
	}
}

vrBackground::vrBackground(const vrBackground& v) : vrBindable(v)
{
	m_OrigBackUrl        = v.m_OrigBackUrl;
	m_OrigBottomUrl      = v.m_OrigBottomUrl;
	m_OrigFrontUrl       = v.m_OrigFrontUrl;
	m_OrigLeftUrl        = v.m_OrigLeftUrl;
	m_OrigRightUrl       = v.m_OrigRightUrl;
	m_OrigTopUrl         = v.m_OrigTopUrl;
	m_GroundAngle        = v.m_GroundAngle;
	m_GroundColor        = v.m_GroundColor;
	m_BackUrl            = v.m_BackUrl;
	m_BottomUrl          = v.m_BottomUrl;
	m_FrontUrl           = v.m_FrontUrl;
	m_LeftUrl            = v.m_LeftUrl;
	m_RightUrl           = v.m_RightUrl;
	m_TopUrl             = v.m_TopUrl;
	m_SkyAngle           = v.m_SkyAngle;
	m_SkyColor           = v.m_SkyColor;
	m_BackgroundGroup    = NULL;
	GetRuntimeClass()->Reference();
}

vrBackground::~vrBackground(void)
{
	if (m_BoundTo)
		m_BoundTo->Bind(this, FALSE);
	m_BoundTo = NULL;
	m_OrigBackUrl.Clear();
	m_OrigBottomUrl.Clear();
	m_OrigFrontUrl.Clear();
	m_OrigLeftUrl.Clear();
	m_OrigRightUrl.Clear();
	m_OrigTopUrl.Clear();
	m_GroundAngle.Clear();
	m_GroundColor.Clear();
	m_BackUrl.Clear();
	m_BottomUrl.Clear();
	m_FrontUrl.Clear();
	m_LeftUrl.Clear();
	m_RightUrl.Clear();
	m_TopUrl.Clear();
	m_SkyAngle.Clear();
	m_SkyColor.Clear();
	vrDELETE(m_BackgroundGroup);
	GetRuntimeClass()->Dereference();
}

vrBackground& vrBackground::operator=(const vrBackground& v)
{
	vrBindable::operator=(v);

	m_OrigBackUrl.Clear();
	m_OrigBackUrl        = v.m_OrigBackUrl;
	m_OrigBottomUrl.Clear();
	m_OrigBottomUrl      = v.m_OrigBottomUrl;
	m_OrigFrontUrl.Clear();
	m_OrigFrontUrl       = v.m_OrigFrontUrl;
	m_OrigLeftUrl.Clear();
	m_OrigLeftUrl        = v.m_OrigLeftUrl;
	m_OrigRightUrl.Clear();
	m_OrigRightUrl       = v.m_OrigRightUrl;
	m_OrigTopUrl.Clear();
	m_OrigTopUrl         = v.m_OrigTopUrl;
	m_GroundAngle.Clear();
	m_GroundAngle        = v.m_GroundAngle;
	m_GroundColor.Clear();
	m_GroundColor        = v.m_GroundColor;
	m_BackUrl.Clear();
	m_BackUrl            = v.m_BackUrl;
	m_BottomUrl.Clear();
	m_BottomUrl          = v.m_BottomUrl;
	m_FrontUrl.Clear();
	m_FrontUrl           = v.m_FrontUrl;
	m_LeftUrl.Clear();
	m_LeftUrl            = v.m_LeftUrl;
	m_RightUrl.Clear();
	m_RightUrl           = v.m_RightUrl;
	m_TopUrl.Clear();
	m_TopUrl             = v.m_TopUrl;
	m_SkyAngle.Clear();
	m_SkyAngle           = v.m_SkyAngle;
	m_SkyColor.Clear();
	m_SkyColor           = v.m_SkyColor;
	vrDELETE(m_BackgroundGroup);
	m_BackgroundGroup    = NULL;

	return *this;
}

SFNode vrBackground::Clone(void) const
{
	return new vrBackground(*this);
}

//----------------------------------------------------------------------
void vrBackground::SetBackgroundGroup(const vrGroup* backgroundgroup)
{
	vrDELETE(m_BackgroundGroup);
	m_BackgroundGroup    = NULL;
}

void vrBackground::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_GROUNDANGLE_STR)
		{
			SetGroundAngle(*((MFFloat *)ev->m_Value));
			SendEventOut(VRML_GROUNDANGLE_STR, &m_GroundAngle);
		}
	else if (ev->m_FieldID == VRML_GROUNDCOLOR_STR)
		{
			SetGroundColor(*((MFColor *)ev->m_Value));
			SendEventOut(VRML_GROUNDCOLOR_STR, &m_GroundColor);
		}
	else if (ev->m_FieldID == VRML_BACKURL_STR)
		{
			SetBackUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_BACKURL_STR, &m_BackUrl);
		}
	else if (ev->m_FieldID == VRML_BOTTOMURL_STR)
		{
			SetBottomUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_BOTTOMURL_STR, &m_BottomUrl);
		}
	else if (ev->m_FieldID == VRML_FRONTURL_STR)
		{
			SetFrontUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_FRONTURL_STR, &m_FrontUrl);
		}
	else if (ev->m_FieldID == VRML_LEFTURL_STR)
		{
			SetLeftUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_LEFTURL_STR, &m_LeftUrl);
		}
	else if (ev->m_FieldID == VRML_RIGHTURL_STR)
		{
			SetRightUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_RIGHTURL_STR, &m_RightUrl);
		}
	else if (ev->m_FieldID == VRML_TOPURL_STR)
		{
			SetTopUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_TOPURL_STR, &m_TopUrl);
		}
	else if (ev->m_FieldID == VRML_SKYANGLE_STR)
		{
			SetSkyAngle(*((MFFloat *)ev->m_Value));
			SendEventOut(VRML_SKYANGLE_STR, &m_SkyAngle);
		}
	else if (ev->m_FieldID == VRML_SKYCOLOR_STR)
		{
			SetSkyColor(*((MFColor *)ev->m_Value));
			SendEventOut(VRML_SKYCOLOR_STR, &m_SkyColor);
		}
	else
		{
			vrBindable::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrBackground::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("groundAngle", GetNGroundAngles(), m_GroundAngle, 0);
		//if (fieldName == "groundAngle")
		//	return (0 == GetNGroundAngles()); // default: []

		CHECK_ARRAY_FIELD("groundColor", GetNGroundColors(), m_GroundColor, 0);
		//if (fieldName == "groundColor")
		//	return (0 == GetNGroundColors()); // default: []

		CHECK_ARRAY_FIELD("backUrl", GetNBackUrls(), m_BackUrl, 0);
		//if (fieldName == "backUrl")
		//	return (0 == GetNBackUrls()); // default: []

		CHECK_ARRAY_FIELD("bottomUrl", GetNBottomUrls(), m_BottomUrl, 0);
		//if (fieldName == "bottomUrl")
		//	return (0 == GetNBottomUrls()); // default: []

		CHECK_ARRAY_FIELD("frontUrl", GetNFrontUrls(), m_FrontUrl, 0);
		//if (fieldName == "frontUrl")
		//	return (0 == GetNFrontUrls()); // default: []

		CHECK_ARRAY_FIELD("leftUrl", GetNLeftUrls(), m_LeftUrl, 0);
		//if (fieldName == "leftUrl")
		//	return (0 == GetNLeftUrls()); // default: []

		CHECK_ARRAY_FIELD("rightUrl", GetNRightUrls(), m_RightUrl, 0);
		//if (fieldName == "rightUrl")
		//	return (0 == GetNRightUrls()); // default: []

		CHECK_ARRAY_FIELD("topUrl", GetNTopUrls(), m_TopUrl, 0);
		//if (fieldName == "topUrl")
		//	return (0 == GetNTopUrls()); // default: []

		CHECK_ARRAY_FIELD("skyAngle", GetNSkyAngles(), m_SkyAngle, 0);
		//if (fieldName == "skyAngle")
		//	return (0 == GetNSkyAngles()); // default: []

		CHECK_ARRAY_FIELD("skyColor", GetNSkyColors(), m_SkyColor, 0);
		//if (fieldName == "skyColor")
		//	return (0 == GetNSkyColors()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("groundAngle")) return FALSE;
		if (!IsDefault("groundColor")) return FALSE;
		if (!IsDefault("backUrl")) return FALSE;
		if (!IsDefault("bottomUrl")) return FALSE;
		if (!IsDefault("frontUrl")) return FALSE;
		if (!IsDefault("leftUrl")) return FALSE;
		if (!IsDefault("rightUrl")) return FALSE;
		if (!IsDefault("topUrl")) return FALSE;
		if (!IsDefault("skyAngle")) return FALSE;
		if (!IsDefault("skyColor")) return FALSE;
	}

	return vrBindable::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrBackground::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "groundAngle")
	{
		SetGroundAngle(*((MFFloat *)val));
		return TRUE;
	} else if (fieldName == "groundColor")
	{
		SetGroundColor(*((MFColor *)val));
		return TRUE;
	} else if (fieldName == "backUrl")
	{
		SetOrigBackUrl(*((MFString *)val));
		MFString s;
		for (int i=0;i<((MFString *)val)->GetCount();i++)
			s.AddValue(vrExpandPath(GetOrigBackUrl(i)));
		SetBackUrl(s);
		s.Clear();
		return TRUE;
	} else if (fieldName == "bottomUrl")
	{
		SetOrigBottomUrl(*((MFString *)val));
		MFString s;
		for (int i=0;i<((MFString *)val)->GetCount();i++)
			s.AddValue(vrExpandPath(GetOrigBottomUrl(i)));
		SetBottomUrl(s);
		s.Clear();
		return TRUE;
	} else if (fieldName == "frontUrl")
	{
		SetOrigFrontUrl(*((MFString *)val));
		MFString s;
		for (int i=0;i<((MFString *)val)->GetCount();i++)
			s.AddValue(vrExpandPath(GetOrigFrontUrl(i)));
		SetFrontUrl(s);
		s.Clear();
		return TRUE;
	} else if (fieldName == "leftUrl")
	{
		SetOrigLeftUrl(*((MFString *)val));
		MFString s;
		for (int i=0;i<((MFString *)val)->GetCount();i++)
			s.AddValue(vrExpandPath(GetOrigLeftUrl(i)));
		SetLeftUrl(s);
		s.Clear();
		return TRUE;
	} else if (fieldName == "rightUrl")
	{
		SetOrigRightUrl(*((MFString *)val));
		MFString s;
		for (int i=0;i<((MFString *)val)->GetCount();i++)
			s.AddValue(vrExpandPath(GetOrigRightUrl(i)));
		SetRightUrl(s);
		s.Clear();
		return TRUE;
	} else if (fieldName == "topUrl")
	{
		SetOrigTopUrl(*((MFString *)val));
		MFString s;
		for (int i=0;i<((MFString *)val)->GetCount();i++)
			s.AddValue(vrExpandPath(GetOrigTopUrl(i)));
		SetTopUrl(s);
		s.Clear();
		return TRUE;
	} else if (fieldName == "skyAngle")
	{
		SetSkyAngle(*((MFFloat *)val));
		return TRUE;
	} else if (fieldName == "skyColor")
	{
		SetSkyColor(*((MFColor *)val));
		return TRUE;
	}

	return vrBindable::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Background.cxx"
