#ifndef __AUDIOCLIP_H3D
#define __AUDIOCLIP_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrAudioClip

	This class corresponds to the AudioClip node in VRML.  
	<A href="../spec/part1/nodesRef.html#AudioClip">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the AudioClip node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#AudioClip">link</a>.</ul>

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
class LIBInterface vrAudioClip : public vrNode
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
	//<dd>Corresponds to the 'loop' exposedField.
	//
	// [default] FALSE
	//
	SFBool              	m_Loop;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'pitch' exposedField.
	//
	// [default] 1.0
	//
	SFFloat             	m_Pitch;

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
	SFTime              	m_Duration;

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
	vrAudioClip(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrAudioClip(const vrAudioClip& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrAudioClip(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrAudioClip& operator=(const vrAudioClip& v);

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
	// <dd>Set the value of the m_Loop member.
	//
	// [in] loop: The loop value.
	//
	void SetLoop(SFBool loop);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Pitch member.
	//
	// [in] pitch: The pitch value.
	//
	void SetPitch(SFFloat pitch);

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
	// <dd>Return the value of the m_Description member.
	//
	SFString GetDescription(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Loop member.
	//
	SFBool GetLoop(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Pitch member.
	//
	SFFloat GetPitch(void) const;

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
	void SetDuration(SFTime duration);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_IsActive member.
	//
	// [in] isactive: The isactive value.
	//
	void SetIsActive(SFBool isactive);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Duration member.
	//
	SFTime GetDuration(void) const;

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
	DECLARE_NODE(vrAudioClip);

	//------------------------------------------------------------
	// hand coded functions
//#ifdef SOUND1
	//IDirectSoundBuffer   *m_Buffer;
	//IDirectSound3DBuffer *m_Buffer3D;
#define IDirectSound void
	  void LoadData(IDirectSound *lpDS);
	  void ClearData(void);
//#endif
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrAudioClip::AddOrigUrl(const SFString& origurl)
{
	m_OrigUrl.AddValue(origurl);
}

inline void vrAudioClip::SetOrigUrl(const MFString& origurl)
{
	m_OrigUrl.Clear();
	m_OrigUrl = origurl;
}

inline SFInt32 vrAudioClip::GetNOrigUrls(void) const
{
	return m_OrigUrl.GetCount();
}

inline SFString vrAudioClip::GetOrigUrl(SFInt32 n) const
{
	return m_OrigUrl[n];
}

inline const MFString& vrAudioClip::GetOrigUrlArray(void) const
{
	return m_OrigUrl;
}

// exposedField sets and gets inlines
inline void vrAudioClip::SetLoop(SFBool loop)
{
	m_Loop = loop;
}

inline void vrAudioClip::SetPitch(SFFloat pitch)
{
	m_Pitch = pitch;
}

inline void vrAudioClip::SetStartTime(SFTime starttime)
{
	m_StartTime = starttime;
}

inline void vrAudioClip::SetStopTime(SFTime stoptime)
{
	m_StopTime = stoptime;
}

inline void vrAudioClip::AddUrl(const SFString& url)
{
	m_Url.AddValue(url);
}

inline void vrAudioClip::SetUrl(const MFString& url)
{
	m_Url.Clear();
	m_Url = url;
}

inline SFString vrAudioClip::GetDescription(void) const
{
	return m_Description;
}

inline SFBool vrAudioClip::GetLoop(void) const
{
	return m_Loop;
}

inline SFFloat vrAudioClip::GetPitch(void) const
{
	return m_Pitch;
}

inline SFTime vrAudioClip::GetStartTime(void) const
{
	return m_StartTime;
}

inline SFTime vrAudioClip::GetStopTime(void) const
{
	return m_StopTime;
}

inline SFInt32 vrAudioClip::GetNUrls(void) const
{
	return m_Url.GetCount();
}

inline SFString vrAudioClip::GetUrl(SFInt32 n) const
{
	return m_Url[n];
}

inline const MFString& vrAudioClip::GetUrlArray(void) const
{
	return m_Url;
}

// eventOut sets and gets inlines
inline void vrAudioClip::SetDuration(SFTime duration)
{
	m_Duration = duration;
}

inline void vrAudioClip::SetIsActive(SFBool isactive)
{
	m_IsActive = isactive;
}

inline SFTime vrAudioClip::GetDuration(void) const
{
	return m_Duration;
}

inline SFBool vrAudioClip::IsActive(void) const
{
	return m_IsActive;
}

inline void vrAudioClip::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

