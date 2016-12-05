#ifndef __TRANSFORM_H3D
#define __TRANSFORM_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\GroupingNode.h"

/*----------------------------------------------------------------------
CLASS
	vrTransform

	This class corresponds to the Transform node in VRML.  
	<A href="../spec/part1/nodesRef.html#Transform">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Transform node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Transform">link</a>.</ul>

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
class LIBInterface vrTransform : public vrGroupingNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'center' exposedField.
	//
	// [default] origin
	//
	SFVec3f             	m_Center;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'rotation' exposedField.
	//
	// [default] defRotation
	//
	SFRotation          	m_Rotation;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'scale' exposedField.
	//
	// [default] xyz1
	//
	SFVec3f             	m_Scale;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'scaleOrientation' exposedField.
	//
	// [default] defRotation
	//
	SFRotation          	m_ScaleOrientation;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'translation' exposedField.
	//
	// [default] origin
	//
	SFVec3f             	m_Translation;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrTransform(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrTransform(const vrTransform& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrTransform(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrTransform& operator=(const vrTransform& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Center member.
	//
	// [in] center: The center value.
	//
	void SetCenter(const SFVec3f& center);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Rotation member.
	//
	// [in] rotation: The rotation value.
	//
	void SetRotation(const SFRotation& rotation);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Scale member.
	//
	// [in] scale: The scale value.
	//
	void SetScale(const SFVec3f& scale);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_ScaleOrientation member.
	//
	// [in] scaleorientation: The scaleorientation value.
	//
	void SetScaleOrientation(const SFRotation& scaleorientation);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Translation member.
	//
	// [in] translation: The translation value.
	//
	void SetTranslation(const SFVec3f& translation);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Center member.
	//
	SFVec3f GetCenter(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Rotation member.
	//
	SFRotation GetRotation(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Scale member.
	//
	SFVec3f GetScale(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_ScaleOrientation member.
	//
	SFRotation GetScaleOrientation(void) const;

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
	DECLARE_NODE(vrTransform);

	//<nodoc>------------------------------------------------------------
	// <dd>Return the matrix that represents the local space that this node lives in.
	//
	virtual vrMatrix GetLocalMatrix(void) const;
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrTransform::SetCenter(const SFVec3f& center)
{
	m_Center = center;
}

inline void vrTransform::SetRotation(const SFRotation& rotation)
{
	m_Rotation = rotation;
}

inline void vrTransform::SetScale(const SFVec3f& scale)
{
	m_Scale = scale;
}

inline void vrTransform::SetScaleOrientation(const SFRotation& scaleorientation)
{
	m_ScaleOrientation = scaleorientation;
}

inline void vrTransform::SetTranslation(const SFVec3f& translation)
{
	m_Translation = translation;
}

inline SFVec3f vrTransform::GetCenter(void) const
{
	return m_Center;
}

inline SFRotation vrTransform::GetRotation(void) const
{
	return m_Rotation;
}

inline SFVec3f vrTransform::GetScale(void) const
{
	return m_Scale;
}

inline SFRotation vrTransform::GetScaleOrientation(void) const
{
	return m_ScaleOrientation;
}

inline SFVec3f vrTransform::GetTranslation(void) const
{
	return m_Translation;
}

inline void vrTransform::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

