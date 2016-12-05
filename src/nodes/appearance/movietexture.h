#ifndef __MOVIETEXTURE_H3D
#define __MOVIETEXTURE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "PixelTexture.h"

/*----------------------------------------------------------------------
CLASS
	vrMovieTexture

	This class corresponds to the MovieTexture node in VRML.  
	<A href="../spec/part1/nodesRef.html#MovieTexture">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the MovieTexture node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#MovieTexture">link</a>.</ul>

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
class LIBInterface vrMovieTexture : public vrPixelTexture
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field origUrl.
	//
	// [default] []
	//
	MFString            	m_OrigUrl;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'loop' exposedField.
	//
	// [default] FALSE
	//
	SFBool              	m_Loop;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'speed' exposedField.
	//
	// [default] 1.0
	//
	SFFloat             	m_Speed;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'startTime' exposedField.
	//
	// [default] 0.0
	//
	SFTime              	m_StartTime;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'stopTime' exposedField.
	//
	// [default] 0.0
	//
	SFTime              	m_StopTime;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'url' exposedField.
	//
	// [default] []
	//
	MFString            	m_Url;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'duration' eventOut.
	//
	// [default] 0.0
	//
	SFFloat             	m_Duration;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'isActive' eventOut.
	//
	// [default] FALSE
	//
	SFBool              	m_IsActive;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrMovieTexture(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrMovieTexture(const vrMovieTexture& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrMovieTexture(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrMovieTexture& operator=(const vrMovieTexture& v);

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
	// <dd>Set the value of the m_Loop member.
	//
	// [in] loop: The loop value.
	//
	void SetLoop(SFBool loop);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Speed member.
	//
	// [in] speed: The speed value.
	//
	void SetSpeed(SFFloat speed);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_StartTime member.
	//
	// [in] starttime: The starttime value.
	//
	void SetStartTime(SFTime starttime);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_StopTime member.
	//
	// [in] stoptime: The stoptime value.
	//
	void SetStopTime(SFTime stoptime);

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
	// <dd>Return the value of the m_Loop member.
	//
	SFBool GetLoop(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Speed member.
	//
	SFFloat GetSpeed(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_StartTime member.
	//
	SFTime GetStartTime(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_StopTime member.
	//
	SFTime GetStopTime(void) const;

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


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Duration member.
	//
	// [in] duration: The duration value.
	//
	void SetDuration(SFFloat duration);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_IsActive member.
	//
	// [in] isactive: The isactive value.
	//
	void SetIsActive(SFBool isactive);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Duration member.
	//
	SFFloat GetDuration(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_IsActive member.
	//
	SFBool IsActive(void) const;


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
	DECLARE_NODE(vrMovieTexture);

	//------------------------------------------------------------
	// hand coded functions
	 // this is a comment
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrMovieTexture::AddOrigUrl(const SFString& origurl)
{
	m_OrigUrl.AddValue(origurl);
}

inline void vrMovieTexture::SetOrigUrl(const MFString& origurl)
{
	m_OrigUrl.Clear();
	m_OrigUrl = origurl;
}

inline SFInt32 vrMovieTexture::GetNOrigUrls(void) const
{
	return m_OrigUrl.GetCount();
}

inline SFString vrMovieTexture::GetOrigUrl(SFInt32 n) const
{
	return m_OrigUrl[n];
}

inline const MFString& vrMovieTexture::GetOrigUrlArray(void) const
{
	return m_OrigUrl;
}

// exposedField sets and gets inlines
inline void vrMovieTexture::SetLoop(SFBool loop)
{
	m_Loop = loop;
}

inline void vrMovieTexture::SetSpeed(SFFloat speed)
{
	m_Speed = speed;
}

inline void vrMovieTexture::SetStartTime(SFTime starttime)
{
	m_StartTime = starttime;
}

inline void vrMovieTexture::SetStopTime(SFTime stoptime)
{
	m_StopTime = stoptime;
}

inline void vrMovieTexture::AddUrl(const SFString& url)
{
	m_Url.AddValue(url);
}

inline void vrMovieTexture::SetUrl(const MFString& url)
{
	m_Url.Clear();
	m_Url = url;
}

inline SFBool vrMovieTexture::GetLoop(void) const
{
	return m_Loop;
}

inline SFFloat vrMovieTexture::GetSpeed(void) const
{
	return m_Speed;
}

inline SFTime vrMovieTexture::GetStartTime(void) const
{
	return m_StartTime;
}

inline SFTime vrMovieTexture::GetStopTime(void) const
{
	return m_StopTime;
}

inline SFInt32 vrMovieTexture::GetNUrls(void) const
{
	return m_Url.GetCount();
}

inline SFString vrMovieTexture::GetUrl(SFInt32 n) const
{
	return m_Url[n];
}

inline const MFString& vrMovieTexture::GetUrlArray(void) const
{
	return m_Url;
}

// eventOut sets and gets inlines
inline void vrMovieTexture::SetDuration(SFFloat duration)
{
	m_Duration = duration;
}

inline void vrMovieTexture::SetIsActive(SFBool isactive)
{
	m_IsActive = isactive;
}

inline SFFloat vrMovieTexture::GetDuration(void) const
{
	return m_Duration;
}

inline SFBool vrMovieTexture::IsActive(void) const
{
	return m_IsActive;
}

inline void vrMovieTexture::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

