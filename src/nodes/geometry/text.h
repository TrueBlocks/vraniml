#ifndef __TEXT_H3D
#define __TEXT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "GeometryNode.h"

/*----------------------------------------------------------------------
CLASS
	vrText

	This class corresponds to the Text node in VRML.  
	<A href="../spec/part1/nodesRef.html#Text">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Text node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Text">link</a>.</ul>

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
class LIBInterface vrText : public vrGeometryNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'string' exposedField.
	//
	// [default] []
	//
	MFString            	m_String;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'fontStyle' exposedField.
	//
	// [default] NULL
	//
	vrFontStyle*        	m_FontStyle;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'length' exposedField.
	//
	// [default] []
	//
	MFFloat             	m_Length;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'maxExtent' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_MaxExtent;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrText(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrText(const vrText& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrText(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrText& operator=(const vrText& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_String array (grow if needed).
	//
	// [in] string: The value to add to the m_String array.
	//
	void AddString(const SFString& string);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_String member (copies values).
	//
	// [in] string: The m_String array.
	//
	void SetString(const MFString& string);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_FontStyle member.
	//
	// [in] fontstyle: The fontstyle value.
	//
	void SetFontStyle(const vrFontStyle* fontstyle);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Length array (grow if needed).
	//
	// [in] length: The value to add to the m_Length array.
	//
	void AddLength(SFFloat length);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Length member (copies values).
	//
	// [in] length: The m_Length array.
	//
	void SetLength(const MFFloat& length);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_MaxExtent member.
	//
	// [in] maxextent: The maxextent value.
	//
	void SetMaxExtent(SFFloat maxextent);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_String member.
	//
	SFInt32 GetNStrings(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_String member.
	//
	// [in] n: The index into the array.
	//
	SFString GetString(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_String member.
	//
	const MFString& GetStringArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_FontStyle member.
	//
	vrFontStyle* GetFontStyle(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Length member.
	//
	SFInt32 GetNLengths(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Length member.
	//
	// [in] n: The index into the array.
	//
	SFFloat GetLength(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Length member.
	//
	const MFFloat& GetLengthArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_MaxExtent member.
	//
	SFFloat GetMaxExtent(void) const;


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
	DECLARE_NODE(vrText);

	//------------------------------------------------------------
	// hand coded functions
	virtual void BuildMesh(void);
	virtual void BuildColors(void);
	virtual void BuildNormals(void);
	virtual void BuildTexCoords(void);
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrText::AddString(const SFString& string)
{
	m_String.AddValue(string);
}

inline void vrText::SetString(const MFString& string)
{
	m_String.Clear();
	m_String = string;
}

inline void vrText::AddLength(SFFloat length)
{
	m_Length.AddValue(length);
}

inline void vrText::SetLength(const MFFloat& length)
{
	m_Length.Clear();
	m_Length = length;
}

inline void vrText::SetMaxExtent(SFFloat maxextent)
{
	m_MaxExtent = maxextent;
}

inline SFInt32 vrText::GetNStrings(void) const
{
	return m_String.GetCount();
}

inline SFString vrText::GetString(SFInt32 n) const
{
	return m_String[n];
}

inline const MFString& vrText::GetStringArray(void) const
{
	return m_String;
}

inline vrFontStyle* vrText::GetFontStyle(void) const
{
	return m_FontStyle;
}

inline SFInt32 vrText::GetNLengths(void) const
{
	return m_Length.GetCount();
}

inline SFFloat vrText::GetLength(SFInt32 n) const
{
	return m_Length[n];
}

inline const MFFloat& vrText::GetLengthArray(void) const
{
	return m_Length;
}

inline SFFloat vrText::GetMaxExtent(void) const
{
	return m_MaxExtent;
}

inline void vrText::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

