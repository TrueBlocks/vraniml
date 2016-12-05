#ifndef __WORLDINFO_H3D
#define __WORLDINFO_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrWorldInfo

	This class corresponds to the WorldInfo node in VRML.  
	<A href="../spec/part1/nodesRef.html#WorldInfo">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the WorldInfo node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#WorldInfo">link</a>.</ul>

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
class LIBInterface vrWorldInfo : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'info' field.
	//
	// [default] []
	//
	MFString            	m_Info;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'title' field.
	//
	// [default] NULL
	//
	SFString            	m_Title;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrWorldInfo(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrWorldInfo(const vrWorldInfo& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrWorldInfo(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrWorldInfo& operator=(const vrWorldInfo& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Info array (grow if needed).
	//
	// [in] info: The value to add to the m_Info array.
	//
	void AddInfo(const SFString& info);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Info member (copies values).
	//
	// [in] info: The m_Info array.
	//
	void SetInfo(const MFString& info);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Title member.
	//
	// [in] title: The title value.
	//
	void SetTitle(const SFString& title);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Info member.
	//
	SFInt32 GetNInfos(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Info member.
	//
	// [in] n: The index into the array.
	//
	SFString GetInfo(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Info member.
	//
	const MFString& GetInfoArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Title member.
	//
	SFString GetTitle(void) const;


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
	// <dd>Returns TRUE if the node (or a particular field) is in it's default state.
	//
	// [in] fieldName: The field to check for default value.  NULL implies check all fields of this node.
	// [out] field: If non-NULL the value of the field will be returned in field.
	//
	virtual SFBool IsDefault(const SFString& fieldName=nullString, vrField *field=NULL) const;

	//<doc>------------------------------------------------------------
	// <dd>Declare that this node may be runtime typed and dynamically created. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrWorldInfo);

};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrWorldInfo::AddInfo(const SFString& info)
{
	m_Info.AddValue(info);
}

inline void vrWorldInfo::SetInfo(const MFString& info)
{
	m_Info.Clear();
	m_Info = info;
}

inline SFInt32 vrWorldInfo::GetNInfos(void) const
{
	return m_Info.GetCount();
}

inline SFString vrWorldInfo::GetInfo(SFInt32 n) const
{
	return m_Info[n];
}

inline const MFString& vrWorldInfo::GetInfoArray(void) const
{
	return m_Info;
}

inline SFString vrWorldInfo::GetTitle(void) const
{
	return m_Title;
}

inline void vrWorldInfo::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

