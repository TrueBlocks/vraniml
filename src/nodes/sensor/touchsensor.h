#ifndef __TOUCHSENSOR_H3D
#define __TOUCHSENSOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "PointingDeviceSensor.h"

/*----------------------------------------------------------------------
CLASS
	vrTouchSensor

	This class corresponds to the TouchSensor node in VRML.  
	<A href="../spec/part1/nodesRef.html#TouchSensor">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the TouchSensor node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#TouchSensor">link</a>.</ul>

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
class LIBInterface vrTouchSensor : public vrPointingDeviceSensor
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'hitNormal' eventOut.
	//
	// [default] origin
	//
	SFVec3f             	m_HitNormal;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'hitPoint' eventOut.
	//
	// [default] origin
	//
	SFVec3f             	m_HitPoint;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'hitTexCoord' eventOut.
	//
	// [default] origin2
	//
	SFVec2f             	m_HitTexCoord;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'isOver' eventOut.
	//
	// [default] FALSE
	//
	SFBool              	m_IsOver;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'touchTime' eventOut.
	//
	// [default] 0.0
	//
	SFTime              	m_TouchTime;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrTouchSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrTouchSensor(const vrTouchSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrTouchSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrTouchSensor& operator=(const vrTouchSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_HitNormal member.
	//
	// [in] hitnormal: The hitnormal value.
	//
	void SetHitNormal(const SFVec3f& hitnormal);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_HitPoint member.
	//
	// [in] hitpoint: The hitpoint value.
	//
	void SetHitPoint(const SFVec3f& hitpoint);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_HitTexCoord member.
	//
	// [in] hittexcoord: The hittexcoord value.
	//
	void SetHitTexCoord(const SFVec2f& hittexcoord);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_IsOver member.
	//
	// [in] isover: The isover value.
	//
	void SetIsOver(SFBool isover);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_TouchTime member.
	//
	// [in] touchtime: The touchtime value.
	//
	void SetTouchTime(SFTime touchtime);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_HitNormal member.
	//
	SFVec3f GetHitNormal(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_HitPoint member.
	//
	SFVec3f GetHitPoint(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_HitTexCoord member.
	//
	SFVec2f GetHitTexCoord(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_IsOver member.
	//
	SFBool IsOver(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_TouchTime member.
	//
	SFTime GetTouchTime(void) const;


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
	DECLARE_NODE(vrTouchSensor);

	//------------------------------------------------------------
	// hand coded functions
	virtual void PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t);
};

//----------------------------------------------------------------------
// eventOut sets and gets inlines
inline void vrTouchSensor::SetHitNormal(const SFVec3f& hitnormal)
{
	m_HitNormal = hitnormal;
}

inline void vrTouchSensor::SetHitPoint(const SFVec3f& hitpoint)
{
	m_HitPoint = hitpoint;
}

inline void vrTouchSensor::SetHitTexCoord(const SFVec2f& hittexcoord)
{
	m_HitTexCoord = hittexcoord;
}

inline void vrTouchSensor::SetIsOver(SFBool isover)
{
	m_IsOver = isover;
}

inline void vrTouchSensor::SetTouchTime(SFTime touchtime)
{
	m_TouchTime = touchtime;
}

inline SFVec3f vrTouchSensor::GetHitNormal(void) const
{
	return m_HitNormal;
}

inline SFVec3f vrTouchSensor::GetHitPoint(void) const
{
	return m_HitPoint;
}

inline SFVec2f vrTouchSensor::GetHitTexCoord(void) const
{
	return m_HitTexCoord;
}

inline SFBool vrTouchSensor::IsOver(void) const
{
	return m_IsOver;
}

inline SFTime vrTouchSensor::GetTouchTime(void) const
{
	return m_TouchTime;
}

inline void vrTouchSensor::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

