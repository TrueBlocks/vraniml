#ifndef __CYLINDER_H3D
#define __CYLINDER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "GeometryNode.h"

/*----------------------------------------------------------------------
CLASS
	vrCylinder

	This class corresponds to the Cylinder node in VRML.  
	<A href="../spec/part1/nodesRef.html#Cylinder">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Cylinder node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Cylinder">link</a>.</ul>

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
class LIBInterface vrCylinder : public vrGeometryNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'bottom' field.
	//
	// [default] TRUE
	//
	SFBool              	m_Bottom;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'height' field.
	//
	// [default] 2.0
	//
	SFFloat             	m_Height;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'radius' field.
	//
	// [default] 1.0
	//
	SFFloat             	m_Radius;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'side' field.
	//
	// [default] TRUE
	//
	SFBool              	m_Side;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'top' field.
	//
	// [default] TRUE
	//
	SFBool              	m_Top;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrCylinder(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrCylinder(const vrCylinder& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrCylinder(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrCylinder& operator=(const vrCylinder& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Bottom member.
	//
	// [in] bottom: The bottom value.
	//
	void SetBottom(SFBool bottom);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Height member.
	//
	// [in] height: The height value.
	//
	void SetHeight(SFFloat height);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Radius member.
	//
	// [in] radius: The radius value.
	//
	void SetRadius(SFFloat radius);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Side member.
	//
	// [in] side: The side value.
	//
	void SetSide(SFBool side);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Top member.
	//
	// [in] top: The top value.
	//
	void SetTop(SFBool top);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Bottom member.
	//
	SFBool GetBottom(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Height member.
	//
	SFFloat GetHeight(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Radius member.
	//
	SFFloat GetRadius(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Side member.
	//
	SFBool GetSide(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Top member.
	//
	SFBool GetTop(void) const;


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
	DECLARE_NODE(vrCylinder);

	//------------------------------------------------------------
	// hand coded functions
	virtual void BuildMesh(void);
	virtual void BuildColors(void);
	virtual void BuildNormals(void);
	virtual void BuildTexCoords(void);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrCylinder::SetBottom(SFBool bottom)
{
	m_Bottom = bottom;
}

inline void vrCylinder::SetHeight(SFFloat height)
{
	m_Height = height;
}

inline void vrCylinder::SetRadius(SFFloat radius)
{
	m_Radius = radius;
}

inline void vrCylinder::SetSide(SFBool side)
{
	m_Side = side;
}

inline void vrCylinder::SetTop(SFBool top)
{
	m_Top = top;
}

inline SFBool vrCylinder::GetBottom(void) const
{
	return m_Bottom;
}

inline SFFloat vrCylinder::GetHeight(void) const
{
	return m_Height;
}

inline SFFloat vrCylinder::GetRadius(void) const
{
	return m_Radius;
}

inline SFBool vrCylinder::GetSide(void) const
{
	return m_Side;
}

inline SFBool vrCylinder::GetTop(void) const
{
	return m_Top;
}

inline void vrCylinder::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

