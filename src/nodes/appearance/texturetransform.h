#ifndef __TEXTURETRANSFORM_H3D
#define __TEXTURETRANSFORM_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrTextureTransform

	This class corresponds to the TextureTransform node in VRML.  
	<A href="../spec/part1/nodesRef.html#TextureTransform">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the TextureTransform node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#TextureTransform">link</a>.</ul>

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
class LIBInterface vrTextureTransform : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'center' exposedField.
	//
	// [default] origin2
	//
	SFVec2f             	m_Center;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'rotation' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_Rotation;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'scale' exposedField.
	//
	// [default] xy1
	//
	SFVec2f             	m_Scale;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'translation' exposedField.
	//
	// [default] origin2
	//
	SFVec2f             	m_Translation;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrTextureTransform(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrTextureTransform(const vrTextureTransform& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrTextureTransform(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrTextureTransform& operator=(const vrTextureTransform& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Center member.
	//
	// [in] center: The center value.
	//
	void SetCenter(const SFVec2f& center);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Rotation member.
	//
	// [in] rotation: The rotation value.
	//
	void SetRotation(SFFloat rotation);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Scale member.
	//
	// [in] scale: The scale value.
	//
	void SetScale(const SFVec2f& scale);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Translation member.
	//
	// [in] translation: The translation value.
	//
	void SetTranslation(const SFVec2f& translation);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Center member.
	//
	SFVec2f GetCenter(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Rotation member.
	//
	SFFloat GetRotation(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Scale member.
	//
	SFVec2f GetScale(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Translation member.
	//
	SFVec2f GetTranslation(void) const;


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
	DECLARE_NODE(vrTextureTransform);

};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrTextureTransform::SetCenter(const SFVec2f& center)
{
	m_Center = center;
}

inline void vrTextureTransform::SetRotation(SFFloat rotation)
{
	m_Rotation = rotation;
}

inline void vrTextureTransform::SetScale(const SFVec2f& scale)
{
	m_Scale = scale;
}

inline void vrTextureTransform::SetTranslation(const SFVec2f& translation)
{
	m_Translation = translation;
}

inline SFVec2f vrTextureTransform::GetCenter(void) const
{
	return m_Center;
}

inline SFFloat vrTextureTransform::GetRotation(void) const
{
	return m_Rotation;
}

inline SFVec2f vrTextureTransform::GetScale(void) const
{
	return m_Scale;
}

inline SFVec2f vrTextureTransform::GetTranslation(void) const
{
	return m_Translation;
}

inline void vrTextureTransform::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

