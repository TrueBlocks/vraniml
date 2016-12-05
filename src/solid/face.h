#ifndef __FACE_H3D
#define __FACE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "Decls.h"
#include "Algorithms\Intersect.h"

#include "Loop.h"

/*----------------------------------------------------------------------
CLASS
	vrFace

	A face is a list of vrLoops.  vrLoops are lists of vrHalfEdges.
	vrHalfEdge nodes point to vrVertex nodes.  Therefor a vrFace
	is a list of verticies.  In other words, a face is a polygon.

DESCRIPTION
	<ul>
	A polygon (possibly with holes) described as a list of verticies.
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
class LIBInterface vrFace : 
	public vrIntrusiveListNode < vrFace * > , public vrPlane
{
private:
  vrFace(void)
		{ }
  vrFace& operator=(const vrFace& l)
		{ return *this; }

  vrSolid    *solid;
  vrLoop     *lout;
  Uint32      index;
  Uint32      mark1;
  Uint32      mark2;

public:  
	//<doc>------------------------------------------------------------
	// <dd>The loop list.
	//
	// [defualt] Empty
	//
  vrLoopList  loops;
	ColorData  *data;

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] s: The solid to which this face belongs.
	// [in] c: The default color for this face.
	//
	vrFace      (vrSolid *s, const SFColor& c=vrWhite);

	//<doc>------------------------------------------------------------
	// <dd>Copy Constructor.
	//
	vrFace      (const vrFace& f);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	~vrFace     ();

	//<nodoc>------------------------------------------------------------
	// <dd>Copies pointers for copy constructors.
	//
	//	void      RemapPointers         (CMapPtrToPtr *map);

	//<doc>------------------------------------------------------------
	// <dd>Change the solid in which this face belongs.
	//
	// [in] s: The solid.
	//
  void        SetSolid              (vrSolid *s);

	//<doc>------------------------------------------------------------
	// <dd>Set the outer loop for this solid.
	//
	// [in] l: The outer loop.
	//
  void        SetLoopOut            (vrLoop *l);

	//<doc>------------------------------------------------------------
	// <dd>Set the index for this solid.
	//
	// [in] i: The index.
	//
  void        SetIndex              (Uint32 i);

	//<doc>------------------------------------------------------------
	// <dd>Set the mark1 value for this solid.
	//
	// [in] mark: The mark1.
	//
  void        SetMark1              (Uint32 mark);

	//<doc>------------------------------------------------------------
	// <dd>Set the mark2 value for this solid.
	//
	// [in] mark: The mark2.
	//
  void        SetMark2              (Uint32 mark);

	//<doc>------------------------------------------------------------
	// <dd>Add a vrLoop to this face.
	//
	// [in] l: The loop.
	// [in] isOuter: TRUE if this should become the outer loop for this face.
	//
  void        AddLoop               (vrLoop *l, SFBool isOuter=FALSE);

	//<doc>------------------------------------------------------------
	// <dd>Remove a loop from this face.
	//
	// [in] l: The loop to remove.
	//
  void        RemoveLoop            (vrLoop *l);
  
	//<doc>------------------------------------------------------------
	// <dd>Get the color of this face.
	//
	// [in] def: The default color if this face has no color.
	//
	SFColor     GetColor              (const SFColor& def) const;

	//<doc>------------------------------------------------------------
	// <dd>Set the color of this face.
	//
	// [in] color: The color.
	//
	void        SetColor              (const SFColor& color);

	//<doc>------------------------------------------------------------
	// <dd>Return the loop's verticies in the given array.  Returns TRUE if the verticies fit into the array.
	//
	// [in/out] max: The number of vecs that can be added.
	// [out] vecs: The memory location into which to copy the verticies.  If NULL, max returns the required number of verticies.
	//
	SFBool      GetVertexLocations(Uint32& max, SFVec3f *vecs) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the vrSolid to which this face belongs.
	//
  vrSolid    *GetSolid              (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the outer vrLoop of this face.
	//
  vrLoop     *GetLoopOut            (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the index of this face.
	//
  Uint32      GetIndex              (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the mark1 value of this face.
	//
  Uint32      GetMark1              (void) const; 

	//<doc>------------------------------------------------------------
	// <dd>Return the mark2 value of this face.
	//
  Uint32      GetMark2              (void) const; 

	//<doc>------------------------------------------------------------
	// <dd>Return TRUE if this face is marked with mark.
	//
	// [in] mark: The mark to check.
	//
  SFBool      Marked1               (Uint32 mark) const;

	//<doc>------------------------------------------------------------
	// <dd>Return TRUE if this face is marked with mark.
	//
	// [in] mark: The mark to check.
	//
  SFBool      Marked2               (Uint32 mark) const;

	//<nodoc>------------------------------------------------------------
	// <dd>This function will disappear.
	//
  // SFColor     GetColor              (void) const;
  
	//<doc>------------------------------------------------------------
	// <dd>Return the first vrHalfEdge in the outer loop.
	//
  vrHalfEdge *GetFirstHe            (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the first vrHalfEdge in the first inner loop (if any).
	//
  vrHalfEdge *GetFirstHeFromSecondLoop(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the vrVertex pointer to by the first vrHalfEdge in the outer loop.
	//
  vrVertex   *GetFirstVertex        (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the first vrLoop in the loop list (may not be outer loop).
	//
  vrLoop     *GetFirstLoop          (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the second vrLoop in the loop list (if present).
	//
  vrLoop     *GetSecondLoop         (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the face normal.
	//
  SFVec3f     GetNormal             (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the 'D' value of the plane equation of the face.
	//
  SFFloat     GetD                  (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Calculate the plane equation.
	//
	// [in] l: The vrLoop to use for the calculation.
	// [out] normOut: The memory location into which to copy the plane normal.
	// [out] dOut: The memory location into which to copy the 'D' value of the plane equation.
	//
  SFBool      CalcEquation          (const vrLoop *l, SFVec3f *normOut, SFFloat *dOut) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the center of the face.
	//
  SFVec3f     GetCenter             (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of loops in this face.
	//
  Uint32      nLoops                (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this face is degenerate (i.e. has no area).
	//
  SFBool      isDegenerate          (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this face is planer (within a tolerance).
	//
  SFBool      isPlanar              (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this face contains the given point.  Returns additional info in the intersection record.
	//
	// [in] v: The query vertex.
	// [out] rec: Memory location into which to copy further information about the intersection.
	//
  SFBool      Contains              (vrVertex *v, vrIntersectRecord& rec) const;

/*
	//<nodoc>------------------------------------------------------------
	// <dd>Returns TRUE if this face and f2 are co-planar.
	//
	// [in] f2: The query face.
	//
  SFBool      isCoplanar            (vrFace *f2) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Returns TRUE if this face and any of it's neighboring faces are co-planar.
	//
	// [out] f: Memory location representing the neighboring face which is co-planar.
	// [out] he: Memory location representing the halfedge (in this face) which borders 'f'.
	//
  SFBool      hasCoplanarNeighbor   (vrFace **f=NULL, vrHalfEdge **he=NULL) const; 

	//<nodoc>------------------------------------------------------------
	// <dd>Returns TRUE if this face has any co-linear verticies (3 or more verticies in a direct line).
	//
	// [out] l: Memory location representing the loop in which the co-lineararity exists.
	// [out] he: Memory location representing the halfedge starting the co-linear chain.
	//
  SFBool      hasColinearVerts      (vrLoop **l=NULL, vrHalfEdge **he=NULL) const; 

	//<nodoc>------------------------------------------------------------
	// <dd>Removes coplanar neighboring faces.
	//
  void        RemoveCoplanarFace    (vrFace *f, vrHalfEdge *he, vrFace **next); 
*/

	//<nodoc>------------------------------------------------------------
	// <dd>Removes co-linear verticies from this face.
	//
	void        RemoveColinearVerts   (LISTPOS& ePos);

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this face has holes.
	//
	SFBool      IsComplex             (void) const;

	//<doc>------------------------------------------------------------
	// <dd>Triangulates this face.
	//
	void        Triangulate           (void);

	//<doc>------------------------------------------------------------
	// <dd>Calculates this face's plane equation.  Returns TRUE if the face is not degenerate.
	//
  SFBool      CalcEquation          (void);

	//<doc>------------------------------------------------------------
	// <dd>Calculates this face's plane equation using a particular loop.  Returns TRUE if the face is not degenerate.
	//
	// [in] l: The loop to use in the calculation.
	//
  SFBool      CalcEquation          (const vrLoop *l);

	//<doc>------------------------------------------------------------
	// <dd>Add an internal ring at the given vertex.
	//
	// [in] v: The location at which to make the loop (should be contained by the face).
	//
  vrEdge     *MakeRing              (const SFVec3f& v);

	//<doc>------------------------------------------------------------
	// <dd>Revert the face (flip it inside out -- reverse the loops).
	//
  void        Revert                (void);

	//<doc>------------------------------------------------------------
	// <dd>Invert the plane normal.
	//
  void        InvertNormal          (void);

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
  void        AdjustOuterLoop       (void);

	//<nodoc>------------------------------------------------------------
	// <dd>Render this face.
	//
  //void        Traverse              (vrRenderTraverser *t) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nearest internal vertex (i.e. not on the outer loop) in any internal loops in this face.
	//
	// [in] he: The query halfedge.
	// [out] dOut: The distance of the nearest vertex to the 'he'.
	//
  vrHalfEdge *NearestInteriorVertex (vrHalfEdge *he, SFFloat *dOut) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns the two closest verticies in the face (from the outer loop to any inner loop).
	//
	// [out] he1Out: The first he.
	// [out] he2Out: The second he.
	//
  void        FindTwoClosest        (vrHalfEdge **he1Out, vrHalfEdge **he2Out) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns the area of the face.
	//
  SFFloat     Area                  (void) const;

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
typedef vrIntrusiveList<vrFace *> vrFaceList;

/***********************************************************************/
inline void vrFace::SetSolid(vrSolid *s)
{
  ASSERT(s);
  solid = s;
}

inline void vrFace::SetLoopOut(vrLoop *l)
{
  // lout may be made NULL just prior to a face's deletion.
  // The verification function will assure that no valid
  // face has a NULL lout.
  lout = l;
}

inline void vrFace::SetIndex(Uint32 i)
{
  index = i;
}

inline void vrFace::SetMark1(Uint32 m)
{
  ASSERT((m == ABOVE) || 
	 (m == BELOW) || 
	 (m == ON));
  mark1 = m;
}

inline void vrFace::SetMark2(Uint32 m)
{
  ASSERT((m == UNKNOWN) || 
	 (m == BRANDNEW) || 
   (m == DELETED) || 
   (m == INVISIBLE) || 
   (m == CALCED) || 
	 (m == VISITED) || 
	 (m == ALTERED));
  mark2 |= m;
}

/***********************************************************************/
inline vrSolid *vrFace::GetSolid(void) const
{
  return solid;
}

inline vrLoop *vrFace::GetLoopOut(void) const
{
  return lout;
}

inline Uint32 vrFace::GetIndex(void) const
{
  return index;
}

inline Uint32 vrFace::GetMark1(void) const
{
  return mark1;
}

inline Uint32 vrFace::GetMark2(void) const
{
  return mark2;
}

//inline SFVec3f vrFace::GetNormal(void) const
//{
//	ASSERT(calced);
//	return Normal;
//}

inline SFVec3f vrFace::GetNormal(void) const
{
  ASSERT(Marked2(CALCED));
  
#ifdef _DEBUG
  SFVec3f n;
	SFFloat f;
	CalcEquation(lout, &n, &f);  // this is const so does not alter 'this'
//	ASSERT(n == m_Normal);
#endif

  return vrPlane::GetNormal();
}

inline SFFloat vrFace::GetD(void) const
{
  ASSERT(Marked2(CALCED));

#ifdef _DEBUG
	SFVec3f n;
	SFFloat f;
	CalcEquation(lout, &n, &f); // this is const so does not alter 'this'
//  ASSERT(vrCompare(f, m_D) == 0);
#endif

	return vrPlane::GetD();
}

inline SFBool vrFace::Marked1(Uint32 m) const
{
  ASSERT((m == ABOVE) || 
	 (m == BELOW) || 
	 (m == ON));
  return (mark1 == m);
}

inline SFBool vrFace::Marked2(Uint32 m) const
{
  ASSERT((m == UNKNOWN) || 
	 (m == BRANDNEW) || 
	 (m == DELETED) || 
   (m == INVISIBLE) || 
   (m == CALCED) || 
	 (m == VISITED) || 
	 (m == ALTERED));
  return (mark2 & m);
}

inline vrLoop *vrFace::GetFirstLoop(void) const
{
	return loops.GetHead();
}

inline Uint32 vrFace::nLoops(void) const
{
  return loops.GetCount();
}

/***********************************************************************/
inline SFBool vrFace::CalcEquation(void)
{
  SetMark2(CALCED);
  return CalcEquation(lout, &m_Normal, &m_D);
}

#endif
