//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "ScalarInterpolator.h"

IMPLEMENT_NODE(vrScalarInterpolator, vrInterpolator);

//----------------------------------------------------------------------
vrScalarInterpolator::vrScalarInterpolator(void) : vrInterpolator()
{
	//m_KeyValue           = array;
	m_Fraction           = 0.0;
	m_Value              = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFFLOAT, VRML_KEYVALUE_STR);
		AddEventIn(SFFLOAT, VRML_SET_FRACTION_STR);
		AddEventOut(SFFLOAT, VRML_VALUE_CHANGED_STR);
		AddExposedField(MFFLOAT, VRML_KEY_STR);
	}
}

vrScalarInterpolator::vrScalarInterpolator(const vrScalarInterpolator& v) : vrInterpolator(v)
{
	m_KeyValue           = v.m_KeyValue;
	m_Fraction           = v.m_Fraction;
	m_Value              = v.m_Value;
	GetRuntimeClass()->Reference();
}

vrScalarInterpolator::~vrScalarInterpolator(void)
{
	m_KeyValue.Clear();
	GetRuntimeClass()->Dereference();
}

vrScalarInterpolator& vrScalarInterpolator::operator=(const vrScalarInterpolator& v)
{
	vrInterpolator::operator=(v);

	m_KeyValue.Clear();
	m_KeyValue           = v.m_KeyValue;
	m_Fraction           = v.m_Fraction;
	m_Value              = v.m_Value;

	return *this;
}

SFNode vrScalarInterpolator::Clone(void) const
{
	return new vrScalarInterpolator(*this);
}

//----------------------------------------------------------------------
void vrScalarInterpolator::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_KEYVALUE_STR)
		{
			SetKeyValue(*((MFFloat *)ev->m_Value));
			SendEventOut(VRML_KEYVALUE_STR, &m_KeyValue);
		}
	else if (ev->m_FieldID == VRML_SET_FRACTION_STR)
		{
			m_Fraction = *((SFFloat *)ev->m_Value);
			m_Value = Evaluate(m_Fraction);
			SendEventOut(VRML_VALUE_CHANGED_STR, &m_Value);
		}
	else
		{
			vrInterpolator::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrScalarInterpolator::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("keyValue", GetNKeyValues(), m_KeyValue, 0);
		//if (fieldName == "keyValue")
		//	return (0 == GetNKeyValues()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("keyValue")) return FALSE;
	}

	return vrInterpolator::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrScalarInterpolator::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "keyValue")
	{
		SetKeyValue(*((MFFloat *)val));
		return TRUE;
	}
	
	return vrInterpolator::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "ScalarInterpolator.cxx"
