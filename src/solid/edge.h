#ifndef __EDGE_H3D
#define __EDGE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

enum {HE1=0, HE2};

#include "Decls.h"

/*----------------------------------------------------------------------
CLASS
	vrEdge

	A connection between two verticies.

DESCRIPTION
	<ul>
	The edge node stores two vrHalfEdge pointers.  One on the left
	and one on the right.  The vrHalfEdge pointers store pointers
	to the vrVertex nodes.
	</ul>

NOTES
	<ul>
	<li>The Solid Modeling library uses a data structure called the
	Half Edge.  More information about this data structure is available
	in the literature.</li>
	<li>This class has private operator= so you cannot assign it.</li>
	<li>You will probably not use this class directly.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrEdge : 
	public vrIntrusiveListNode < vrEdge * >
{
private:
  vrEdge& operator=(const vrEdge& l) { return *this; }

  vrHalfEdge *he1;
  vrHalfEdge *he2;
  Uint32     index;

public:
  Uint32     m_Mark;

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	vrEdge    (void);

	//<doc>------------------------------------------------------------
	// <dd>Copy Constructor.
	//
	vrEdge    (const vrEdge& e);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] s: The solid to which this edge belongs.
	//
	vrEdge    (vrSolid *s);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	~vrEdge    ();
  
	//<doc>------------------------------------------------------------
	// <dd>Swap the edge's half-edges (effectivly reversing the edge).
	//
  void      SwapHes (void);

	//<doc>------------------------------------------------------------
	// <dd>Set a halfedge.
	//
	// [in] whichHe: 0 = Left, 1 = Right.
	// [in] he: The halfedge pointer.
	//
  void      SetHe          (SFBool whichHe, vrHalfEdge *he);

	//<doc>------------------------------------------------------------
	// <dd>Set the edge's index.
	//
	// [in] i: The index.
	//
  void      SetIndex       (Uint32 i);

	//<doc>------------------------------------------------------------
	// <dd>Set the edge's mark.
	//
	// [in] m: The mark.
	//
  void      SetMark        (Uint32 m);

	//<nodoc>------------------------------------------------------------
	// <dd>For future use in copy constructor and operator=
	//
	//  void      RemapPointers         (CMapPtrToPtr *map);
  
	//<doc>------------------------------------------------------------
	// <dd>Return one of the edge's halfedges.
	//
	// [in] whichHe: 0 = Left, 1 = Right.
	//
	vrHalfEdge *GetHe          (SFBool whichHe) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the edge's index.
	//
  Uint32    GetIndex       (void)            const;

	//<doc>------------------------------------------------------------
	// <dd>Return the edge's mark.
	//
  Uint32    GetMark        (void)            const;

	//<doc>------------------------------------------------------------
	// <dd>Return TRUE if this edge is marked with 'm'.
	//
	// [in] m: The mark to check.
	//
  SFBool    Marked         (Uint32 m)        const;

	//<doc>------------------------------------------------------------
	// <dd>Return the vrSolid to which this edge belongs. (he{1,2}->wloop->face->solid)
	//
  vrSolid    *GetSolid       (void)            const;

	//<doc>------------------------------------------------------------
	// <dd>Return the vrLoop to which this edge belongs. (he{1,2}->wloop)
	//
  vrLoop     *GetLoop        (SFBool whichHe) const; 

	//<doc>------------------------------------------------------------
	// <dd>Return one of the vrVertex to which this edge points. (he{1,2}->vertex)
	//
	// [in] whichHe: 0 = Left, 1 = Right.
	//
  vrVertex   *GetVertex      (SFBool whichHe) const;

	//<doc>------------------------------------------------------------
	// <dd>Return one of the indicies of the one of the vrVertex to which this edge points. (he{1,2}->vertex->index)
	//
	// [in] whichHe: 0 = Left, 1 = Right.
	//
  Uint32    GetVertexIndex (SFBool whichHe) const; 

	//<doc>------------------------------------------------------------
	// <dd>Add a half edge to this edge.
	//
	// [in] v: The vertex to which the halfedge points.
	// [in] where: The halfedge to add.
	// [in] sign: 0 = Left, 1 = Right.
	//
  vrHalfEdge *AddHalfEdge    (vrVertex *v, vrHalfEdge *where, SFBool sign);

	//<doc>------------------------------------------------------------
	// <dd>Delete a half edge.
	//
	// [in] he: The half edge to delete.
	//
  vrHalfEdge *DeleteHalfEdge (vrHalfEdge *he);

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
typedef vrIntrusiveList<vrEdge *> vrEdgeList;

/***********************************************************************/
inline vrEdge::~vrEdge()
{ 
  he1    = NULL;
  he2    = NULL;
  index  = (Uint32)-1;
  m_Mark = DELETED;
}

/***********************************************************************/
inline void vrEdge::SetHe(SFBool whichHe, vrHalfEdge *he)
{
  // May be NULL
  if (whichHe == HE1) {
  	he1 = he;
	} else {
		ASSERT(whichHe == HE2);
		he2 = he;
	}
}

inline void vrEdge::SetIndex(Uint32 i)
{
  index = i;
}

inline void vrEdge::SetMark(Uint32 m)
{
  ASSERT((m == UNKNOWN) || 
				 (m == DELETED) || 
				 (m == BRANDNEW) || 
				 (m == CREASE) || 
				 (m == VISITED) ||
				 (m == INVISIBLE));
  m_Mark = m;
}

/***********************************************************************/
inline vrHalfEdge *vrEdge::GetHe(SFBool whichHe) const
{
  if (whichHe == HE1) {
  	return he1;
	} else {
		ASSERT(whichHe == HE2);
		return he2;
	}
}

inline Uint32 vrEdge::GetIndex(void) const
{
  return index;
}

inline Uint32 vrEdge::GetMark(void) const
{
  return m_Mark;
}

inline SFBool vrEdge::Marked(Uint32 m) const
{
  ASSERT((m == UNKNOWN) || 
				 (m == DELETED) || 
				 (m == BRANDNEW) || 
				 (m == CREASE) || 
				 (m == VISITED) ||
				 (m == INVISIBLE));
  return (m_Mark & m);
}

#endif
