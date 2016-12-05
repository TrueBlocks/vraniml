#ifndef __SHAPE_H3D
#define __SHAPE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrShape

	This class corresponds to the Shape node in VRML.  
	<A href="../spec/part1/nodesRef.html#Shape">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Shape node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Shape">link</a>.</ul>

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
class LIBInterface vrShape : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'appearance' exposedField.
	//
	// [default] NULL
	//
	vrAppearance*       	m_Appearance;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'geometry' exposedField.
	//
	// [default] NULL
	//
	vrGeometryNode*     	m_Geometry;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrShape(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrShape(const vrShape& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrShape(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrShape& operator=(const vrShape& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Appearance member.
	//
	// [in] appearance: The appearance value.
	//
	void SetAppearance(const vrAppearance* appearance);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Geometry member.
	//
	// [in] geometry: The geometry value.
	//
	void SetGeometry(const vrGeometryNode* geometry);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Appearance member.
	//
	vrAppearance* GetAppearance(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Geometry member.
	//
	vrGeometryNode* GetGeometry(void) const;


	//<nodoc>------------------------------------------------------------
	// <dd>Set the value of a field given the field's name and a value.
	// <dd>Note: Error checking is done on 'fieldName' but cannot be done on 'val',
	// <dd>      so make sure you send the correct type of data to this method.
	//
	// [in] fieldName: The name of the field to set (as specified in the VRML97 specification).
	// [in] val: Void pointer to a field of the type corresponding to fieldName.
	//
	virtual SFBool SetFieldValue(const SFString& fieldName, void *val);

	//<nodoc>------------------------------------------------------------
	// <dd>Add the given node to this node.  Runtime typing is used to
	//     determine which node to add.
	//
	// [in] node: The node to add.
	//
	virtual void AddChild(SFNode node);

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
	// <dd>Find a node by class type.  Returns NULL if not found. (Overridden to search vrNode derived data members).
	//
	// [in] pClass: Pointer to a vrRuntimeClass representing the searched for type.
	//
	virtual SFNode FindByType(vrRuntimeClass *pClass) const;

	//<doc>------------------------------------------------------------
	// <dd>Find a node by name.  Returns NULL if not found.  (Overridden to search vrNode derived data members)
	//
	// [in] nodeName: The name of the node being searched for.
	//
	virtual SFNode FindByName(const SFString& nodeName) const;

	//<doc>------------------------------------------------------------
	// <dd>Apply 'userFn' to all contained nodes (including any children and/or direct references).  [ <a href="../forevery.htm">Additional information.</a> ]
	//
	// [in] userFn: Pointer to a function returning SFBool and taking an SFNode and void pointer as arguments.  'userFn' is applied to this node and all children (if any).
	// [in] userData: Pointer to arbitrary user data.
	// [in] afterFn: Pointer to a function to apply after applying 'userFn' to all children (for example: popping a stack).
	//
	virtual SFBool ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn=NULL);

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
	DECLARE_NODE(vrShape);

};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline vrAppearance* vrShape::GetAppearance(void) const
{
	return m_Appearance;
}

inline vrGeometryNode* vrShape::GetGeometry(void) const
{
	return m_Geometry;
}

inline void vrShape::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

