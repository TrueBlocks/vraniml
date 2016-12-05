//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "WorldInfo.h"

IMPLEMENT_NODE(vrWorldInfo, vrNode);

//----------------------------------------------------------------------
vrWorldInfo::vrWorldInfo(void) : vrNode()
{
	//m_Info               = array;
	//m_Title              = NULL;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddField(MFSTRING, VRML_INFO_STR);
		AddField(SFSTRING, VRML_TITLE_STR);
	}
}

vrWorldInfo::vrWorldInfo(const vrWorldInfo& v) : vrNode(v)
{
	m_Info               = v.m_Info;
	m_Title              = v.m_Title;
	GetRuntimeClass()->Reference();
}

vrWorldInfo::~vrWorldInfo(void)
{
	m_Info.Clear();
	GetRuntimeClass()->Dereference();
}

vrWorldInfo& vrWorldInfo::operator=(const vrWorldInfo& v)
{
	vrNode::operator=(v);

	m_Info.Clear();
	m_Info               = v.m_Info;
	m_Title              = v.m_Title;

	return *this;
}

SFNode vrWorldInfo::Clone(void) const
{
	return new vrWorldInfo(*this);
}

//----------------------------------------------------------------------
void vrWorldInfo::SetTitle(const SFString& title)
{
	m_Title = title;
}


//----------------------------------------------------------------------
SFBool vrWorldInfo::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("info", GetNInfos(), m_Info, 0);
		//if (fieldName == "info")
		//	return (0 == GetNInfos()); // default: []

		CHECK_STRING_FIELD("title", m_Title);
		//if (fieldName == "title")
		//	return m_Title.Empty();

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("info")) return FALSE;
		if (!IsDefault("title")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrWorldInfo::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "info")
	{
		SetInfo(*((MFString *)val));
		return TRUE;
	} else if (fieldName == "title")
	{
		SetTitle(((char *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
