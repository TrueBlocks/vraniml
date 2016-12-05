//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"

Uint32    nEndsA;
Uint32    nEndsB;
vrHalfEdge *EndsA[MAX_LOOSE_ENDS];
vrHalfEdge *EndsB[MAX_LOOSE_ENDS];

SFBool CanJoin(vrHalfEdge *hea, vrHalfEdge *heb, vrHalfEdge **reta, vrHalfEdge **retb);
SFBool SpecialCase(vrHalfEdge *he1, vrHalfEdge *he2);

class vrHackThing
{
public:
  vrHalfEdge *hes[4];
  SFBool   cl[4];
};
vrHackThing thing[MAX_NULL_EDGES];

inline void DEBLOOSEENDS(vrHalfEdge *hea, vrHalfEdge *heb, const SFString& s)
{
	VRTRACE("%s", s);
	VRTRACE("\t\t\tA: %3d", hea->GetFace()->GetIndex()); DEBHE(hea, "");
	VRTRACE("  B: %3d", heb->GetFace()->GetIndex()); DEBHE(heb, ""); VRTRACE("\n");
}

inline void DEBENDS(const SFString& s)
{
VRTRACE("Loose Ends %s", (const char *)s);
	for (Uint32 n=0;n<nEndsA;n++)
	{
		vrHalfEdge *ha = EndsA[n];
		vrHalfEdge *hb = EndsB[n];
		DEBLOOSEENDS(ha, hb, "");
	}
}

/*********************************************************************/
void vrBoolopRecord::Connect(void)
{
//afxTraceEnabled = TRUE;
//DEB(this, "Before Connect");

  ASSERT(A->Marked(SOLID_A));
  ASSERT(B->Marked(SOLID_B));
  
  nFacesA = nFacesB = 0;
  nEndsA  = nEndsB  = 0;

  SortNullEdges();
//DEB(this, "After SortNullEdges");

  vrEdge *edgeA=NULL, *edgeB=NULL;
	while (NextNullEdge(&edgeA, &edgeB))
	{
    vrHalfEdge *outA = edgeA->GetHe(HE1);
    vrHalfEdge *inB  = edgeB->GetHe(HE2);
		vrHalfEdge *inA  = edgeA->GetHe(HE2);
    vrHalfEdge *outB = edgeB->GetHe(HE1);

//DEBLOOSEENDS(outA, inB,  "outA| inB :");
//DEBLOOSEENDS(inA,  outB, "inA | outB:");

#ifdef _DEBUG
//    ASSERT(outA->cl == OUT);
//    ASSERT(inB->cl == IN);
#endif

	  vrHalfEdge *joinInA, *joinOutA, *joinInB, *joinOutB;
    if (CanJoin(outA, inB, &joinInA, &joinOutB))
		{
#ifdef _DEBUG
//      ASSERT(joinInA->cl == IN);
//      ASSERT(joinOutB->cl == OUT);
#endif
      ASSERT(outA == edgeA->GetHe(HE1));
			A->Join(joinInA, outA, SpecialCase(joinInA, outA));
      if (!joinInA->GetMate()->Marked(LOOSE))
			{
				vrFace *f = A->Cut(joinInA, TRUE);
				if (f)
				{
					AddFaceA(f);
				}
      }

      ASSERT(inB == edgeB->GetHe(HE2));
			B->Join(joinOutB, inB, FALSE);
      if (!joinOutB->GetMate()->Marked(LOOSE))
			{
				vrFace *f = B->Cut(joinOutB, TRUE);
				if (f)
				{
					AddFaceB(f);
				}
      }
    }

#ifdef _DEBUG
//    ASSERT(inA->cl == IN);
//    ASSERT(outB->cl == OUT);
#endif

    if (CanJoin(inA, outB, &joinOutA, &joinInB))
		{
#ifdef _DEBUG
//      ASSERT(joinOutA->cl == OUT);
//      ASSERT(joinInB->cl == IN);
#endif

      ASSERT(inA == edgeA->GetHe(HE2));
      A->Join(joinOutA, inA, FALSE);
      if (!joinOutA->GetMate()->Marked(LOOSE))
			{
				vrFace *f = A->Cut(joinOutA, TRUE);
				if (f)
				{
					AddFaceA(f);
				}
      }

      ASSERT(outB == edgeB->GetHe(HE1));
		  B->Join(joinInB, outB, SpecialCase(joinInB, outB));
      if(!joinInB->GetMate()->Marked(LOOSE))
			{
				vrFace *f = B->Cut(joinInB, TRUE);
				if (f)
				{
					AddFaceB(f);
				}
      }
    }

    if (joinInA && joinInB && joinOutA && joinOutB)
		{
      ASSERT(outA == edgeA->GetHe(HE1));
			vrFace *f = A->Cut(outA, TRUE);
      if (f)
			{
				AddFaceA(f);
			}

      ASSERT(outB == edgeB->GetHe(HE1));
			f = B->Cut(outB, TRUE);
      if (f)
			{
				AddFaceB(f);
			}
    }

DEBENDS("After spin\n");
  }

DEBENDS("After spin\n");

  nEdgesA = nEdgesB = 0;

	// There should be no further loose ends
//	ASSERT(!nEndsA);
//	ASSERT(!nEndsB);

  return;
}

/*********************************************************************************/
SFBool vrBoolopRecord::NextNullEdge(vrEdge **ea, vrEdge **eb) const
{
  static Uint32 next_edge = 0;

  *ea = NULL;
  *eb = NULL;

  if (next_edge < nEdgesA)
	{
    *ea = edgesA[next_edge];
    *eb = edgesB[next_edge++];
    ASSERT(*eb);
    ASSERT(*ea);
    ASSERT(nEndsA == nEndsB);
	  return TRUE;
  }
  next_edge = 0;
  return FALSE;
}

/***********************************************************************/
SFBool CanJoin(vrHalfEdge *hea, vrHalfEdge *heb, vrHalfEdge **reta, vrHalfEdge **retb)
{
  hea->SetMark(NOT_LOOSE);
  heb->SetMark(NOT_LOOSE);

  *reta = NULL;
  *retb = NULL;

  for (Uint32 i=0; i<nEndsA; i++)
	{
    if (hea->isNeighbor(EndsA[i]))
		{
//VRTRACE("\t\thea: %3d", hea->GetFace()->GetIndex()); DEBHE(hea, ""); VRTRACE(" is a neighbor of ");
//VRTRACE("EndsA[%d]: %3d", i, hea->GetFace()->GetIndex()); DEBHE(EndsA[i], ""); VRTRACE("\n");
			if (heb->isNeighbor(EndsB[i]))
			{
//VRTRACE("\t--->heb: %3d", heb->GetFace()->GetIndex()); DEBHE(heb, ""); VRTRACE(" is also a neighbor of ");
//VRTRACE("EndsB[%d]: %3d", i, heb->GetFace()->GetIndex()); DEBHE(EndsB[i], ""); VRTRACE("\n\n");
				*reta = EndsA[i];
	      *retb = EndsB[i];

//DEBLOOSEENDS(hea, heb, "Found neighboring loose end:\n");

				/* Move the rest down */
		    for(Uint32 j=i+1; j<nEndsA; j++)
				{
					EndsA[j-1] = EndsA[j];
					EndsB[j-1] = EndsB[j];
				}
				nEndsA--;
				nEndsB--;
	      (*reta)->SetMark(NOT_LOOSE);
		    (*retb)->SetMark(NOT_LOOSE);
			  ASSERT(*reta);
				ASSERT(*retb);
				return TRUE;
			} else
			{
//VRTRACE("\t--->heb: %3d", heb->GetFace()->GetIndex()); DEBHE(heb, ""); VRTRACE(" is NOT a neighbor of ");
//VRTRACE("EndsB[%d]: %3d", i, heb->GetFace()->GetIndex()); DEBHE(EndsB[i], ""); VRTRACE("\n\n");
			}
		} else
		{
//VRTRACE("\t\thea: %3d", hea->GetFace()->GetIndex()); DEBHE(hea, ""); VRTRACE(" is NOT a neighbor of ");
//VRTRACE("EndsA[%d]: %3d", i, hea->GetFace()->GetIndex()); DEBHE(EndsA[i], ""); VRTRACE("\n");
		}
  }
  hea->SetMark(LOOSE);
  heb->SetMark(LOOSE);

//DEBLOOSEENDS(hea, heb, "Adding Loose Ends\n");

  EndsA[nEndsA++] = hea;
  EndsB[nEndsB++] = heb;

  *reta = NULL;
  *retb = NULL;
  return FALSE;
}
 
/***********************************************************************/
SFBool VertexGreaterThan(vrVertex *v1, vrVertex *v2);
void vrBoolopRecord::SortNullEdges(void)
{
  ASSERT(nEdgesA == nEdgesB);

  // Sort the null edges by 'z' within 'y' within 'x'
	for (register Uint32 i=0; i<nEdgesA; i++)
	{
    for (register Uint32 j=i+1; j<nEdgesA; j++)
		{
      vrVertex *v1 = edgesA[i]->GetVertex(HE1);
      vrVertex *v2 = edgesA[j]->GetVertex(HE1);

			// Note: since these are NULL edges either vertex will do for the sort.
			ASSERT(*v1 == *edgesA[i]->GetVertex(HE2));
			ASSERT(*v2 == *edgesA[j]->GetVertex(HE2));

      if (VertexGreaterThan(v1, v2))
			{
				BoolSwap(i, j);
      }
    }
  }

  for (i=0;i<nEdgesA;i++)
	{
    edgesA[i]->SetIndex(i);
    edgesB[i]->SetIndex(i);
    vrEdge *e = edgesA[i];
    thing[i].hes[0] = e->GetHe  (HE1);
    thing[i].cl [0] = e->GetLoop(HE1)->isOuterLoop();
    thing[i].hes[1] = e->GetHe  (HE2);
    thing[i].cl [1] = e->GetLoop(HE2)->isOuterLoop();
    e = edgesB[i];
    thing[i].hes[2] = e->GetHe  (HE1);
    thing[i].cl [2] = e->GetLoop(HE1)->isOuterLoop();
    thing[i].hes[3] = e->GetHe  (HE2);
    thing[i].cl [3] = e->GetLoop(HE2)->isOuterLoop();
  }

#ifdef _DEBUG
//  VRTRACE("\tSortNullEdges (after sort)\n");
//  for (i=0;i<nEdgesA;i++)
//	{
//    DEBEDGES("\t", edgesA[i], edgesB[i]);
//  }
//  for (i=0;i<nEdgesA;i++) {
//    DEB(edgesA[i], "");
//  }
//  VRTRACE("\n");
#endif
}

SFBool VertexGreaterThan(vrVertex *v1, vrVertex *v2)
{
  // Is v1 greater than v2?
	
	SFInt32 res = vrCompare(v1->x, v2->x, BIGEPS);
  if (res == -1)
	{
    return FALSE;
  } else if (res == 0)
	{
    res = vrCompare(v1->y, v2->y, BIGEPS);
    if (res == -1)
		{
      return FALSE;
    } else if (res == 0)
		{
      res = vrCompare(v1->z, v2->z, BIGEPS);
      if (res == -1)
			{
				return FALSE;
      }
    }
  }
  
  return TRUE;
}

SFBool GetThingCl(vrHalfEdge *he)
{
  Uint32 index = he->GetEdge()->GetIndex();

  for (Uint32 i=0;i<4;i++) 
	{
    if (thing[index].hes[i] == he->GetMate()) 
		{
      return thing[index].cl[i];
    }
  }
  ASSERT(0);
  return FALSE;
}

// This peice of shit routine fixes a couple of bugs.
SFBool SpecialCase(vrHalfEdge *he1, vrHalfEdge *he2)
{
//	return FALSE;
//#if 0
	vrLoop *l = he1->GetLoop();

  if (l == he2->GetLoop())
	{
    if (he1->Prev()->Prev() != he2)
		{
      if (!l->isOuterLoop())
			{
        SFBool cl1 = GetThingCl(he1);
        SFBool cl2 = GetThingCl(he2);
        if (cl1 && cl2)
				{
          return FALSE;
        }
        return TRUE;
      }
    }
  }

  return FALSE;
//#endif
}

