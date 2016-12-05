#ifndef __APPEARANCE_H3D
#define __APPEARANCE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrAppearance

	This class corresponds to the Appearance node in VRML.  
	<A href="../spec/part1/nodesRef.html#Appearance">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Appearance node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Appearance">link</a>.</ul>

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
class LIBInterface vrAppearance : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'material' exposedField.
	//
	// [default] NULL
	//
	vrMaterial*         	m_Material;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'texture' exposedField.
	//
	// [default] NULL
	//
	vrPixelTexture*     	m_Texture;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'textureTransform' exposedField.
	//
	// [default] NULL
	//
	vrTextureTransform* 	m_TextureTransform;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrAppearance(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrAppearance(const vrAppearance& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrAppearance(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrAppearance& operator=(const vrAppearance& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Material member.
	//
	// [in] material: The material value.
	//
	void SetMaterial(const vrMaterial* material);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Texture member.
	//
	// [in] texture: The texture value.
	//
	void SetTexture(const vrPixelTexture* texture);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_TextureTransform member.
	//
	// [in] texturetransform: The texturetransform value.
	//
	void SetTextureTransform(const vrTextureTransform* texturetransform);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Material member.
	//
	vrMaterial* GetMaterial(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Texture member.
	//
	vrPixelTexture* GetTexture(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_TextureTransform member.
	//
	vrTextureTransform* GetTextureTransform(void) const;


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
	DECLARE_NODE(vrAppearance);

};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline vrMaterial* vrAppearance::GetMaterial(void) const
{
	return m_Material;
}

inline vrPixelTexture* vrAppearance::GetTexture(void) const
{
	return m_Texture;
}

inline vrTextureTransform* vrAppearance::GetTextureTransform(void) const
{
	return m_TextureTransform;
}

inline void vrAppearance::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

