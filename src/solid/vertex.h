#ifndef __VERTEX_H3D
#define __VERTEX_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "Decls.h"
#include "HalfEdge.h"

/*----------------------------------------------------------------------
CLASS
	vrVertex

	A point in 3-space pointed at by a vrHalfEdge.

DESCRIPTION
	<ul>
	The vrVertex class stores the vertex information about a vrFace.
	</ul>

NOTES
	<ul>
	<li>You will probably not use this class directly.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrVertex : 
	public vrIntrusiveListNode < vrVertex * >, public SFVec3f 
{
private:
  vrHalfEdge *he;
  Uint32     index;
  SFFloat    scratch;
  Uint32     m_Mark;

public:
	ColorData *data;

	//<doc>------------------------------------------------------------
	// <dd>Default Constructor.
	//
	vrVertex      (void);

	//<doc>------------------------------------------------------------
	// <dd>Copy Constructor.
	//
	vrVertex      (const vrVertex& v);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] v: The coordinates of the vertex.
	//
	vrVertex      (const SFVec3f& v);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] s: The solid to which this vertex belongs.
	// [in] x,y,z: The coordinates of the vertex.
	//
	vrVertex      (vrSolid *s, SFFloat x, SFFloat y, SFFloat z);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	~vrVertex      (void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrVertex&  operator=   (const vrVertex& v);

	//<nodoc>------------------------------------------------------------
	// <dd>Used for copy construction and equals.
	//
	//	void      RemapPointers(CMapPtrToPtr *map);

	//<doc>------------------------------------------------------------
	// <dd>Calculate the normal surrounding this vertex.
	//
	void        CalcNormal     (void);

	//<doc>------------------------------------------------------------
	// <dd>Set the texture coordinate for this vertex.
	//
	// [in] coord: The texture coordinate.
	//
	void        SetTexCoord    (const SFVec2f& coord);

	//<doc>------------------------------------------------------------
	// <dd>Set the color for this vertex.
	//
	// [in] color: The color.
	//
	void        SetColor       (const SFColor& color);

	//<doc>------------------------------------------------------------
	// <dd>Set the normal for this vertex.
	//
	// [in] normal: The normal.
	//
	void        SetNormal      (const SFVec3f& normal);

	//<doc>------------------------------------------------------------
	// <dd>Set the HE for this vertex.
	//
	// [in] he: The halfedge.
	//
  void        SetHe          (vrHalfEdge *he);

	//<doc>------------------------------------------------------------
	// <dd>Set the index for this vertex.
	//
	// [in] i: The index.
	//
  void        SetIndex       (Uint32 i);

	//<doc>------------------------------------------------------------
	// <dd>Set the ID for this vertex.
	//
	// [in] i: The id.
	//
  void        SetId          (Uint32 i);

	//<doc>------------------------------------------------------------
	// <dd>Set the scratch value for this vertex.
	//
	// [in] f: The value.
	//
  void        SetScratch     (SFFloat f);

	//<doc>------------------------------------------------------------
	// <dd>Set the mark for this vertex.
	//
	// [in] mark: The mark.
	//
  void        SetMark        (Uint32 mark);

	//<doc>------------------------------------------------------------
	// <dd>Set the coordinates for this vertex.
	//
	// [in] pt: The coordinate.
	//
  void        SetLocation    (const SFVec3f& pt);

	//<doc>------------------------------------------------------------
	// <dd>Return the texture coordinates for this vertex.
	//
	// [in] def: Default value if this vertex has no texture coord.
	//
	SFVec2f     GetTextureCoord(const SFVec2f& def) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the color for this vertex.
	//
	// [in] def: Default value if this vertex has no color.
	//
	SFColor     GetColor       (const SFColor& def) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the normal for this vertex.
	//
	// [in] def: Default value if this vertex has no normal.
	//
	SFVec3f     GetNormal      (const SFVec3f& def) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the half edge for this vertex.
	//
  vrHalfEdge *GetHe          (void)        const;

	//<doc>------------------------------------------------------------
	// <dd>Return the index for this vertex.
	//
  Uint32      GetIndex       (void)        const;

	//<doc>------------------------------------------------------------
	// <dd>Return the scratch value for this vertex.
	//
  SFFloat     GetScratch     (void)        const;

	//<doc>------------------------------------------------------------
	// <dd>Return the mark value for this vertex.
	//
  Uint32      GetMark        (void)        const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this vertex is marked with 'mark'.
	//
	// [in] mark: The mark to check.
	//
  SFBool      IsMarked       (Uint32 mark) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the vrEdge that this vertex is a part of (he->edge).
	//
  vrEdge     *GetEdge        (void)        const;
  
#ifdef _DEBUG
	//<doc>------------------------------------------------------------
	// <dd>Debugging support.  Display the contents of the vrEdge to the dc.
	//
	// [in] dc: The vrDumpContext to which to dump this edge.
	//
  void      Show           (vrDumpContext& dc)            const;

	//<doc>------------------------------------------------------------
	// <dd>Debugging support.  Verify the edge.
	//
  void      Verify         (void)            const;

	//<doc>------------------------------------------------------------
	// <dd>Debugging support.  Write the neighborhood of this vertex.
	//
	void        WriteNeighborhood(void);
#endif
};
typedef vrIntrusiveList<vrVertex *> vrVertexList;
typedef vrArrayBase<vrVertex*>      vrVertexArray;
  
//----------------------------------------------------------------------
inline vrHalfEdge *vrVertex::GetHe(void) const
{
  return he;
}

inline Uint32 vrVertex::GetIndex(void) const
{
  return index;
}

inline SFFloat vrVertex::GetScratch(void) const
{
  return scratch;
}

inline Uint32 vrVertex::GetMark(void) const
{
  return m_Mark;
}

inline SFBool vrVertex::IsMarked(Uint32 m) const
{
  return (m_Mark == m);
}

inline vrEdge *vrVertex::GetEdge(void) const
{
  ASSERT(he);
  return he->GetEdge();
}

//----------------------------------------------------------------------
inline void vrVertex::SetHe(vrHalfEdge *h)
{
  /* may be NULL for example see lkev */
  he = h;
}

inline void vrVertex::SetIndex(Uint32 i)
{
  index = i;
}

inline void vrVertex::SetScratch(SFFloat f)
{
  scratch = f;
}

inline void vrVertex::SetMark(Uint32 m)
{
  ASSERT(m == DELETED || 
					m == BRANDNEW || 
					m == ON || 
					m == VISITED || 
					m == UNKNOWN);
  m_Mark = m;
}

inline void vrVertex::SetLocation(const SFVec3f& pt)
{
  x = pt.x; 
	y = pt.y; 
	z = pt.z;
}

#endif
