#ifndef __HALFEDGE_H3D
#define __HALFEDGE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "Decls.h"

enum {NOT_LOOSE=0, LOOSE};

/*----------------------------------------------------------------------
CLASS
	vrHalfEdge

	The basis for connecting the various elements that make up
	a vrSolid.

DESCRIPTION
	<ul>
	vrHalfEdge objects point to vrEdge objects, vrLoop
	objects and vrVertex obects. This provides the ability to move
	from one data structure to another.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrHalfEdge : 
	public vrIntrusiveListNode < vrHalfEdge * >
{
private:
  vrHalfEdge()
		{ }
  vrHalfEdge& operator=(const vrHalfEdge& l)
		{ return *this; }

  vrVertex  *vertex;
  vrEdge    *edge;
  vrLoop    *wloop;
  Uint32     m_Mark;
  
public:
	ColorData *data;

	//<doc>------------------------------------------------------------
	// <dd>Copy Constructor.
	//
	vrHalfEdge       (const vrHalfEdge& he);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] v: The vertex to which the halfedge points.
	//
	vrHalfEdge       (vrVertex *v);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] l: The loop to which the halfedge belongs.
	// [in] v: The vertex to which the halfedge points.
	//
	vrHalfEdge       (vrLoop *l, vrVertex *v);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] he: A vrHalfEdge to copy from.
	//
	vrHalfEdge       (vrHalfEdge *he);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	~vrHalfEdge      ();

	//<nodoc>------------------------------------------------------------
	// <dd>Copies pointers for copy constructors.
	//
	//void      RemapPointers    (CMapPtrToPtr *map);

	//<doc>------------------------------------------------------------
	// <dd>Set the vertex to which this half edge points.
	//
	// [in] v: The vertex.
	//
  void        SetVertex        (vrVertex *v);

	//<doc>------------------------------------------------------------
	// <dd>Set the edge to which this half edge points.
	//
	// [in] e: The edge.
	//
  void        SetEdge          (vrEdge *e);

	//<doc>------------------------------------------------------------
	// <dd>Set the loop to which this half edge points.
	//
	// [in] l: The loop.
	//
  void        SetLoop          (vrLoop *l);

	//<doc>------------------------------------------------------------
	// <dd>Set the mark for this half edge.
	//
	// [in] m: The mark.
	//
  void        SetMark          (Uint32 m);

	//<doc>------------------------------------------------------------
	// <dd>Set the next pointer of this half edge.
	//
	// [in] node: The next he.
	//
  void        SetNext          (vrHalfEdge *node);

	//<doc>------------------------------------------------------------
	// <dd>Set the prev pointer of this half edge.
	//
	// [in] node: The prev he.
	//
  void        SetPrev          (vrHalfEdge *node);
  
	//<doc>------------------------------------------------------------
	// <dd>Return the vertex to which this half edge points.
	//
  vrVertex   *GetVertex        (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the edge to which this half edge points.
	//
  vrEdge     *GetEdge          (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the loop to which this half edge points.
	//
  vrLoop     *GetLoop          (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the mark for this halfedge.
	//
  Uint32      GetMark          (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this half edge is marked with 'm'.
	//
  SFBool      Marked           (Uint32 m) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns the solid to which this half edge belongs (wloop->face->solid).
	//
  vrSolid    *GetSolid         (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the mate half edge (edge->he{1,2}).
	//
  vrHalfEdge *GetMate          (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the index of this half edge's vertex (vertex->index).
	//
  Uint32      GetIndex         (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the face to which this halfedge belongs (wloop->face).
	//
  vrFace     *GetFace          (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the normal to the face to which this halfedge belongs (wloop->face->GetNormal()).
	//
  SFVec3f     GetFaceNormal    (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the face to which this half edge's mate points (GetMate()->face).
	//
  vrFace     *GetMateFace      (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the normal to the face to which this half edge's mate points (GetMate()->face->GetNormal()).
	//
  SFVec3f     GetMateFaceNormal(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the index to the mate's vertex (GetMate()->vertex->index).
	//
  Uint32      GetMateIndex     (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the mate's vertex (GetMate()->vertex).
	//
  vrVertex   *GetMateVertex    (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the loop to which this edge points (edge->he{1,2}->wloop).
	//
	// [in] whichHe: 0 = Left, 1 = Right
	//
  vrLoop     *GetEdgeLoop      (SFBool whichHe) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the halfedge to which the edge points (edge->he{1,2}).
	//
	// [in] whichHe: 0 = Left, 1 = Right
	//
  vrHalfEdge *GetEdgeHe        (SFBool whichHe) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the normal for this halfedge.
	//
	// [in] def: The default normal if this halfedge has no normal.
	//
	SFVec3f     GetNormal       (const SFVec3f& def) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the color for this halfedge.
	//
	// [in] def: The default color if this halfedge has no color.
	//
	SFColor     GetColor        (const SFColor& def) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the texture coord for this halfedge.
	//
	// [in] def: The default texture coord if this halfedge has no texture coord.
	//
	SFVec2f     GetTextureCoord (const SFVec2f& def) const;

	//<doc>------------------------------------------------------------
	// <dd>Set the texture coord for this halfedge.
	//
	// [in] decoord: The coordinate.
	//
	void        SetTexCoord     (const SFVec2f& coord);

	//<doc>------------------------------------------------------------
	// <dd>Set the color for this halfedge.
	//
	// [in] color: The color.
	//
	void        SetColor        (const SFColor& color);

	//<doc>------------------------------------------------------------
	// <dd>Set the normal for this halfedge.
	//
	// [in] normal: The normal.
	//
	void        SetNormal       (const SFVec3f& normal);

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this halfedge is a null edge.
	//
  SFBool      isNullEdge      (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this halfedge is a null strut.
	//
  SFBool      isNullStrut     (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the given halfedge is this half edge's mate.
	//
	// [in] he: The query half edge.
	//
  SFBool      isMate          (vrHalfEdge *he) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the given halfedge is this half edge's neighbor.
	//
	// [in] he: The query half edge.
	//
  SFBool      isNeighbor      (vrHalfEdge *he) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this halfedge is Wide (i.e. forms an angle greater than 180 degrees with preceeding and following edges).
	//
	// [in] inc180: If TRUE includes exact 180 degrees in definition of Wide.
	//
  SFBool      isWide          (SFBool inc180) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this halfedge is exactly 180 degrees.
	//
  SFBool      is180           (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this halfedge is forms a convex angle with preceeding and following edges.
	//
  SFBool      isConvexEdge    (void) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
  SFBool      isSectorWide    (Uint32 ind) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns the vector that bisects the angle formed by preceeding and following edges.
	//
  SFVec3f     Bisect          (void) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
  SFVec3f     InsideVector    (void) const;

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
#endif
}; 
typedef vrRingList<vrHalfEdge *> vrHalfEdgeList;

/***********************************************************************/
/* Mutators */
inline void vrHalfEdge::SetVertex(vrVertex *v)
{
  ASSERT(v);
  vertex = v;
}

inline void vrHalfEdge::SetEdge(vrEdge *e)
{
  /* may be NULL (see DeleteHalfEdge) */
  edge = e;
}

inline void vrHalfEdge::SetLoop(vrLoop *l)
{
  ASSERT(l);
  wloop = l;
}

inline void vrHalfEdge::SetMark(Uint32 m)
{
  ASSERT((m == LOOSE) || 
	 (m == NOT_LOOSE) || 
	 (m == BRANDNEW) || 
	 (m == PARTIAL_NORMAL) || 
	 (m == DELETED));
  m_Mark = m;
}

/***********************************************************************/
/* Inspectors */
inline vrVertex *vrHalfEdge::GetVertex(void) const
{
  return vertex;
}

inline vrEdge *vrHalfEdge::GetEdge(void) const
{
  return edge;
}

inline vrLoop *vrHalfEdge::GetLoop(void) const
{
  return wloop;
}

inline Uint32 vrHalfEdge::GetMark(void) const
{
  return m_Mark;
}

inline SFBool vrHalfEdge::Marked(Uint32 m) const
{
  return (m_Mark == m);
}

inline vrFace *vrHalfEdge::GetMateFace(void) const
{
  ASSERT(GetMate());
  return GetMate()->GetFace();
}

inline SFVec3f vrHalfEdge::GetMateFaceNormal(void) const
{
  ASSERT(GetMate());
  return GetMate()->GetFaceNormal();
}

inline Uint32 vrHalfEdge::GetMateIndex(void) const
{
  ASSERT(GetMate());
  return GetMate()->GetIndex();
}

inline vrVertex *vrHalfEdge::GetMateVertex(void) const
{
  ASSERT(GetMate());
  return GetMate()->GetVertex();
}

/***********************************************************************/
/* Queries */
inline SFBool vrHalfEdge::isMate(vrHalfEdge *he) const
{
  vrHalfEdge *m = GetMate();
  if (m == he) 
	{
    ASSERT(this == he->GetMate());
    ASSERT(edge == he->GetEdge());
    return TRUE;
  } else 
	{
    ASSERT(this != he->GetMate());
    ASSERT(edge != he->GetEdge());
    return FALSE;
  }
}

inline SFBool vrHalfEdge::is180(void) const
{
	return (isWide(TRUE) && !isWide(FALSE));
}

/***********************************************************************/
/* Other */
#ifdef _DEBUG
void DEBHE(vrHalfEdge *he, char *sss);
#else
#define DEBHE(a,b)
#endif

#endif
