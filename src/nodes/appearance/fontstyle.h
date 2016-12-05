#ifndef __FONTSTYLE_H3D
#define __FONTSTYLE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrFontStyle

	This class corresponds to the FontStyle node in VRML.  
	<A href="../spec/part1/nodesRef.html#FontStyle">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the FontStyle node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#FontStyle">link</a>.</ul>

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
class LIBInterface vrFontStyle : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'family' field.
	//
	// [default] "SERIF"
	//
	SFString            	m_Family;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'horizontal' field.
	//
	// [default] TRUE
	//
	SFBool              	m_Horizontal;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'justify' field.
	//
	// [default] "BEGIN"
	//
	MFString            	m_Justify;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'language' field.
	//
	// [default] NULL
	//
	SFString            	m_Language;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'leftToRight' field.
	//
	// [default] TRUE
	//
	SFBool              	m_LeftToRight;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'size' field.
	//
	// [default] 1.0
	//
	SFFloat             	m_Size;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'spacing' field.
	//
	// [default] 1.0
	//
	SFFloat             	m_Spacing;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'style' field.
	//
	// [default] "PLAIN"
	//
	SFString            	m_Style;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'topToBottom' field.
	//
	// [default] TRUE
	//
	SFBool              	m_TopToBottom;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrFontStyle(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrFontStyle(const vrFontStyle& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrFontStyle(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrFontStyle& operator=(const vrFontStyle& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Family member.
	//
	// [in] family: The family value.
	//
	void SetFamily(const SFString& family);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Horizontal member.
	//
	// [in] horizontal: The horizontal value.
	//
	void SetHorizontal(SFBool horizontal);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Justify array (grow if needed).
	//
	// [in] justify: The value to add to the m_Justify array.
	//
	void AddJustify(const SFString& justify);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Justify member (copies values).
	//
	// [in] justify: The m_Justify array.
	//
	void SetJustify(const MFString& justify);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Language member.
	//
	// [in] language: The language value.
	//
	void SetLanguage(const SFString& language);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_LeftToRight member.
	//
	// [in] lefttoright: The lefttoright value.
	//
	void SetLeftToRight(SFBool lefttoright);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Size member.
	//
	// [in] size: The size value.
	//
	void SetSize(SFFloat size);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Spacing member.
	//
	// [in] spacing: The spacing value.
	//
	void SetSpacing(SFFloat spacing);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Style member.
	//
	// [in] style: The style value.
	//
	void SetStyle(const SFString& style);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_TopToBottom member.
	//
	// [in] toptobottom: The toptobottom value.
	//
	void SetTopToBottom(SFBool toptobottom);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Family member.
	//
	SFString GetFamily(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Horizontal member.
	//
	SFBool GetHorizontal(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Justify member.
	//
	SFInt32 GetNJustifys(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Justify member.
	//
	// [in] n: The index into the array.
	//
	SFString GetJustify(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Justify member.
	//
	const MFString& GetJustifyArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Language member.
	//
	SFString GetLanguage(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_LeftToRight member.
	//
	SFBool GetLeftToRight(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Size member.
	//
	SFFloat GetSize(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Spacing member.
	//
	SFFloat GetSpacing(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Style member.
	//
	SFString GetStyle(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_TopToBottom member.
	//
	SFBool GetTopToBottom(void) const;


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
	DECLARE_NODE(vrFontStyle);

};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrFontStyle::SetHorizontal(SFBool horizontal)
{
	m_Horizontal = horizontal;
}

inline void vrFontStyle::AddJustify(const SFString& justify)
{
	m_Justify.AddValue(justify);
}

inline void vrFontStyle::SetJustify(const MFString& justify)
{
	m_Justify.Clear();
	m_Justify = justify;
}

inline void vrFontStyle::SetLeftToRight(SFBool lefttoright)
{
	m_LeftToRight = lefttoright;
}

inline void vrFontStyle::SetSize(SFFloat size)
{
	m_Size = size;
}

inline void vrFontStyle::SetSpacing(SFFloat spacing)
{
	m_Spacing = spacing;
}

inline void vrFontStyle::SetTopToBottom(SFBool toptobottom)
{
	m_TopToBottom = toptobottom;
}

inline SFString vrFontStyle::GetFamily(void) const
{
	return m_Family;
}

inline SFBool vrFontStyle::GetHorizontal(void) const
{
	return m_Horizontal;
}

inline SFInt32 vrFontStyle::GetNJustifys(void) const
{
	return m_Justify.GetCount();
}

inline SFString vrFontStyle::GetJustify(SFInt32 n) const
{
	return m_Justify[n];
}

inline const MFString& vrFontStyle::GetJustifyArray(void) const
{
	return m_Justify;
}

inline SFString vrFontStyle::GetLanguage(void) const
{
	return m_Language;
}

inline SFBool vrFontStyle::GetLeftToRight(void) const
{
	return m_LeftToRight;
}

inline SFFloat vrFontStyle::GetSize(void) const
{
	return m_Size;
}

inline SFFloat vrFontStyle::GetSpacing(void) const
{
	return m_Spacing;
}

inline SFString vrFontStyle::GetStyle(void) const
{
	return m_Style;
}

inline SFBool vrFontStyle::GetTopToBottom(void) const
{
	return m_TopToBottom;
}

inline void vrFontStyle::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

