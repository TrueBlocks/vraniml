#ifndef __OBJECT3D_H3D
#define __OBJECT3D_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "Browser\UserData.h"
#include "FieldDefs.h"
#include "Browser\Event.h"

class vrNode;
class vrTraverser;
class vrRouteList;
class vrEvent;

typedef vrNode *SFNode;
typedef vrArrayBase<SFNode> MFNode;
typedef SFBool (*PFBO3V)(SFNode, void *);

template<class TYPE>
class vrNodeStack :
	public vrRefCountStack < TYPE >
{
};

/*----------------------------------------------------------------------
CLASS
	vrNode

	The vrNode is the base class for all VRML nodes.

DESCRIPTION
	<ul>
	This class implements interfaces for various node related functions
	such as node naming, bounding box calculation, adding children nodes,
	setting and adding fields, etc.
	</ul>

NOTES
	<ul>
	<li>You will not use this class directly, instead you might use it as
		the base class for your own derived classes.</li>
	<li>All node classes share certain aspects which are described <a href="../nodespec.htm">here</a>.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrNode : public vrBaseNode
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>A dynamically allocated list of vrRoute objects that eminate from this node.
	// <dd>For each ROUTE statement in a .wrl file, this list will contain a vrRoute
	// <dd>   if this node is the source of the Route.
	// [default:] NULL
	//
	vrRouteList     *m_RouteList;

  //<doc>------------------------------------------------------------
  // <dd>The name of this node (as described in the DEF syntax of VRML).
	// [default:] NULL
	//
	SFString         m_Name;

  //<doc>------------------------------------------------------------
  // <dd>The bounding box (in the object's own space) that is represented
	// <dd>   by this node and its children (if any).
	//
  vrBoundingBox    m_Bounds;

  //<doc>------------------------------------------------------------
  // <dd>A list of vrUserDataItem objects each of which stores user defined
	// <dd>   data for this object.  An identifier is needed for each user
	// <dd>   defined data object because nodes may be multiply referenced
	// <dd>   (or DEF/USE'd).
	//
	vrUserDataList  *m_UserDataList;

public:
	MFString         m_IsMaps;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the given field is 'IS' mapped (in a PROTO)
	//
	// [in] fieldName: The field to check for IS mapping.
	//
	SFBool IsIsMapped(const SFString& fieldName) const;

	SFString         m_ProtoGroup;
	typedef enum { 
			normalNode=0, // a regular node not involed in a proto
			protoGroup, // a grouping node to hold the proto definition
			subsequentProtoNode, // nodes added to protos after the first node
			firstProtoNode, // the first node added to a proto
			protoNode, // a node added to a proto definition
			protoGroupInstance, // and instance of a PROTO group
			protoSFNode, // an SFNode that is a field in a PROTO
		} vrNodeType;
	vrNodeType       m_NodeType;

	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrNode            (void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrNode            (const vrNode& ob);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual          ~vrNode            (void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrNode&           operator=             (const vrNode& ob);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of this node.
	//
	virtual SFNode    Clone                 (void) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Clear the name and route list (if any) of this node.
	//
	void              Clear               (void);

	//<doc>------------------------------------------------------------
	// <dd>Set the name of this node (equates to the VRML concept of DEF).
	// <dd>A copy is made of the name string.
	// <dd>The name is verified as per VRML97 rules for naming nodes.
	//
	// [in] name: The name of this node.
	//
	void              SetName             (const SFString& name);

	//<doc>------------------------------------------------------------
	// <dd>Returns the name of this node or NULL.  Used by FindByName function for example.
	//
	SFString          GetName             (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this node has one or more routes eminating from it.
	//
	SFInt32           HasRoutes           (void) const
		{ return (m_RouteList != NULL); };

	//<doc>------------------------------------------------------------
	// <dd>Add a vrRoute to this node by specifying the source field, destintation node and destination field.
	// <dd>Rules for adding routes is defined here.
	//
	// [in] srcField: A vrField name for a node of this type that initiates the route.
	// [in] dstNode: The node to which the srcField is routed.
	// [in] dstField: The vrField in the dstNode to which the srcField is routed.
	// [in] internal: TRUE if this is an interally generated route (i.e. not defined in the VRML specification).
	//
	vrRoute          *AddRoute      (const SFString& srcField, SFNode dstNode, const SFString& dstField, SFBool internal=FALSE);

	//<doc>------------------------------------------------------------
	// <dd>Add a vrRoute to this node by specifying the source field, destintation node and destination field.
	// <dd>Rules for adding routes is defined here.
	//
	// [in] srcType: A vrField ID for a node of this type that initiates the route.
	// [in] dstNode: The node to which the srcField is routed.
	// [in] dstType: The vrField in the dstNode to which the srcField is routed.
	// [in] internal: TRUE if this is an interally generated route (i.e. not defined in the VRML specification).
	//
	vrRoute          *AddRoute      (SFInt32 srcType,     SFNode dstNode, SFInt32  dstType, SFBool internal=FALSE);

	//<nodoc>------------------------------------------------------------
	// <dd>Add a vrRoute directly to this node.  Note: the node does not make a copy and owns (and therefor will destroy) the vrRoute pointer.
	// <dd>It is assumed that the vrRoute references this node as its source node.
	//
	// [in] route: A pointer to the vrRoute to add to this node.
	//
	void              AddRoute      (vrRoute *route);

	//<doc>------------------------------------------------------------
	// <dd>Remove a vrRoute from this node.
	// <dd>If the route pointer is not found there is no effect or warning.
	//
	// [in] route: A pointer to the vrRoute to add to this node.
	//
	void              RemoveRoute   (vrRoute *route);

	//<doc>------------------------------------------------------------
	// <dd>Return a pointer to a vrRoute if this node has a route matching the given characteristics.
	// <dd>If the route pointer is not found NULL is returned.
	//
	// [in] srcField: A vrField name for a node of this type that initiates the route.
	// [in] dstNode: The node to which the srcField is routed.
	// [in] dstField: The vrField in the dstNode to which the srcField is routed.
	//
	vrRoute          *FindRoute     (const SFString& srcField, SFNode dstNode, const SFString& dstField) const;

	//<doc>------------------------------------------------------------
	// <dd>Return a pointer to this node's route list (or NULL).
	//
	vrRouteList      *GetRouteList	(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Respond to a traversal by an arbitrary traverser.
	// <dd>Note: Normally, nodes just call t->Traverse(this) to have the traverser handle the traversal.
	// <dd>      you may override this method in your derived class to handle traversals of node types.
	//
	// [in] trav: The vrTraverser requesting the traversal.
	//
	virtual void      Traverse      (vrTraverser *t) const;

	//<doc>------------------------------------------------------------
	// <dd>Receive an event during an event cascade or directly from caller.
	//
	// [in] event: The vrEvent to be processed.
	//
	virtual void      ReceiveEventIn(vrEvent *e)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>After receiving an event in send any corresponding event outs.
	//
	// [in] eventID: The eventOut to send.
	// [in] data: Void pointer to event data.
	//
	virtual void      SendEventOut	(SFInt32 eventID, void *data);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of a field given the field's name and a value.
	// <dd>Note: Error checking is done on 'fieldName' but cannot be done on 'val',
	// <dd>      so make sure you send the correct type of data to this method.
	//
	// [in] fieldName: The name of the field to set (as specified in the VRML97 specification).
	// [in] val: Void pointer to a field of the type corresponding to fieldName.
	//
	virtual SFBool    SetFieldValue(const SFString& fieldName, void *val)
		{ return FALSE; };

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the node (or a particular field) is in it's default state.
	//
	// [in] fieldName: The field to check for default value.  NULL implies check all fields of this node.
	// [out] field: If non-NULL the value of the field will be returned in field.
	//
	virtual  SFBool   IsDefault(const SFString& fieldName=nullString, vrField *field=NULL) const
		{ return TRUE; };

	//<doc>------------------------------------------------------------
	// <dd>Add a child to this node.  The node is verified before being added as
	// <dd>   per the VRML specification.
	// <dd>Note: This function does nothing by default.
	//
	// [in] node: The node to add.
	//
	virtual void      AddChild     (SFNode node);

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
	DECLARE_NODE(vrNode);

	//<nodoc>------------------------------------------------------------
	// <dd>Return the matrix that represents the local space that this node lives in.
	//
	virtual vrMatrix  GetLocalMatrix(void) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Return this node's bounding boxes (in local space).
	//
	virtual vrBoundingBox GetBoundingBox (void) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Recalculate this node (and all of it's childrens) bounding boxes.
	//
	vrBoundingBox     CalcBoxes   (vrMatrix& matrix);

	//<doc>------------------------------------------------------------
	// <dd>Return the vrUserData stored at this 'id'.
	//
	// [in] id: An identifier for the user defined data to be retrieved.
	//
	vrUserData *GetUserData(const SFString& id) const;

	//<doc>------------------------------------------------------------
	// <dd>Add a vrUserData to the node at this 'id'.  If 'id' is unique
	// <dd>   for each occurence of a node in the scene graph (for example
	// <dd>   if the node is multiply referenced (or DEF/USE'd) then you
	// <dd>   can store unique data per node.  If the same id is used for
	// <dd>   multiply referenced objects then the same user data will be
	// <dd>   stored for all occurances of the node.
	//
	// <dd>Note: The node owns the user data once it is passed in so do not
	// <dd>   delete it.  The node will delete the user data when the node
	// <dd>   is destroyed.  This means you should not store temporary 
	// <dd>   user data (i.e. user data created on the stack) without 
	// <dd>   removing it prior to going out of scope.
	//
	// [in] id: A unique identifier for this instance of user defined data.
	// [in] data: A vrUserData derived class holder user defined data.
	//
	void SetUserData(const SFString& id, vrUserData *data);

	virtual void CompleteNode(vrNode *top)
		{
			return;
		}

	SFString ClassName(void) const
		{
			ASSERT(GetRuntimeClass());
			return GetRuntimeClass()->ClassName();
		}
};
// Syntactic sugar
#define vrNodeType vrNode::vrNodeType

inline void vrNode::AddChild(SFNode node)
{
	// Base classes should override this if needed
	ASSERT(0);
}

// Return the matrix implied by this node
inline vrMatrix vrNode::GetLocalMatrix(void) const
{
	return IdentityMatrix();
}

#include "Traversers\Traverser.h"

// Used only by IsDefault to check a field for default values and
// possibly return the value
#define CHECK_FIELD(_str, _field, _def) \
{ \
	if (fieldName == (_str)) \
	{ \
		if (field) \
			SetValEx(field, (void*)&(_field)); \
		if (IsIsMapped(fieldName)) \
			return TRUE; \
		return ((_def) == (_field)); \
	} \
}

// Used only by IsDefault to check a field for default values and
// possibly return the value.  Used for array fields
#define CHECK_ARRAY_FIELD(_str, _func, _field, _def) \
{ \
	if (fieldName == (_str)) \
	{ \
		if (field) \
			SetValEx(field, (void*)&(_field)); \
		if (IsIsMapped(fieldName)) \
			return TRUE; \
		return ((_def) == _func); \
	} \
}

// Used only by IsDefault to check a field for default values and
// possibly return the value.  Used for string fields
#define CHECK_STRING_FIELD(_str, _field) \
{ \
	if (fieldName == (_str)) \
	{ \
		if (field) \
			SetValEx(field, (void*)&(_field)); \
		if (IsIsMapped(fieldName)) \
			return TRUE; \
		return (_field).Empty(); \
	} \
}

#endif

