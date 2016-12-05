//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Collision.h"

IMPLEMENT_NODE(vrCollision, vrGroupingNode);

//----------------------------------------------------------------------
vrCollision::vrCollision(void) : vrGroupingNode()
{
	m_Collide            = TRUE;
	m_Proxy              = NULL;
	m_CollideTime        = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventIn(MFNODE, VRML_ADDCHILDREN_STR);
		AddEventIn(MFNODE, VRML_REMOVECHILDREN_STR);
		AddExposedField(MFNODE, VRML_CHILDREN_STR);
		AddExposedField(SFBOOL, VRML_COLLIDE_STR);
		AddEventOut(SFTIME, VRML_COLLIDETIME_STR);
		AddField(SFVEC3F, VRML_BBOXCENTER_STR);
		AddField(SFVEC3F, VRML_BBOXSIZE_STR);
	  AddField(SFNODE, VRML_PROXY_STR);
	}
}

vrCollision::vrCollision(const vrCollision& v) : vrGroupingNode(v)
{
	m_Collide            = v.m_Collide;
	m_Proxy=NULL;
	SetProxy(((v.m_Proxy) ? (SFNode)v.m_Proxy->Clone() : NULL));
	m_CollideTime        = v.m_CollideTime;
	GetRuntimeClass()->Reference();
}

vrCollision::~vrCollision(void)
{
	vrDELETE(m_Proxy);
	GetRuntimeClass()->Dereference();
}

vrCollision& vrCollision::operator=(const vrCollision& v)
{
	vrGroupingNode::operator=(v);

	m_Collide            = v.m_Collide;

	vrDELETE(m_Proxy);
	SetProxy(((v.m_Proxy) ? (SFNode)v.m_Proxy->Clone() : NULL));
	m_CollideTime        = v.m_CollideTime;

	return *this;
}

SFNode vrCollision::Clone(void) const
{
	return new vrCollision(*this);
}

//----------------------------------------------------------------------
void vrCollision::SetProxy(const SFNode proxy)
{
	vrDELETE(m_Proxy);

	m_Proxy = (SFNode)proxy; //((proxy) ? (SFNode)proxy->Clone() : NULL);
	if (m_Proxy)
		m_Proxy->Reference();
}

void vrCollision::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_COLLIDE_STR)
		{
			SetCollide(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_COLLIDE_STR, &m_Collide);
		}
	else
		{
			vrGroupingNode::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFNode vrCollision::FindByType(vrRuntimeClass *pClass) const
{
	if (m_Proxy && m_Proxy->IsKindOf(pClass))
		return ((SFNode)m_Proxy);

	return vrGroupingNode::FindByType(pClass);
}

SFNode vrCollision::FindByName(const SFString& nodeName) const
{
	SFNode node = NULL;

	if (m_Proxy && ((node = m_Proxy->FindByName(nodeName)) != NULL))
		return (node);

	return vrGroupingNode::FindByName(nodeName);
}

SFBool vrCollision::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	if (m_Proxy)
		m_Proxy->ForEvery(userFn, userData, afterFn);

	return vrGroupingNode::ForEvery(userFn, userData, afterFn);
}


//----------------------------------------------------------------------
SFBool vrCollision::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("collide", m_Collide, TRUE);
		//if (fieldName == "collide")
		//	return (TRUE == m_Collide);

		CHECK_FIELD("proxy", m_Proxy, NULL);
		//if (fieldName == "proxy")
		//	return (NULL == m_Proxy);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("collide")) return FALSE;
		if (!IsDefault("proxy")) return FALSE;
	}

	return vrGroupingNode::IsDefault(fieldName, field);
}

void vrCollision::AddChild(SFNode node)
{
	{
//		ASSERT(node->IsKindOf(GETRUNTIME_CLASS(SFNode)));
//		SetProxy((SFNode)node);
		vrGroupingNode::AddChild(node);
	}
}

//----------------------------------------------------------------------
SFBool vrCollision::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "collide")
	{
		SetCollide(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "proxy")
	{
		AddChild((SFNode)val);
		return TRUE;
	}
	
	return vrGroupingNode::SetFieldValue(fieldName, val);
}
