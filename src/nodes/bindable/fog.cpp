//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Fog.h"
#include "Browser\Browser.h"

IMPLEMENT_NODE(vrFog, vrBindable);

//----------------------------------------------------------------------
vrFog::vrFog(void) : vrBindable()
{
	m_Color              = vrWhite;
	m_FogType            = "LINEAR";
	m_VisibilityRange    = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFCOLOR, VRML_COLOR_STR);
		AddExposedField(SFSTRING, VRML_FOGTYPE_STR);
		AddExposedField(SFFLOAT, VRML_VISIBILITYRANGE_STR);
		AddEventIn(SFBOOL, VRML_SET_BIND_STR);
		AddEventOut(SFBOOL, VRML_ISBOUND_STR);
	}
}

vrFog::vrFog(const vrFog& v) : vrBindable(v)
{
	m_Color              = v.m_Color;
	m_FogType            = v.m_FogType;
	m_VisibilityRange    = v.m_VisibilityRange;
	GetRuntimeClass()->Reference();
}

vrFog::~vrFog(void)
{
	if (m_BoundTo)
	  m_BoundTo->Bind(this, FALSE);
	m_BoundTo = NULL;
	GetRuntimeClass()->Dereference();
}

vrFog& vrFog::operator=(const vrFog& v)
{
	vrBindable::operator=(v);

	m_Color              = v.m_Color;
	m_FogType            = v.m_FogType;
	m_VisibilityRange    = v.m_VisibilityRange;

	return *this;
}

SFNode vrFog::Clone(void) const
{
	return new vrFog(*this);
}

//----------------------------------------------------------------------
void vrFog::SetFogType(const SFString& fogtype)
{
	m_FogType = fogtype;
}

void vrFog::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_COLOR_STR)
		{
			SetColor(*((SFColor *)ev->m_Value));
			SendEventOut(VRML_COLOR_STR, &m_Color);
		}
	else if (ev->m_FieldID == VRML_FOGTYPE_STR)
		{
			SetFogType(*((SFString *)ev->m_Value));
			SendEventOut(VRML_FOGTYPE_STR, &m_FogType);
		}
	else if (ev->m_FieldID == VRML_VISIBILITYRANGE_STR)
		{
			SetVisibilityRange(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_VISIBILITYRANGE_STR, &m_VisibilityRange);
		}
	else
		{
			vrBindable::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrFog::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("color", m_Color, vrWhite);
		//if (fieldName == "color")
		//	return (vrWhite == m_Color);

		CHECK_FIELD("fogType", m_FogType, "LINEAR");
		//if (fieldName == "fogType")
		//	return ("LINEAR" == m_FogType);

		CHECK_FIELD("visibilityRange", m_VisibilityRange, (SFFloat)0.0);
		//if (fieldName == "visibilityRange")
		//	return ((SFFloat)0.0 == m_VisibilityRange);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("color")) return FALSE;
		if (!IsDefault("fogType")) return FALSE;
		if (!IsDefault("visibilityRange")) return FALSE;
	}

	return vrBindable::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrFog::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "color")
	{
		SetColor(*((SFColor *)val));
		return TRUE;
	} else if (fieldName == "fogType")
	{
		SetFogType(((char *)val));
		return TRUE;
	} else if (fieldName == "visibilityRange")
	{
		SetVisibilityRange(*((SFFloat *)val));
		return TRUE;
	}
	
	return vrBindable::SetFieldValue(fieldName, val);
}

void vrFog::CompleteNode(vrNode *top)
{
	// Let parent complete this node if needed
	vrBindable::CompleteNode(top);

	if (!top || !top->IsKindOf(GETRUNTIME_CLASS(vrBrowser)))
		return;

	vrBrowser *b = (vrBrowser*)top;
	// Only bind the first encountered node
	if (!b->GetFog())
		b->Bind(this, TRUE);
}

