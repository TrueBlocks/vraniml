#ifndef __BOOL_H3D
#define __BOOL_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "..\..\Solid.h"
#include "..\Stats.h"

#define BIGEPS       ((SFFloat)(0.00001*100.0f))
#define EPS_SQUARED  ((SFFloat)(0.00001*0.00001))

#undef ABOVE
#define IN -1
#undef BELOW
#define OUT 1

#ifdef _DEBUG
// Don't care
#define DC  2
#endif

/***********************************************************************/
typedef struct
{
  vrVertex *va;
  vrVertex *vb;
} vrVertexVertexRecord;

/***********************************************************************/
typedef struct
{
  vrVertex *v;
  vrFace   *f;
} vrVertexFaceRecord;

/***********************************************************************/
class vrBoolopRecord
{
  Uint32             nVertsV;
  vrVertexVertexRecord vertsV[MAX_ON_VERTS];

  Uint32             nVertsA;
  Uint32             nVertsB;
  vrVertexFaceRecord   vertsA[MAX_ON_VERTS];
  vrVertexFaceRecord   vertsB[MAX_ON_VERTS];

  Uint32             nEdgesA;
  Uint32             nEdgesB;
  vrEdge              *edgesA[MAX_NULL_EDGES];
  vrEdge              *edgesB[MAX_NULL_EDGES];

  Uint32             nFacesA;
  Uint32             nFacesB;
  vrFace              *facesA[MAX_NEW_FACES*2];
  vrFace              *facesB[MAX_NEW_FACES*2];

  vrSolid             *A;
  vrSolid             *B;

  vrSolid            **result;

  SFInt32               op;

public:
	SFBool             noVV;
	SFBool             quit;

#ifdef _STATS
	CStatistics       *stats;
#endif

                 vrBoolopRecord  (void);
                ~vrBoolopRecord  ();

  void    Reset         (vrSolid *a, vrSolid *b, vrSolid **res, SFInt32 operation);

  void    Generate      (void);
  void    ProcessEdge   (vrSolid *s, vrEdge *e);
  void    DoGenerate    (vrEdge *e, vrFace *f);
  void    VertexOnFace  (vrVertex *v, vrFace *f);

  SFBool Classify      (void);
  SFBool LastDitch     (void);

  void    Connect       (void);
  SFBool NextNullEdge  (vrEdge **ea, vrEdge **eb) const;
  void    SortNullEdges (void);
  void    BoolSwap      (Uint32 i, Uint32 j);
  
  void    Finish        (void);
  
  void    Complete      (void);
  
  void    AddVertVert   (vrVertex *v1, vrVertex *v2, SFBool BvsA);
  void    AddVertFace   (vrVertex *v, vrFace *f, SFBool BvsA);
  void    AddEdgeA      (vrEdge *e);
  void    AddEdgeB      (vrEdge *e);
  void    AddFaceA      (vrFace *fac);
  void    AddFaceB      (vrFace *fac);
  
  /* Gets */
  vrVertex *GetVertVertA  (Uint32 i) const;
  vrVertex *GetVertVertB  (Uint32 i) const;
  vrFace   *GetFaceA      (Uint32 i) const;
  vrFace   *GetFaceB      (Uint32 i) const;
  vrVertex *GetVertA      (Uint32 i) const;
  vrVertex *GetVertB      (Uint32 i) const;
  SFBool GetOperation  (void)     const;

	friend class vrBoolVertVertClassifyRecord;

#ifdef _DEBUG
  void    Show          (vrDumpContext& dc)     const;
  void    Show1         (vrDumpContext& dc)     const;
#endif
};

inline vrBoolopRecord::vrBoolopRecord(void)
{
  nVertsV = 0;
  nVertsA = 0;
  nVertsB = 0;
  nEdgesA = 0;
  nEdgesB = 0;
  nFacesA = 0;
  nFacesB = 0;

  A = NULL;
  B = NULL;

  result = NULL;

  op = 0;
	noVV = TRUE;
	quit=FALSE;
	stats=NULL;
}

inline vrBoolopRecord::~vrBoolopRecord()
{
}

inline void vrBoolopRecord::Reset(vrSolid *a, vrSolid *b, vrSolid **res, SFInt32 operation)
{
  nVertsV = 0;
  nVertsA = 0;
  nVertsB = 0;
  nEdgesA = 0;
  nEdgesB = 0;
  nFacesA = 0;
  nFacesB = 0;

  A = a;
  B = b;

  result = res;

  op = operation;
	noVV = TRUE;
	quit=FALSE;
}

inline void vrBoolopRecord::BoolSwap(Uint32 i, Uint32 j)
{
	vrEdge *tmp = edgesA[i];
  edgesA[i] = edgesA[j];
  edgesA[j] = tmp;
  
  tmp = edgesB[i];
  edgesB[i] = edgesB[j];
  edgesB[j] = tmp;

  // Note: The location of these Null Edges should be the same (since
	//		we've inserted a null edge into both solids whereever there was an
	//		interaction).  Remember that which vertex we check is unimportant
	//		because this is a Null Edge.
	ASSERT(*edgesB[i]->GetVertex(HE1) == *edgesA[i]->GetVertex(HE1));
	ASSERT(*edgesB[j]->GetVertex(HE2) == *edgesA[j]->GetVertex(HE2));
}

inline vrVertex *vrBoolopRecord::GetVertVertA(Uint32 i) const
{
	ASSERT(i < nVertsV);
  return vertsV[i].va;
}

inline vrVertex *vrBoolopRecord::GetVertVertB(Uint32 i) const
{
	ASSERT(i < nVertsV);
  return vertsV[i].vb;
}

inline vrFace *vrBoolopRecord::GetFaceA(Uint32 i) const
{
	ASSERT(i < nVertsA);
  return vertsA[i].f;
}

inline vrFace *vrBoolopRecord::GetFaceB(Uint32 i) const
{
	ASSERT(i < nVertsB);
  return vertsB[i].f;
}

inline vrVertex *vrBoolopRecord::GetVertA(Uint32 i) const
{
	ASSERT(i < nVertsA);
  return vertsA[i].v;
}

inline vrVertex *vrBoolopRecord::GetVertB(Uint32 i) const
{
	ASSERT(i < nVertsB);
  return vertsB[i].v;
}

inline SFBool vrBoolopRecord::GetOperation(void) const
{
  return op;
}

inline void vrBoolopRecord::AddFaceA(vrFace *fac)
{
  ASSERT(nFacesA < MAX_NEW_FACES);
  facesA[nFacesA++] = fac;
}

inline void vrBoolopRecord::AddFaceB(vrFace *fac)
{
  ASSERT(nFacesB < MAX_NEW_FACES);
  facesB[nFacesB++] = fac;
}

/*
 * This macro simple renumbers solid B so it's indicies start at 100.  This
 * makes it easier to distinquish between the two solids when debugging 
 */
#ifdef _DEBUG
#define RENUM(tttt, nnnn, llll) \
  { \
    SFInt32 i=(nnnn); \
    LISTPOS pos = llll.GetHeadPosition(); \
    while(pos) { \
      tttt *x = llll.GetNext(pos); \
      x->SetIndex(i++); \
    } \
    (llll).SetNextIndex(i); \
  }
#endif

#ifdef _DEBUG
#define DEBEDGES(ssss, e1, e2) \
{ \
  VRTRACE("%s [%d] A:(%3d(% 3d) %3d(% 3d)) -- B:(%3d(% 3d) %3d(% 3d)) outer: %d %d %d %d\n", \
  ssss, \
  (e1)->GetIndex(), \
  (e1)->GetVertexIndex(HE1), \
  (e1)->GetHe(HE1)->cl, \
  (e1)->GetVertexIndex(HE2), \
  (e1)->GetHe(HE2)->cl, \
  (e2)->GetVertexIndex(HE1), \
  (e2)->GetHe(HE1)->cl, \
  (e2)->GetVertexIndex(HE2), \
  (e2)->GetHe(HE2)->cl, \
  (e1)->GetLoop(HE1)->isOuterLoop(), \
  (e1)->GetLoop(HE2)->isOuterLoop(), \
  (e2)->GetLoop(HE1)->isOuterLoop(), \
  (e2)->GetLoop(HE2)->isOuterLoop()); \
}
#else
#define DEBEDGES(a, b, c)
#endif
#undef DEBEDGES
#define DEBEDGES(a, b, c)

#define DEBBB(he1, he2, sss)
#if 0
 \
  do { \
    VRTRACE("%s[%d %d+%d %d sc: %d]\n", sss, \
    he1->mark2, \
    he1->GetMate()->mark2, \
    he2->mark2, \
    he2->GetMate()->mark2, \
    SpecialCase(he1, he2)); \
  } while (0);
#endif
      
static char cla[][5] = { "IN", "ON ", "OUT ", "DC " };

inline Uint32 NextNum(Uint32 n, Uint32 N)
{
	return ((n+1)%N);
}

inline Uint32 PrevNum(Uint32 n, Uint32 N)
{
	return ((n==0) ? N-1 : n-1);
}

#endif
