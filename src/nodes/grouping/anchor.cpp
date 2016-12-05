//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Anchor.h"

IMPLEMENT_NODE(vrAnchor, vrGroupingNode);

//----------------------------------------------------------------------
vrAnchor::vrAnchor(void) : vrGroupingNode()
{
	//m_OrigUrl            = array;
	//m_Description        = NULL;
	//m_Parameter          = array;
	//m_Url                = array;
	m_hasSensor          = TRUE;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventIn(MFNODE, VRML_ADDCHILDREN_STR);
		AddEventIn(MFNODE, VRML_REMOVECHILDREN_STR);
		AddExposedField(MFNODE, VRML_CHILDREN_STR);
		AddExposedField(SFSTRING, VRML_DESCRIPTION_STR);
		AddExposedField(MFSTRING, VRML_PARAMETER_STR);
		AddExposedField(MFSTRING, VRML_URL_STR);
		AddField(SFVEC3F, VRML_BBOXCENTER_STR);
		AddField(SFVEC3F, VRML_BBOXSIZE_STR);
	}
}

vrAnchor::vrAnchor(const vrAnchor& v) : vrGroupingNode(v)
{
	m_OrigUrl            = v.m_OrigUrl;
	m_Description        = v.m_Description;
	m_Parameter          = v.m_Parameter;
	m_Url                = v.m_Url;
	GetRuntimeClass()->Reference();
}

vrAnchor::~vrAnchor(void)
{
	m_OrigUrl.Clear();
	m_Parameter.Clear();
	m_Url.Clear();
	GetRuntimeClass()->Dereference();
}

vrAnchor& vrAnchor::operator=(const vrAnchor& v)
{
	vrGroupingNode::operator=(v);

	m_OrigUrl.Clear();
	m_OrigUrl            = v.m_OrigUrl;
	m_Description        = v.m_Description;
	m_Parameter.Clear();
	m_Parameter          = v.m_Parameter;
	m_Url.Clear();
	m_Url                = v.m_Url;

	return *this;
}

SFNode vrAnchor::Clone(void) const
{
	return new vrAnchor(*this);
}

//----------------------------------------------------------------------
void vrAnchor::SetDescription(const SFString& description)
{
	m_Description = description;
}

void vrAnchor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_DESCRIPTION_STR)
		{
			SetDescription(*((SFString *)ev->m_Value));
			SendEventOut(VRML_DESCRIPTION_STR, &m_Description);
		}
	else if (ev->m_FieldID == VRML_PARAMETER_STR)
		{
			SetParameter(*((MFString *)ev->m_Value));
			SendEventOut(VRML_PARAMETER_STR, &m_Parameter);
		}
	else if (ev->m_FieldID == VRML_URL_STR)
		{
			SetUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_URL_STR, &m_Url);
		}
	else
		{
			vrGroupingNode::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrAnchor::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_STRING_FIELD("description", m_Description);
		//if (fieldName == "description")
		//	return m_Description.Empty();

		CHECK_ARRAY_FIELD("parameter", GetNParameters(), m_Parameter, 0);
		//if (fieldName == "parameter")
		//	return (0 == GetNParameters()); // default: []

		CHECK_ARRAY_FIELD("url", GetNUrls(), m_Url, 0);
		//if (fieldName == "url")
		//	return (0 == GetNUrls()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("description")) return FALSE;
		if (!IsDefault("parameter")) return FALSE;
		if (!IsDefault("url")) return FALSE;
	}

	return vrGroupingNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrAnchor::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "description")
	{
		SetDescription(((char *)val));
		return TRUE;
	} else if (fieldName == "parameter")
	{
		SetParameter(*((MFString *)val));
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
	
	return vrGroupingNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Anchor.cxx"

