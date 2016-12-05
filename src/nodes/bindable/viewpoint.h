#ifndef __VIEWPOINT_H3D
#define __VIEWPOINT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Bindable.h"

/*----------------------------------------------------------------------
CLASS
	vrViewpoint

	This class corresponds to the Viewpoint node in VRML.  
	<A href="../spec/part1/nodesRef.html#Viewpoint">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Viewpoint node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Viewpoint">link</a>.</ul>

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
class LIBInterface vrViewpoint : public vrBindable
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'description' field.
	//
	// [default] NULL
	//
	SFString            	m_Description;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'fieldOfView' exposedField.
	//
	// [default] 0.785398 
	//
	SFFloat             	m_FieldOfView;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'jump' exposedField.
	//
	// [default] TRUE
	//
	SFBool              	m_Jump;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'orientation' exposedField.
	//
	// [default] defRotation
	//
	SFRotation          	m_Orientation;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'position' exposedField.
	//
	// [default] zAxis*10
	//
	SFVec3f             	m_Position;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'bindTime' eventOut.
	//
	// [default] 0.0
	//
	SFTime              	m_BindTime;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrViewpoint(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrViewpoint(const vrViewpoint& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrViewpoint(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrViewpoint& operator=(const vrViewpoint& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Description member.
	//
	// [in] description: The description value.
	//
	void SetDescription(const SFString& description);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Description member.
	//
	SFString GetDescription(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_FieldOfView member.
	//
	// [in] fieldofview: The fieldofview value.
	//
	void SetFieldOfView(SFFloat fieldofview);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Jump member.
	//
	// [in] jump: The jump value.
	//
	void SetJump(SFBool jump);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Orientation member.
	//
	// [in] orientation: The orientation value.
	//
	void SetOrientation(const SFRotation& orientation);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Position member.
	//
	// [in] position: The position value.
	//
	void SetPosition(const SFVec3f& position);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_FieldOfView member.
	//
	SFFloat GetFieldOfView(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Jump member.
	//
	SFBool GetJump(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Orientation member.
	//
	SFRotation GetOrientation(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Position member.
	//
	SFVec3f GetPosition(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_BindTime member.
	//
	// [in] bindtime: The bindtime value.
	//
	void SetBindTime(SFTime bindtime);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_BindTime member.
	//
	SFTime GetBindTime(void) const;


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
	DECLARE_NODE(vrViewpoint);

	void CompleteNode(vrNode *top);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline SFString vrViewpoint::GetDescription(void) const
{
	return m_Description;
}

// exposedField sets and gets inlines
inline void vrViewpoint::SetFieldOfView(SFFloat fieldofview)
{
	m_FieldOfView = fieldofview;
}

inline void vrViewpoint::SetJump(SFBool jump)
{
	m_Jump = jump;
}

inline void vrViewpoint::SetOrientation(const SFRotation& orientation)
{
	m_Orientation = orientation;
}

inline void vrViewpoint::SetPosition(const SFVec3f& position)
{
	m_Position = position;
}

inline SFFloat vrViewpoint::GetFieldOfView(void) const
{
	return m_FieldOfView;
}

inline SFBool vrViewpoint::GetJump(void) const
{
	return m_Jump;
}

inline SFRotation vrViewpoint::GetOrientation(void) const
{
	return m_Orientation;
}

inline SFVec3f vrViewpoint::GetPosition(void) const
{
	return m_Position;
}

// eventOut sets and gets inlines
inline void vrViewpoint::SetBindTime(SFTime bindtime)
{
	m_BindTime = bindtime;
}

inline SFTime vrViewpoint::GetBindTime(void) const
{
	return m_BindTime;
}

inline void vrViewpoint::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

