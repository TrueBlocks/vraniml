#ifndef __INTERPOLATOR_H3D
#define __INTERPOLATOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrInterpolator

	This class corresponds to the Interpolator node in VRML.  
	<A href="../spec/part1/nodesRef.html#Interpolator">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Interpolator node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Interpolator">link</a>.</ul>

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
class LIBInterface vrInterpolator : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'key' exposedField.
	//
	// [default] []
	//
	MFFloat             	m_Key;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrInterpolator(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrInterpolator(const vrInterpolator& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrInterpolator(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrInterpolator& operator=(const vrInterpolator& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Key array (grow if needed).
	//
	// [in] key: The value to add to the m_Key array.
	//
	void AddKey(SFFloat key);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Key member (copies values).
	//
	// [in] key: The m_Key array.
	//
	void SetKey(const MFFloat& key);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Key member.
	//
	SFInt32 GetNKeys(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Key member.
	//
	// [in] n: The index into the array.
	//
	SFFloat GetKey(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Key member.
	//
	const MFFloat& GetKeyArray(void) const;


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
	// <dd>Declare that this node may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrInterpolator);

};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrInterpolator::AddKey(SFFloat key)
{
	m_Key.AddValue(key);
}

inline void vrInterpolator::SetKey(const MFFloat& key)
{
	m_Key.Clear();
	m_Key = key;
}

inline SFInt32 vrInterpolator::GetNKeys(void) const
{
	return m_Key.GetCount();
}

inline SFFloat vrInterpolator::GetKey(SFInt32 n) const
{
	return m_Key[n];
}

inline const MFFloat& vrInterpolator::GetKeyArray(void) const
{
	return m_Key;
}

inline void vrInterpolator::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

