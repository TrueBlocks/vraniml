#ifndef __ANCHOR_H3D
#define __ANCHOR_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\GroupingNode.h"

/*----------------------------------------------------------------------
CLASS
	vrAnchor

	This class corresponds to the Anchor node in VRML.  
	<A href="../spec/part1/nodesRef.html#Anchor">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Anchor node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Anchor">link</a>.</ul>

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
class LIBInterface vrAnchor : public vrGroupingNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origUrl.
	//
	// [default] []
	//
	MFString            	m_OrigUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'description' exposedField.
	//
	// [default] NULL
	//
	SFString            	m_Description;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'parameter' exposedField.
	//
	// [default] []
	//
	MFString            	m_Parameter;

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
	vrAnchor(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrAnchor(const vrAnchor& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrAnchor(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrAnchor& operator=(const vrAnchor& v);

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
	// <dd>Set the value of the m_Description member.
	//
	// [in] description: The description value.
	//
	void SetDescription(const SFString& description);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Parameter array (grow if needed).
	//
	// [in] parameter: The value to add to the m_Parameter array.
	//
	void AddParameter(const SFString& parameter);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Parameter member (copies values).
	//
	// [in] parameter: The m_Parameter array.
	//
	void SetParameter(const MFString& parameter);

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
	// <dd>Return the value of the m_Description member.
	//
	SFString GetDescription(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Parameter member.
	//
	SFInt32 GetNParameters(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Parameter member.
	//
	// [in] n: The index into the array.
	//
	SFString GetParameter(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Parameter member.
	//
	const MFString& GetParameterArray(void) const;

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
	DECLARE_NODE(vrAnchor);

	//------------------------------------------------------------
	// hand coded functions
	void PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrAnchor::AddOrigUrl(const SFString& origurl)
{
	m_OrigUrl.AddValue(origurl);
}

inline void vrAnchor::SetOrigUrl(const MFString& origurl)
{
	m_OrigUrl.Clear();
	m_OrigUrl = origurl;
}

inline SFInt32 vrAnchor::GetNOrigUrls(void) const
{
	return m_OrigUrl.GetCount();
}

inline SFString vrAnchor::GetOrigUrl(SFInt32 n) const
{
	return m_OrigUrl[n];
}

inline const MFString& vrAnchor::GetOrigUrlArray(void) const
{
	return m_OrigUrl;
}

// exposedField sets and gets inlines
inline void vrAnchor::AddParameter(const SFString& parameter)
{
	m_Parameter.AddValue(parameter);
}

inline void vrAnchor::SetParameter(const MFString& parameter)
{
	m_Parameter.Clear();
	m_Parameter = parameter;
}

inline void vrAnchor::AddUrl(const SFString& url)
{
	m_Url.AddValue(url);
}

inline void vrAnchor::SetUrl(const MFString& url)
{
	m_Url.Clear();
	m_Url = url;
}

inline SFString vrAnchor::GetDescription(void) const
{
	return m_Description;
}

inline SFInt32 vrAnchor::GetNParameters(void) const
{
	return m_Parameter.GetCount();
}

inline SFString vrAnchor::GetParameter(SFInt32 n) const
{
	return m_Parameter[n];
}

inline const MFString& vrAnchor::GetParameterArray(void) const
{
	return m_Parameter;
}

inline SFInt32 vrAnchor::GetNUrls(void) const
{
	return m_Url.GetCount();
}

inline SFString vrAnchor::GetUrl(SFInt32 n) const
{
	return m_Url[n];
}

inline const MFString& vrAnchor::GetUrlArray(void) const
{
	return m_Url;
}

inline void vrAnchor::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

