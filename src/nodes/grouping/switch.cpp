//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Switch.h"

IMPLEMENT_NODE(vrSwitch, vrNode);

//----------------------------------------------------------------------
vrSwitch::vrSwitch(void) : vrNode()
{
	//m_Choice             = array;
	m_WhichChoice        = -1;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFNODE, VRML_CHOICE_STR);
		AddExposedField(SFINT32, VRML_WHICHCHOICE_STR);
	}
}

vrSwitch::vrSwitch(const vrSwitch& v) : vrNode(v)
{
	for (int i=0;i<v.m_Choice.GetCount();i++)
	{
		SFNode node = v.m_Choice[i];
		SFNode clone = node->Clone();
		AddChoice(clone);
	}
	m_WhichChoice        = v.m_WhichChoice;
	GetRuntimeClass()->Reference();
}

vrSwitch::~vrSwitch(void)
{
	for (int i=0;i<GetNChoices();i++)
	{
		SFNode ob = GetChoice(i);
		if (ob->Dereference())
			delete ob;
	}
	m_Choice.Clear();

	GetRuntimeClass()->Dereference();
}

vrSwitch& vrSwitch::operator=(const vrSwitch& v)
{
	vrNode::operator=(v);

	m_Choice.Clear();
	for (int i=0;i<v.m_Choice.GetCount();i++)
	{
		SFNode node = v.m_Choice[i];
		SFNode clone = node->Clone();
		AddChoice(clone);
	}
	m_WhichChoice        = v.m_WhichChoice;

	return *this;
}

SFNode vrSwitch::Clone(void) const
{
	return new vrSwitch(*this);
}

//----------------------------------------------------------------------
void vrSwitch::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_CHOICE_STR)
		{
			SetChoice(*((MFNode *)ev->m_Value));
			SendEventOut(VRML_CHOICE_STR, &m_Choice);
		}
	else if (ev->m_FieldID == VRML_WHICHCHOICE_STR)
		{
			SetWhichChoice(*((SFInt32 *)ev->m_Value));
			SendEventOut(VRML_WHICHCHOICE_STR, &m_WhichChoice);
		}
}

//----------------------------------------------------------------------
SFBool vrSwitch::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("choice", GetNChoices(), m_Choice, 0);
		//if (fieldName == "choice")
		//	return (0 == GetNChoices()); // default: []

		CHECK_FIELD("whichChoice", m_WhichChoice, -1);
		//if (fieldName == "whichChoice")
		//	return (-1 == m_WhichChoice);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("choice")) return FALSE;
		if (!IsDefault("whichChoice")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrSwitch::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "choice")
	{
		SetChoice(*((MFNode *)val));
		return TRUE;
	} else if (fieldName == "whichChoice")
	{
		SetWhichChoice(*((SFInt32 *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

//----------------------------------------------------------------------
#include "Switch.cxx"
