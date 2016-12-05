//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Shape.h"
#include "..\Appearance\Appearance.h"
#include "..\Geometry\GeometryNode.h"

IMPLEMENT_NODE(vrShape, vrNode);

//----------------------------------------------------------------------
vrShape::vrShape(void) : vrNode()
{
	m_Appearance         = NULL;
	m_Geometry           = NULL;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddField(SFNODE, VRML_APPEARANCE_STR);
		AddField(SFNODE, VRML_GEOMETRY_STR);
	}
}

vrShape::vrShape(const vrShape& v) : vrNode(v)
{
	m_Appearance=NULL;
	SetAppearance(((v.m_Appearance) ? (vrAppearance*)v.m_Appearance->Clone() : NULL));
	m_Geometry=NULL;
	SetGeometry(((v.m_Geometry) ? (vrGeometryNode*)v.m_Geometry->Clone() : NULL));
	GetRuntimeClass()->Reference();
}

vrShape::~vrShape(void)
{
	vrDELETE(m_Appearance);
	// Do this here
	if (m_Geometry)
		m_Geometry->SetGeom(NULL);
	//	vrDELETE(m_Geometry);
	GetRuntimeClass()->Dereference();
}

vrShape& vrShape::operator=(const vrShape& v)
{
	vrNode::operator=(v);

	vrDELETE(m_Appearance);
	SetAppearance(((v.m_Appearance) ? (vrAppearance*)v.m_Appearance->Clone() : NULL));
	vrDELETE(m_Geometry);
	SetGeometry(((v.m_Geometry) ? (vrGeometryNode*)v.m_Geometry->Clone() : NULL));

	return *this;
}

SFNode vrShape::Clone(void) const
{
	return new vrShape(*this);
}

//----------------------------------------------------------------------
void vrShape::SetAppearance(const vrAppearance* appearance)
{
	vrDELETE(m_Appearance);
	m_Appearance = (vrAppearance*)appearance; //((appearance) ? (vrAppearance*)appearance->Clone() : NULL);
	if (m_Appearance)
		m_Appearance->Reference();
}

void vrShape::SetGeometry(const vrGeometryNode* geometry)
{
	if (m_Geometry)
		m_Geometry->SetGeom(NULL);
	//	vrDELETE(m_Geometry);
	m_Geometry = (vrGeometryNode*)geometry; //((geometry) ? (vrGeometryNode*)geometry->Clone() : NULL);
	if (m_Geometry)
		m_Geometry->Reference();
}

void vrShape::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_APPEARANCE_STR)
		{
			SetAppearance(*((vrAppearance* *)ev->m_Value));
			SendEventOut(VRML_APPEARANCE_STR, &m_Appearance);
		}
	else if (ev->m_FieldID == VRML_GEOMETRY_STR)
		{
			SetGeometry(*((vrGeometryNode* *)ev->m_Value));
			SendEventOut(VRML_GEOMETRY_STR, &m_Geometry);
		}
}

//----------------------------------------------------------------------
SFNode vrShape::FindByType(vrRuntimeClass *pClass) const
{
	if (m_Appearance && m_Appearance->IsKindOf(pClass))
		return ((SFNode)m_Appearance);

	if (m_Geometry && m_Geometry->IsKindOf(pClass))
		return ((SFNode)m_Geometry);

	return vrNode::FindByType(pClass);
}

SFNode vrShape::FindByName(const SFString& nodeName) const
{
	SFNode node = NULL;

	if (m_Appearance && ((node = m_Appearance->FindByName(nodeName)) != NULL))
		return (node);

	if (m_Geometry && ((node = m_Geometry->FindByName(nodeName)) != NULL))
		return (node);

	return vrNode::FindByName(nodeName);
}

SFBool vrShape::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	if (m_Appearance)
		m_Appearance->ForEvery(userFn, userData, afterFn);

	if (m_Geometry)
		m_Geometry->ForEvery(userFn, userData, afterFn);

	return vrNode::ForEvery(userFn, userData, afterFn);
}


//----------------------------------------------------------------------
SFBool vrShape::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("appearance", m_Appearance, NULL);
		//if (fieldName == "appearance")
		//	return (NULL == m_Appearance);

		CHECK_FIELD("geometry", m_Geometry, NULL);
		//if (fieldName == "geometry")
		//	return (NULL == m_Geometry);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("appearance")) return FALSE;
		if (!IsDefault("geometry")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

void vrShape::AddChild(SFNode node)
{
	if (node->IsKindOf(GETRUNTIME_CLASS(vrAppearance)))
	{
		SetAppearance((vrAppearance*)node);
	} else 
	{
		ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrGeometryNode)));
		SetGeometry((vrGeometryNode*)node);
	}
}

//----------------------------------------------------------------------
SFBool vrShape::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "appearance")
	{
		AddChild((SFNode)val);
		return TRUE;
	} else if (fieldName == "geometry")
	{
		AddChild((SFNode)val);
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
