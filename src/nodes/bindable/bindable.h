#ifndef __BINDABLE_H3D
#define __BINDABLE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

#define PENDING_BIND   1000  // next traversal should bind this node
#define PENDING_UNBIND 2000  // next traversal should unbind this node

/*----------------------------------------------------------------------
CLASS
	vrBindable

	This class corresponds to the Bindable node in VRML.  
	<A href="../spec/part1/nodesRef.html#Bindable">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Bindable node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Bindable">link</a>.</ul>

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
class LIBInterface vrBindable : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field boundTo.
	//
	// [default] NULL
	//
	vrBrowser*          	m_BoundTo;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'isBound' eventOut.
	//
	// [default] FALSE
	//
	SFBool              	m_IsBound;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'bind' eventIn.
	//
	// [default] FALSE
	//
	SFBool              	m_Bind;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrBindable(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrBindable(const vrBindable& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrBindable(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrBindable& operator=(const vrBindable& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_BoundTo member.
	//
	// [in] boundto: The boundto value.
	//
	void SetBoundTo(const vrBrowser* boundto);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_BoundTo member.
	//
	vrBrowser* GetBoundTo(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_IsBound member.
	//
	// [in] isbound: The isbound value.
	//
	void SetIsBound(SFBool isbound);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_IsBound member.
	//
	SFBool IsBound(void) const;


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
	DECLARE_NODE(vrBindable);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline vrBrowser* vrBindable::GetBoundTo(void) const
{
	return m_BoundTo;
}

// eventOut sets and gets inlines
inline void vrBindable::SetIsBound(SFBool isbound)
{
	m_IsBound = isbound;
}

inline SFBool vrBindable::IsBound(void) const
{
	return m_IsBound;
}

inline void vrBindable::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

