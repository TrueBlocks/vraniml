#ifndef __ORIENTATIONINTERPOLATOR_H3D
#define __ORIENTATIONINTERPOLATOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Interpolator.h"

/*----------------------------------------------------------------------
CLASS
	vrOrientationInterpolator

	This class corresponds to the OrientationInterpolator node in VRML.  
	<A href="../spec/part1/nodesRef.html#OrientationInterpolator">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the OrientationInterpolator node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#OrientationInterpolator">link</a>.</ul>

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
class LIBInterface vrOrientationInterpolator : public vrInterpolator
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'keyValue' exposedField.
	//
	// [default] []
	//
	MFRotation          	m_KeyValue;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'value' eventOut.
	//
	// [default] defRotation
	//
	SFRotation          	m_Value;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'fraction' eventIn.
	//
	// [default] 0.0
	//
	SFFloat             	m_Fraction;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrOrientationInterpolator(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrOrientationInterpolator(const vrOrientationInterpolator& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrOrientationInterpolator(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrOrientationInterpolator& operator=(const vrOrientationInterpolator& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_KeyValue array (grow if needed).
	//
	// [in] keyvalue: The value to add to the m_KeyValue array.
	//
	void AddKeyValue(const SFRotation& keyvalue);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_KeyValue member (copies values).
	//
	// [in] keyvalue: The m_KeyValue array.
	//
	void SetKeyValue(const MFRotation& keyvalue);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_KeyValue member.
	//
	SFInt32 GetNKeyValues(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_KeyValue member.
	//
	// [in] n: The index into the array.
	//
	SFRotation GetKeyValue(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_KeyValue member.
	//
	const MFRotation& GetKeyValueArray(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Value member.
	//
	// [in] value: The value value.
	//
	void SetValue(const SFRotation& value);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Value member.
	//
	SFRotation GetValue(void) const;


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
	DECLARE_NODE(vrOrientationInterpolator);

	//------------------------------------------------------------
	// hand coded functions
	SFRotation Evaluate(SFFloat t) const;
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrOrientationInterpolator::AddKeyValue(const SFRotation& keyvalue)
{
	m_KeyValue.AddValue(keyvalue);
}

inline void vrOrientationInterpolator::SetKeyValue(const MFRotation& keyvalue)
{
	m_KeyValue.Clear();
	m_KeyValue = keyvalue;
}

inline SFInt32 vrOrientationInterpolator::GetNKeyValues(void) const
{
	return m_KeyValue.GetCount();
}

inline SFRotation vrOrientationInterpolator::GetKeyValue(SFInt32 n) const
{
	return m_KeyValue[n];
}

inline const MFRotation& vrOrientationInterpolator::GetKeyValueArray(void) const
{
	return m_KeyValue;
}

// eventOut sets and gets inlines
inline void vrOrientationInterpolator::SetValue(const SFRotation& value)
{
	m_Value = value;
}

inline SFRotation vrOrientationInterpolator::GetValue(void) const
{
	return m_Value;
}

inline void vrOrientationInterpolator::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

