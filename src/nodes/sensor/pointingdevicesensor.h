#ifndef __POINTINGDEVICESENSOR_H3D
#define __POINTINGDEVICESENSOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Sensor.h"

#define MOUSE_UP   1
#define MOUSE_DOWN 2
#define MOUSE_MOVE 3

/*----------------------------------------------------------------------
CLASS
	vrPointingDeviceSensor

	This class corresponds to the PointingDeviceSensor node in VRML.  
	<A href="../spec/part1/nodesRef.html#PointingDeviceSensor">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the PointingDeviceSensor node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#PointingDeviceSensor">link</a>.</ul>

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
class LIBInterface vrPointingDeviceSensor : public vrSensor
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field firstPoint.
	//
	// [default] origin
	//
	SFVec3f             	m_FirstPoint;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'autoOffset' exposedField.
	//
	// [default] TRUE
	//
	SFBool              	m_AutoOffset;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'trackPoint' eventOut.
	//
	// [default] origin
	//
	SFVec3f             	m_TrackPoint;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrPointingDeviceSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrPointingDeviceSensor(const vrPointingDeviceSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrPointingDeviceSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrPointingDeviceSensor& operator=(const vrPointingDeviceSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_FirstPoint member.
	//
	// [in] firstpoint: The firstpoint value.
	//
	void SetFirstPoint(const SFVec3f& firstpoint);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_FirstPoint member.
	//
	SFVec3f GetFirstPoint(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_AutoOffset member.
	//
	// [in] autooffset: The autooffset value.
	//
	void SetAutoOffset(SFBool autooffset);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_AutoOffset member.
	//
	SFBool GetAutoOffset(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_TrackPoint member.
	//
	// [in] trackpoint: The trackpoint value.
	//
	void SetTrackPoint(const SFVec3f& trackpoint);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_TrackPoint member.
	//
	SFVec3f GetTrackPoint(void) const;


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
	DECLARE_NODE(vrPointingDeviceSensor);

	//------------------------------------------------------------
	// hand coded functions
	virtual void PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrPointingDeviceSensor::SetFirstPoint(const SFVec3f& firstpoint)
{
	m_FirstPoint = firstpoint;
}

inline SFVec3f vrPointingDeviceSensor::GetFirstPoint(void) const
{
	return m_FirstPoint;
}

// exposedField sets and gets inlines
inline void vrPointingDeviceSensor::SetAutoOffset(SFBool autooffset)
{
	m_AutoOffset = autooffset;
}

inline SFBool vrPointingDeviceSensor::GetAutoOffset(void) const
{
	return m_AutoOffset;
}

// eventOut sets and gets inlines
inline void vrPointingDeviceSensor::SetTrackPoint(const SFVec3f& trackpoint)
{
	m_TrackPoint = trackpoint;
}

inline SFVec3f vrPointingDeviceSensor::GetTrackPoint(void) const
{
	return m_TrackPoint;
}

inline void vrPointingDeviceSensor::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

