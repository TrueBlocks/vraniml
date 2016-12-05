//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#define BIGEPS       (0.00001*100.0f)
#define EPS_SQUARED  (0.00001*0.00001)

#include "Split.h"
#include "SplitClassify.h"

static vrSplitClassifyRecord clRec;

/*********************************************************************/
SFBool vrSplitRecord::Classify(void)
{
  nEdges=0;

  clRec.Reset(this);

  DEB(this, "split record before classify\n");

  // For each new vertex created in the Generate stage classify
	// it as belonging to either the ABOVE or BELOW side of the splitting
	// plane.
	for (Uint32 i=0;i<nVerts;i++) 
	{
    clRec.SetVertex(i);

    clRec.GetNeighborhood();
    DEB(&clRec, "after getneighborhood\n");

    clRec.ReclassifyOnSectors();
    DEB(&clRec, "\tafter reclassify\n");

    clRec.ReclassifyOnEdges();
    DEB(&clRec, "\tafter reclassEdges\n");

    clRec.InsertNullEdges();
    DEB(&clRec, "\tafter insert NULL\n");
		DEB(this, "split record after classify\n");
  }

	DEB(this, "split record after classify\n");

  nVerts=0;
  return (nEdges != 0);
}

/*********************************************************************/
void vrSplitClassifyRecord::GetNeighborhood(void)
{
  nNbrs = 0;
  vrHalfEdge *he = v->GetHe();
  do
	{
    vrVertex *vvv = he->Next()->GetVertex();
    SFInt32 cl = vrCompare(SP.GetDistance(*vvv), 0.0f);
    AddNeighborhood(he, cl);
   /* if (he->isWide(FALSE)) 
		{
      SFVec3f bisector = he->Bisect();
      cl = vrCompare(SP.GetDistance(bisector), 0.0f);

      if (cl != ON) AddNeighborhood(he, cl);
//      AddNeighborhood(he, cl);
    }*/
  } while ((he = he->GetMate()->Next()) != v->GetHe());
}

/*********************************************************************/
void vrSplitClassifyRecord::ReclassifyOnSectors(void)
{
  ASSERT(spRec);

  for (Uint32 i=0; i<nNbrs; i++) 
	{
    vrFace *fac = neighbors[i].sector->GetFace();
  	ASSERT(SP.GetNormal() == spRec->GetSPNormal());
	  SFVec3f spNormal = SP.GetNormal();
    SFVec3f c = CrossProduct(fac->GetNormal(), spNormal);
    SFFloat d = DotProduct(c, c);
 
    if (vrCompare((SFFloat)d, (SFFloat)0.0f, (SFFloat)EPS_SQUARED) == 0) 
		{

#ifdef _DEBUG
//			if (AfxGetApp()->GetProfileInt("Debug", "SpecialCaseMessageBox", FALSE))
//			{
//				AfxMessageBox("Split::ReclassifyOnSectors --> Coplaner sector");
//			}
#endif

      // We know that at least one vertex of this
			// edge is on the splitting plane (by construction)
			// If the edge's face's normal is colinear with 
			// the splitting plane normal then that edge
			// must be coplaner with the splitting plane.
			// If the face normal points in the same 
			// direction as the splitting plane, classify
			// both ends of the neighborhood as BELOW, else ABOVE
			d = DotProduct(fac->GetNormal(), spNormal);
      Uint32 prv = (i+nNbrs-1)%nNbrs;

			// This sector is coplaner with the splitting plane
			ASSERT(neighbors[i].cl == ON && neighbors[prv].cl == ON);
      if (vrCompare(d, 0.0f) == 1) 
			{
				// same
				neighbors[prv].cl = BELOW;
				neighbors[i].cl = BELOW;
      } else 
			{
				neighbors[prv].cl = ABOVE;
				neighbors[i].cl = ABOVE;
      }
    }
  }
}

/*********************************************************************/
void vrSplitClassifyRecord::ReclassifyOnEdges(void)
{
  for (Uint32 i=0; i<nNbrs; i++) 
	{
    /* If any neighborhoods are as yet unclassified.... */
    if (neighbors[i].cl == ON) 
		{
#ifdef _DEBUG
//			if (AfxGetApp()->GetProfileInt("Debug", "SpecialCaseMessageBox", FALSE))
//			{
//				AfxMessageBox("Split::ReclassifyOnEdges --> Unclassified Neighborhood");
//			}
#endif

      SFInt32 prv = neighbors[(nNbrs+i-1)%nNbrs].cl;
      SFInt32 nxt = neighbors[(i+1)%nNbrs].cl;
      
      // Four possibilities:
			//
			//     Prev      This    Next    Classify
			//     ABOVE      ON     ABOVE     ABOVE
			//     BELOW      ON     BELOW     BELOW

			//     ABOVE      ON     BELOW     ABOVE
			//     BELOW      ON     ABOVE     ABOVE
			// (this choice is arbitraty but InsertNullEdges is
			//  dependant on the choice.  If ABOVE that look for
			//  ABOVE sectors)
			neighbors[i].cl = (prv==nxt) ? prv : ABOVE;
    }
  }
}

/*********************************************************************/
void vrSplitClassifyRecord::InsertNullEdges(void)
{
#ifdef _DEBUG
	// At this point all neighborhoods should be classified
	for (Uint32 iii=0;iii<nNbrs;iii++)
	{
		ASSERT(neighbors[iii].cl!=ON);
	}
	ASSERT(spRec);
#endif

  Uint32 cur=0;
  Uint32 nxt = 0;
  while (TRUE)
	{
		// look for first crossing (from BELOW to ABOVE)
    nxt = (cur+1)%nNbrs;
    if ((neighbors[cur].cl == BELOW && neighbors[nxt].cl == ABOVE))
		{
			break;
    }
    if (++cur == nNbrs) return;
  }
	ASSERT(nxt!=-1); // should have picked up something
  
	// Gary 11/26/96
	cur = nxt;

  Uint32 start = cur;
  vrHalfEdge *head = neighbors[start].sector;
  ASSERT(head);
  
  while (TRUE) 
	{
    while (TRUE) 
		{
			// look for next crossing (back to BELOW)
			nxt = (cur+1)%nNbrs;
			if ((neighbors[cur].cl == ABOVE && neighbors[nxt].cl == BELOW)) 
			{
				break;
			}
			cur = nxt; 
			//-- we better find it or we will spin forever!
			ASSERT(cur != start);
    }
    
    //tail = neighbors[cur].sector; Gary 11/26/96
    vrHalfEdge *tail = neighbors[nxt].sector;
    ASSERT(tail);
    
		// add in a null edge and save it
		tail->GetSolid()->lmev(head, tail, *head->GetVertex());
    spRec->AddEdge(head->Prev()->GetEdge());
    
    while (TRUE) 
		{
			// look for next crossing (from BELOW to ABOVE)
			nxt = (cur+1)%nNbrs;
			if ((neighbors[cur].cl == BELOW && neighbors[nxt].cl == ABOVE)) 
			{
				break;
			}
			cur = nxt;
// Moved here - Gary 11/26/96
    }
//		if (cur == start) Gary 11/26/96
		if ((cur+1)%nNbrs == start) 
			{
				// can't find any more so quit
				return;
			}
  }
}

#ifdef _DEBUG
static char cla[][8] = { "BELOW", "ON ", "ABOVE " };

void vrSplitNeighborhood::Show(vrDumpContext& dc) const
{
//  VRTRACE("sector->index: %3d, cl = %s", sector->GetIndex(), cla[cl+1]);
}

void vrSplitClassifyRecord::Show(vrDumpContext& dc) const
{
//  if (!afxTraceEnabled)
//		return;

  if (nNbrs)
	{
	  for (Uint32 i=0; i<nNbrs; i++)
		{
      VRTRACE("\tneighbor[%d]: ", i);
      neighbors[i].Show(dc);
      VRTRACE("\n");
    }
    VRTRACE("\n");
  }
}
#endif
