//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "GeometryNode.h"
#include "Solid/Solid.h"

IMPLEMENT_NODE(vrGeometryNode, vrNode);

//----------------------------------------------------------------------
vrGeometryNode::vrGeometryNode(void) : vrNode()
{
	m_Ccw                = TRUE;
	m_Convex             = TRUE;
	m_CreaseAngle        = 0.0;
	m_Solid              = TRUE;
	m_Geom               = NULL;
	m_Native             = TRUE;
}

vrGeometryNode::vrGeometryNode(const vrGeometryNode& v) : vrNode(v)
{
	m_Ccw                = v.m_Ccw;
	m_Convex             = v.m_Convex;
	m_CreaseAngle        = v.m_CreaseAngle;
	m_Solid              = v.m_Solid;
	m_Geom               = NULL;
	m_Native             = v.m_Native;
}

vrGeometryNode::~vrGeometryNode(void)
{
	if (m_Geom)
		SetGeom(NULL);
}

vrGeometryNode& vrGeometryNode::operator=(const vrGeometryNode& v)
{
	vrNode::operator=(v);

	m_Ccw                = v.m_Ccw;
	m_Convex             = v.m_Convex;
	m_CreaseAngle        = v.m_CreaseAngle;
	m_Solid              = v.m_Solid;
	SetGeom(NULL);
	m_Native             = v.m_Native;

	return *this;
}

SFNode vrGeometryNode::Clone(void) const
{
	ASSERT(0);
	return NULL; //new vrGeometryNode(*this);
}

//----------------------------------------------------------------------
void vrGeometryNode::SetGeom(const vrSolid* geom)
{
	// geom == 1 is used as a flag sometimes
	if (m_Geom && ((SFInt32)m_Geom)>0x10)
		if (m_Geom->Dereference())
			delete m_Geom;
	m_Geom = (vrSolid*)geom;
	if (m_Geom && ((SFInt32)m_Geom)>0x10)
		m_Geom->Reference();
}


//----------------------------------------------------------------------
SFBool vrGeometryNode::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("ccw", m_Ccw, TRUE);
		//if (fieldName == "ccw")
		//	return (TRUE == m_Ccw);

		CHECK_FIELD("convex", m_Convex, TRUE);
		//if (fieldName == "convex")
		//	return (TRUE == m_Convex);

		CHECK_FIELD("creaseAngle", m_CreaseAngle, (SFFloat)0.0);
		//if (fieldName == "creaseAngle")
		//	return ((SFFloat)0.0 == m_CreaseAngle);

		CHECK_FIELD("solid", m_Solid, TRUE);
		//if (fieldName == "solid")
		//	return (TRUE == m_Solid);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("ccw")) return FALSE;
		if (!IsDefault("convex")) return FALSE;
		if (!IsDefault("creaseAngle")) return FALSE;
		if (!IsDefault("solid")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

//----------------------------------------------------------------------
SFBool vrGeometryNode::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "ccw")
	{
		SetCcw(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "convex")
	{
		SetConvex(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "creaseAngle")
	{
		SetCreaseAngle(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "solid")
	{
		SetSolid(*((SFBool *)val));
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}

//----------------------------------------------------------------------
#include "GeometryNode.cxx"
