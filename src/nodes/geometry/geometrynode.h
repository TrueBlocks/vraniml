#ifndef __GEOMETRYNODE_H3D
#define __GEOMETRYNODE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrGeometryNode

	This class corresponds to the GeometryNode node in VRML.  
	<A href="../spec/part1/nodesRef.html#GeometryNode">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the GeometryNode node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#GeometryNode">link</a>.</ul>

NOTES
	<ul>
	<li>All node classes share certain aspects which are described <a href="../nodespec.htm">here</a>.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrGeometryNode : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'ccw' field.
	//
	// [default] TRUE
	//
	SFBool              	m_Ccw;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'convex' field.
	//
	// [default] TRUE
	//
	SFBool              	m_Convex;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'creaseAngle' field.
	//
	// [default] 0.0
	//
	SFFloat             	m_CreaseAngle;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'solid' field.
	//
	// [default] TRUE
	//
	SFBool              	m_Solid;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field geom.
	//
	// [default] NULL
	//
	vrSolid*            	m_Geom;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field native.
	//
	// [default] TRUE
	//
	SFBool              	m_Native;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrGeometryNode(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrGeometryNode(const vrGeometryNode& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrGeometryNode(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrGeometryNode& operator=(const vrGeometryNode& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Ccw member.
	//
	// [in] ccw: The ccw value.
	//
	void SetCcw(SFBool ccw);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Convex member.
	//
	// [in] convex: The convex value.
	//
	void SetConvex(SFBool convex);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_CreaseAngle member.
	//
	// [in] creaseangle: The creaseangle value.
	//
	void SetCreaseAngle(SFFloat creaseangle);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Solid member.
	//
	// [in] solid: The solid value.
	//
	void SetSolid(SFBool solid);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Geom member.
	//
	// [in] geom: The geom value.
	//
	void SetGeom(const vrSolid* geom);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Native member.
	//
	// [in] native: The native value.
	//
	void SetNative(SFBool native);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Ccw member.
	//
	SFBool GetCcw(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Convex member.
	//
	SFBool GetConvex(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_CreaseAngle member.
	//
	SFFloat GetCreaseAngle(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Solid member.
	//
	SFBool GetSolid(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Geom member.
	//
	vrSolid* GetGeom(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Native member.
	//
	SFBool GetNative(void) const;


	//<nodoc>------------------------------------------------------------
	// <dd>Set the value of a field given the field's name and a value.
	// <dd>Note: Error checking is done on 'fieldName' but cannot be done on 'val',
	// <dd>      so make sure you send the correct type of data to this method.
	//
	// [in] fieldName: The name of the field to set (as specified in the VRML97 specification).
	// [in] val: Void pointer to a field of the type corresponding to fieldName.
	//
	virtual SFBool SetFieldValue(const SFString& fieldName, void *val);


	//<doc>------------------------------------------------------------
	// <dd>Respond to a traversal by an arbitrary traverser.  Note: Normally, nodes just call t->Traverse(this)
	// <dd>to have the traverser handle the traversal.  you may override this method in your derived class to
	// <dd>handle traversals of node types.
	//
	// [in] trav: The vrTraverser requesting the traversal.
	//
	virtual void Traverse(vrTraverser *trav) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the node (or a particular field) is in it's default state.
	//
	// [in] fieldName: The field to check for default value.  NULL implies check all fields of this node.
	// [out] field: If non-NULL the value of the field will be returned in field.
	//
	virtual SFBool IsDefault(const SFString& fieldName=nullString, vrField *field=NULL) const;

	//<doc>------------------------------------------------------------
	// <dd>Declare that this node may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrGeometryNode);

	//------------------------------------------------------------
	// hand coded functions
	virtual void BuildMesh(void);
	virtual void BuildColors(void) {};
	virtual void BuildNormals(void) {};
	virtual void BuildTexCoords(void) {};
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrGeometryNode::SetCcw(SFBool ccw)
{
	m_Ccw = ccw;
}

inline void vrGeometryNode::SetConvex(SFBool convex)
{
	m_Convex = convex;
}

inline void vrGeometryNode::SetCreaseAngle(SFFloat creaseangle)
{
	m_CreaseAngle = creaseangle;
}

inline void vrGeometryNode::SetSolid(SFBool solid)
{
	m_Solid = solid;
}

inline void vrGeometryNode::SetNative(SFBool native)
{
	m_Native = native;
}

inline SFBool vrGeometryNode::GetCcw(void) const
{
	return m_Ccw;
}

inline SFBool vrGeometryNode::GetConvex(void) const
{
	return m_Convex;
}

inline SFFloat vrGeometryNode::GetCreaseAngle(void) const
{
	return m_CreaseAngle;
}

inline SFBool vrGeometryNode::GetSolid(void) const
{
	return m_Solid;
}

inline vrSolid* vrGeometryNode::GetGeom(void) const
{
	return m_Geom;
}

inline SFBool vrGeometryNode::GetNative(void) const
{
	return m_Native;
}

inline void vrGeometryNode::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

