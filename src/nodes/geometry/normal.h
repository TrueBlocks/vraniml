#ifndef __NORMAL_H3D
#define __NORMAL_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrNormal

	This class corresponds to the Normal node in VRML.  
	<A href="../spec/part1/nodesRef.html#Normal">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Normal node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Normal">link</a>.</ul>

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
class LIBInterface vrNormal : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'vector' exposedField.
	//
	// [default] []
	//
	MFVec3f             	m_Vector;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrNormal(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrNormal(const vrNormal& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrNormal(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrNormal& operator=(const vrNormal& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Vector array (grow if needed).
	//
	// [in] vector: The value to add to the m_Vector array.
	//
	void AddVector(const SFVec3f& vector);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Vector member (copies values).
	//
	// [in] vector: The m_Vector array.
	//
	void SetVector(const MFVec3f& vector);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Vector member.
	//
	SFInt32 GetNVectors(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Vector member.
	//
	// [in] n: The index into the array.
	//
	SFVec3f GetVector(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Vector member.
	//
	const MFVec3f& GetVectorArray(void) const;


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
	// <dd>Receive an event during an event cascade or directly from caller.
	//
	// [in] event: The vrEvent to be processed.
	//
	virtual void ReceiveEventIn(vrEvent *event);

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
	DECLARE_NODE(vrNormal);

};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrNormal::AddVector(const SFVec3f& vector)
{
	m_Vector.AddValue(vector);
}

inline void vrNormal::SetVector(const MFVec3f& vector)
{
	m_Vector.Clear();
	m_Vector = vector;
}

inline SFInt32 vrNormal::GetNVectors(void) const
{
	return m_Vector.GetCount();
}

inline SFVec3f vrNormal::GetVector(SFInt32 n) const
{
	return m_Vector[n];
}

inline const MFVec3f& vrNormal::GetVectorArray(void) const
{
	return m_Vector;
}

inline void vrNormal::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

