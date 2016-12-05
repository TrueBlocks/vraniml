//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "GroupingNode.h"
#include "Common/Light.h"

IMPLEMENT_NODE(vrGroupingNode, vrNode);

//----------------------------------------------------------------------
vrGroupingNode::vrGroupingNode(void) : vrNode()
{
	m_BboxCenter         = origin;
	m_BboxSize           = -xyz1;
	m_Children           = NULL;
	m_hasSensor          = FALSE;
	m_hasLight           = FALSE;
}

vrGroupingNode::vrGroupingNode(const vrGroupingNode& v) : vrNode(v)
{
	m_BboxCenter         = v.m_BboxCenter;
	m_BboxSize           = v.m_BboxSize;
	m_hasSensor          = v.m_hasSensor;
	m_hasLight           = v.m_hasLight;

	m_Children = NULL;
	if (v.m_Children)
	{
		LISTPOS pos = v.m_Children->GetHeadPosition();
		while (pos)
		{
			SFNode obj = v.m_Children->GetNext(pos);
			AddChild(obj->Clone());
		}
	}
}

void vrGroupingNode::Clear()
{
	vrNode::Clear();

	if (m_Children)
	{
		LISTPOS pos = m_Children->GetHeadPosition();
		while (pos)
		{
			SFNode ob = m_Children->GetNext(pos);
			if (ob->Dereference())
				delete ob;
		}
		m_Children->RemoveAll();
		delete m_Children;
	}
	m_Children = NULL;
	m_hasSensor = FALSE;
	m_hasLight = FALSE;
}

vrGroupingNode::~vrGroupingNode(void)
{
	Clear();
}

vrGroupingNode& vrGroupingNode::operator=(const vrGroupingNode& v)
{
	Clear();
	
	vrNode::operator=(v);

	m_Children = NULL;
	if (v.m_Children)
	{
		LISTPOS pos = v.m_Children->GetHeadPosition();
		while (pos)
		{
			SFNode obj = v.m_Children->GetNext(pos);
			AddChild(obj->Clone());
		}
	}

	m_BboxCenter         = v.m_BboxCenter;
	m_BboxSize           = v.m_BboxSize;
	m_hasSensor          = v.m_hasSensor;
	m_hasLight           = v.m_hasLight;

	return *this;
}

SFNode vrGroupingNode::Clone(void) const
{
	return new vrGroupingNode(*this);
}

#include "Nodes\Sensor\VisibilitySensor.h"
#include "Nodes\Sensor\TimeSensor.h"
#include "Nodes\Sensor\ProximitySensor.h"

#ifdef _DEBUG
#include "Nodes\AllNodes.h"
#endif
//--------------------------------------------------------------------
void vrGroupingNode::AddChild(SFNode node)
{ 
#ifdef _DEBUG
	ASSERT(m_NodeType==protoGroup ||
					m_NodeType==protoGroupInstance ||
					node->IsKindOf(GETRUNTIME_CLASS(vrAnchor)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrBackground)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrBillboard)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrCollision)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrColorInterpolator)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrCoordinateInterpolator)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrCylinderSensor)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrDirectionalLight)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrFog)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrGroup)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrInline)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrLOD)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrNavigationInfo)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrNormalInterpolator)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrOrientationInterpolator)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrPlaneSensor)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrPointLight)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrPositionInterpolator)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrProximitySensor)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrScalarInterpolator)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrScript)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrShape)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrSound)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrSpotLight)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrSphereSensor)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrSwitch)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrTimeSensor)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrTouchSensor)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrTransform)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrViewpoint)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrVisibilitySensor)) ||
					node->IsKindOf(GETRUNTIME_CLASS(vrWorldInfo))
				);
#endif

	if (!m_Children)
	{
		m_Children = new vrNodeList;
	}

	if (node->IsReferenced())
	{
		if (m_Children->Find(node))
			return; // ignore nodes already in the grouping node
	}

	m_Children->AddTail(node);

	if (!m_hasSensor && node->IsKindOf(GETRUNTIME_CLASS(vrSensor)))
	{
		// If the grouping node has certain kinds of sensors 
		// we want to know about it
		m_hasSensor = (!node->IsKindOf(GETRUNTIME_CLASS(vrVisibilitySensor)) &&
										!node->IsKindOf(GETRUNTIME_CLASS(vrTimeSensor)) &&
										!node->IsKindOf(GETRUNTIME_CLASS(vrProximitySensor)));
	}

	// If this grouping node has lights we need to know about it.
	if (!m_hasLight && node->IsKindOf(GETRUNTIME_CLASS(vrLight)))
		m_hasLight = TRUE;
}

//----------------------------------------------------------------------
SFNode vrGroupingNode::FindByType(vrRuntimeClass *pClass) const
{
	if (IsKindOf(pClass))
		return ((SFNode)this);	

	if (m_Children)
	{
		LISTPOS pos = m_Children->GetHeadPosition();
		while (pos)
		{
			SFNode node = m_Children->GetNext(pos);
			SFNode n = node->FindByType(pClass);
			if (n)
				return n;
		}
	}
	return NULL;
}

//----------------------------------------------------------------------
SFNode vrGroupingNode::FindByName(const SFString& nodeName) const
{
	if (GetName() == nodeName)
		return ((SFNode)this);
	
	if (m_Children)
	{
		LISTPOS pos = m_Children->GetHeadPosition();
		while (pos)
		{
			SFNode node = m_Children->GetNext(pos);
			SFNode n = node->FindByName(nodeName);
			if (n)
				return n;
		}
	}
	return NULL;
}

SFBool vrGroupingNode::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	if (!userFn(this, userData)) 
	{
		return FALSE;
	}
	
	if (m_Children)
	{
		LISTPOS pos = m_Children->GetHeadPosition();
		while (pos) 
		{
			SFNode node = m_Children->GetNext(pos);
			if (!node->ForEvery(userFn, userData, afterFn))
			{
				// TODO: Should this really be FALSE?
				return TRUE;
			}
		}
	}

	if (afterFn)
	{
		if (!afterFn(this, userData))
		{
			return FALSE;
		}
	}

	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrGroupingNode::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("bboxCenter", m_BboxCenter, origin);
		//if (fieldName == "bboxCenter")
		//	return (origin == m_BboxCenter);

		CHECK_FIELD("bboxSize", m_BboxSize, (-xyz1));
		//if (fieldName == "bboxSize")
		//	return ((-xyz1) == m_BboxSize);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- check all fields
		if (!IsDefault("bboxCenter")) return FALSE;
		if (!IsDefault("bboxSize")) return FALSE;
	}

	return FALSE;
}

SFBool vrGroupingNode::IsParentOf(SFNode node)
{
	if (HasChildren())
	{
		LISTPOS pos = GetChildren()->GetHeadPosition();
		while (pos)
		{
			// only if it's a direct child of parentNode
			SFNode ob = GetChildren()->GetNext(pos);
			if (ob == node)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

/*
void vrGroupingNode::RemoveChild(vrNode *node)
{	
	if (HasChildren())
	{
		LISTPOS pos = m_Children->Find(node);
		if (pos)
		{
			// remove this node.
			m_Children->RemoveAt(pos);
			
			// If it is a type we are interested in update the has flags
			if (node->IsKindOf(GETRUNTIME_CLASS(vrLight)))
				m_hasLight = (FindByType(GETRUNTIME_CLASS(vrLight)) != NULL);
			
			// Must check for all three types
			m_hasSensor = FindByType(GETRUNTIME_CLASS(vrVisibilitySensor));
			if (!m_hasSensor)
				m_hasSensor = FindByType(GETRUNTIME_CLASS(vrTimeSensor));
			if (m_hasSensor)
				m_hasSensor = FindByType(GETRUNTIME_CLASS(vrProximitySensor));
		}
	}
}
*/

void vrGroupingNode::MoveChildren(vrGroupingNode *to)
{
	// Move the children of this node to the given node
	if (m_Children)
	{
		while (m_Children->GetCount())
		{
			to->AddChild(m_Children->RemoveHead());
		}
	}
	m_hasLight = m_hasSensor = FALSE;
}

SFBool vrGroupingNode::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "bboxCenter")
	{
		m_BboxCenter = *((SFVec3f *)val);
		return TRUE;
	} else if (fieldName == "bboxSize")
	{
		m_BboxSize = *((SFVec3f *)val);
		return TRUE;
	}

	ASSERT(0); // invalid field name
	return FALSE;
}

