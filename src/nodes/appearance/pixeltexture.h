#ifndef __PIXELTEXTURE_H3D
#define __PIXELTEXTURE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrPixelTexture

	This class corresponds to the PixelTexture node in VRML.  
	<A href="../spec/part1/nodesRef.html#PixelTexture">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the PixelTexture node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#PixelTexture">link</a>.</ul>

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
class LIBInterface vrPixelTexture : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'repeatS' field.
	//
	// [default] TRUE
	//
	SFBool              	m_RepeatS;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'repeatT' field.
	//
	// [default] TRUE
	//
	SFBool              	m_RepeatT;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'width' field.
	//
	// [default] 0
	//
	SFInt32             	m_Width;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'height' field.
	//
	// [default] 0
	//
	SFInt32             	m_Height;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'nComponents' field.
	//
	// [default] 0
	//
	SFInt32             	m_NComponents;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field format.
	//
	// [default] 0x1908
	//
	SFInt32             	m_Format;

	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field colorBuffer.
	//
	// [default] NULL
	//
	char								 *m_ColorBuffer;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrPixelTexture(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrPixelTexture(const vrPixelTexture& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrPixelTexture(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrPixelTexture& operator=(const vrPixelTexture& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_RepeatS member.
	//
	// [in] repeats: The repeats value.
	//
	void SetRepeatS(SFBool repeats);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_RepeatT member.
	//
	// [in] repeatt: The repeatt value.
	//
	void SetRepeatT(SFBool repeatt);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Width member.
	//
	// [in] width: The width value.
	//
	void SetWidth(SFInt32 width);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Height member.
	//
	// [in] height: The height value.
	//
	void SetHeight(SFInt32 height);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_NComponents member.
	//
	// [in] ncomponents: The ncomponents value.
	//
	void SetNComponents(SFInt32 ncomponents);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Format member.
	//
	// [in] format: The format value.
	//
	void SetFormat(SFInt32 format);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_ColorBuffer member.
	//
	// [in] colorbuffer: The colorbuffer value.
	//
	void SetColorBuffer(const SFImage& colorbuffer);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_RepeatS member.
	//
	SFBool GetRepeatS(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_RepeatT member.
	//
	SFBool GetRepeatT(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Width member.
	//
	SFInt32 GetWidth(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Height member.
	//
	SFInt32 GetHeight(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_NComponents member.
	//
	SFInt32 GetNComponents(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Format member.
	//
	SFInt32 GetFormat(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_ColorBuffer member.
	//
	char *GetColorBuffer(void) const;


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
	DECLARE_NODE(vrPixelTexture);

	//------------------------------------------------------------
	// hand coded functions
	vrPixelTexture(SFInt32 width, SFInt32 height, SFInt32 nComponents, SFInt32 format);
	void AddPixel(SFInt32 i);
	void *AddToArray(SFInt32 v, void *vArray, SFInt32 size);
	void AllocateSpace(void);
	SFInt32               m_nPixels;
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrPixelTexture::SetRepeatS(SFBool repeats)
{
	m_RepeatS = repeats;
}

inline void vrPixelTexture::SetRepeatT(SFBool repeatt)
{
	m_RepeatT = repeatt;
}

inline void vrPixelTexture::SetWidth(SFInt32 width)
{
	m_Width = width;
}

inline void vrPixelTexture::SetHeight(SFInt32 height)
{
	m_Height = height;
}

inline void vrPixelTexture::SetNComponents(SFInt32 ncomponents)
{
	m_NComponents = ncomponents;
}

inline void vrPixelTexture::SetFormat(SFInt32 format)
{
	m_Format = format;
}

inline SFBool vrPixelTexture::GetRepeatS(void) const
{
	return m_RepeatS;
}

inline SFBool vrPixelTexture::GetRepeatT(void) const
{
	return m_RepeatT;
}

inline SFInt32 vrPixelTexture::GetWidth(void) const
{
	return m_Width;
}

inline SFInt32 vrPixelTexture::GetHeight(void) const
{
	return m_Height;
}

inline SFInt32 vrPixelTexture::GetNComponents(void) const
{
	return m_NComponents;
}

inline SFInt32 vrPixelTexture::GetFormat(void) const
{
	return m_Format;
}

inline char *vrPixelTexture::GetColorBuffer(void) const
{
	return m_ColorBuffer;
}

inline void vrPixelTexture::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

