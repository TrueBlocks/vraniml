//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "FontStyle.h"

IMPLEMENT_NODE(vrFontStyle, vrNode);

//----------------------------------------------------------------------
vrFontStyle::vrFontStyle(void) : vrNode()
{
	m_Family             = "SERIF";
	m_Horizontal         = TRUE;
	m_Justify.AddValue("BEGIN");
	//m_Language           = NULL;
	m_LeftToRight        = TRUE;
	m_Size               = 1.0;
	m_Spacing            = 1.0;
	m_Style              = "PLAIN";
	m_TopToBottom        = TRUE;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddField(SFSTRING, VRML_FAMILY_STR);
		AddField(SFBOOL, VRML_HORIZONTAL_STR);
		AddField(MFSTRING, VRML_JUSTIFY_STR);
		AddField(SFSTRING, VRML_LANGUAGE_STR);
		AddField(SFBOOL, VRML_LEFTTORIGHT_STR);
		AddField(SFFLOAT, VRML_SIZE_STR);
		AddField(SFFLOAT, VRML_SPACING_STR);
		AddField(SFSTRING, VRML_STYLE_STR);
		AddField(SFBOOL, VRML_TOPTOBOTTOM_STR);
	}
}

vrFontStyle::vrFontStyle(const vrFontStyle& v) : vrNode(v)
{
	m_Family             = v.m_Family;
	m_Horizontal         = v.m_Horizontal;
	m_Justify            = v.m_Justify;
	m_Language           = v.m_Language;
	m_LeftToRight        = v.m_LeftToRight;
	m_Size               = v.m_Size;
	m_Spacing            = v.m_Spacing;
	m_Style              = v.m_Style;
	m_TopToBottom        = v.m_TopToBottom;
	GetRuntimeClass()->Reference();
}

vrFontStyle::~vrFontStyle(void)
{
	m_Justify.Clear();
	GetRuntimeClass()->Dereference();
}

vrFontStyle& vrFontStyle::operator=(const vrFontStyle& v)
{
	vrNode::operator=(v);

	m_Family             = v.m_Family;
	m_Horizontal         = v.m_Horizontal;
	m_Justify.Clear();
	m_Justify            = v.m_Justify;
	m_Language           = v.m_Language;
	m_LeftToRight        = v.m_LeftToRight;
	m_Size               = v.m_Size;
	m_Spacing            = v.m_Spacing;
	m_Style              = v.m_Style;
	m_TopToBottom        = v.m_TopToBottom;

	return *this;
}

SFNode vrFontStyle::Clone(void) const
{
	return new vrFontStyle(*this);
}

//----------------------------------------------------------------------
void vrFontStyle::SetFamily(const SFString& family)
{
	m_Family = family;
}

void vrFontStyle::SetLanguage(const SFString& language)
{
	m_Language = language;
}

void vrFontStyle::SetStyle(const SFString& style)
{
	m_Style = style;
}


//----------------------------------------------------------------------
SFBool vrFontStyle::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("family", m_Family, "SERIF");
		//if (fieldName == "family")
		//	return ("SERIF" == m_Family);

		CHECK_FIELD("horizontal", m_Horizontal, TRUE);
		//if (fieldName == "horizontal")
		//	return (TRUE == m_Horizontal);

		if (fieldName == "justify")
		{
			if (field)
				SetValEx(field, (void*)&m_Justify);
			if (IsIsMapped(fieldName))
				return TRUE;
			return (!strcmp("BEGIN", GetJustify(0))); // default: "BEGIN"
		}

		CHECK_STRING_FIELD("language", m_Language);
		//if (fieldName == "language")
		//	return m_Language.Empty();

		CHECK_FIELD("leftToRight", m_LeftToRight, TRUE);
		//if (fieldName == "leftToRight")
		//	return (TRUE == m_LeftToRight);

		CHECK_FIELD("size", m_Size, (SFFloat)1.0);
		//if (fieldName == "size")
		//	return ((SFFloat)1.0 == m_Size);

		CHECK_FIELD("spacing", m_Spacing, (SFFloat)1.0);
		//if (fieldName == "spacing")
		//	return ((SFFloat)1.0 == m_Spacing);

		CHECK_FIELD("style", m_Style, "PLAIN");
		//if (fieldName == "style")
		//	return ("PLAIN" == m_Style);

		CHECK_FIELD("topToBottom", m_TopToBottom, TRUE);
		//if (fieldName == "topToBottom")
		//	return (TRUE == m_TopToBottom);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("family")) return FALSE;
		if (!IsDefault("horizontal")) return FALSE;
		if (!IsDefault("justify")) return FALSE;
		if (!IsDefault("language")) return FALSE;
		if (!IsDefault("leftToRight")) return FALSE;
		if (!IsDefault("size")) return FALSE;
		if (!IsDefault("spacing")) return FALSE;
		if (!IsDefault("style")) return FALSE;
		if (!IsDefault("topToBottom")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrFontStyle::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "family")
	{
		SetFamily(((char *)val));
		return TRUE;
	} else if (fieldName == "horizontal")
	{
		SetHorizontal(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "justify")
	{
		SetJustify(*((MFString *)val));
		return TRUE;
	} else if (fieldName == "language")
	{
		SetLanguage(((char *)val));
		return TRUE;
	} else if (fieldName == "leftToRight")
	{
		SetLeftToRight(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "size")
	{
		SetSize(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "spacing")
	{
		SetSpacing(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "style")
	{
		SetStyle(((char *)val));
		return TRUE;
	} else if (fieldName == "topToBottom")
	{
		SetTopToBottom(*((SFBool *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
