#ifndef __COLOR_H3D
#define __COLOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrColor

	This class corresponds to the Color node in VRML.  
	<A href="../spec/part1/nodesRef.html#Color">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Color node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Color">link</a>.</ul>

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
class LIBInterface vrColor : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'color' exposedField.
	//
	// [default] []
	//
	MFColor             	m_Color;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrColor(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrColor(const vrColor& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrColor(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrColor& operator=(const vrColor& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Color array (grow if needed).
	//
	// [in] color: The value to add to the m_Color array.
	//
	void AddColor(const SFColor& color);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Color member (copies values).
	//
	// [in] color: The m_Color array.
	//
	void SetColor(const MFColor& color);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Color member.
	//
	SFInt32 GetNColors(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Color member.
	//
	// [in] n: The index into the array.
	//
	SFColor GetColor(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Color member.
	//
	const MFColor& GetColorArray(void) const;


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
	DECLARE_NODE(vrColor);

};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrColor::AddColor(const SFColor& color)
{
	m_Color.AddValue(color);
}

inline void vrColor::SetColor(const MFColor& color)
{
	m_Color.Clear();
	m_Color = color;
}

inline SFInt32 vrColor::GetNColors(void) const
{
	return m_Color.GetCount();
}

inline SFColor vrColor::GetColor(SFInt32 n) const
{
	return m_Color[n];
}

inline const MFColor& vrColor::GetColorArray(void) const
{
	return m_Color;
}

inline void vrColor::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

