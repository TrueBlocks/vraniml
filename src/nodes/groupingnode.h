#ifndef __GROUPINGNODE_H3D
#define __GROUPINGNODE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Node.h"

typedef vrRefCountList<SFNode> vrNodeList;

/*----------------------------------------------------------------------
CLASS
	vrGroupingNode

DESCRIPTION
	<ul>This class serves as the base class for the all grouping nodes including
	importantly the vrBrowser class.  It maintains a list of children nodes
	and is the basis for the VRML scene graph.
	</ul>

NOTES
	<ul>
	<li>You will probably not use this class directly, it will serve as the basis for derived classes.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrGroupingNode : public vrNode
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>The list of children nodes of this grouping node.  This is the scene graph.
	// [default:] NULL
	//
	vrNodeList      *m_Children;

  //<doc>------------------------------------------------------------
  // <dd>The user supplied bounding box center (from the .wrl file).
	// [default:] zero
	//
	SFVec3f          m_BboxCenter;

  //<doc>------------------------------------------------------------
  // <dd>The user supplied bounding box size (from the .wrl file).
	// [default:] zero
	//
	SFVec3f          m_BboxSize;

  //<nodoc>------------------------------------------------------------
  // <dd>TRUE if this grouping node contains a direct child derived from type vrSensor.
	// [default:] FALSE
	//
	SFBool           m_hasSensor;

  //<nodoc>------------------------------------------------------------
  // <dd>TRUE if this grouping node contains a node type derived from vrLight
	// [default:] FALSE
	//
	SFBool           m_hasLight;

public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
  vrGroupingNode(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
  vrGroupingNode(const vrGroupingNode& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrGroupingNode(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
  vrGroupingNode& operator=(const vrGroupingNode& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of this node (and all its children).
	//
	virtual  SFNode              Clone(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the Bbox center field.
	//
	// [in] bboxcenter: The value.
	//
  void                SetBboxCenter(const SFVec3f& bboxcenter);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the Bbox size field.
	//
	// [in] bboxsize: The value.
	//
  void                SetBboxSize(const SFVec3f& bboxsize);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the bbox center field.
	//
  SFVec3f             GetBboxCenter(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the bbox size field.
	//
	SFVec3f             GetBboxSize(void) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Clear the node's child list after calling vrNode::Clear
	//
	void                Clear      (void);

	//<doc>------------------------------------------------------------
	// <dd>Add a child to this node.  The node is verified before being added as
	// <dd>   per the VRML specification.
	//
	// [in] node: The node to add as a child.  Runtime typing is used to determine if the node is a valid child node.
	//
	virtual void      AddChild     (SFNode node);

	//<nodoc>------------------------------------------------------------
	// <dd>Move this node's children to a different grouping node.
	//
	// [in] to: The grouping node to move the children to.
	//
	void              MoveChildren(vrGroupingNode *to);

	//<doc>------------------------------------------------------------
	// <dd>Returns a pointer to this nodes children list or NULL.
	//
	//
  vrNodeList       *GetChildren (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this node has children.
	//
	//
  SFBool            HasChildren (void) const
		{ return (SFBool)(m_Children!=NULL); }

	//<doc>------------------------------------------------------------
	// <dd>Respond to a traversal by an arbitrary traverser.
	// <dd>Note: Normally, nodes just call t->Traverse(this) to have the traverser handle the traversal.
	// <dd>      you may override this method in your derived class to handle traversals of node types.
	//
	// [in] trav: The vrTraverser requesting the traversal.
	//
	virtual void      Traverse      (vrTraverser *t) const;

	//<doc>------------------------------------------------------------
	// <dd>Set the value of a field given the field's name and a value.
	// <dd>Note: Error checking is done on 'fieldName' but cannot be done on 'val',
	// <dd>      so make sure you send the correct type of data to this method.
	//
	// [in] fieldName: The name of the field to set (as specified in the VRML97 specification).
	// [in] val: Void pointer to a field of the type corresponding to fieldName.
	//
	virtual SFBool    SetFieldValue(const SFString& fieldName, void *val);

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the node (or a particular field) is in it's default state.
	//
	// [in] fieldName: The field to check for default value.  NULL implies check all fields of this node.
	// [out] field: If non-NULL the value of the field will be returned in field.
	//
	virtual  SFBool   IsDefault(const SFString& fieldName=nullString, vrField *field=NULL) const;

	//<doc>------------------------------------------------------------
	// <dd>Find a node by type (searches any vrNode derived data members).  Returns NULL if not found.
	//
	// [in] pClass: Pointer to a vrRuntimeClass representing the searched for type.
	//
	virtual SFNode    FindByType   (vrRuntimeClass *pClass) const;

	//<doc>------------------------------------------------------------
	// <dd>Find a node by name (searches vrNode derived data members).  Returns NULL if not found.
	//
	// [in] nodeName: The name of the node being searched for.
	//
	virtual SFNode    FindByName   (const SFString& nodeName) const;

	//<doc>------------------------------------------------------------
	// <dd>Apply 'userFn' to all contained nodes (including any children and/or direct references).  [ <a href="../forevery.htm">Additional information.</a> ]
	//
	// [in] userFn: Pointer to a function returning SFBool and taking an SFNode and void pointer as arguments.  'userFn' is applied to this node and all children (if any).
	// [in] userData: Pointer to arbitrary user data.
	// [in] afterFn: Pointer to a function to apply after applying 'userFn' to all children (for example: popping a stack).
	//
	virtual SFBool    ForEvery     (PFBO3V userFn, void *userData, PFBO3V afterFn=NULL);

	//<doc>------------------------------------------------------------
	// <dd>Declare that this node may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrGroupingNode);

	//<nodoc>------------------------------------------------------------
	// <dd>Returns TRUE if this node contains a direct child that is a sensor.
	//
	SFBool HasSensor(void) const
		{ return m_hasSensor; };

	//<nodoc>------------------------------------------------------------
	// <dd>Returns TRUE if this node contains a light.
	//
	SFBool HasLight(void) const
		{ return m_hasLight; };

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this node is a direct parent the query node.
	//
	// [in] node: The query node.
	//
	SFBool IsParentOf(SFNode node);
};

inline vrNodeList *vrGroupingNode::GetChildren(void) const
{
	return m_Children;
}

inline void vrGroupingNode::SetBboxCenter(const SFVec3f& bboxcenter)
{
	m_BboxCenter = bboxcenter;
}

inline void vrGroupingNode::SetBboxSize(const SFVec3f& bboxsize)
{
	m_BboxSize = bboxsize;
}

inline SFVec3f vrGroupingNode::GetBboxCenter(void) const
{
	return m_BboxCenter;
}

inline SFVec3f vrGroupingNode::GetBboxSize(void) const
{
	return m_BboxSize;
}

inline void vrGroupingNode::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}

#endif

