#ifndef __INLINE_H3D
#define __INLINE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\GroupingNode.h"

/*----------------------------------------------------------------------
CLASS
	vrInline

	This class corresponds to the Inline node in VRML.  
	<A href="../spec/part1/nodesRef.html#Inline">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Inline node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Inline">link</a>.</ul>

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
class LIBInterface vrInline : public vrGroupingNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origUrl.
	//
	// [default] []
	//
	MFString            	m_OrigUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'url' exposedField.
	//
	// [default] []
	//
	MFString            	m_Url;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrInline(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrInline(const vrInline& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrInline(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrInline& operator=(const vrInline& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_OrigUrl array (grow if needed).
	//
	// [in] origurl: The value to add to the m_OrigUrl array.
	//
	void AddOrigUrl(const SFString& origurl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_OrigUrl member (copies values).
	//
	// [in] origurl: The m_OrigUrl array.
	//
	void SetOrigUrl(const MFString& origurl);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_OrigUrl member.
	//
	SFInt32 GetNOrigUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_OrigUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetOrigUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_OrigUrl member.
	//
	const MFString& GetOrigUrlArray(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Url array (grow if needed).
	//
	// [in] url: The value to add to the m_Url array.
	//
	void AddUrl(const SFString& url);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Url member (copies values).
	//
	// [in] url: The m_Url array.
	//
	void SetUrl(const MFString& url);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Url member.
	//
	SFInt32 GetNUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Url member.
	//
	// [in] n: The index into the array.
	//
	SFString GetUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Url member.
	//
	const MFString& GetUrlArray(void) const;


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
	DECLARE_NODE(vrInline);

};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrInline::AddOrigUrl(const SFString& origurl)
{
	m_OrigUrl.AddValue(origurl);
}

inline void vrInline::SetOrigUrl(const MFString& origurl)
{
	m_OrigUrl.Clear();
	m_OrigUrl = origurl;
}

inline SFInt32 vrInline::GetNOrigUrls(void) const
{
	return m_OrigUrl.GetCount();
}

inline SFString vrInline::GetOrigUrl(SFInt32 n) const
{
	return m_OrigUrl[n];
}

inline const MFString& vrInline::GetOrigUrlArray(void) const
{
	return m_OrigUrl;
}

// exposedField sets and gets inlines
inline void vrInline::AddUrl(const SFString& url)
{
	m_Url.AddValue(url);
}

inline void vrInline::SetUrl(const MFString& url)
{
	m_Url.Clear();
	m_Url = url;
}

inline SFInt32 vrInline::GetNUrls(void) const
{
	return m_Url.GetCount();
}

inline SFString vrInline::GetUrl(SFInt32 n) const
{
	return m_Url[n];
}

inline const MFString& vrInline::GetUrlArray(void) const
{
	return m_Url;
}

inline void vrInline::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

