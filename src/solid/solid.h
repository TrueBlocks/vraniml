#ifndef __SOLID_H3D
#define __SOLID_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"
#include "Decls.h"

#define MAX_ON_VERTS     1000
#define MAX_NULL_EDGES   1000
#define MAX_NEW_FACES    1000
#define MAX_LOOSE_ENDS   1000
#define MAX_UNDO_RECORDS  500

#include "Face.h"
#include "Edge.h"
#include "Vertex.h"
#include "Algorithms\Undo.h"

/*----------------------------------------------------------------------
CLASS
	vrSolid - the basis for all geometry nodes, this class stores all
	geometry data.  It also serves as the basis for support for
	advanced algorithms.

DESCRIPTION
	<ul>
	The vrSolid class implements 'solid modeling' using a data structures
	called the half edge.  The half edge data structure is described
	in the 3D liturature.
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
class LIBInterface vrSolid : public vrBaseNode 
{
private:
	//<doc>------------------------------------------------------------
	//<dd>Temporary data used to mark this solid during certain algorithms.
	//
	// [default] DC
	//
  Uint32                m_Mark;

public:
	//<doc>------------------------------------------------------------
	//<dd>The list of faces making up this solid.
	//
	// [default] empty
	//
  vrFaceList            faces;

	//<doc>------------------------------------------------------------
	//<dd>The list of edges making up this solid.
	//
	// [default] empty
	//
  vrEdgeList            edges;

	//<doc>------------------------------------------------------------
	//<dd>The list of verticies making up this solid.
	//
	// [default] empty
	//
  vrVertexList          verts;

	//<doc>------------------------------------------------------------
	//<dd>The default color of this solid (if not found per vertex or per face).
	//
	// [default] vrBlack
	//
	SFBool                m_SolidColor;

	//<nodoc>------------------------------------------------------------
	//<dd>Future use for optimization, contains a pointer to a vertex array if this solid has been optimized.
	//
	// [default] NULL 
	//
	//	vrVertexArray           *m_Strips;

public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrSolid(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	// [in] s: The solid to copy.
	//
	vrSolid(const vrSolid& s);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
  ~vrSolid(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	// [in] s: The solid to copy.
	//
	vrSolid& operator=(const vrSolid& s);

	//<doc>------------------------------------------------------------
	// <dd>Creates a clone of this solid.
	//
	vrBaseNode *Clone(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] x, y, z: Initial location of first vertex of the new solid.
	//
	vrSolid(SFFloat x, SFFloat y, SFFloat z);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] v: Initial location of first vertex of the new solid.
	//
	vrSolid(const SFVec3f& v);

	//<doc>------------------------------------------------------------
	// <dd>Change the mark of this solid.
	//
	// [in] mark: the new mark.
	//
  void SetMark(Uint32 mark);

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this solid is marked with 'mark'.
	//
	// [in] mark: the test mark.
	//
  SFBool Marked(Uint32 mark) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns the current mark of this solid.
	//
  Uint32 GetMark(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Set's the mark of each face in this solid with 'mark'.
	//
	// [in] mark: the mark.
	//
  void SetFaceMarks(Uint32 mark);

	//<doc>------------------------------------------------------------
	// <dd>Set's the mark of each vertex in this solid with 'mark'.
	//
	// [in] mark: the mark.
	//
  void SetVertexMarks(Uint32 mark);

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this solid is a Wire (i.e. like a loosened hanger for example).
	//
	SFBool isWire(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if this solid is a Lamina (i.e. has no volume - like a flattened basketball).
	//
  SFBool isLamina(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns a pointer to the face with the given ID or NULL.
	//
	// [in] faceID: The face to find.
	//
	vrFace *findFace(Uint32 faceID) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns a pointer to the vertex with the given ID or NULL.
	//
	// [in] vertexID: The vertex to find.
	//
  vrVertex *findVertex(Uint32 vertexID) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns a pointer to the edge with the given ID or NULL.
	//
	// [in] edgeID: The edge to find.
	//
  vrEdge *findEdge(Uint32 edgeID) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns a pointer to the half edge in the given face that connects vertex 'v1' and vertex 'v2' or NULL.
	//
	// [in] f: The face to search.
	// [in] v1: The vertex from which the half edge eminates.
	// [in] v2: The vertex to which the half edge goes.
	//
  vrHalfEdge *findHalfEdge(vrFace *f, Uint32 v1, Uint32 v2) const;

	//<doc>------------------------------------------------------------
	// <dd>Returns a pointer to the half edge in the given face that starts at vertex 'v1' or NULL.
	//
	// [in] f: The face to search.
	// [in] v1: The vertex from which the half edge eminates.
	//
  vrHalfEdge *findHalfEdge(vrFace *f, Uint32 v1) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the maximum and minimum extents of the solid.
	//
	// [out] minn: The smallest x,y,z components in this solid.
	// [out] maxx: The largest x,y,z components in this solid.
	//
	SFVec3f Extents(SFVec3f& minn, SFVec3f& maxx) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the volume enclosed by the solid.
	//
  SFFloat Volume(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the surface area of the solid.
	//
  SFFloat Area(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return statistics about the solid.
	//
	// [out] nVerts: The number of verticies in this solid.
	// [out] nEdges: The number of edges in this solid.
	// [out] nFaces: The number of faces in this solid.
	// [out] nLoops: The number of loops in this solid.
	// [out] nHalfEdges: The number of half edges in this solid.
	//
  SFVec3f Stats(Uint32& nVerts, Uint32& nEdges, Uint32& nFaces, Uint32& nLoops, Uint32& nHalfEdges) const;

	//<doc>------------------------------------------------------------
	// <dd>Return TRUE if this solid completly contains (or is equal to) solid 'B'.
	//
  SFBool Contains(vrSolid *B) const;

	//<doc>------------------------------------------------------------
	// <dd>Add a face to this solid.
	//
	// [in] f: The face to add.
	//
	void AddFace(vrFace *f);

	//<doc>------------------------------------------------------------
	// <dd>Add an edge to this solid.
	//
	// [in] e: The edge to add.
	//
  void AddEdge(vrEdge *e);

	//<doc>------------------------------------------------------------
	// <dd>Add a vertex to this solid.
	//
	// [in] v: The vertex to add.
	//
  void AddVertex(vrVertex *v);

	//<doc>------------------------------------------------------------
	// <dd>Create a solid from a list of verticies and indicies (such as one might get from a VRML IndexedFaceSet).
	//
	// [in] verticies: A list of verticies.
	// [in] indicies: Indicies into the list of verticies defining the faces of the solid.
	//
	void BuildFromIndexSet(const vrVertexArray& verticies, const MFInt32& indicies);

	//<doc>------------------------------------------------------------
	// <dd>Calculate the plane equations for all faces in this solid.
	//
	void CalcPlaneEquations(void);

	//<doc>------------------------------------------------------------
	// <dd>Mark edges where neighboring faces form an angle greater than or equal to 'crease'.
	//
	// [in] crease: The angle above which a crease in the model is found.
	//
	void MarkCreases(SFFloat crease);

	//<doc>------------------------------------------------------------
	// <dd>Triangulate the faces of the solid.
	//
	void Triangulate(void);

	//<doc>------------------------------------------------------------
	// <dd>Merge two solids into one (copying 's2', which should be deleted when not in use).
	//
	// [in] s2: The solid to merge into this solid.
	//
  void Merge(vrSolid *s2);

	//<doc>------------------------------------------------------------
	// <dd>Modify each vertex in the solid by the matrix 'm'.
	//
	// [in] m: The matrix with which to transform the verticies.
	//
  void TransformGeometry(const vrMatrix& m);

	//<doc>------------------------------------------------------------
	// <dd>Modify each vertex in the solid by the matrix 'm' which would be formed by a translation of x,y,z.
	//
	// [in] x,y,z: The translation with which to transform the verticies.
	//
	void TransformGeometry(SFFloat x, SFFloat y, SFFloat z);

	//<doc>------------------------------------------------------------
	// <dd>
	//
  // [in] f:
	// [in] v:
	// [in] cx:
	// [in] cy:
	// [in] rad:
	// [in] h:
	// [in] phi1:
	// [in] ph2:
	// [in] n:
	//
  void Arc(Uint32 f, Uint32 v, SFFloat cx, SFFloat cy, SFFloat rad, SFFloat h, SFFloat phi1, SFFloat ph2, Uint32 n);

	//<doc>------------------------------------------------------------
	// <dd>Perform a translational sweep along an arc defined by 'v'.
	//
  // [in] f: The face to sweep.
	// [in] n: The number of verticies in 'v'.
	// [in] v: The array of verticies to sweep the face along.
	//
  void ArcSweep(vrFace *f, Uint32 n, const SFVec3f v[]);

	//<doc>------------------------------------------------------------
	// <dd>Perform a translational sweep of face 'f' along the vector 'v'.
	//
  // [in] f: The face to sweep.
	// [in] v: The vector to sweep the face along.
	//
  void TranslationalSweep(vrFace *f, const SFVec3f& v);

	//<doc>------------------------------------------------------------
	// <dd>Perform a rotational sweep around the zaxis in 'nFaces' steps.
	//
  // [in] nFaces: The number of steps to take in the sweep.
	//
  void RotationalSweep(Uint32 nFaces);

	//<doc>------------------------------------------------------------
	// <dd>Perform a rotational sweep around the zaxis in 'nFaces' steps of a wire. (Note: if solid is not a wire nothing happens).
	//
  // [in] nFaces: The number of steps to take in the sweep.
	//
  vrFace *SweepWire(Uint32 nFaces);

	//<doc>------------------------------------------------------------
	// <dd>Modify the verticies in the solid by applying 'func' (a function that takes a 'z' coordinate and returns a modified 'z' coordinate) to each 'z' coord.
	//
  // [in] func: The function (taking an SFFloat and returning an SFFloat) to apply to each 'z' coordinate.
	//
  void Twist(PFF func);

	//<doc>------------------------------------------------------------
	// <dd>Merge all verticies of the given face into a single vertex and remove the face.
	//
  // [in] f: The face to collapse.
	//
  void CollapseFace(vrFace *f);

	//<doc>------------------------------------------------------------
	// <dd>Remove coplaner neighboring faces and colinear neighboring edges.
	//
	void RemoveCoplaneColine(void);

	//<doc>------------------------------------------------------------
	// <dd>Split this solid into two at the splitting plane (SP).  Return
	// <dd>the 'Above' (ie on same side as plane normal) and 'Below' solids.
	// <dd>(Note: if splitting plane does not cross the solid return FALSE and this solid is untouched).
	//
	// [in] SP: The splitting plane to split this solid.
	// [out] Above: A pointer to a pointer to a solid into which to place the solid that is split above the splitting plane.
	// [out] Below: A pointer to a pointer to a solid into which to place the solid that is split below the splitting plane.
	//
	SFBool Split(const vrPlane& SP, vrSolid **Above, vrSolid **Below);

	//<doc>------------------------------------------------------------
	// <dd>Perform on of the valid boolean operations (UNION, DIFFERENCE, INTERSECTION)
	// <dd>on this solid with the given solid.  Return the result in 'result'.  If stats is
	// <dd>non-NULL record information about the operation for debugging.
	// <dd>The equation of the operation is A op B where op is UNION, DIFFERENCE or INTERSECTION).
	//
	// [in] A: The first solid in the above equation.
	// [in] B: The second solid in the above equation.
	// [out] result: A pointer to a pointer to a solid into which to place the result of the operation.
	// [out] stats: A pointer to a vrStatistics structure into which to copy statistics about the operation (usually NULL except during debugging).
	//
  SFBool BoolOp(vrSolid *A, vrSolid *B, vrSolid **result, SFInt32 op, void *statRec);

	//<doc>------------------------------------------------------------
	// <dd>Perform the UNION operation on this solid.  This solid serves as the A solid. (see BoolOp).
	//
	// [in] B: The second solid in the above equation.
	// [out] result: A pointer to a pointer to a solid into which to place the result of the operation.
	// [out] stats: A pointer to a vrStatistics structure into which to copy statistics about the operation (usually NULL except during debugging).
	//
  SFBool Union(vrSolid *B, vrSolid **result, void *statRec=NULL);

	//<doc>------------------------------------------------------------
	// <dd>Perform the INTERSECTION operation on this solid.  This solid serves as the A solid. (see BoolOp).
	//
	// [in] B: The second solid in the above equation.
	// [out] result: A pointer to a pointer to a solid into which to place the result of the operation.
	// [out] stats: A pointer to a vrStatistics structure into which to copy statistics about the operation (usually NULL except during debugging).
	//
  SFBool Intersection(vrSolid *B, vrSolid **result, void *statRec=NULL);

	//<doc>------------------------------------------------------------
	// <dd>Perform the DIFFERENCE operation on this solid.  This solid serves as the A solid. (see BoolOp).
	//
	// [in] B: The second solid in the above equation.
	// [out] result: A pointer to a pointer to a solid into which to place the result of the operation.
	// [out] stats: A pointer to a vrStatistics structure into which to copy statistics about the operation (usually NULL except during debugging).
	//
  SFBool Difference(vrSolid *B, vrSolid **result, void *statRec=NULL);

	//<doc>------------------------------------------------------------
	// <dd>Cleanup the solid (i.e. given vertices and faces rebuild all other components).  Not used except by BoolOp operators.
	//
	void Cleanup(void);

	//<doc>------------------------------------------------------------
	// <dd>Renumber all objects in the solid (for presentation for example).
	//
  void Renumber(void);

	//<doc>------------------------------------------------------------
	// <dd>Turn the solid inside out -- re-order all faces.
	//
  void Revert(void);

	//<doc>------------------------------------------------------------
	// <dd>Write the file to the given fp.
	//
	// [in] fp: The file to write to.
	// [in] forward: order the verticies forward or backward (ie. clockwise or counterclockwise).
	//
  SFBool Write(FILE *fp, SFBool forward=FALSE) const;

	//<doc>------------------------------------------------------------
	// <dd>Set the color of all faces in this solid.
	//
	// [in] color: The new color.
	//
	void SetColor(const SFColor& color);

  //----------------------------------------------------------
	// The remainder of the functions for this class are used
	// by internal algorithms only and are not documented.
	//
	void        Join               (vrHalfEdge *he1, vrHalfEdge *he2, SFBool swap);
  vrFace     *Cut                (vrHalfEdge *he1, SFBool BvsA);
  void        Glue               (vrSolid *s2, vrFace *f1, vrFace *f2);
  void        LoopGlue           (vrFace *f);
  void        MoveFace           (vrFace *f, vrSolid *s);

	void        RemoveVertexAtIndex(Uint32 index);
	void        RemoveVertexAtPt   (const SFVec3f& pos);
	void        RemoveFaceAtIndex  (Uint32 index);

	vrFace     *GetFirstFace       (void) const;
	vrEdge     *GetFirstEdge       (void) const;
	vrVertex   *GetFirstVertex     (void) const;

  // Low level euler operators
  vrVertex   *lmev               (vrHalfEdge *he1, vrHalfEdge *he2, SFFloat x, SFFloat y, SFFloat z);
  vrVertex   *lmev               (vrHalfEdge *he1, vrHalfEdge *he2, const SFVec3f& v);
  vrFace     *lmef               (vrHalfEdge *he1, vrHalfEdge *he2);
  vrFace     *lmfkrh             (vrLoop *l);
  void        lmekr              (vrHalfEdge *he1, vrHalfEdge *he2);
  void        lkef               (vrHalfEdge *he1, vrHalfEdge *he2);
	void        lkev               (vrHalfEdge *he1, vrHalfEdge *he2);
  void        lkvfs              (void);
  void        lkemr              (vrHalfEdge *he1, vrHalfEdge *he2);
  void        lkfmrh             (vrFace *f1, vrFace *f2);
  void        lringmv            (vrLoop *l, vrFace *toFace, SFBool isOuter);
  void        laringmv           (vrFace *f1, vrFace *f2);
  SFBool      smev               (Uint32 f,  Uint32 v1, SFFloat x, SFFloat y, SFFloat z);
  SFBool      smef               (Uint32 f,  Uint32 v1, Uint32 v3);

  // Higher level euler operators (take vertex labels as input)
	SFBool      mev                (Uint32 f1, Uint32 f2, Uint32 v1, Uint32 v2, Uint32 v3,SFFloat x, SFFloat y, SFFloat z);
  SFBool      kev                (Uint32 f,  Uint32 v1, Uint32 v2);
  SFBool      kev2               (vrHalfEdge *he1, vrHalfEdge *he2);
  SFBool      mef                (Uint32 f,  Uint32 v1, Uint32 v2, Uint32 v3, Uint32 v4);
  SFBool      kef                (Uint32 f,  Uint32 v1, Uint32 v2);
  SFBool      kemr               (Uint32 f,  Uint32 v1, Uint32 v2);
  SFBool      mekr               (Uint32 f,  Uint32 v1, Uint32 v2, Uint32 v3, Uint32 v4);
  SFBool      kfmrh              (Uint32 f1, Uint32 f2);
  SFBool      mfkrh              (Uint32 f,  Uint32 v1, Uint32 v2);
  SFBool      ringmv             (Uint32 f1, Uint32 f2, Uint32 v1, Uint32 v2, SFBool inout);
  void        kvfs               (void);
  void        mvfs               (SFFloat x, SFFloat y, SFFloat z);
  void        mvfs               (const SFVec3f& vv);

public:
/*
	void           RemoveDegenerateFaces(void);
  SFBool         hasDegenerateFaces   (vrFace **faceOut=NULL) const;

  void			     Import					      (FILE *fp);

	//	void           SetFirstFace         (vrFace *f);
	//	void           SetFirstEdge         (vrEdge *e);
	//	void           SetFirstVertex       (vrVertex *v);
*/

#ifdef _DEBUG
  void      Show  (vrDumpContext& dc) const;
  void      Verify(void) const;
/*
private:
  // should we perform verification after ever euler op?
  SFBool        check_eulers;
*/
#endif

private :
/*
  SFBool        hasCoplanarFaces     (void)                                 const; 
  SFBool        hasColinearVerts     (void)                                 const; 
  void          RemoveCoplanarFaces  (void); 
  void          RemoveColinearVerts  (void); 
*/

#ifdef ENABLE_UNDO
/*
private:
  SFBool                generateUndoLog;
  vrEulerOpList         undoLog;
  vrTransactionLog      transLog;

public:
  void      Invert           (FILE *fp);
  void      RemoveEdges      (void);
  void      RemoveFaces      (void);

  void      BeginTransaction (void);
  void      EndTransaction   (void);
  void      UndoTransaction  (void);

  void      UndoEulerOp      (void);

  void      AddUndoRecord    (Uint32 op, 
															 Uint32 i1, Uint32 i2, 
															 Uint32 i3  = 0,   Uint32 i4  = 0, 
															 Uint32 i5  = 0,   Uint32 i6  = 0, 
															 SFFloat f1 = 0.0, SFFloat f2 = 0.0, 
															 SFFloat f3 = 0.0, SFFloat f4 = 0.0);
*/
#endif
};

SFBool Intersects(vrVertex *v1, vrVertex *v2, vrVertex *v3, SFFloat& t);
SFBool Intersects(vrVertex *v1, vrVertex *v2, vrVertex *v3, vrVertex *v4, SFInt32 drop, SFFloat& t1, SFFloat& t2);

inline Uint32 vrSolid::GetMark(void) const
{
  return m_Mark;
}

inline SFBool vrSolid::Marked(Uint32 m) const
{
  return (m_Mark == m);
}

inline void vrSolid::SetMark(Uint32 m)
{
  m_Mark = m;
}

inline SFBool vrSolid::isWire(void) const
{
  return (faces.GetCount() == 1);
}

inline SFBool vrSolid::isLamina(void) const
{
  return (faces.GetCount() == 2);
}

inline void vrSolid::TransformGeometry(SFFloat x, SFFloat y, SFFloat z)
{
	TransformGeometry(TranslationMatrix(SFVec3f(x, y, z)));
}

inline vrFace *vrSolid::GetFirstFace(void) const
{
	return faces.GetHead();
}

inline vrEdge *vrSolid::GetFirstEdge(void) const
{
	return edges.GetHead();
}

inline vrVertex *vrSolid::GetFirstVertex(void) const
{
	return verts.GetHead();
}

inline vrVertex *vrSolid::lmev(vrHalfEdge *he1, vrHalfEdge *he2, const SFVec3f& vv)
{
  return lmev(he1, he2, vv.x, vv.y, vv.z);
}

inline void vrSolid::mvfs(const SFVec3f& vv)
{
  mvfs(vv.x, vv.y, vv.z);
}

#ifndef ENABLE_UNDO
inline void AddUndoRecord(Uint32 op, Uint32 i1, Uint32 i2, 
														 Uint32 i3  = 0,   Uint32 i4  = 0, 
														 Uint32 i5  = 0,   Uint32 i6  = 0, 
														 SFFloat f1 = 0.0, SFFloat f2 = 0.0, 
														 SFFloat f3 = 0.0, SFFloat f4 = 0.0)
{
}
#endif

#endif