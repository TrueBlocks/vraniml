//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Split.h"

#define BIGEPS       (0.00001*100.0f)
#define EPS_SQUARED  (0.00001*wLimits::Small)

int EdgeCompare (const void *e1, const void *e2);
SFBool CanJoin (vrHalfEdge *he, vrHalfEdge **ret);

/*********************************************************************/
void vrSplitRecord::Connect(void)
{
  nFaces = 0;

//  DEB(this, "this before Connect\n");

  /* Sort the null edges by x then y then z so GetNextNullEdge picks the correct edge */
  qsort(edges, nEdges, sizeof(vrEdge*), EdgeCompare);
  
  vrEdge *nextEdge;
  vrHalfEdge *he1, *he2;
  while (GetNextNullEdge(&nextEdge))
	{
    if (CanJoin(nextEdge->GetHe(HE1), &he1))
		{
      s->Join(he1, nextEdge->GetHe(HE1), FALSE);
      if (!he1->GetMate()->Marked(LOOSE))
			{
        vrFace *ff = s->Cut(he1, FALSE);
        if (ff) 
				{
					AddFace(ff);
				}
      }
    }

    if (CanJoin(nextEdge->GetHe(HE2), &he2))
		{
      s->Join(he2, nextEdge->GetHe(HE2), FALSE);
      if (!he2->GetMate()->Marked(LOOSE))
			{
        vrFace *ff = s->Cut(he2, FALSE);
        if (ff) 
				{
					AddFace(ff);
				}
      }
    }

    if (he1 && he2)
		{
      vrFace *ff = s->Cut(nextEdge->GetHe(HE1), FALSE);
      if (ff) 
			{
				AddFace(ff);
			}
    }
  }

  /* There should be no loose ends remaining */
  ASSERT(!nEnds);

  nEdges = 0;
}

SFBool vrSplitRecord::GetNextNullEdge(vrEdge **e)
{
  static Uint32 next_edge=0;

  *e = NULL;

  if (next_edge < nEdges)
	{
    *e = edges[next_edge++];
    return TRUE;
  }
  next_edge = 0;
  return FALSE;
}

SFBool vrSplitRecord::CanJoin(vrHalfEdge *he, vrHalfEdge **ret)
{
  he->SetMark(NOT_LOOSE);
  *ret = NULL;

  for (Uint32 i=0;i<nEnds;i++)
	{
    if (he->isNeighbor(looseEnds[i]))
		{
      looseEnds[i]->SetMark(NOT_LOOSE);
      *ret = looseEnds[i];
      /* Move the remaining loose halfedges */
      for (Uint32 j=i+1;j<nEnds;j++)
			{
				looseEnds[j-1] = looseEnds[j];
      }
      nEnds--;
      return TRUE;
    }
  }
  he->SetMark(LOOSE);
  AddLooseEnd(he);

  return FALSE;
}

void vrSplitRecord::AddLooseEnd(vrHalfEdge *he)
{
  ASSERT(nEnds < MAX_LOOSE_ENDS);
  looseEnds[nEnds++] = he;
}

int EdgeCompare(const void *e1, const void *e2)
{
  vrVertex  *v1 = (*(vrEdge **)e1)->GetVertex(HE1);
  vrVertex  *v2 = (*(vrEdge **)e2)->GetVertex(HE1);
  
  SFInt32 res = vrCompare(v1->x, v2->x, (SFFloat)BIGEPS);
  if (!res)
	{
    res = vrCompare(v1->y, v2->y, (SFFloat)BIGEPS);
    if (!res)
		{

      res = vrCompare(v1->z, v2->z, (SFFloat)BIGEPS);
    }
  }

  return res;
}

#if 0
static SFBool SpecialCase(vrHalfEdge *he1, vrHalfEdge *he2)
{
  Loop *l = he1->GetLoop();
  if (l == he2->GetLoop()) {
    if (he1->Prev()->Prev() != he2) {
      if (!he1->GetLoop()->isOuterLoop()) {
        return TRUE;
      }
    }
  }
  return FALSE;
}
#endif

