#ifndef __TIMESENSOR_H3D
#define __TIMESENSOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Sensor.h"

/*----------------------------------------------------------------------
CLASS
	vrTimeSensor

	This class corresponds to the TimeSensor node in VRML.  
	<A href="../spec/part1/nodesRef.html#TimeSensor">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the TimeSensor node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#TimeSensor">link</a>.</ul>

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
class LIBInterface vrTimeSensor : public vrSensor
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'cycleInterval' exposedField.
	//
	// [default] 1.0
	//
	SFTime              	m_CycleInterval;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'loop' exposedField.
	//
	// [default] FALSE
	//
	SFBool              	m_Loop;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'startTime' exposedField.
	//
	// [default] 0.0
	//
	SFTime              	m_StartTime;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'stopTime' exposedField.
	//
	// [default] 0.0
	//
	SFTime              	m_StopTime;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'cycleTime' eventOut.
	//
	// [default] 0.0
	//
	SFTime              	m_CycleTime;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'fraction' eventOut.
	//
	// [default] 0.0
	//
	SFFloat             	m_Fraction;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'time' eventOut.
	//
	// [default] 0.0
	//
	SFTime              	m_Time;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrTimeSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrTimeSensor(const vrTimeSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrTimeSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrTimeSensor& operator=(const vrTimeSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_CycleInterval member.
	//
	// [in] cycleinterval: The cycleinterval value.
	//
	void SetCycleInterval(SFTime cycleinterval);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Loop member.
	//
	// [in] loop: The loop value.
	//
	void SetLoop(SFBool loop);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_StartTime member.
	//
	// [in] starttime: The starttime value.
	//
	void SetStartTime(SFTime starttime);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_StopTime member.
	//
	// [in] stoptime: The stoptime value.
	//
	void SetStopTime(SFTime stoptime);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_CycleInterval member.
	//
	SFTime GetCycleInterval(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Loop member.
	//
	SFBool GetLoop(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_StartTime member.
	//
	SFTime GetStartTime(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_StopTime member.
	//
	SFTime GetStopTime(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_CycleTime member.
	//
	// [in] cycletime: The cycletime value.
	//
	void SetCycleTime(SFTime cycletime);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Fraction member.
	//
	// [in] fraction: The fraction value.
	//
	void SetFraction(SFFloat fraction);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Time member.
	//
	// [in] time: The time value.
	//
	void SetTime(SFTime time);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_CycleTime member.
	//
	SFTime GetCycleTime(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Fraction member.
	//
	SFFloat GetFraction(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Time member.
	//
	SFTime GetTime(void) const;


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
	DECLARE_NODE(vrTimeSensor);

	//------------------------------------------------------------
	// hand coded functions
	        void SendEvents(double now);
	virtual void Deactivate(void);
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrTimeSensor::SetCycleInterval(SFTime cycleinterval)
{
	m_CycleInterval = cycleinterval;
}

inline void vrTimeSensor::SetLoop(SFBool loop)
{
	m_Loop = loop;
}

inline void vrTimeSensor::SetStartTime(SFTime starttime)
{
	m_StartTime = starttime;
}

inline void vrTimeSensor::SetStopTime(SFTime stoptime)
{
	m_StopTime = stoptime;
}

inline SFTime vrTimeSensor::GetCycleInterval(void) const
{
	return m_CycleInterval;
}

inline SFBool vrTimeSensor::GetLoop(void) const
{
	return m_Loop;
}

inline SFTime vrTimeSensor::GetStartTime(void) const
{
	return m_StartTime;
}

inline SFTime vrTimeSensor::GetStopTime(void) const
{
	return m_StopTime;
}

// eventOut sets and gets inlines
inline void vrTimeSensor::SetCycleTime(SFTime cycletime)
{
	m_CycleTime = cycletime;
}

inline void vrTimeSensor::SetFraction(SFFloat fraction)
{
	m_Fraction = fraction;
}

inline void vrTimeSensor::SetTime(SFTime time)
{
	m_Time = time;
}

inline SFTime vrTimeSensor::GetCycleTime(void) const
{
	return m_CycleTime;
}

inline SFFloat vrTimeSensor::GetFraction(void) const
{
	return m_Fraction;
}

inline SFTime vrTimeSensor::GetTime(void) const
{
	return m_Time;
}

inline void vrTimeSensor::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

