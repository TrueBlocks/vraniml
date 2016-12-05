#ifndef __BACKGROUND_H3D
#define __BACKGROUND_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Bindable.h"

/*----------------------------------------------------------------------
CLASS
	vrBackground

	This class corresponds to the Background node in VRML.  
	<A href="../spec/part1/nodesRef.html#Background">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Background node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Background">link</a>.</ul>

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
class LIBInterface vrBackground : public vrBindable
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origBackUrl.
	//
	// [default] []
	//
	MFString            	m_OrigBackUrl;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origBottomUrl.
	//
	// [default] []
	//
	MFString            	m_OrigBottomUrl;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origFrontUrl.
	//
	// [default] []
	//
	MFString            	m_OrigFrontUrl;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origLeftUrl.
	//
	// [default] []
	//
	MFString            	m_OrigLeftUrl;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origRightUrl.
	//
	// [default] []
	//
	MFString            	m_OrigRightUrl;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origTopUrl.
	//
	// [default] []
	//
	MFString            	m_OrigTopUrl;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field backgroundGroup.
	//
	// [default] NULL
	//
	vrGroup*            	m_BackgroundGroup;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'groundAngle' exposedField.
	//
	// [default] []
	//
	MFFloat             	m_GroundAngle;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'groundColor' exposedField.
	//
	// [default] []
	//
	MFColor             	m_GroundColor;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'backUrl' exposedField.
	//
	// [default] []
	//
	MFString            	m_BackUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'bottomUrl' exposedField.
	//
	// [default] []
	//
	MFString            	m_BottomUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'frontUrl' exposedField.
	//
	// [default] []
	//
	MFString            	m_FrontUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'leftUrl' exposedField.
	//
	// [default] []
	//
	MFString            	m_LeftUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'rightUrl' exposedField.
	//
	// [default] []
	//
	MFString            	m_RightUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'topUrl' exposedField.
	//
	// [default] []
	//
	MFString            	m_TopUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'skyAngle' exposedField.
	//
	// [default] []
	//
	MFFloat             	m_SkyAngle;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'skyColor' exposedField.
	//
	// [default] []
	//
	MFColor             	m_SkyColor;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrBackground(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrBackground(const vrBackground& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrBackground(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrBackground& operator=(const vrBackground& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_OrigBackUrl array (grow if needed).
	//
	// [in] origbackurl: The value to add to the m_OrigBackUrl array.
	//
	void AddOrigBackUrl(const SFString& origbackurl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_OrigBackUrl member (copies values).
	//
	// [in] origbackurl: The m_OrigBackUrl array.
	//
	void SetOrigBackUrl(const MFString& origbackurl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_OrigBottomUrl array (grow if needed).
	//
	// [in] origbottomurl: The value to add to the m_OrigBottomUrl array.
	//
	void AddOrigBottomUrl(const SFString& origbottomurl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_OrigBottomUrl member (copies values).
	//
	// [in] origbottomurl: The m_OrigBottomUrl array.
	//
	void SetOrigBottomUrl(const MFString& origbottomurl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_OrigFrontUrl array (grow if needed).
	//
	// [in] origfronturl: The value to add to the m_OrigFrontUrl array.
	//
	void AddOrigFrontUrl(const SFString& origfronturl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_OrigFrontUrl member (copies values).
	//
	// [in] origfronturl: The m_OrigFrontUrl array.
	//
	void SetOrigFrontUrl(const MFString& origfronturl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_OrigLeftUrl array (grow if needed).
	//
	// [in] origlefturl: The value to add to the m_OrigLeftUrl array.
	//
	void AddOrigLeftUrl(const SFString& origlefturl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_OrigLeftUrl member (copies values).
	//
	// [in] origlefturl: The m_OrigLeftUrl array.
	//
	void SetOrigLeftUrl(const MFString& origlefturl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_OrigRightUrl array (grow if needed).
	//
	// [in] origrighturl: The value to add to the m_OrigRightUrl array.
	//
	void AddOrigRightUrl(const SFString& origrighturl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_OrigRightUrl member (copies values).
	//
	// [in] origrighturl: The m_OrigRightUrl array.
	//
	void SetOrigRightUrl(const MFString& origrighturl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_OrigTopUrl array (grow if needed).
	//
	// [in] origtopurl: The value to add to the m_OrigTopUrl array.
	//
	void AddOrigTopUrl(const SFString& origtopurl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_OrigTopUrl member (copies values).
	//
	// [in] origtopurl: The m_OrigTopUrl array.
	//
	void SetOrigTopUrl(const MFString& origtopurl);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_BackgroundGroup member.
	//
	// [in] backgroundgroup: The backgroundgroup value.
	//
	void SetBackgroundGroup(const vrGroup* backgroundgroup);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_OrigBackUrl member.
	//
	SFInt32 GetNOrigBackUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_OrigBackUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetOrigBackUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_OrigBackUrl member.
	//
	const MFString& GetOrigBackUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_OrigBottomUrl member.
	//
	SFInt32 GetNOrigBottomUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_OrigBottomUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetOrigBottomUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_OrigBottomUrl member.
	//
	const MFString& GetOrigBottomUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_OrigFrontUrl member.
	//
	SFInt32 GetNOrigFrontUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_OrigFrontUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetOrigFrontUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_OrigFrontUrl member.
	//
	const MFString& GetOrigFrontUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_OrigLeftUrl member.
	//
	SFInt32 GetNOrigLeftUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_OrigLeftUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetOrigLeftUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_OrigLeftUrl member.
	//
	const MFString& GetOrigLeftUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_OrigRightUrl member.
	//
	SFInt32 GetNOrigRightUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_OrigRightUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetOrigRightUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_OrigRightUrl member.
	//
	const MFString& GetOrigRightUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_OrigTopUrl member.
	//
	SFInt32 GetNOrigTopUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_OrigTopUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetOrigTopUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_OrigTopUrl member.
	//
	const MFString& GetOrigTopUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_BackgroundGroup member.
	//
	vrGroup* GetBackgroundGroup(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_GroundAngle array (grow if needed).
	//
	// [in] groundangle: The value to add to the m_GroundAngle array.
	//
	void AddGroundAngle(SFFloat groundangle);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_GroundAngle member (copies values).
	//
	// [in] groundangle: The m_GroundAngle array.
	//
	void SetGroundAngle(const MFFloat& groundangle);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_GroundColor array (grow if needed).
	//
	// [in] groundcolor: The value to add to the m_GroundColor array.
	//
	void AddGroundColor(const SFColor& groundcolor);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_GroundColor member (copies values).
	//
	// [in] groundcolor: The m_GroundColor array.
	//
	void SetGroundColor(const MFColor& groundcolor);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_BackUrl array (grow if needed).
	//
	// [in] backurl: The value to add to the m_BackUrl array.
	//
	void AddBackUrl(const SFString& backurl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_BackUrl member (copies values).
	//
	// [in] backurl: The m_BackUrl array.
	//
	void SetBackUrl(const MFString& backurl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_BottomUrl array (grow if needed).
	//
	// [in] bottomurl: The value to add to the m_BottomUrl array.
	//
	void AddBottomUrl(const SFString& bottomurl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_BottomUrl member (copies values).
	//
	// [in] bottomurl: The m_BottomUrl array.
	//
	void SetBottomUrl(const MFString& bottomurl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_FrontUrl array (grow if needed).
	//
	// [in] fronturl: The value to add to the m_FrontUrl array.
	//
	void AddFrontUrl(const SFString& fronturl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_FrontUrl member (copies values).
	//
	// [in] fronturl: The m_FrontUrl array.
	//
	void SetFrontUrl(const MFString& fronturl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_LeftUrl array (grow if needed).
	//
	// [in] lefturl: The value to add to the m_LeftUrl array.
	//
	void AddLeftUrl(const SFString& lefturl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_LeftUrl member (copies values).
	//
	// [in] lefturl: The m_LeftUrl array.
	//
	void SetLeftUrl(const MFString& lefturl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_RightUrl array (grow if needed).
	//
	// [in] righturl: The value to add to the m_RightUrl array.
	//
	void AddRightUrl(const SFString& righturl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_RightUrl member (copies values).
	//
	// [in] righturl: The m_RightUrl array.
	//
	void SetRightUrl(const MFString& righturl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_TopUrl array (grow if needed).
	//
	// [in] topurl: The value to add to the m_TopUrl array.
	//
	void AddTopUrl(const SFString& topurl);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_TopUrl member (copies values).
	//
	// [in] topurl: The m_TopUrl array.
	//
	void SetTopUrl(const MFString& topurl);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_SkyAngle array (grow if needed).
	//
	// [in] skyangle: The value to add to the m_SkyAngle array.
	//
	void AddSkyAngle(SFFloat skyangle);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_SkyAngle member (copies values).
	//
	// [in] skyangle: The m_SkyAngle array.
	//
	void SetSkyAngle(const MFFloat& skyangle);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_SkyColor array (grow if needed).
	//
	// [in] skycolor: The value to add to the m_SkyColor array.
	//
	void AddSkyColor(const SFColor& skycolor);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_SkyColor member (copies values).
	//
	// [in] skycolor: The m_SkyColor array.
	//
	void SetSkyColor(const MFColor& skycolor);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_GroundAngle member.
	//
	SFInt32 GetNGroundAngles(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_GroundAngle member.
	//
	// [in] n: The index into the array.
	//
	SFFloat GetGroundAngle(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_GroundAngle member.
	//
	const MFFloat& GetGroundAngleArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_GroundColor member.
	//
	SFInt32 GetNGroundColors(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_GroundColor member.
	//
	// [in] n: The index into the array.
	//
	SFColor GetGroundColor(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_GroundColor member.
	//
	const MFColor& GetGroundColorArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_BackUrl member.
	//
	SFInt32 GetNBackUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_BackUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetBackUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_BackUrl member.
	//
	const MFString& GetBackUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_BottomUrl member.
	//
	SFInt32 GetNBottomUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_BottomUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetBottomUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_BottomUrl member.
	//
	const MFString& GetBottomUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_FrontUrl member.
	//
	SFInt32 GetNFrontUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_FrontUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetFrontUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_FrontUrl member.
	//
	const MFString& GetFrontUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_LeftUrl member.
	//
	SFInt32 GetNLeftUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_LeftUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetLeftUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_LeftUrl member.
	//
	const MFString& GetLeftUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_RightUrl member.
	//
	SFInt32 GetNRightUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_RightUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetRightUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_RightUrl member.
	//
	const MFString& GetRightUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_TopUrl member.
	//
	SFInt32 GetNTopUrls(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_TopUrl member.
	//
	// [in] n: The index into the array.
	//
	SFString GetTopUrl(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_TopUrl member.
	//
	const MFString& GetTopUrlArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_SkyAngle member.
	//
	SFInt32 GetNSkyAngles(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_SkyAngle member.
	//
	// [in] n: The index into the array.
	//
	SFFloat GetSkyAngle(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_SkyAngle member.
	//
	const MFFloat& GetSkyAngleArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_SkyColor member.
	//
	SFInt32 GetNSkyColors(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_SkyColor member.
	//
	// [in] n: The index into the array.
	//
	SFColor GetSkyColor(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_SkyColor member.
	//
	const MFColor& GetSkyColorArray(void) const;


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
	DECLARE_NODE(vrBackground);

	//------------------------------------------------------------
	// hand coded functions
	void BuildMesh();
	SFBool MakePanorama(const SFVec3f& trans, const SFRotation& rot, const MFString& url);
	SFBool IsClearOnly(void) const;
	void CompleteNode(vrNode *top);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrBackground::AddOrigBackUrl(const SFString& origbackurl)
{
	m_OrigBackUrl.AddValue(origbackurl);
}

inline void vrBackground::SetOrigBackUrl(const MFString& origbackurl)
{
	m_OrigBackUrl.Clear();
	m_OrigBackUrl = origbackurl;
}

inline void vrBackground::AddOrigBottomUrl(const SFString& origbottomurl)
{
	m_OrigBottomUrl.AddValue(origbottomurl);
}

inline void vrBackground::SetOrigBottomUrl(const MFString& origbottomurl)
{
	m_OrigBottomUrl.Clear();
	m_OrigBottomUrl = origbottomurl;
}

inline void vrBackground::AddOrigFrontUrl(const SFString& origfronturl)
{
	m_OrigFrontUrl.AddValue(origfronturl);
}

inline void vrBackground::SetOrigFrontUrl(const MFString& origfronturl)
{
	m_OrigFrontUrl.Clear();
	m_OrigFrontUrl = origfronturl;
}

inline void vrBackground::AddOrigLeftUrl(const SFString& origlefturl)
{
	m_OrigLeftUrl.AddValue(origlefturl);
}

inline void vrBackground::SetOrigLeftUrl(const MFString& origlefturl)
{
	m_OrigLeftUrl.Clear();
	m_OrigLeftUrl = origlefturl;
}

inline void vrBackground::AddOrigRightUrl(const SFString& origrighturl)
{
	m_OrigRightUrl.AddValue(origrighturl);
}

inline void vrBackground::SetOrigRightUrl(const MFString& origrighturl)
{
	m_OrigRightUrl.Clear();
	m_OrigRightUrl = origrighturl;
}

inline void vrBackground::AddOrigTopUrl(const SFString& origtopurl)
{
	m_OrigTopUrl.AddValue(origtopurl);
}

inline void vrBackground::SetOrigTopUrl(const MFString& origtopurl)
{
	m_OrigTopUrl.Clear();
	m_OrigTopUrl = origtopurl;
}

inline SFInt32 vrBackground::GetNOrigBackUrls(void) const
{
	return m_OrigBackUrl.GetCount();
}

inline SFString vrBackground::GetOrigBackUrl(SFInt32 n) const
{
	return m_OrigBackUrl[n];
}

inline const MFString& vrBackground::GetOrigBackUrlArray(void) const
{
	return m_OrigBackUrl;
}

inline SFInt32 vrBackground::GetNOrigBottomUrls(void) const
{
	return m_OrigBottomUrl.GetCount();
}

inline SFString vrBackground::GetOrigBottomUrl(SFInt32 n) const
{
	return m_OrigBottomUrl[n];
}

inline const MFString& vrBackground::GetOrigBottomUrlArray(void) const
{
	return m_OrigBottomUrl;
}

inline SFInt32 vrBackground::GetNOrigFrontUrls(void) const
{
	return m_OrigFrontUrl.GetCount();
}

inline SFString vrBackground::GetOrigFrontUrl(SFInt32 n) const
{
	return m_OrigFrontUrl[n];
}

inline const MFString& vrBackground::GetOrigFrontUrlArray(void) const
{
	return m_OrigFrontUrl;
}

inline SFInt32 vrBackground::GetNOrigLeftUrls(void) const
{
	return m_OrigLeftUrl.GetCount();
}

inline SFString vrBackground::GetOrigLeftUrl(SFInt32 n) const
{
	return m_OrigLeftUrl[n];
}

inline const MFString& vrBackground::GetOrigLeftUrlArray(void) const
{
	return m_OrigLeftUrl;
}

inline SFInt32 vrBackground::GetNOrigRightUrls(void) const
{
	return m_OrigRightUrl.GetCount();
}

inline SFString vrBackground::GetOrigRightUrl(SFInt32 n) const
{
	return m_OrigRightUrl[n];
}

inline const MFString& vrBackground::GetOrigRightUrlArray(void) const
{
	return m_OrigRightUrl;
}

inline SFInt32 vrBackground::GetNOrigTopUrls(void) const
{
	return m_OrigTopUrl.GetCount();
}

inline SFString vrBackground::GetOrigTopUrl(SFInt32 n) const
{
	return m_OrigTopUrl[n];
}

inline const MFString& vrBackground::GetOrigTopUrlArray(void) const
{
	return m_OrigTopUrl;
}

inline vrGroup* vrBackground::GetBackgroundGroup(void) const
{
	return m_BackgroundGroup;
}

// exposedField sets and gets inlines
inline void vrBackground::AddGroundAngle(SFFloat groundangle)
{
	m_GroundAngle.AddValue(groundangle);
}

inline void vrBackground::SetGroundAngle(const MFFloat& groundangle)
{
	m_GroundAngle.Clear();
	m_GroundAngle = groundangle;
}

inline void vrBackground::AddGroundColor(const SFColor& groundcolor)
{
	m_GroundColor.AddValue(groundcolor);
}

inline void vrBackground::SetGroundColor(const MFColor& groundcolor)
{
	m_GroundColor.Clear();
	m_GroundColor = groundcolor;
}

inline void vrBackground::AddBackUrl(const SFString& backurl)
{
	m_BackUrl.AddValue(backurl);
}

inline void vrBackground::SetBackUrl(const MFString& backurl)
{
	m_BackUrl.Clear();
	m_BackUrl = backurl;
}

inline void vrBackground::AddBottomUrl(const SFString& bottomurl)
{
	m_BottomUrl.AddValue(bottomurl);
}

inline void vrBackground::SetBottomUrl(const MFString& bottomurl)
{
	m_BottomUrl.Clear();
	m_BottomUrl = bottomurl;
}

inline void vrBackground::AddFrontUrl(const SFString& fronturl)
{
	m_FrontUrl.AddValue(fronturl);
}

inline void vrBackground::SetFrontUrl(const MFString& fronturl)
{
	m_FrontUrl.Clear();
	m_FrontUrl = fronturl;
}

inline void vrBackground::AddLeftUrl(const SFString& lefturl)
{
	m_LeftUrl.AddValue(lefturl);
}

inline void vrBackground::SetLeftUrl(const MFString& lefturl)
{
	m_LeftUrl.Clear();
	m_LeftUrl = lefturl;
}

inline void vrBackground::AddRightUrl(const SFString& righturl)
{
	m_RightUrl.AddValue(righturl);
}

inline void vrBackground::SetRightUrl(const MFString& righturl)
{
	m_RightUrl.Clear();
	m_RightUrl = righturl;
}

inline void vrBackground::AddTopUrl(const SFString& topurl)
{
	m_TopUrl.AddValue(topurl);
}

inline void vrBackground::SetTopUrl(const MFString& topurl)
{
	m_TopUrl.Clear();
	m_TopUrl = topurl;
}

inline void vrBackground::AddSkyAngle(SFFloat skyangle)
{
	m_SkyAngle.AddValue(skyangle);
}

inline void vrBackground::SetSkyAngle(const MFFloat& skyangle)
{
	m_SkyAngle.Clear();
	m_SkyAngle = skyangle;
}

inline void vrBackground::AddSkyColor(const SFColor& skycolor)
{
	m_SkyColor.AddValue(skycolor);
}

inline void vrBackground::SetSkyColor(const MFColor& skycolor)
{
	m_SkyColor.Clear();
	m_SkyColor = skycolor;
}

inline SFInt32 vrBackground::GetNGroundAngles(void) const
{
	return m_GroundAngle.GetCount();
}

inline SFFloat vrBackground::GetGroundAngle(SFInt32 n) const
{
	return m_GroundAngle[n];
}

inline const MFFloat& vrBackground::GetGroundAngleArray(void) const
{
	return m_GroundAngle;
}

inline SFInt32 vrBackground::GetNGroundColors(void) const
{
	return m_GroundColor.GetCount();
}

inline SFColor vrBackground::GetGroundColor(SFInt32 n) const
{
	return m_GroundColor[n];
}

inline const MFColor& vrBackground::GetGroundColorArray(void) const
{
	return m_GroundColor;
}

inline SFInt32 vrBackground::GetNBackUrls(void) const
{
	return m_BackUrl.GetCount();
}

inline SFString vrBackground::GetBackUrl(SFInt32 n) const
{
	return m_BackUrl[n];
}

inline const MFString& vrBackground::GetBackUrlArray(void) const
{
	return m_BackUrl;
}

inline SFInt32 vrBackground::GetNBottomUrls(void) const
{
	return m_BottomUrl.GetCount();
}

inline SFString vrBackground::GetBottomUrl(SFInt32 n) const
{
	return m_BottomUrl[n];
}

inline const MFString& vrBackground::GetBottomUrlArray(void) const
{
	return m_BottomUrl;
}

inline SFInt32 vrBackground::GetNFrontUrls(void) const
{
	return m_FrontUrl.GetCount();
}

inline SFString vrBackground::GetFrontUrl(SFInt32 n) const
{
	return m_FrontUrl[n];
}

inline const MFString& vrBackground::GetFrontUrlArray(void) const
{
	return m_FrontUrl;
}

inline SFInt32 vrBackground::GetNLeftUrls(void) const
{
	return m_LeftUrl.GetCount();
}

inline SFString vrBackground::GetLeftUrl(SFInt32 n) const
{
	return m_LeftUrl[n];
}

inline const MFString& vrBackground::GetLeftUrlArray(void) const
{
	return m_LeftUrl;
}

inline SFInt32 vrBackground::GetNRightUrls(void) const
{
	return m_RightUrl.GetCount();
}

inline SFString vrBackground::GetRightUrl(SFInt32 n) const
{
	return m_RightUrl[n];
}

inline const MFString& vrBackground::GetRightUrlArray(void) const
{
	return m_RightUrl;
}

inline SFInt32 vrBackground::GetNTopUrls(void) const
{
	return m_TopUrl.GetCount();
}

inline SFString vrBackground::GetTopUrl(SFInt32 n) const
{
	return m_TopUrl[n];
}

inline const MFString& vrBackground::GetTopUrlArray(void) const
{
	return m_TopUrl;
}

inline SFInt32 vrBackground::GetNSkyAngles(void) const
{
	return m_SkyAngle.GetCount();
}

inline SFFloat vrBackground::GetSkyAngle(SFInt32 n) const
{
	return m_SkyAngle[n];
}

inline const MFFloat& vrBackground::GetSkyAngleArray(void) const
{
	return m_SkyAngle;
}

inline SFInt32 vrBackground::GetNSkyColors(void) const
{
	return m_SkyColor.GetCount();
}

inline SFColor vrBackground::GetSkyColor(SFInt32 n) const
{
	return m_SkyColor[n];
}

inline const MFColor& vrBackground::GetSkyColorArray(void) const
{
	return m_SkyColor;
}

inline void vrBackground::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

