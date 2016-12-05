#ifndef __SPHERE_H3D
#define __SPHERE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "GeometryNode.h"

/*----------------------------------------------------------------------
CLASS
	vrSphere

	This class corresponds to the Sphere node in VRML.  
	<A href="../spec/part1/nodesRef.html#Sphere">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Sphere node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Sphere">link</a>.</ul>

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
class LIBInterface vrSphere : public vrGeometryNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'radius' field.
	//
	// [default] 1
	//
	SFFloat             	m_Radius;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field slices.
	//
	// [default] 16
	//
	SFInt32             	m_Slices;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field stacks.
	//
	// [default] 16
	//
	SFInt32             	m_Stacks;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrSphere(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrSphere(const vrSphere& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrSphere(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrSphere& operator=(const vrSphere& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Radius member.
	//
	// [in] radius: The radius value.
	//
	void SetRadius(SFFloat radius);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Slices member.
	//
	// [in] slices: The slices value.
	//
	void SetSlices(SFInt32 slices);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Stacks member.
	//
	// [in] stacks: The stacks value.
	//
	void SetStacks(SFInt32 stacks);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Radius member.
	//
	SFFloat GetRadius(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Slices member.
	//
	SFInt32 GetSlices(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Stacks member.
	//
	SFInt32 GetStacks(void) const;


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
	// <dd>Declare that this node may be runtime typed and dynamically created. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrSphere);

	//------------------------------------------------------------
	// hand coded functions
	virtual void BuildMesh(void);
	virtual void BuildColors(void);
	virtual void BuildNormals(void);
	virtual void BuildTexCoords(void);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrSphere::SetRadius(SFFloat radius)
{
	m_Radius = radius;
}

inline void vrSphere::SetSlices(SFInt32 slices)
{
	m_Slices = slices;
}

inline void vrSphere::SetStacks(SFInt32 stacks)
{
	m_Stacks = stacks;
}

inline SFFloat vrSphere::GetRadius(void) const
{
	return m_Radius;
}

inline SFInt32 vrSphere::GetSlices(void) const
{
	return m_Slices;
}

inline SFInt32 vrSphere::GetStacks(void) const
{
	return m_Stacks;
}

inline void vrSphere::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

