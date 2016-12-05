//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Billboard.h"

IMPLEMENT_NODE(vrBillboard, vrGroupingNode);

//----------------------------------------------------------------------
vrBillboard::vrBillboard(void) : vrGroupingNode()
{
	m_AxisOfRotation     = yAxis;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventIn(MFNODE, VRML_ADDCHILDREN_STR);
		AddEventIn(MFNODE, VRML_REMOVECHILDREN_STR);
		AddExposedField(MFNODE, VRML_CHILDREN_STR);
		AddExposedField(SFVEC3F, VRML_AXISOFROTATION_STR);
		AddField(SFVEC3F, VRML_BBOXCENTER_STR);
		AddField(SFVEC3F, VRML_BBOXSIZE_STR);
	}
}

vrBillboard::vrBillboard(const vrBillboard& v) : vrGroupingNode(v)
{
	m_AxisOfRotation     = v.m_AxisOfRotation;
	GetRuntimeClass()->Reference();
}

vrBillboard::~vrBillboard(void)
{
	GetRuntimeClass()->Dereference();
}

vrBillboard& vrBillboard::operator=(const vrBillboard& v)
{
	vrGroupingNode::operator=(v);

	m_AxisOfRotation     = v.m_AxisOfRotation;

	return *this;
}

SFNode vrBillboard::Clone(void) const
{
	return new vrBillboard(*this);
}

//----------------------------------------------------------------------
void vrBillboard::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_AXISOFROTATION_STR)
		{
			SetAxisOfRotation(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_AXISOFROTATION_STR, &m_AxisOfRotation);
		}
	else
		{
			vrGroupingNode::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrBillboard::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("axisOfRotation", m_AxisOfRotation, yAxis);
		//if (fieldName == "axisOfRotation")
		//	return (yAxis == m_AxisOfRotation);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("axisOfRotation")) return FALSE;
	}

	return vrGroupingNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrBillboard::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "axisOfRotation")
	{
		SetAxisOfRotation(*((SFVec3f *)val));
		return TRUE;
	}
	
	return vrGroupingNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Billboard.cxx"
