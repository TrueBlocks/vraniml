#ifndef __SENSOR_H3D
#define __SENSOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrSensor

	This class corresponds to the Sensor node in VRML.  
	<A href="../spec/part1/nodesRef.html#Sensor">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Sensor node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Sensor">link</a>.</ul>

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
class LIBInterface vrSensor : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'enabled' exposedField.
	//
	// [default] TRUE
	//
	SFBool              	m_Enabled;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'isActive' eventOut.
	//
	// [default] FALSE
	//
	SFBool              	m_IsActive;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrSensor(const vrSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrSensor& operator=(const vrSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Enabled member.
	//
	// [in] enabled: The enabled value.
	//
	void SetEnabled(SFBool enabled);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Enabled member.
	//
	SFBool GetEnabled(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_IsActive member.
	//
	// [in] isactive: The isactive value.
	//
	void SetIsActive(SFBool isactive);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_IsActive member.
	//
	SFBool IsActive(void) const;


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
	DECLARE_NODE(vrSensor);

	//------------------------------------------------------------
	// hand coded functions
	virtual void Deactivate(void);
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrSensor::SetEnabled(SFBool enabled)
{
	m_Enabled = enabled;
}

inline SFBool vrSensor::GetEnabled(void) const
{
	return m_Enabled;
}

// eventOut sets and gets inlines
inline void vrSensor::SetIsActive(SFBool isactive)
{
	m_IsActive = isactive;
}

inline SFBool vrSensor::IsActive(void) const
{
	return m_IsActive;
}

inline void vrSensor::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

