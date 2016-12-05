//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Utils\Utility.h"
#include "TestClasses.h"

#include "Script.h"

IMPLEMENT_NODE(vrScript, vrNode);

//----------------------------------------------------------------------
vrScript::vrScript(void) : vrNode()
{
	//m_OrigUrl            = array;
	//m_Url                = array;
	m_DirectOutput       = FALSE;
	m_MustEvaluate       = FALSE;

	m_FieldList = NULL;

	if (GetRuntimeClass()->Reference()==2)
	{
//		vrNode::AddExposedField(MFSTRING, VRML_URL_STR);
//		vrNode::AddField(SFBOOL, VRML_DIRECTOUTPUT_STR);
//		vrNode::AddField(SFBOOL, VRML_MUSTEVALUATE_STR);
	}
}

vrScript::vrScript(const vrScript& v) : vrNode(v)
{
	m_OrigUrl            = v.m_OrigUrl;
	m_Url                = v.m_Url;
	m_DirectOutput       = v.m_DirectOutput;
	m_MustEvaluate       = v.m_MustEvaluate;

	m_FieldList = NULL;
	if (v.m_FieldList)
	{
		LISTPOS pos = v.m_FieldList->GetHeadPosition();
		while (pos)
		{
			vrField *field = v.m_FieldList->GetNext(pos);
			vrField *clone = new vrField(*field);
			m_FieldList->AddTail(clone);
		}
	}

	GetRuntimeClass()->Reference();
}

vrScript::~vrScript(void)
{
	m_OrigUrl.Clear();
	m_Url.Clear();
	GetRuntimeClass()->Dereference();

	ClearFieldList();
	ASSERT(!m_FieldList);
}

vrScript& vrScript::operator=(const vrScript& v)
{
	vrNode::operator=(v);

	m_OrigUrl.Clear();
	m_OrigUrl            = v.m_OrigUrl;
	m_Url.Clear();
	m_Url                = v.m_Url;
	m_DirectOutput       = v.m_DirectOutput;
	m_MustEvaluate       = v.m_MustEvaluate;

	ClearFieldList();
	m_FieldList = NULL;
	if (v.m_FieldList)
	{
		LISTPOS pos = v.m_FieldList->GetHeadPosition();
		while (pos)
		{
			vrField *field = v.m_FieldList->GetNext(pos);
			vrField *clone = new vrField(*field);
			m_FieldList->AddTail(clone);
		}
	}

	return *this;
}

SFNode vrScript::Clone(void) const
{
	return new vrScript(*this);
}

//----------------------------------------------------------------------
/*
void vrScript::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_URL_STR)
		{
			SetUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_URL_STR, &m_Url);
		}
}
*/

//----------------------------------------------------------------------
SFBool vrScript::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		if (fieldName == "url")
			return (0 == GetNUrls()); // default: []

		if (fieldName == "directOutput")
			return (FALSE == m_DirectOutput);

		if (fieldName == "mustEvaluate")
			return (FALSE == m_MustEvaluate);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("url")) return FALSE;
		if (!IsDefault("directOutput")) return FALSE;
		if (!IsDefault("mustEvaluate")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrScript::SetFieldValue(const SFString& fieldName, void *val)
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
	} else if (fieldName == "directOutput")
	{
		SetDirectOutput(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "mustEvaluate")
	{
		SetMustEvaluate(*((SFBool *)val));
		return TRUE;
	}
	if (m_FieldList)
	{
		LISTPOS pos = m_FieldList->GetHeadPosition();
		while (pos)
		{
			vrField *field = m_FieldList->GetNext(pos);
			if (field->GetName() == fieldName)
				return TRUE;
		}
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

#include "Script.cxx"
