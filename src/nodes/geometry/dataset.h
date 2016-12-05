#ifndef __DATASET_H3D
#define __DATASET_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "GeometryNode.h"

/*----------------------------------------------------------------------
CLASS
	vrDataSet

	This class corresponds to the DataSet node in VRML.  
	<A href="../spec/part1/nodesRef.html#DataSet">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the DataSet node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#DataSet">link</a>.</ul>

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
class LIBInterface vrDataSet : public vrGeometryNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'colorPerVertex' field.
	//
	// [default] TRUE
	//
	SFBool              	m_ColorPerVertex;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'normalPerVertex' field.
	//
	// [default] TRUE
	//
	SFBool              	m_NormalPerVertex;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'colorIndex' field.
	//
	// [default] []
	//
	MFInt32             	m_ColorIndex;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'coordIndex' field.
	//
	// [default] []
	//
	MFInt32             	m_CoordIndex;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'normalIndex' field.
	//
	// [default] []
	//
	MFInt32             	m_NormalIndex;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'texCoordIndex' field.
	//
	// [default] []
	//
	MFInt32             	m_TexCoordIndex;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'color' field.
	//
	// [default] NULL   
	//
	vrColor*            	m_Color;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'coord' field.
	//
	// [default] NULL   
	//
	vrCoordinate*       	m_Coord;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'normal' field.
	//
	// [default] NULL   
	//
	vrNormal*           	m_Normal;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'texCoord' field.
	//
	// [default] NULL   
	//
	vrTextureCoordinate*	m_TexCoord;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'colorIndexEv' eventIn.
	//
	// [default] 0
	//
	SFInt32             	m_ColorIndexEv;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'coordIndexEv' eventIn.
	//
	// [default] 0
	//
	SFInt32             	m_CoordIndexEv;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'normalIndexEv' eventIn.
	//
	// [default] 0
	//
	SFInt32             	m_NormalIndexEv;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'texCoordIndexEv' eventIn.
	//
	// [default] 0
	//
	SFInt32             	m_TexCoordIndexEv;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrDataSet(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrDataSet(const vrDataSet& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrDataSet(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrDataSet& operator=(const vrDataSet& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_ColorPerVertex member.
	//
	// [in] colorpervertex: The colorpervertex value.
	//
	void SetColorPerVertex(SFBool colorpervertex);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_NormalPerVertex member.
	//
	// [in] normalpervertex: The normalpervertex value.
	//
	void SetNormalPerVertex(SFBool normalpervertex);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_ColorIndex array (grow if needed).
	//
	// [in] colorindex: The value to add to the m_ColorIndex array.
	//
	void AddColorIndex(SFInt32 colorindex);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_ColorIndex member (copies values).
	//
	// [in] colorindex: The m_ColorIndex array.
	//
	void SetColorIndex(const MFInt32& colorindex);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_CoordIndex array (grow if needed).
	//
	// [in] coordindex: The value to add to the m_CoordIndex array.
	//
	void AddCoordIndex(SFInt32 coordindex);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_CoordIndex member (copies values).
	//
	// [in] coordindex: The m_CoordIndex array.
	//
	void SetCoordIndex(const MFInt32& coordindex);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_NormalIndex array (grow if needed).
	//
	// [in] normalindex: The value to add to the m_NormalIndex array.
	//
	void AddNormalIndex(SFInt32 normalindex);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_NormalIndex member (copies values).
	//
	// [in] normalindex: The m_NormalIndex array.
	//
	void SetNormalIndex(const MFInt32& normalindex);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_TexCoordIndex array (grow if needed).
	//
	// [in] texcoordindex: The value to add to the m_TexCoordIndex array.
	//
	void AddTexCoordIndex(SFInt32 texcoordindex);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_TexCoordIndex member (copies values).
	//
	// [in] texcoordindex: The m_TexCoordIndex array.
	//
	void SetTexCoordIndex(const MFInt32& texcoordindex);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Color member.
	//
	// [in] color: The color value.
	//
	void SetColor(const vrColor* color);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Coord member.
	//
	// [in] coord: The coord value.
	//
	void SetCoord(const vrCoordinate* coord);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Normal member.
	//
	// [in] normal: The normal value.
	//
	void SetNormal(const vrNormal* normal);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_TexCoord member.
	//
	// [in] texcoord: The texcoord value.
	//
	void SetTexCoord(const vrTextureCoordinate* texcoord);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_ColorPerVertex member.
	//
	SFBool GetColorPerVertex(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_NormalPerVertex member.
	//
	SFBool GetNormalPerVertex(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_ColorIndex member.
	//
	SFInt32 GetNColorIndexs(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_ColorIndex member.
	//
	// [in] n: The index into the array.
	//
	SFInt32 GetColorIndex(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_ColorIndex member.
	//
	const MFInt32& GetColorIndexArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_CoordIndex member.
	//
	SFInt32 GetNCoordIndexs(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_CoordIndex member.
	//
	// [in] n: The index into the array.
	//
	SFInt32 GetCoordIndex(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_CoordIndex member.
	//
	const MFInt32& GetCoordIndexArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_NormalIndex member.
	//
	SFInt32 GetNNormalIndexs(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_NormalIndex member.
	//
	// [in] n: The index into the array.
	//
	SFInt32 GetNormalIndex(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_NormalIndex member.
	//
	const MFInt32& GetNormalIndexArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_TexCoordIndex member.
	//
	SFInt32 GetNTexCoordIndexs(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_TexCoordIndex member.
	//
	// [in] n: The index into the array.
	//
	SFInt32 GetTexCoordIndex(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_TexCoordIndex member.
	//
	const MFInt32& GetTexCoordIndexArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Color member.
	//
	vrColor* GetColor(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Coord member.
	//
	vrCoordinate* GetCoord(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Normal member.
	//
	vrNormal* GetNormal(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_TexCoord member.
	//
	vrTextureCoordinate* GetTexCoord(void) const;


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
	// <dd>Declare that this node may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrDataSet);

	//------------------------------------------------------------
	// hand coded functions
	void                 AddColor(const SFColor& color);
	SFInt32              GetNColors(void) const;
	SFColor              GetColor(SFInt32 n) const;
	void                 AddCoord(const SFVec3f& vec3f);
	SFInt32              GetNCoords(void) const;
	SFVec3f              GetCoord(SFInt32 n) const;
	void                 AddNormal(const SFVec3f& vec3f);
	SFInt32              GetNNormals(void) const;
	SFVec3f              GetNormal(SFInt32 n) const;
	void                 AddTexCoord(const SFVec2f& vec2f);
	SFInt32              GetNTexCoords(void) const;
	SFVec2f              GetTexCoord(SFInt32 n) const;
	virtual void BuildMesh(void);
	virtual void BuildColors(void);
	virtual void BuildNormals(void);
	virtual void BuildTexCoords(void);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrDataSet::SetColorPerVertex(SFBool colorpervertex)
{
	m_ColorPerVertex = colorpervertex;
}

inline void vrDataSet::SetNormalPerVertex(SFBool normalpervertex)
{
	m_NormalPerVertex = normalpervertex;
}

inline void vrDataSet::AddColorIndex(SFInt32 colorindex)
{
	m_ColorIndex.AddValue(colorindex);
}

inline void vrDataSet::SetColorIndex(const MFInt32& colorindex)
{
	m_ColorIndex.Clear();
	m_ColorIndex = colorindex;
}

inline void vrDataSet::AddCoordIndex(SFInt32 coordindex)
{
	m_CoordIndex.AddValue(coordindex);
}

inline void vrDataSet::SetCoordIndex(const MFInt32& coordindex)
{
	m_CoordIndex.Clear();
	m_CoordIndex = coordindex;
}

inline void vrDataSet::AddNormalIndex(SFInt32 normalindex)
{
	m_NormalIndex.AddValue(normalindex);
}

inline void vrDataSet::SetNormalIndex(const MFInt32& normalindex)
{
	m_NormalIndex.Clear();
	m_NormalIndex = normalindex;
}

inline void vrDataSet::AddTexCoordIndex(SFInt32 texcoordindex)
{
	m_TexCoordIndex.AddValue(texcoordindex);
}

inline void vrDataSet::SetTexCoordIndex(const MFInt32& texcoordindex)
{
	m_TexCoordIndex.Clear();
	m_TexCoordIndex = texcoordindex;
}

inline SFBool vrDataSet::GetColorPerVertex(void) const
{
	return m_ColorPerVertex;
}

inline SFBool vrDataSet::GetNormalPerVertex(void) const
{
	return m_NormalPerVertex;
}

inline SFInt32 vrDataSet::GetNColorIndexs(void) const
{
	return m_ColorIndex.GetCount();
}

inline SFInt32 vrDataSet::GetColorIndex(SFInt32 n) const
{
	return m_ColorIndex[n];
}

inline const MFInt32& vrDataSet::GetColorIndexArray(void) const
{
	return m_ColorIndex;
}

inline SFInt32 vrDataSet::GetNCoordIndexs(void) const
{
	return m_CoordIndex.GetCount();
}

inline SFInt32 vrDataSet::GetCoordIndex(SFInt32 n) const
{
	return m_CoordIndex[n];
}

inline const MFInt32& vrDataSet::GetCoordIndexArray(void) const
{
	return m_CoordIndex;
}

inline SFInt32 vrDataSet::GetNNormalIndexs(void) const
{
	return m_NormalIndex.GetCount();
}

inline SFInt32 vrDataSet::GetNormalIndex(SFInt32 n) const
{
	return m_NormalIndex[n];
}

inline const MFInt32& vrDataSet::GetNormalIndexArray(void) const
{
	return m_NormalIndex;
}

inline SFInt32 vrDataSet::GetNTexCoordIndexs(void) const
{
	return m_TexCoordIndex.GetCount();
}

inline SFInt32 vrDataSet::GetTexCoordIndex(SFInt32 n) const
{
	return m_TexCoordIndex[n];
}

inline const MFInt32& vrDataSet::GetTexCoordIndexArray(void) const
{
	return m_TexCoordIndex;
}

inline vrColor* vrDataSet::GetColor(void) const
{
	return m_Color;
}

inline vrCoordinate* vrDataSet::GetCoord(void) const
{
	return m_Coord;
}

inline vrNormal* vrDataSet::GetNormal(void) const
{
	return m_Normal;
}

inline vrTextureCoordinate* vrDataSet::GetTexCoord(void) const
{
	return m_TexCoord;
}

inline void vrDataSet::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

