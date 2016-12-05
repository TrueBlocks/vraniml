#ifndef __SPLIT_H3D
#define __SPLIT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "..\..\solid.h"

/*********************************************************************/
class vrSplitRecord
{
	vrSolid       *s;					// The solid we are splitting
  vrPlane    SP;					// The splitting plane
  vrSolid      **A;					// The resulting solid A
  vrSolid      **B;					// The resulting solid A

  Uint32       nVerts;
  Uint32       nFaces;
  Uint32       nEdges;
  Uint32       nEnds;

  vrVertex      *verts[MAX_ON_VERTS];
  vrEdge        *edges[MAX_NULL_EDGES];
  vrFace        *faces[MAX_NEW_FACES*2];
  vrHalfEdge    *looseEnds[MAX_LOOSE_ENDS];

public:
             vrSplitRecord     (void);
            ~vrSplitRecord     ();
					 
  // Initialization
	void       Reset           (const vrPlane& sp, vrSolid *s, vrSolid **a, vrSolid **b);

  // 
	void       AddVert         (vrVertex *v);
  void       AddEdge         (vrEdge *e);
  void       AddFace         (vrFace *f);
  void       AddLooseEnd     (vrHalfEdge *he);
  
  // The four part algorigthm
	void       Generate        (void);
  SFBool    Classify        (void);
  void       Connect         (void);
	  SFBool    GetNextNullEdge (vrEdge **e);
	  SFBool    CanJoin         (vrHalfEdge *he, vrHalfEdge **ret);
  void       Finish          (void);
	  void       FinishClassify  (void);
  void       Complete        (void);
  

	SFVec3f   GetSPNormal       (void)     const;
	vrPlane GetSplittingPlane (void)     const;
	vrVertex    *GetVert           (Uint32 i) const;

#ifdef _DEBUG
  void    Show            (vrDumpContext& dc)     const;
  void    Verify          (void)     const;
#endif
};

inline SFVec3f vrSplitRecord::GetSPNormal(void) const
{
	return SP.GetNormal();
}

inline vrPlane vrSplitRecord::GetSplittingPlane(void) const
{
	return vrPlane(SP);
}

inline vrVertex *vrSplitRecord::GetVert(Uint32 i) const
{
	ASSERT(i < nVerts);
	return verts[i];
}

inline vrSplitRecord::vrSplitRecord(void) :
  SP(0.0f, 0.0f, 0.0f, 0.0f)
{
  nVerts = 0;
  nEdges = 0;
  nFaces = 0;
  nEnds  = 0;
  A      = NULL;
  B      = NULL;
  s      = NULL;
}

inline vrSplitRecord::~vrSplitRecord()
{
}

inline void vrSplitRecord::Reset(const vrPlane& sp, vrSolid *sol, vrSolid **a, vrSolid **b)
{
  SP     = vrPlane(sp.GetNormal(), sp.GetD());

  nVerts = 0;
  nEdges = 0;
  nFaces = 0;
  nEnds  = 0;
  s  = sol;
  A  = a;
  B  = b;
  *A = NULL;
  *B = NULL;
}

inline void vrSplitRecord::AddEdge(vrEdge *e)
{
  ASSERT(e);

  ASSERT(nEdges < MAX_NULL_EDGES);
  edges[nEdges++] = e;
}

inline void vrSplitRecord::AddFace(vrFace *fac)
{
  ASSERT(fac);
  ASSERT(nFaces < MAX_NEW_FACES);
  faces[nFaces++] = fac;
}

#endif
