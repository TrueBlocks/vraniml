#ifndef __SWITCH_H3D
#define __SWITCH_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrSwitch

	This class corresponds to the Switch node in VRML.  
	<A href="../spec/part1/nodesRef.html#Switch">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Switch node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Switch">link</a>.</ul>

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
class LIBInterface vrSwitch : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'choice' exposedField.
	//
	// [default] []
	//
	MFNode              	m_Choice;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'whichChoice' exposedField.
	//
	// [default] -1
	//
	SFInt32             	m_WhichChoice;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrSwitch(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrSwitch(const vrSwitch& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrSwitch(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrSwitch& operator=(const vrSwitch& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Choice array (grow if needed).
	//
	// [in] choice: The value to add to the m_Choice array.
	//
	void AddChoice(const SFNode& choice);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Choice member (copies values).
	//
	// [in] choice: The m_Choice array.
	//
	void SetChoice(const MFNode& choice);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_WhichChoice member.
	//
	// [in] whichchoice: The whichchoice value.
	//
	void SetWhichChoice(SFInt32 whichchoice);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Choice member.
	//
	SFInt32 GetNChoices(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Choice member.
	//
	// [in] n: The index into the array.
	//
	SFNode GetChoice(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Choice member.
	//
	const MFNode& GetChoiceArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_WhichChoice member.
	//
	SFInt32 GetWhichChoice(void) const;


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
	DECLARE_NODE(vrSwitch);


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
// exposedField sets and gets inlines
inline void vrSwitch::AddChild(SFNode node)
{
	AddChoice(node);
}

inline void vrSwitch::AddChoice(const SFNode& choice)
{
	m_Choice.AddValue(choice);
	SFNode& c = (SFNode&)choice;
	c->Reference();
}

inline void vrSwitch::SetChoice(const MFNode& choice)
{
	m_Choice.Clear();
	m_Choice = choice;
}

inline void vrSwitch::SetWhichChoice(SFInt32 whichchoice)
{
	m_WhichChoice = whichchoice;
}

inline SFInt32 vrSwitch::GetNChoices(void) const
{
	return m_Choice.GetCount();
}

inline SFNode vrSwitch::GetChoice(SFInt32 n) const
{
	return m_Choice[n];
}

inline const MFNode& vrSwitch::GetChoiceArray(void) const
{
	return m_Choice;
}

inline SFInt32 vrSwitch::GetWhichChoice(void) const
{
	return m_WhichChoice;
}

inline void vrSwitch::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}

#endif

