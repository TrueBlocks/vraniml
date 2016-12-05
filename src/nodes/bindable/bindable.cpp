//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Bindable.h"

IMPLEMENT_NODE(vrBindable, vrNode);

//----------------------------------------------------------------------
vrBindable::vrBindable(void) : vrNode()
{
	m_Bind               = FALSE;
	m_IsBound            = FALSE;
	m_BoundTo            = NULL;
}

vrBindable::vrBindable(const vrBindable& v) : vrNode(v)
{
	m_Bind               = FALSE;
	m_IsBound            = FALSE;
	m_BoundTo            = NULL;
}

vrBindable::~vrBindable(void)
{
	ASSERT(!m_BoundTo);
}

vrBindable& vrBindable::operator=(const vrBindable& v)
{
	vrNode::operator=(v);

	m_Bind               = FALSE;
	m_IsBound            = FALSE;
	m_BoundTo            = NULL;

	return *this;
}

SFNode vrBindable::Clone(void) const
{
	return new vrBindable(*this);
}

//----------------------------------------------------------------------
void vrBindable::SetBoundTo(const vrBrowser* boundto)
{
	m_BoundTo = (vrBrowser*)boundto;
}

void vrBindable::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_SET_BIND_STR)
		{
			m_Bind = *((SFBool *)ev->m_Value);
			if (m_Bind)
			{
				SetIsBound(PENDING_BIND);
			} else
			{
				SetIsBound(PENDING_UNBIND);
			}
		}
}

//----------------------------------------------------------------------
SFBool vrBindable::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		ASSERT(0); // should never happen
	}
	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrBindable::SetFieldValue(const SFString& fieldName, void *val)
{
	ASSERT(0); // Invalid field name
	return FALSE;
}
