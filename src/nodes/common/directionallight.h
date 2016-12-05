#ifndef __DIRECTIONALLIGHT_H3D
#define __DIRECTIONALLIGHT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Light.h"

/*----------------------------------------------------------------------
CLASS
	vrDirectionalLight

	This class corresponds to the DirectionalLight node in VRML.  
	<A href="../spec/part1/nodesRef.html#DirectionalLight">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the DirectionalLight node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#DirectionalLight">link</a>.</ul>

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
class LIBInterface vrDirectionalLight : public vrLight
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'direction' exposedField.
	//
	// [default] -zAxis
	//
	SFVec3f             	m_Direction;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrDirectionalLight(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrDirectionalLight(const vrDirectionalLight& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrDirectionalLight(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrDirectionalLight& operator=(const vrDirectionalLight& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Direction member.
	//
	// [in] direction: The direction value.
	//
	void SetDirection(const SFVec3f& direction);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Direction member.
	//
	SFVec3f GetDirection(void) const;


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
	DECLARE_NODE(vrDirectionalLight);

};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrDirectionalLight::SetDirection(const SFVec3f& direction)
{
	m_Direction = direction;
}

inline SFVec3f vrDirectionalLight::GetDirection(void) const
{
	return m_Direction;
}

inline void vrDirectionalLight::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

