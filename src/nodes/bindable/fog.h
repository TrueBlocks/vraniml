#ifndef __FOG_H3D
#define __FOG_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Bindable.h"

/*----------------------------------------------------------------------
CLASS
	vrFog

	This class corresponds to the Fog node in VRML.  
	<A href="../spec/part1/nodesRef.html#Fog">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Fog node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Fog">link</a>.</ul>

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
class LIBInterface vrFog : public vrBindable
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'color' exposedField.
	//
	// [default] vrWhite
	//
	SFColor             	m_Color;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'fogType' exposedField.
	//
	// [default] "LINEAR"
	//
	SFString            	m_FogType;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'visibilityRange' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_VisibilityRange;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrFog(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrFog(const vrFog& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrFog(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrFog& operator=(const vrFog& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Color member.
	//
	// [in] color: The color value.
	//
	void SetColor(const SFColor& color);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_FogType member.
	//
	// [in] fogtype: The fogtype value.
	//
	void SetFogType(const SFString& fogtype);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_VisibilityRange member.
	//
	// [in] visibilityrange: The visibilityrange value.
	//
	void SetVisibilityRange(SFFloat visibilityrange);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Color member.
	//
	SFColor GetColor(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_FogType member.
	//
	SFString GetFogType(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_VisibilityRange member.
	//
	SFFloat GetVisibilityRange(void) const;


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
	DECLARE_NODE(vrFog);

	void CompleteNode(vrNode *top);
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrFog::SetColor(const SFColor& color)
{
	m_Color = color;
}

inline void vrFog::SetVisibilityRange(SFFloat visibilityrange)
{
	m_VisibilityRange = visibilityrange;
}

inline SFColor vrFog::GetColor(void) const
{
	return m_Color;
}

inline SFString vrFog::GetFogType(void) const
{
	return m_FogType;
}

inline SFFloat vrFog::GetVisibilityRange(void) const
{
	return m_VisibilityRange;
}

inline void vrFog::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

