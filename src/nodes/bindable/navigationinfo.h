#ifndef __NAVIGATIONINFO_H3D
#define __NAVIGATIONINFO_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Bindable.h"

/*----------------------------------------------------------------------
CLASS
	vrNavigationInfo

	This class corresponds to the NavigationInfo node in VRML.  
	<A href="../spec/part1/nodesRef.html#NavigationInfo">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the NavigationInfo node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#NavigationInfo">link</a>.</ul>

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
class LIBInterface vrNavigationInfo : public vrBindable
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'avatarSize' exposedField.
	//
	// [default] 0.25
	//
	MFFloat             	m_AvatarSize;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'headlight' exposedField.
	//
	// [default] TRUE
	//
	SFBool              	m_Headlight;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'speed' exposedField.
	//
	// [default] 1.0 
	//
	SFFloat             	m_Speed;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'type' exposedField.
	//
	// [default] "WALK" 
	//
	MFString            	m_Type;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'visibilityLimit' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_VisibilityLimit;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrNavigationInfo(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrNavigationInfo(const vrNavigationInfo& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrNavigationInfo(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrNavigationInfo& operator=(const vrNavigationInfo& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_AvatarSize array (grow if needed).
	//
	// [in] avatarsize: The value to add to the m_AvatarSize array.
	//
	void AddAvatarSize(SFFloat avatarsize);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_AvatarSize member (copies values).
	//
	// [in] avatarsize: The m_AvatarSize array.
	//
	void SetAvatarSize(const MFFloat& avatarsize);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Headlight member.
	//
	// [in] headlight: The headlight value.
	//
	void SetHeadlight(SFBool headlight);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Speed member.
	//
	// [in] speed: The speed value.
	//
	void SetSpeed(SFFloat speed);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Type array (grow if needed).
	//
	// [in] type: The value to add to the m_Type array.
	//
	void AddType(const SFString& type);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Type member (copies values).
	//
	// [in] type: The m_Type array.
	//
	void SetType(const MFString& type);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_VisibilityLimit member.
	//
	// [in] visibilitylimit: The visibilitylimit value.
	//
	void SetVisibilityLimit(SFFloat visibilitylimit);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_AvatarSize member.
	//
	SFInt32 GetNAvatarSizes(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_AvatarSize member.
	//
	// [in] n: The index into the array.
	//
	SFFloat GetAvatarSize(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_AvatarSize member.
	//
	const MFFloat& GetAvatarSizeArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Headlight member.
	//
	SFBool GetHeadlight(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Speed member.
	//
	SFFloat GetSpeed(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Type member.
	//
	SFInt32 GetNTypes(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Type member.
	//
	// [in] n: The index into the array.
	//
	SFString GetType(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Type member.
	//
	const MFString& GetTypeArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_VisibilityLimit member.
	//
	SFFloat GetVisibilityLimit(void) const;


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
	DECLARE_NODE(vrNavigationInfo);

	void CompleteNode(vrNode *top);
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrNavigationInfo::AddAvatarSize(SFFloat avatarsize)
{
	m_AvatarSize.AddValue(avatarsize);
}

inline void vrNavigationInfo::SetAvatarSize(const MFFloat& avatarsize)
{
	m_AvatarSize.Clear();
	m_AvatarSize = avatarsize;
}

inline void vrNavigationInfo::SetHeadlight(SFBool headlight)
{
	m_Headlight = headlight;
}

inline void vrNavigationInfo::SetSpeed(SFFloat speed)
{
	m_Speed = speed;
}

inline void vrNavigationInfo::AddType(const SFString& type)
{
	m_Type.AddValue(type);
}

inline void vrNavigationInfo::SetType(const MFString& type)
{
	m_Type.Clear();
	m_Type = type;
}

inline void vrNavigationInfo::SetVisibilityLimit(SFFloat visibilitylimit)
{
	m_VisibilityLimit = visibilitylimit;
}

inline SFInt32 vrNavigationInfo::GetNAvatarSizes(void) const
{
	return m_AvatarSize.GetCount();
}

inline SFFloat vrNavigationInfo::GetAvatarSize(SFInt32 n) const
{
	return m_AvatarSize[n];
}

inline const MFFloat& vrNavigationInfo::GetAvatarSizeArray(void) const
{
	return m_AvatarSize;
}

inline SFBool vrNavigationInfo::GetHeadlight(void) const
{
	return m_Headlight;
}

inline SFFloat vrNavigationInfo::GetSpeed(void) const
{
	return m_Speed;
}

inline SFInt32 vrNavigationInfo::GetNTypes(void) const
{
	return m_Type.GetCount();
}

inline SFString vrNavigationInfo::GetType(SFInt32 n) const
{
	return m_Type[n];
}

inline const MFString& vrNavigationInfo::GetTypeArray(void) const
{
	return m_Type;
}

inline SFFloat vrNavigationInfo::GetVisibilityLimit(void) const
{
	return m_VisibilityLimit;
}

inline void vrNavigationInfo::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

