#ifndef __PLANESENSOR_H3D
#define __PLANESENSOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "PointingDeviceSensor.h"

/*----------------------------------------------------------------------
CLASS
	vrPlaneSensor

	This class corresponds to the PlaneSensor node in VRML.  
	<A href="../spec/part1/nodesRef.html#PlaneSensor">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the PlaneSensor node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#PlaneSensor">link</a>.</ul>

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
class LIBInterface vrPlaneSensor : public vrPointingDeviceSensor
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'offset' exposedField.
	//
	// [default] origin
	//
	SFVec3f             	m_Offset;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'maxPosition' exposedField.
	//
	// [default] xy1*-1
	//
	SFVec2f             	m_MaxPosition;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'minPosition' exposedField.
	//
	// [default] origin2
	//
	SFVec2f             	m_MinPosition;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'translation' eventOut.
	//
	// [default] origin
	//
	SFVec3f             	m_Translation;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrPlaneSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrPlaneSensor(const vrPlaneSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrPlaneSensor(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrPlaneSensor& operator=(const vrPlaneSensor& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Offset member.
	//
	// [in] offset: The offset value.
	//
	void SetOffset(const SFVec3f& offset);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MaxPosition member.
	//
	// [in] maxposition: The maxposition value.
	//
	void SetMaxPosition(const SFVec2f& maxposition);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MinPosition member.
	//
	// [in] minposition: The minposition value.
	//
	void SetMinPosition(const SFVec2f& minposition);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Offset member.
	//
	SFVec3f GetOffset(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MaxPosition member.
	//
	SFVec2f GetMaxPosition(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MinPosition member.
	//
	SFVec2f GetMinPosition(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Translation member.
	//
	// [in] translation: The translation value.
	//
	void SetTranslation(const SFVec3f& translation);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Translation member.
	//
	SFVec3f GetTranslation(void) const;


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
	DECLARE_NODE(vrPlaneSensor);

	//------------------------------------------------------------
	// hand coded functions
	virtual void PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t);
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrPlaneSensor::SetOffset(const SFVec3f& offset)
{
	m_Offset = offset;
}

inline void vrPlaneSensor::SetMaxPosition(const SFVec2f& maxposition)
{
	m_MaxPosition = maxposition;
}

inline void vrPlaneSensor::SetMinPosition(const SFVec2f& minposition)
{
	m_MinPosition = minposition;
}

inline SFVec3f vrPlaneSensor::GetOffset(void) const
{
	return m_Offset;
}

inline SFVec2f vrPlaneSensor::GetMaxPosition(void) const
{
	return m_MaxPosition;
}

inline SFVec2f vrPlaneSensor::GetMinPosition(void) const
{
	return m_MinPosition;
}

// eventOut sets and gets inlines
inline void vrPlaneSensor::SetTranslation(const SFVec3f& translation)
{
	m_Translation = translation;
}

inline SFVec3f vrPlaneSensor::GetTranslation(void) const
{
	return m_Translation;
}

inline void vrPlaneSensor::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

