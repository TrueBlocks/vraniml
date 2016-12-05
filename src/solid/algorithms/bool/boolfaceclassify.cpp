//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"
#include "BoolFaceClassify.h"

/*********************************************************************/
void vrBoolVertFaceClassifyRecord::VF_Classify(Uint32 i, SFBool isB)
{
  DEBUG_MARKER("**");

  SetVertexFace(i, isB);

  VF_GetNeighborhood();
	DEB(this, "After GetNeighborhood");
  VF_ReclassifyOnSectors();
	DEB(this, "After ReclassifyOnSectors");
  VF_ReclassifyOnEdges();
	DEB(this, "After ReclassifyOnEdges");
  VF_InsertNullEdges();
	DEB(this, "After InsertNullEdges");
}

void vrBoolVertFaceClassifyRecord::ShiftDown(void)
{
	neighbors[nNbrs] = neighbors[0];
	for (Uint32 i=0;i<nNbrs;i++)
	{
		neighbors[i] = neighbors[i+1];
	}
}

SFBool vrBoolVertFaceClassifyRecord::PrepareNextCrossing(void)
{
	// mark entries as intersecting
	for (Uint32 k=0;k<nNbrs;k++)
	{
		Uint32 prev  = PrevNum(k, nNbrs);
		Uint32 next  = NextNum(k, nNbrs);
		SFInt32 clPrev = neighbors[prev].cl;
		SFInt32 cl     = neighbors[k].cl;
		SFInt32 clNext = neighbors[next].cl;
		neighbors[k].intersects=TRUE;
		if (clPrev == cl && cl == clNext)
		{
			neighbors[k].intersects=FALSE;
		}
	}
	
	// Remove any non-intersecting neighbors
	Uint32 n=0;
	for (k=0;k<nNbrs;k++)
	{
		if (neighbors[k].intersects)
		{
			neighbors[n] = neighbors[k];
			n++;
		}
	}
	nNbrs = n;

	// Move to the first crossing
	if (nNbrs)
	{
		ASSERT(nNbrs>1);
		while (!(neighbors[0].cl == IN && neighbors[1].cl == OUT))
		{
			ShiftDown();
		}
	}

	return (nNbrs>0);
}

SFBool IsOnOuterLoop(vrVertex *v)
{
	vrLoop *lout = v->GetHe()->GetFace()->GetLoopOut();
	LISTPOS hPos = lout->halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = lout->halfedges.GetNext(hPos);
		if (he->GetVertex() == v) return TRUE;
	}
	return FALSE;
}

void vrBoolVertFaceClassifyRecord::FindNextCrossing(vrHalfEdge **hInOut, vrHalfEdge **hOutIn)
{
//	DEB(this);

	// Note: neighbors may have the same he (because of isWide adding) therefor
	//       we look for IN-OUT crossings and then look at Mate()->Next() for
	//       OUT-IN

	ASSERT(neighbors[0].cl == IN);
	ASSERT(neighbors[1].cl == OUT);

	Uint32 next = NextNum(1, nNbrs);
	ASSERT(neighbors[next].cl==IN || neighbors[next].cl == OUT);

	if (neighbors[next].cl==IN)
	{
		// IN-OUT              --> IN-IN
		// IN-OUT-IN           --> IN-IN-IN
		// IN-OUT-IN-OUT...    --> IN-IN-IN-OUT
		// IN-OUT-IN-IN-OUT... --> IN-IN-IN-IN-OUT
#ifdef _DEBUG
		if (nNbrs==2)
		{
			ASSERT(next==0);
			ASSERT(neighbors[0].cl == IN && neighbors[1].cl == OUT);
		} else
		{
			ASSERT(nNbrs==3); // temporary for my test cases
			ASSERT(next==2);
			ASSERT(neighbors[0].cl == IN && neighbors[1].cl == OUT && neighbors[2].cl == IN);
		}
#endif
		
		*hInOut = neighbors[0].sector->GetMate()->Next();
		*hOutIn = neighbors[1].sector->GetMate()->Next();

		// Mark OUT as IN so it gets skipped in next round
		neighbors[1].cl = IN;
	} else
	{
		//ASSERT(0);
		ASSERT(next!=0);
		ASSERT(neighbors[next].cl==OUT);
		ASSERT(neighbors[NextNum(next, nNbrs)].cl==IN);
	
		// IN-OUT-OUT                        --> IN-IN-IN
		// IN-OUT-OUT-IN                     --> IN-IN-IN-IN
		// IN-OUT-OUT-IN-IN (cant happen)    --> 
		// IN-OUT-OUT-IN-IN-OUT...           --> IN-IN-IN-IN-IN-OUT...
		// IN-OUT-OUT-IN-OUT...              --> IN-IN-IN-IN-OUT...
		// IN-OUT-OUT-OUT... (cant happen)
	
//		ASSERT(nNbrs==3); // temporary for my test cases

		ASSERT(next==2);
		ASSERT(neighbors[0].cl == IN && neighbors[1].cl == OUT && neighbors[next].cl == OUT);
			
		*hInOut = neighbors[0].sector->GetMate()->Next();
		*hOutIn = neighbors[next].sector->GetMate()->Next();

	VRTRACE("hInOut: %d-%d-%d\thOutIn: %d %d %d\n", 
				(*hInOut)->Prev()->GetIndex(), (*hInOut)->GetIndex(), (*hInOut)->Next()->GetIndex(),
				(*hOutIn)->Prev()->GetIndex(), (*hOutIn)->GetIndex(), (*hOutIn)->Next()->GetIndex());

		if (!IsOnOuterLoop(v))
		{
			vrHalfEdge *t1 = *hInOut;
			vrHalfEdge *t2 = *hOutIn;
			*hOutIn = t1;
			*hInOut = t2;
		}
	VRTRACE("hInOut: %d-%d-%d\thOutIn: %d %d %d\n", 
				(*hInOut)->Prev()->GetIndex(), (*hInOut)->GetIndex(), (*hInOut)->Next()->GetIndex(),
				(*hOutIn)->Prev()->GetIndex(), (*hOutIn)->GetIndex(), (*hOutIn)->Next()->GetIndex());

		// Mark OUT as IN so it gets skipped in next round
		neighbors[1].cl = IN;
		neighbors[2].cl = IN;
		ShiftDown();
	}

	ShiftDown();
	ShiftDown();

//DEB(this);
}

void vrBoolVertFaceClassifyRecord::Seperate(vrHalfEdge *hInOut, vrHalfEdge *hOutIn)
{
#ifdef _STATS
		if (bopRec->stats) bopRec->stats->cl.vf_crossings++;

		if ((hInOut->GetIndex() == hOutIn->GetIndex()) && (hInOut->Next()->GetIndex() == hOutIn->Next()->GetIndex()))
		{
			if (bopRec->stats) bopRec->stats->cl.vf_dangling++;
		}
		if (hInOut->GetFace() == hOutIn->GetFace())
		{
			if (bopRec->stats) bopRec->stats->cl.vf_sameface++;
		}
#endif
      
	vrSolid *s = hInOut->GetSolid();
	ASSERT(hOutIn->GetSolid()==s);
	VRTRACE("hInOut: %d-%d-%d\thOutIn: %d %d %d\n", 
				hInOut->Prev()->GetIndex(), hInOut->GetIndex(), hInOut->Next()->GetIndex(),
				hOutIn->Prev()->GetIndex(), hOutIn->GetIndex(), hOutIn->Next()->GetIndex());

#ifdef _DEBUG
	//vrFace *f1 = hInOut->GetFace();
	//vrFace *f2 = hOutIn->GetFace();
	//DEB(f1, "f1");
	//DEB(f2, "f2");
#endif

	SFBool isOuter = IsOnOuterLoop(v);

	// Hack to fix problem with VF only interactions working backwards
	if (bopRec->noVV)
	{
		s->lmev(hInOut, hOutIn, *hInOut->GetVertex());
	} else
	{
		s->lmev(hOutIn, hInOut, *hInOut->GetVertex());
	}
	vrEdge *e = hInOut->Prev()->GetEdge();      
	if (!isOuter)
	{
		e->SwapHes();
	}

  if (isB)
	{
		bopRec->AddEdgeB(e);
	} else
	{
		bopRec->AddEdgeA(e);
	}

	e = f->MakeRing(*hInOut->GetVertex());
	if (!isOuter)
	{
		e->SwapHes();
	}

  if (!isB)
	{
		bopRec->AddEdgeB(e);
	} else
	{
		bopRec->AddEdgeA(e);
	}

	//DEB(f1, "f1");
	//DEB(f2, "f2");
}

/*********************************************************************/
void vrBoolVertFaceClassifyRecord::VF_InsertNullEdges(void)
{
	while (PrepareNextCrossing())
	{
	  vrHalfEdge *hInOut=NULL, *hOutIn=NULL;
  
		FindNextCrossing(&hInOut, &hOutIn);

		Seperate(hInOut, hOutIn);
  }
}

/*********************************************************************/
void vrBoolVertFaceClassifyRecord::VF_GetNeighborhood(void)
{
  nNbrs = 0;
  vrHalfEdge *he = v->GetHe();
  do
	{
    vrVertex *vvv = he->Next()->GetVertex();
    SFInt32 cl = vrCompare(SP.GetDistance(*vvv), 0.0f);
#ifdef _STATS
		if (bopRec->stats) bopRec->stats->cl.vf_neighbors++;
#endif
    if (he->isWide(FALSE)) 
		{
      SFInt32 pCl = cl;
			
			SFVec3f bisector = he->Bisect();
			VRTRACE("bisector: %f %f %f\n", bisector.x, bisector.y, bisector.z);
      cl   = vrCompare(SP.GetDistance(bisector), 0.0f);
#ifdef _STATS
			if (bopRec->stats) bopRec->stats->cl.vf_neighbors++;
			if (bopRec->stats) bopRec->stats->cl.vf_wide++;
#endif
      // If bisector is classified as ON then it must be
			// the case that next and previous are classified 
			// oppositly obviating the need for bisector so
			// ignore it
			if (pCl != 0) VF_AddNeighborhood(he, pCl);
			if (cl  != 0) VF_AddNeighborhood(he, cl);
    } else
		{
	    VF_AddNeighborhood(he, cl);
		}
  } while ((he = he->GetMate()->Next()) != v->GetHe());
}

/*********************************************************************/
void vrBoolVertFaceClassifyRecord::VF_ReclassifyOnSectors(void)
{
  ASSERT(bopRec);

  for (Uint32 i=0; i<nNbrs; i++)
	{
    vrFace *fac = neighbors[i].sector->GetFace();
		ASSERT(SP.GetNormal() == f->GetNormal());
		SFVec3f spNormal = SP.GetNormal();
    SFVec3f c = CrossProduct(fac->GetNormal(), spNormal);
    SFFloat d = DotProduct(c, c);

    if (vrCompare(d, 0.0f, EPS_SQUARED) == 0)
		{

#ifdef _STATS
			if (bopRec->stats) bopRec->stats->cl.vf_onsectors++;
#endif

#ifdef _DEBUG
//			if (AfxGetApp()->GetProfileInt("Debug", "SpecialCaseMessageBox", FALSE))
//			{
//				AfxMessageBox("Bool::ReclassifyOnSectors --> Coplaner sector");
//			}
#endif

			d = DotProduct(fac->GetNormal(), spNormal);
      Uint32 prv = (i+nNbrs-1)%nNbrs;

      if (vrCompare(d, 0.0f) == 1)
			{
        if (isB)
				{
      	  neighbors[i].cl   = (op == vrUNION) ? IN : OUT;
	        neighbors[prv].cl = (op == vrUNION) ? IN : OUT;
      	} else
				{
	        neighbors[i].cl   = (op == vrUNION) ? OUT : IN;
      	  neighbors[prv].cl = (op == vrUNION) ? OUT : IN;
	      }
      } else
			{
      	if (isB)
				{
	        neighbors[i].cl   = (op == vrUNION) ? IN : OUT;
      	  neighbors[prv].cl = (op == vrUNION) ? IN : OUT;
	      } else
				{
	        neighbors[i].cl   = (op == vrUNION) ? IN : OUT;
      	  neighbors[prv].cl = (op == vrUNION) ? IN : OUT;
	      }
      }
    }
  }
}

void vrBoolVertFaceClassifyRecord::VF_ReclassifyOnEdges(void)
{
  for (Uint32 i=0; i<nNbrs; i++)
	{

    if (neighbors[i].cl == ON)
		{
#ifdef _STATS
			if (bopRec->stats) bopRec->stats->cl.vf_onedges++;
#endif

      SFInt32 prv = neighbors[(nNbrs+i-1)%nNbrs].cl;
      SFInt32 nxt = neighbors[(i+1)%nNbrs].cl;

      // Four possibilities:
			//
			//     Prev      This    Next    Classify
			//     IN         ON     IN        IN
			//     OUT        ON     OUT       OUT

			//     IN         ON     OUT       IN
			//     OUT        ON     IN        IN
			// (this choice is arbitraty but InsertNullEdges is
			//  dependant on the choice.  If IN that look for
			//  IN sectors)
			neighbors[i].cl = (prv==nxt) ? prv : IN;
    }
  }

#ifdef _DEBUG
	// At this point all neighborhoods should be classified
	for (Uint32 iii=0;iii<nNbrs;iii++)
	{
		ASSERT(neighbors[iii].cl!=ON);
	}
#endif
}

void vrBoolVertFaceClassifyRecord::SetVertexFace(Uint32 i, SFBool iB)
{
  ASSERT(bopRec);
  
  isB = iB;

  if (isB)
	{
    v = bopRec->GetVertB(i);
    f = bopRec->GetFaceB(i);
  } else
	{
    v = bopRec->GetVertA(i);
    f = bopRec->GetFaceA(i);
  }
  SP = vrPlane(f->GetNormal(), f->GetD());
  nNbrs=0;
}

/**********************************************************************/
#ifdef _DEBUG

void vrVFNeighborhood::Show(vrDumpContext& dc) const
{
	VRTRACE("%3d %3d %3d (%d)[%s]", 
		sector->Prev()->GetIndex(), 
		sector->GetIndex(), 
		sector->Next()->GetIndex(), 
		intersects,
		(const char *)(cla[cl+1])); 
//	VRTRACE(" [%s]", (const char *)(cla[cl+1])); 
}

void vrBoolVertFaceClassifyRecord::Show(vrDumpContext& dc) const
{
/*
  if (!traceContext)
		return;
*/

  for (Uint32 i=0; i<nNbrs; i++)
	{
    VRTRACE("\t");
		Uint32 next = NextNum(i,nNbrs);
		if (neighbors[i].cl == IN && neighbors[next].cl == OUT)
		{
			VRTRACE("* ");
		} else if (neighbors[i].cl == OUT && neighbors[next].cl == IN)
		{
			VRTRACE("+ ");
		} else
		{
			VRTRACE("  ");
		}
		if (neighbors[i].sector == neighbors[next].sector)
		{
			VRTRACE("#");
		} else
		{
			VRTRACE(" ");
		}
    VRTRACE(" [%d]: ", i);
    neighbors[i].Show(dc);
    VRTRACE("\n");
  }
  VRTRACE("\n");
}

#endif
