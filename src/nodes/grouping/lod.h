#ifndef __LOD_H3D
#define __LOD_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrLOD

	This class corresponds to the LOD node in VRML.  
	<A href="../spec/part1/nodesRef.html#LOD">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the LOD node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#LOD">link</a>.</ul>

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
class LIBInterface vrLOD : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field activeLevel.
	//
	// [default] -1
	//
	SFInt32             	m_ActiveLevel;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'center' field.
	//
	// [default] origin
	//
	SFVec3f             	m_Center;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'range' field.
	//
	// [default] []
	//
	MFFloat             	m_Range;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'level' exposedField.
	//
	// [default] []
	//
	MFNode              	m_Level;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrLOD(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrLOD(const vrLOD& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrLOD(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrLOD& operator=(const vrLOD& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_ActiveLevel member.
	//
	// [in] activelevel: The activelevel value.
	//
	void SetActiveLevel(SFInt32 activelevel);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Center member.
	//
	// [in] center: The center value.
	//
	void SetCenter(const SFVec3f& center);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Range array (grow if needed).
	//
	// [in] range: The value to add to the m_Range array.
	//
	void AddRange(SFFloat range);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Range member (copies values).
	//
	// [in] range: The m_Range array.
	//
	void SetRange(const MFFloat& range);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_ActiveLevel member.
	//
	SFInt32 GetActiveLevel(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Center member.
	//
	SFVec3f GetCenter(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Range member.
	//
	SFInt32 GetNRanges(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Range member.
	//
	// [in] n: The index into the array.
	//
	SFFloat GetRange(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Range member.
	//
	const MFFloat& GetRangeArray(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Level array (grow if needed).
	//
	// [in] level: The value to add to the m_Level array.
	//
	void AddLevel(const SFNode& level);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Level member (copies values).
	//
	// [in] level: The m_Level array.
	//
	void SetLevel(const MFNode& level);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Level member.
	//
	SFInt32 GetNLevels(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Level member.
	//
	// [in] n: The index into the array.
	//
	SFNode GetLevel(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Level member.
	//
	const MFNode& GetLevelArray(void) const;


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
	DECLARE_NODE(vrLOD);


	//<nodoc>------------------------------------------------------------
	// <dd>Add a child to this vrGroupingNode derived class.
	//
	// [in] node: The node to add.
	//
	virtual void AddChild(SFNode node);

	//------------------------------------------------------------
	// hand coded functions
	SFNode      FindByType          (vrRuntimeClass *pClass) const;
	SFNode      FindByName          (const SFString& nodeName) const;
	SFBool      ForEvery            (PFBO3V userFn, void *userData, PFBO3V afterFn=NULL);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrLOD::SetActiveLevel(SFInt32 activelevel)
{
	m_ActiveLevel = activelevel;
}

inline void vrLOD::SetCenter(const SFVec3f& center)
{
	m_Center = center;
}

inline void vrLOD::AddRange(SFFloat range)
{
	m_Range.AddValue(range);
}

inline void vrLOD::SetRange(const MFFloat& range)
{
	m_Range.Clear();
	m_Range = range;
}

inline SFInt32 vrLOD::GetActiveLevel(void) const
{
	return m_ActiveLevel;
}

inline SFVec3f vrLOD::GetCenter(void) const
{
	return m_Center;
}

inline SFInt32 vrLOD::GetNRanges(void) const
{
	return m_Range.GetCount();
}

inline SFFloat vrLOD::GetRange(SFInt32 n) const
{
	return m_Range[n];
}

inline const MFFloat& vrLOD::GetRangeArray(void) const
{
	return m_Range;
}

// exposedField sets and gets inlines
inline void vrLOD::AddChild(SFNode node)
{
	AddLevel(node);
}

inline void vrLOD::AddLevel(const SFNode& level)
{
	m_Level.AddValue(level);
	SFNode& c = (SFNode&)level;
	c->Reference();
}

inline void vrLOD::SetLevel(const MFNode& level)
{
	m_Level.Clear();
	m_Level = level;
}

inline SFInt32 vrLOD::GetNLevels(void) const
{
	return m_Level.GetCount();
}

inline SFNode vrLOD::GetLevel(SFInt32 n) const
{
	return m_Level[n];
}

inline const MFNode& vrLOD::GetLevelArray(void) const
{
	return m_Level;
}

inline void vrLOD::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}

#endif

