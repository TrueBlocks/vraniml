//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Text.h"
#include "..\Appearance\FontStyle.h"

IMPLEMENT_NODE(vrText, vrGeometryNode);

//----------------------------------------------------------------------
vrText::vrText(void) : vrGeometryNode()
{
	//m_String             = array;
	m_FontStyle          = NULL;
	//m_Length             = array;
	m_MaxExtent          = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFSTRING, VRML_STRING_STR);
		AddField(SFNODE, VRML_FONTSTYLE_STR);
		AddField(MFFLOAT, VRML_LENGTH_STR);
		AddField(SFFLOAT, VRML_MAXEXTENT_STR);
	}
}

vrText::vrText(const vrText& v) : vrGeometryNode(v)
{
	m_String             = v.m_String;
	m_FontStyle=NULL;
	SetFontStyle(((v.m_FontStyle) ? (vrFontStyle*)v.m_FontStyle->Clone() : NULL));
	m_Length             = v.m_Length;
	m_MaxExtent          = v.m_MaxExtent;
	GetRuntimeClass()->Reference();
}

vrText::~vrText(void)
{
	m_String.Clear();
	vrDELETE(m_FontStyle);
	m_Length.Clear();
	GetRuntimeClass()->Dereference();
}

vrText& vrText::operator=(const vrText& v)
{
	vrGeometryNode::operator=(v);

	m_String.Clear();
	m_String             = v.m_String;
	vrDELETE(m_FontStyle);
	SetFontStyle(((v.m_FontStyle) ? (vrFontStyle*)v.m_FontStyle->Clone() : NULL));
	m_Length.Clear();
	m_Length             = v.m_Length;
	m_MaxExtent          = v.m_MaxExtent;

	return *this;
}

SFNode vrText::Clone(void) const
{
	return new vrText(*this);
}

//----------------------------------------------------------------------
void vrText::SetFontStyle(const vrFontStyle* fontstyle)
{
	vrDELETE(m_FontStyle);
	m_FontStyle = (vrFontStyle*)fontstyle; //((fontstyle) ? (vrFontStyle*)fontstyle->Clone() : NULL);
	if (m_FontStyle)
		m_FontStyle->Reference();
}

void vrText::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_STRING_STR)
		{
			SetString(*((MFString *)ev->m_Value));
			SendEventOut(VRML_STRING_STR, &m_String);
		}
	else if (ev->m_FieldID == VRML_FONTSTYLE_STR)
		{
			SetFontStyle(*((vrFontStyle* *)ev->m_Value));
			SendEventOut(VRML_FONTSTYLE_STR, &m_FontStyle);
		}
	else if (ev->m_FieldID == VRML_LENGTH_STR)
		{
			SetLength(*((MFFloat *)ev->m_Value));
			SendEventOut(VRML_LENGTH_STR, &m_Length);
		}
	else if (ev->m_FieldID == VRML_MAXEXTENT_STR)
		{
			SetMaxExtent(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_MAXEXTENT_STR, &m_MaxExtent);
		}
	else
		{
			vrGeometryNode::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFNode vrText::FindByType(vrRuntimeClass *pClass) const
{
	if (m_FontStyle && m_FontStyle->IsKindOf(pClass))
		return ((SFNode)m_FontStyle);

	return vrGeometryNode::FindByType(pClass);
}

SFNode vrText::FindByName(const SFString& nodeName) const
{
	SFNode node = NULL;

	if (m_FontStyle && ((node = m_FontStyle->FindByName(nodeName)) != NULL))
		return (node);

	return vrGeometryNode::FindByName(nodeName);
}

SFBool vrText::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	if (m_FontStyle)
		m_FontStyle->ForEvery(userFn, userData, afterFn);

	return vrGeometryNode::ForEvery(userFn, userData, afterFn);
}


//----------------------------------------------------------------------
SFBool vrText::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("string", GetNStrings(), m_String, 0);
		//if (fieldName == "string")
		//	return (0 == GetNStrings()); // default: []

		CHECK_FIELD("fontStyle", m_FontStyle, NULL);
		//if (fieldName == "fontStyle")
		//	return (NULL == m_FontStyle);

		CHECK_ARRAY_FIELD("length", GetNLengths(), m_Length, 0);
		//if (fieldName == "length")
		//	return (0 == GetNLengths()); // default: []

		CHECK_FIELD("maxExtent", m_MaxExtent, (SFFloat)0.0);
		//if (fieldName == "maxExtent")
		//	return ((SFFloat)0.0 == m_MaxExtent);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("string")) return FALSE;
		if (!IsDefault("fontStyle")) return FALSE;
		if (!IsDefault("length")) return FALSE;
		if (!IsDefault("maxExtent")) return FALSE;
	}

	return vrGeometryNode::IsDefault(fieldName, field);
}

void vrText::AddChild(SFNode node)
{
	{
		ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrFontStyle)));
		SetFontStyle((vrFontStyle*)node);
	}
}

//----------------------------------------------------------------------
SFBool vrText::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "string")
	{
		SetString(*((MFString *)val));
		return TRUE;
	} else if (fieldName == "fontStyle")
	{
		AddChild((SFNode)val);
		return TRUE;
	} else if (fieldName == "length")
	{
		SetLength(*((MFFloat *)val));
		return TRUE;
	} else if (fieldName == "maxExtent")
	{
		SetMaxExtent(*((SFFloat *)val));
		return TRUE;
	}

	return vrGeometryNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Text.cxx"
