#ifndef __LOOP_H3D
#define __LOOP_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "Decls.h"
#include "Algorithms\Intersect.h"

#include "HalfEdge.h"

/*----------------------------------------------------------------------
CLASS
	vrLoop

	A vrRingList of vrHalfEdges defining a vrFace.

DESCRIPTION
	<ul>
	A vrFace contains a list of vrLoop objects.  The vrLoop stores a ring list
	of vrHalfEdges.  Each halfedge points to a vrVertex and the 'loop'
	defines the verticies of a vrFace.  Inside loops may also be present
	in a vrFace in which case the face has a hole.
	</ul>

NOTES
	<ul>
	<li>You will not use this class directly.</li>
	<li>Copy constructors are private so you can't copy it.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrLoop : 
	public vrIntrusiveListNode < vrLoop * >
{
private:
  vrLoop() {}
  vrLoop& operator=(const vrLoop& l) { return *this; }

  vrFace        *face;

public:
	//<doc>------------------------------------------------------------
	// <dd>The halfedge list.
	//
	// [defualt] Empty
	//
  vrHalfEdgeList       halfedges;

	//<doc>------------------------------------------------------------
	// <dd>Copy Constructor.
	//
	vrLoop                  (const vrLoop& l);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] f: The face to which this loop belongs.
	// [in] isOuter: TRUE if this loop is the outer loop of the face.
	//
	vrLoop                  (vrFace *f, SFBool isOuter=TRUE);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	//
	~vrLoop                  ();

	//<nodoc>------------------------------------------------------------
	// <dd>Future use in copy constructor.
	//
	//  void      RemapPointers         (CMapPtrToPtr *map);

	//<doc>------------------------------------------------------------
	// <dd>Set this loop's vrFace pointer.
	//
	// [in] f: The face to set.
	//
  void      SetFace               (vrFace *f);

	//<doc>------------------------------------------------------------
	// <dd>Set the first halfedge in the vrLoop.
	//
	// [in] he: The halfedge to make the head of the list.
	//
  void      SetFirstHe            (vrHalfEdge *he);

	//<doc>------------------------------------------------------------
	// <dd>Add a halfedge to the end of the list.
	//
	// [in] he: The halfedge to add.
	//
  void      AddHalfEdge           (vrHalfEdge *he);

	//<doc>------------------------------------------------------------
	// <dd>Add a halfedge to the end of the list before the given halfedge.
	//
	// [in] before: The halfedge to add 'he' after.
	// [in] he: The halfedge to add.
	//
  void      AddHalfEdge           (vrHalfEdge *before, vrHalfEdge *he);

	//<doc>------------------------------------------------------------
	// <dd>Return the loop's verticies in the given array.  Returns TRUE if the verticies fit into the array.
	//
	// [in/out] max: The number of vecs that can be added.
	// [out] vecs: The memory location into which to copy the verticies.  If NULL, max returns the required number of verticies.
	//
	SFBool GetVertexLocations(Uint32& max, SFVec3f *vecs) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the vrFace to which this loop belongs.
	//
  vrFace     *GetFace               (void)                                        const;

	//<doc>------------------------------------------------------------
	// <dd>Return the first vrHalfEdge in this loop.
	//
  vrHalfEdge *GetFirstHe            (void)                                        const;

	//<doc>------------------------------------------------------------
	// <dd>Return the vrSolid to which this loop belongs.
	//
  vrSolid    *GetSolid              (void)                                        const;

	//<doc>------------------------------------------------------------
	// <dd>Return the halfedge in this loop that is closest (Euclidian distance to the halfedge's vertex) to the given he.
	//
  vrHalfEdge *GetNearest            (vrHalfEdge *he)                                const;

	//<doc>------------------------------------------------------------
	// <dd>Return TRUE if this loop is the face's outer loop.
	//
  SFBool   isOuterLoop           (void)                                        const;

	//<doc>------------------------------------------------------------
	// <dd>Return TRUE area represented by this loop.
	//
  SFFloat   Area                  (void)                                        const;
  
/*
	//<nodoc>------------------------------------------------------------
	// <dd>Future use.
	//
  SFBool   hasColinearVerts      (vrHalfEdge **he=NULL)                          const; 

	//<nodoc>------------------------------------------------------------
	// <dd>Future use.
	//
  void      RemoveColinearVertex  (vrHalfEdge *he); 
*/

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the vertex is 'inside' this loop.  Returns intersection information in the vrIntersectRecord.
	//
	// [in] v: The query vertex.
	// [in] rec: A location in which to return information about the intersection.
	//
  SFBool   BoundaryContains      (vrVertex *v, vrIntersectRecord& rec)             const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the loop contains the vertex.  Returns intersection information in the vrIntersectRecord.
	//
	// [in] v: The query vertex.
	// [in] rec: A location in which to return information about the intersection.
	//
  SFBool   Contains              (vrVertex *v, SFInt32 drop, vrIntersectRecord& rec) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the loop contains the vertex.  Returns intersection information in the vrIntersectRecord.
	//
	// [in] v: The query vertex.
	//
  SFBool   CheckForContainment   (const SFVec3f& v, SFInt32 drop) const;

	//<doc>------------------------------------------------------------
	// <dd>Remove the he from this loop.
	//
	// [in] he: The he to remove.
	//
  void      RemoveHe              (vrHalfEdge *he);

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
typedef vrIntrusiveList<vrLoop *> vrLoopList;

/***********************************************************************/
inline void vrLoop::SetFace(vrFace *f)
{
  ASSERT(f);
  face = f;
}

inline void vrLoop::SetFirstHe(vrHalfEdge *he)
{
  // he may be NULL.
  halfedges.SetHead(he);
}

/***********************************************************************/
inline vrFace *vrLoop::GetFace(void) const
{
  return face;
}

#endif
