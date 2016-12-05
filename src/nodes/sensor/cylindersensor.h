#ifndef __CYLINDERSENSOR_H3D
#define __CYLINDERSENSOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "PointingDeviceSensor.h"

/*----------------------------------------------------------------------
CLASS
	vrCylinderSensor

	This class corresponds to the CylinderSensor node in VRML.  
	<A href="../spec/part1/nodesRef.html#CylinderSensor">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the CylinderSensor node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#CylinderSensor">link</a>.</ul>

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
class LIBInterface vrCylinderSensor : public vrPointingDeviceSensor
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'offset' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_Offset;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'diskAngle' exposedField.
	//
	// [default] 0.262
	//
	SFFloat             	m_DiskAngle;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'maxAngle' exposedField.
	//
	// [default] -1.0
	//
	SFFloat             	m_MaxAngle;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'minAngle' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_MinAngle;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'rotation' eventOut.
	//
	// [default] defRotation
	//
	SFRotation          	m_Rotation;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrCylinderSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrCylinderSensor(const vrCylinderSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrCylinderSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrCylinderSensor& operator=(const vrCylinderSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Offset member.
	//
	// [in] offset: The offset value.
	//
	void SetOffset(SFFloat offset);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_DiskAngle member.
	//
	// [in] diskangle: The diskangle value.
	//
	void SetDiskAngle(SFFloat diskangle);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MaxAngle member.
	//
	// [in] maxangle: The maxangle value.
	//
	void SetMaxAngle(SFFloat maxangle);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MinAngle member.
	//
	// [in] minangle: The minangle value.
	//
	void SetMinAngle(SFFloat minangle);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Offset member.
	//
	SFFloat GetOffset(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_DiskAngle member.
	//
	SFFloat GetDiskAngle(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MaxAngle member.
	//
	SFFloat GetMaxAngle(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MinAngle member.
	//
	SFFloat GetMinAngle(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Rotation member.
	//
	// [in] rotation: The rotation value.
	//
	void SetRotation(const SFRotation& rotation);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Rotation member.
	//
	SFRotation GetRotation(void) const;


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
	DECLARE_NODE(vrCylinderSensor);

	//------------------------------------------------------------
	// hand coded functions
	virtual void PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t);
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrCylinderSensor::SetOffset(SFFloat offset)
{
	m_Offset = offset;
}

inline void vrCylinderSensor::SetDiskAngle(SFFloat diskangle)
{
	m_DiskAngle = diskangle;
}

inline void vrCylinderSensor::SetMaxAngle(SFFloat maxangle)
{
	m_MaxAngle = maxangle;
}

inline void vrCylinderSensor::SetMinAngle(SFFloat minangle)
{
	m_MinAngle = minangle;
}

inline SFFloat vrCylinderSensor::GetOffset(void) const
{
	return m_Offset;
}

inline SFFloat vrCylinderSensor::GetDiskAngle(void) const
{
	return m_DiskAngle;
}

inline SFFloat vrCylinderSensor::GetMaxAngle(void) const
{
	return m_MaxAngle;
}

inline SFFloat vrCylinderSensor::GetMinAngle(void) const
{
	return m_MinAngle;
}

// eventOut sets and gets inlines
inline void vrCylinderSensor::SetRotation(const SFRotation& rotation)
{
	m_Rotation = rotation;
}

inline SFRotation vrCylinderSensor::GetRotation(void) const
{
	return m_Rotation;
}

inline void vrCylinderSensor::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

