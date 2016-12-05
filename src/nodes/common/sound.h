#ifndef __SOUND_H3D
#define __SOUND_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrSound

	This class corresponds to the Sound node in VRML.  
	<A href="../spec/part1/nodesRef.html#Sound">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Sound node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Sound">link</a>.</ul>

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
class LIBInterface vrSound : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'spatialize' field.
	//
	// [default] TRUE
	//
	SFBool              	m_Spatialize;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'direction' exposedField.
	//
	// [default] zAxis
	//
	SFVec3f             	m_Direction;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'intensity' exposedField.
	//
	// [default] 1.0
	//
	SFFloat             	m_Intensity;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'location' exposedField.
	//
	// [default] origin
	//
	SFVec3f             	m_Location;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'maxBack' exposedField.
	//
	// [default] 10.0
	//
	SFFloat             	m_MaxBack;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'maxFront' exposedField.
	//
	// [default] 10.0
	//
	SFFloat             	m_MaxFront;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'minBack' exposedField.
	//
	// [default] 1.0
	//
	SFFloat             	m_MinBack;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'minFront' exposedField.
	//
	// [default] 1.0
	//
	SFFloat             	m_MinFront;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'priority' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_Priority;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'source' exposedField.
	//
	// [default] NULL
	//
	vrAudioClip*        	m_Source;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrSound(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrSound(const vrSound& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrSound(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrSound& operator=(const vrSound& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Spatialize member.
	//
	// [in] spatialize: The spatialize value.
	//
	void SetSpatialize(SFBool spatialize);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Spatialize member.
	//
	SFBool GetSpatialize(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Direction member.
	//
	// [in] direction: The direction value.
	//
	void SetDirection(const SFVec3f& direction);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Intensity member.
	//
	// [in] intensity: The intensity value.
	//
	void SetIntensity(SFFloat intensity);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Location member.
	//
	// [in] location: The location value.
	//
	void SetLocation(const SFVec3f& location);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MaxBack member.
	//
	// [in] maxback: The maxback value.
	//
	void SetMaxBack(SFFloat maxback);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MaxFront member.
	//
	// [in] maxfront: The maxfront value.
	//
	void SetMaxFront(SFFloat maxfront);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MinBack member.
	//
	// [in] minback: The minback value.
	//
	void SetMinBack(SFFloat minback);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MinFront member.
	//
	// [in] minfront: The minfront value.
	//
	void SetMinFront(SFFloat minfront);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Priority member.
	//
	// [in] priority: The priority value.
	//
	void SetPriority(SFFloat priority);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Source member.
	//
	// [in] source: The source value.
	//
	void SetSource(const vrAudioClip* source);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Direction member.
	//
	SFVec3f GetDirection(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Intensity member.
	//
	SFFloat GetIntensity(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Location member.
	//
	SFVec3f GetLocation(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MaxBack member.
	//
	SFFloat GetMaxBack(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MaxFront member.
	//
	SFFloat GetMaxFront(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MinBack member.
	//
	SFFloat GetMinBack(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MinFront member.
	//
	SFFloat GetMinFront(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Priority member.
	//
	SFFloat GetPriority(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Source member.
	//
	vrAudioClip* GetSource(void) const;


	//<nodoc>------------------------------------------------------------
	// <dd>Set the value of a field given the field's name and a value.
	// <dd>Note: Error checking is done on 'fieldName' but cannot be done on 'val',
	// <dd>      so make sure you send the correct type of data to this method.
	//
	// [in] fieldName: The name of the field to set (as specified in the VRML97 specification).
	// [in] val: Void pointer to a field of the type corresponding to fieldName.
	//
	virtual SFBool SetFieldValue(const SFString& fieldName, void *val);

	//<nodoc>------------------------------------------------------------
	// <dd>Add the given node to this node.  Runtime typing is used to
	//     determine which node to add.
	//
	// [in] node: The node to add.
	//
	virtual void AddChild(SFNode node);

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
	// <dd>Find a node by class type.  Returns NULL if not found. (Overridden to search vrNode derived data members).
	//
	// [in] pClass: Pointer to a vrRuntimeClass representing the searched for type.
	//
	virtual SFNode FindByType(vrRuntimeClass *pClass) const;

	//<doc>------------------------------------------------------------
	// <dd>Find a node by name.  Returns NULL if not found.  (Overridden to search vrNode derived data members)
	//
	// [in] nodeName: The name of the node being searched for.
	//
	virtual SFNode FindByName(const SFString& nodeName) const;

	//<doc>------------------------------------------------------------
	// <dd>Apply 'userFn' to all contained nodes (including any children and/or direct references).  [ <a href="../forevery.htm">Additional information.</a> ]
	//
	// [in] userFn: Pointer to a function returning SFBool and taking an SFNode and void pointer as arguments.  'userFn' is applied to this node and all children (if any).
	// [in] userData: Pointer to arbitrary user data.
	// [in] afterFn: Pointer to a function to apply after applying 'userFn' to all children (for example: popping a stack).
	//
	virtual SFBool ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn=NULL);

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
	DECLARE_NODE(vrSound);

};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrSound::SetSpatialize(SFBool spatialize)
{
	m_Spatialize = spatialize;
}

inline SFBool vrSound::GetSpatialize(void) const
{
	return m_Spatialize;
}

// exposedField sets and gets inlines
inline void vrSound::SetDirection(const SFVec3f& direction)
{
	m_Direction = direction;
}

inline void vrSound::SetIntensity(SFFloat intensity)
{
	m_Intensity = intensity;
}

inline void vrSound::SetLocation(const SFVec3f& location)
{
	m_Location = location;
}

inline void vrSound::SetMaxBack(SFFloat maxback)
{
	m_MaxBack = maxback;
}

inline void vrSound::SetMaxFront(SFFloat maxfront)
{
	m_MaxFront = maxfront;
}

inline void vrSound::SetMinBack(SFFloat minback)
{
	m_MinBack = minback;
}

inline void vrSound::SetMinFront(SFFloat minfront)
{
	m_MinFront = minfront;
}

inline void vrSound::SetPriority(SFFloat priority)
{
	m_Priority = priority;
}

inline SFVec3f vrSound::GetDirection(void) const
{
	return m_Direction;
}

inline SFFloat vrSound::GetIntensity(void) const
{
	return m_Intensity;
}

inline SFVec3f vrSound::GetLocation(void) const
{
	return m_Location;
}

inline SFFloat vrSound::GetMaxBack(void) const
{
	return m_MaxBack;
}

inline SFFloat vrSound::GetMaxFront(void) const
{
	return m_MaxFront;
}

inline SFFloat vrSound::GetMinBack(void) const
{
	return m_MinBack;
}

inline SFFloat vrSound::GetMinFront(void) const
{
	return m_MinFront;
}

inline SFFloat vrSound::GetPriority(void) const
{
	return m_Priority;
}

inline vrAudioClip* vrSound::GetSource(void) const
{
	return m_Source;
}

inline void vrSound::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

