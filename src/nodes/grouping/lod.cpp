//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "LOD.h"

IMPLEMENT_NODE(vrLOD, vrNode);

//----------------------------------------------------------------------
vrLOD::vrLOD(void) : vrNode()
{
	m_ActiveLevel        = -1;
	//m_Level              = array;
	m_Center             = origin;
	//m_Range              = array;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFNODE, VRML_LEVEL_STR);
		AddField(SFVEC3F, VRML_CENTER_STR);
		AddField(MFFLOAT, VRML_RANGE_STR);
	}
}

vrLOD::vrLOD(const vrLOD& v) : vrNode(v)
{
	m_ActiveLevel        = v.m_ActiveLevel;
	for (int i=0;i<v.m_Level.GetCount();i++)
	{
		SFNode node = v.m_Level[i];
		SFNode clone = node->Clone();
		AddLevel(clone);
	}
	m_Center             = v.m_Center;
	m_Range              = v.m_Range;
	GetRuntimeClass()->Reference();
}

vrLOD::~vrLOD(void)
{
	for (int i=0;i<GetNLevels();i++)
	{
		SFNode ob = GetLevel(i);
		if (ob->Dereference())
			delete ob;
	}
	m_Level.Clear();
	m_Range.Clear();

	GetRuntimeClass()->Dereference();
}

vrLOD& vrLOD::operator=(const vrLOD& v)
{
	vrNode::operator=(v);

	m_ActiveLevel        = v.m_ActiveLevel;
	m_Level.Clear();
	for (int i=0;i<v.m_Level.GetCount();i++)
	{
		SFNode node = v.m_Level[i];
		SFNode clone = node->Clone();
		AddLevel(clone);
	}
	m_Center             = v.m_Center;
	m_Range.Clear();
	m_Range              = v.m_Range;

	return *this;
}

SFNode vrLOD::Clone(void) const
{
	return new vrLOD(*this);
}

//----------------------------------------------------------------------
void vrLOD::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_LEVEL_STR)
		{
			SetLevel(*((MFNode *)ev->m_Value));
			SendEventOut(VRML_LEVEL_STR, &m_Level);
		}
}

//----------------------------------------------------------------------
SFBool vrLOD::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("level", GetNLevels(), m_Level, 0);
		//if (fieldName == "level")
		//	return (0 == GetNLevels()); // default: []

		CHECK_FIELD("center", m_Center, origin);
		//if (fieldName == "center")
		//	return (origin == m_Center);

		CHECK_ARRAY_FIELD("range", GetNRanges(), m_Range, 0);
		//if (fieldName == "range")
		//	return (0 == GetNRanges()); // default: []

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("level")) return FALSE;
		if (!IsDefault("center")) return FALSE;
		if (!IsDefault("range")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrLOD::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "level")
	{
		SetLevel(*((MFNode *)val));
		return TRUE;
	} else if (fieldName == "center")
	{
		SetCenter(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "range")
	{
		SetRange(*((MFFloat *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

//----------------------------------------------------------------------
#include "LOD.cxx"
