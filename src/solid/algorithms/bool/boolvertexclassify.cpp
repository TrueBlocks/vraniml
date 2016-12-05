//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"
#include "BoolVertexClassify.h"

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
void vrBoolVertVertClassifyRecord::VV_Classify(Uint32 i)
{
/*
	GrabNeighborhood(i);
	return;
*/

	DEB(bopRec, "Before VV_Classify");
  DEBUG_MARKER("**");

	nNbrsA = nNbrsB = nSectors = 0;
  SetVertexVertex(i);

  Preprocess(v,  FALSE);
  Preprocess(v2, TRUE);

  GetNeighborhood();
	DEB(this, "\nAfter GetNeighborhood");

  ReclassifyOnSectors();
//	DEB(this, "\nAfter ReclassifyOnSectors");
  ReclassifyOnEdges();
//	DEB(this, "\nAfter ReclassifyOnEdges");

  if (nSectors)
	{
//afxTraceEnabled=TRUE;
		InsertNullEdges();
//afxTraceEnabled=FALSE;
//		DEB(this, "\nAfter InsertNullEdges");
	} else
	{
		VRTRACE("Reclassify chucked out all sectors\n");
	}

//	DEB(bopRec, "After VV_Classify");
}

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
static vrEdge *Separate1(vrHalfEdge *from, vrHalfEdge *to);
static vrEdge *Separate2(vrHalfEdge *he);

void vrBoolVertVertClassifyRecord::InsertNullEdges(void)
{
#ifdef _DEBUG
//	DoChecks();
#endif

  while (PrepareNextCrossing())
	{
	  vrHalfEdge *aHead=NULL, *aTail=NULL, *bHead=NULL, *bTail=NULL;
  
		// marks used sectors as non-intersecting
		FindNextCrossing(&aHead, &aTail, &bHead, &bTail);

		// performs the lmev's
		Seperate(aHead, aTail, bHead, bTail);
  }
}
 
void vrBoolVertVertClassifyRecord::Seperate(vrHalfEdge *aHead,
																						vrHalfEdge *aTail,
																						vrHalfEdge *bHead,
																						vrHalfEdge *bTail)
{
	ASSERT(((aHead==aTail)&&!(bHead==bTail)) ||
					((bHead==bTail)&&!(aHead==aTail)) ||
					((aHead!=aTail)&&(bHead!=bTail)));

  vrEdge *e1, *e2;
  if (aHead == aTail)
	{
    e1 = Separate2(aHead);
    bopRec->AddEdgeA(e1);

    e2 = Separate1(bHead, bTail);
    bopRec->AddEdgeB(e2);

  } else if(bHead == bTail)
	{
    e2 = Separate1(aTail, aHead);
    bopRec->AddEdgeA(e2);

    e1 = Separate2(bHead);
    bopRec->AddEdgeB(e1);

  } else
	{
    e1 = Separate1(aTail, aHead);
    bopRec->AddEdgeA(e1);

    e2 = Separate1(bHead, bTail);
    bopRec->AddEdgeB(e2);
  }
}

static vrEdge *Separate1(vrHalfEdge *from, vrHalfEdge *to)
{
  ASSERT(from); ASSERT(to);
	ASSERT(from != to);

  ASSERT(!(from->Prev()->isNullEdge() && from->Prev()->isNullStrut()));
  ASSERT(!(to->Prev()->isNullEdge()   && to->Prev()->isNullStrut()));
	ASSERT(from->GetVertex() == to->GetVertex());
  ASSERT(from->GetSolid() == to->GetSolid());

  vrSolid *s = to->GetSolid();
	SFVec3f v = *to->GetVertex();

	s->lmev(from, to, v);

  vrEdge *e = from->Prev()->GetEdge();

	ASSERT(e);
	ASSERT(!e->GetHe(HE1)->isNullStrut());

  return e;
}

static vrEdge *Separate2(vrHalfEdge *he)
{
  ASSERT(he);

  ASSERT(!(he->Prev()->isNullEdge()));
  
  vrSolid *s = he->GetSolid();
	SFVec3f v = *he->GetVertex();
	
	s->lmev(he, he, v);
 
  vrEdge *e = he->Prev()->GetEdge();

	ASSERT(e);
	ASSERT(e->GetHe(HE1)->isNullStrut());

  return e;
}
 
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
inline void CheckIntersectFlag(vrSector *sector)
{
	if (sector->clNextA == sector->clPrevA && (sector->clNextA != ON))
	{
		sector->intersects = FALSE;
#ifdef _DEBUG
		sector->clNextA = DC; 
		sector->clPrevA = DC; 
		sector->clNextB = DC; 
		sector->clPrevB = DC;
#endif
	}

	if (sector->clNextB == sector->clPrevB && (sector->clNextB != ON))
	{
		sector->intersects = FALSE;
#ifdef _DEBUG
		sector->clNextA = DC; 
		sector->clPrevA = DC; 
		sector->clNextB = DC; 
		sector->clPrevB = DC;
#endif
	}
}

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
void vrBoolVertVertClassifyRecord::ReclassifyOnSectors()
{
  VRTRACE("ReclassifyOnSectors\n");

  // search for coplanar sectors
  for (Uint32 i=0; i<nSectors; i++)
	{
    if (sectors[i].clNextA == ON && 
				sectors[i].clPrevA == ON &&
				sectors[i].clNextB == ON && 
				sectors[i].clPrevB == ON)
		{
      VRTRACE("\n\tsector[%d] neighborhoods are coplanar (all ON)\n", i);

      Uint32 indexA = sectors[i].indexA;
      Uint32 indexB = sectors[i].indexB;

      // apply reclassification rules as per Table 15.1
      SFVec3f normA = nhA[indexA].he->GetFaceNormal();
      SFVec3f normB = nhB[indexB].he->GetFaceNormal();

//      DEBI(nhA[indexA].he->GetFace(), "\theA->GetFace()");
//      DEBI(nhB[indexB].he->GetFace(), "\theB->GetFace()");

		  SFInt32  newAcl, newBcl;
      if (normA == normB)
			{
//        VRTRACE("\t\tFace normals are the same\n");
				newAcl = (op == vrUNION) ? OUT : IN;
				newBcl = (op == vrUNION) ? IN : OUT;
	    } else
			{
//        VRTRACE("\t\tFace normals are opposite\n");
				newAcl = (op == vrUNION) ? IN : OUT;
				newBcl = (op == vrUNION) ? IN : OUT;
      }
      
      VRTRACE("\t\tNew classifications for this sector: newAcl: %s  newBcl: %s\n", cla[newAcl+1], cla[newBcl+1]);
//      VRTRACE("\t\tLook for other sectors in which we can use these new classifications\n");

      // reclassify intersecting neighbors
      for (Uint32 j=0; j<nSectors; j++)
			{
//				VRTRACE("\t\t====================================================\n");
//        VRTRACE("\t\tchecking sector[%d]: ", j); DEB(&sectors[j],""); VRTRACE("\n");

//				VRTRACE("\tchecking sector[%d]\n", j);

				if (sectors[j].intersects)
				{
//					VRTRACE("\t\tintersects ---> looking for common neighbors\n");
					ASSERT((i!=j) || ((sectors[j].indexA == indexA) && (sectors[j].indexB == indexB)));

					if ((sectors[j].indexA == indexA))
					{
			  		// Find common A neighborhoods and change B's codes
						sectors[j].clPrevB = (sectors[j].clPrevB == ON) ? newBcl : sectors[j].clPrevB;
			  		sectors[j].clNextB = (sectors[j].clNextB == ON) ? newBcl : sectors[j].clNextB;
					}
					if ((sectors[j].indexB == indexB))
					{
			  		// Find common B neighborhoods and change A's codes
			  		sectors[j].clPrevA = (sectors[j].clPrevA == ON) ? newAcl : sectors[j].clPrevA;
			  		sectors[j].clNextA = (sectors[j].clNextA == ON) ? newAcl : sectors[j].clNextA;
					}
					
					CheckIntersectFlag(&sectors[j]);
				} else
				{
//					VRTRACE("\t\tdoes not intersect ---> skipping\n");
				}
			}
//			DEB(this, "\nSpin");
    } else
		{
      VRTRACE("\tsector[%d] is not coplanar --> skipping\n", i);
    }
  }
}

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
void vrBoolVertVertClassifyRecord::ReclassifyOnEdges(void)
{
  for (Uint32 i=0; i<nSectors; i++)
	{
    if (sectors[i].intersects)
		{
			ReclassifyDoublyOnEdges(i);
//			DEB(this, "\nSpin");
			ReclassifySinglyOnEdges(i);
//			DEB(this, "\nSpin");
    }
  }
}

void vrBoolVertVertClassifyRecord::ReclassifyDoublyOnEdges(Uint32 i)
{
	if ((sectors[i].clNextA == ON &&  sectors[i].clNextB == ON) ||
			(sectors[i].clPrevA == ON &&  sectors[i].clPrevB == ON))
	{

		SFInt32  newAcl = (op == vrUNION) ? OUT : IN;
		SFInt32  newBcl = (op == vrUNION) ? IN  : OUT;
  
		Uint32 indexA  = sectors[i].indexA;
		Uint32 indexB  = sectors[i].indexB;
  
//  VRTRACE("\t\tindexA: %d  indexB: %d  pIndexA: %d pIndexB: %d\n", indexA, indexB, pIndexA, pIndexB);
//  VRTRACE("\t\tNew classifications for this sector: newAcl: %s  newBcl: %s\n", cla[newAcl+1], cla[newBcl+1]);

//  VRTRACE("\t\tLook for other sectors in which we can use these new classifications\n");
		for (Uint32 j=0; j<nSectors; j++)
		{
			if (sectors[j].intersects)
			{
//					VRTRACE("\t\tintersects ---> looking for common neighbors\n");
				ASSERT((i!=j) || ((sectors[j].indexA == indexA) && (sectors[j].indexB == indexB)));

				if ((sectors[j].indexA == indexA))
				{
	  			// Find common A neighborhoods and change B's codes
					sectors[j].clPrevB = (sectors[j].clPrevB == ON) ? newBcl : sectors[j].clPrevB;
	  			sectors[j].clNextB = (sectors[j].clNextB == ON) ? newBcl : sectors[j].clNextB;
				}
				if ((sectors[j].indexB == indexB))
				{
	  			// Find common B neighborhoods and change A's codes
	  			sectors[j].clPrevA = (sectors[j].clPrevA == ON) ? newAcl : sectors[j].clPrevA;
	  			sectors[j].clNextA = (sectors[j].clNextA == ON) ? newAcl : sectors[j].clNextA;
				}
						
				CheckIntersectFlag(&sectors[j]);
			} else
			{
//					VRTRACE("\t\tdoes not intersect ---> skipping\n");
			}
		}
	}
}

void vrBoolVertVertClassifyRecord::ReclassifySinglyOnEdges(Uint32 i)
{
	Uint32 indexA  = sectors[i].indexA;
	Uint32 indexB  = sectors[i].indexB;
#ifdef _DEBUG
	//Uint32 pIndexA = PrevNum(indexA, nNbrsA);
	//Uint32 pIndexB = PrevNum(indexB, nNbrsB);
#endif

	SFInt32 newAcl = (op == vrUNION) ? OUT : IN;
	SFInt32 newBcl = (op == vrUNION) ? OUT : IN;

  if (sectors[i].clPrevA == ON || sectors[i].clNextA == ON ||
			sectors[i].clPrevB == ON || sectors[i].clNextB == ON)
  {
		for (Uint32 j=0; j<nSectors; j++)
		{
			if (sectors[j].intersects)
			{
//					VRTRACE("\t\tintersects ---> looking for common neighbors\n");
				ASSERT((i!=j) || ((sectors[j].indexA == indexA) && (sectors[j].indexB == indexB)));

				if ((sectors[j].indexA == indexA))
				{
	  			// Find common A neighborhoods and change B's codes
					sectors[j].clPrevB = (sectors[j].clPrevB == ON) ? newBcl : sectors[j].clPrevB;
	  			sectors[j].clNextB = (sectors[j].clNextB == ON) ? newBcl : sectors[j].clNextB;
				}
				if ((sectors[j].indexB == indexB))
				{
	  			// Find common B neighborhoods and change A's codes
	  			sectors[j].clPrevA = (sectors[j].clPrevA == ON) ? newAcl : sectors[j].clPrevA;
	  			sectors[j].clNextA = (sectors[j].clNextA == ON) ? newAcl : sectors[j].clNextA;
				}
						
				CheckIntersectFlag(&sectors[j]);
			}
		}
	}
}


/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
Uint32 vrBoolVertVertClassifyRecord::Preprocess(vrVertex *v, SFBool isB)
{
  char s[][20] = { "A", "B" };
  VRTRACE("\nPreprocess with vertex: %d(%s)\n", v->GetIndex(), s[isB]);

  vrHalfEdge *he = v->GetHe();
  ASSERT(he);

  do
	{
		SFVec3f vPrev = *he->Prev()->GetVertex() - *he->GetVertex();
    SFVec3f vNext = *he->Next()->GetVertex() - *he->GetVertex();

    /* check for "wide" sectors */
    if (FALSE) //he->isWide(FALSE))
		{
		  SFVec3f biSector = he->Bisect();
			biSector -= *he->GetVertex();
			AddNeighbor(he, vPrev,    biSector, isB, 1);
			AddNeighbor(he, biSector, vNext,    isB, 2);
    } else
		{
			AddNeighbor(he, vPrev, vNext, isB, 0);
		}
  } while((he = he->GetMate()->Next()) != v->GetHe());
  
  return 0;
}

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
void vrBoolVertVertClassifyRecord::GetNeighborhood(void)
{
  VRTRACE("\nGetNeighborhood\n");

  for (Uint32 i=0; i<nNbrsA; i++)
	{
    for (Uint32 j=0; j<nNbrsB; j++)
		{
#ifdef _DEBUG
//			vrHalfEdge *he1 = nhA[i].he; 
//			vrHalfEdge *he2 = nhB[j].he;
//			VRTRACE("\n\t========================================================");
//			VRTRACE("\n\tSectorTest (%d of %d): (%d-%d-%d) (%d-%d-%d)\n", (i*nNbrsB)+j+1, nNbrsA*nNbrsB,
//					he1->Prev()->GetIndex(), he1->GetIndex(), he1->Next()->GetIndex(),
//					he2->Prev()->GetIndex(), he2->GetIndex(), he2->Next()->GetIndex());
#endif
			if (TRUE) //SectorTest(&nhA[i], &nhB[j]))
			{
      	AddSector(i, j);
      }
//			VRTRACE("\n\t========================================================");
    }
  }
}
 
/*********************************************************************************/
void vrBoolVertVertClassifyRecord::AddNeighbor(vrHalfEdge *he, 
																	const SFVec3f& vP, 
																	const SFVec3f& vN, SFBool isB, long fromBisect)
{
	//
	// Note: A Neighborhood is:
	//
	//	  he:     a halfedge (and therefor a vertex)
	//    vNext:  the vector that when added to 'v' gives v->GetHe()->Next()
	//    vPrev:  the vector that when added to 'v' gives v->GetHe()->Prev()
	//    vCross: the cross product of vNext and vPrev
	//               (vCross is the opposite of the face normal????)
	//               (Very open question: why the opposite)
	//
	SFVec3f vC = -CrossProduct(vP, vN);

	ASSERT(he);
//	ASSERT(*he->GetVertex() + vN == *he->Next()->GetVertex());
//	ASSERT(*he->GetVertex() + vP == *he->Prev()->GetVertex());
	
#ifdef _DEBUG
#ifndef BISECT
	vrFace *f = he->GetFace();
	SFVec3f normal = f->GetNormal();
	ASSERT(vC == SFVec3f(0.0f) || Normalize(normal) == -Normalize(vC));
#endif
#endif

	if (isB)
	{
		ASSERT(nNbrsB < MAX_SECTORS);
		nhB[nNbrsB  ].he         = he;
		nhB[nNbrsB  ].fromBisect = fromBisect;
		nhB[nNbrsB  ].vNext      = vN;
		nhB[nNbrsB  ].vPrev      = vP;
		nhB[nNbrsB++].vCross     = vC;
    VRTRACE("\tAdding B neighborhood[%d-(%d)]: %d-%d-%d\n", nNbrsB-1, fromBisect,
        he->Prev()->GetIndex(), he->GetIndex(), he->Next()->GetIndex());
//    VRTRACE("\t\t(%f %f %f)\n\t\t(%f %f %f)\n\t\t(%f %f %f)\n",
//        vP.x, vP.y, vP.z,
//        vN.x, vN.y, vN.z, 
//        vC.x, vC.y, vC.z);
	} else
	{
		ASSERT(nNbrsA < MAX_SECTORS);
		nhA[nNbrsA  ].he     = he;
		nhA[nNbrsA  ].fromBisect = fromBisect;
		nhA[nNbrsA  ].vNext  = vN;
		nhA[nNbrsA  ].vPrev  = vP;
		nhA[nNbrsA++].vCross = vC;
    VRTRACE("\tAdding A neighborhood[%d-(%d)]: %d-%d-%d\n", nNbrsA-1, fromBisect,
        he->Prev()->GetIndex(), he->GetIndex(), he->Next()->GetIndex());
//    VRTRACE("\t\t(%f %f %f)\n\t\t(%f %f %f)\n\t\t(%f %f %f)\n",
//        vP.x, vP.y, vP.z,
//        vN.x, vN.y, vN.z, 
//        vC.x, vC.y, vC.z);
	}
}

/*********************************************************************************/
void vrBoolVertVertClassifyRecord::AddSector(Uint32 i, Uint32 j)
{
	//
	// Note: A Sector is:
	//
	//   indexA:      index into the A neighborhood array that we are dealing with
	//   clNextA:     classification of vNext with normal of face from B
	//   clPrevA:     classification of vPrev with normal of face from B
  //
	//   indexB:      index into the B neighborhood array that we are dealing with
  //   clNextB:     classification of vNext with normal of face from A 
	//   clPrevB:     classification of vPrev with normal of face from A
  //
	//   intersects:  SFBool TRUE if these two neighborhoods intersect
	//

	ASSERT(i < nNbrsA);
	ASSERT(j < nNbrsB);
	
	vrHalfEdge *ha = nhA[i].he;
	vrHalfEdge *hb = nhB[j].he;

	SFVec3f normalA = ha->GetFaceNormal();

	SFVec3f normalB = hb->GetFaceNormal();
	
//	VRTRACE("\tAddSector:\n");
//	VRTRACE("\t\tnorma: (%f %f %f)  normb: (%f %f %f)\n", 
//						normalA.x, normalA.y, normalA.z,
//						normalB.x, normalB.y, normalB.z);
	    
  SFFloat d1 = DotProduct(normalB, nhA[i].vNext);
	SFFloat d2 = DotProduct(normalB, nhA[i].vPrev);
	SFFloat d3 = DotProduct(normalA, nhB[j].vNext);
	SFFloat d4 = DotProduct(normalA, nhB[j].vPrev);

//  VRTRACE("\t\td1: %f  d2: %f  d3: %f  d4: %f\n", d1, d2, d3, d4);

  sectors[nSectors].indexA  = i;
  sectors[nSectors].indexB  = j;
  sectors[nSectors].clNextA = vrCompare(d1, 0.0f);
  sectors[nSectors].clPrevA = vrCompare(d2, 0.0f);
  sectors[nSectors].clNextB = vrCompare(d3, 0.0f);
  sectors[nSectors].clPrevB = vrCompare(d4, 0.0f);
  // This will be later determined to perhaps be FALSE in re-classifiers
	sectors[nSectors++].intersects = TRUE;

//  VRTRACE("\tAdded sector[%d](%d,%d): ", nSectors-1, i, j);
//  DEB(&sectors[nSectors-1], "");
//  VRTRACE("\n");
}

#ifdef _DEBUG
/*********************************************************************************/
void vrVVNeighborhood::Show(vrDumpContext& dc) const
{
  VRTRACE("%d-%d-%d",
//        "(%5.1f %5.1f %5.1f) "
//        "(%5.1f %5.1f %5.1f) "
//        "(%5.1f %5.3f %5.3f)",
	  he->Prev()->GetIndex(), he->GetIndex(), he->Next()->GetIndex());
//  	vNext.x, vNext.y, vNext.z,
//	  vPrev.x, vPrev.y, vPrev.z,
//  	vCross.x, vCross.y, vCross.z);
}

void vrSector::Show(vrDumpContext& dc) const
{
  VRTRACE("\t\t\tA(%d): (%-4.4s-%-4.4s)  B(%d): (%-4.4s-%-4.4s) (%d) ", 
	   indexA, cla[clPrevA+1], cla[clNextA+1], 
	   indexB, cla[clPrevB+1], cla[clNextB+1], intersects);
}

void vrBoolVertVertClassifyRecord::Show(vrDumpContext& dc) const
{
	VRTRACE("\tSectors:\n");
	if (nSectors)
	{
    for (Uint32 i=0; i<nSectors; i++)
		{
			VRTRACE("\t\tsector[%d]: ", i);
      sectors[i].Show(dc);
      VRTRACE("A: %d %d %d ", 
				nhA[sectors[i].indexA].he->Prev()->GetIndex(),
				nhA[sectors[i].indexA].he->GetIndex(),
				nhA[sectors[i].indexA].he->Next()->GetIndex());
      VRTRACE("B: %d %d %d\n",
	      nhB[sectors[i].indexB].he->Prev()->GetIndex(),
	      nhB[sectors[i].indexB].he->GetIndex(),
	      nhB[sectors[i].indexB].he->Next()->GetIndex());
    }
    VRTRACE("\n");
  }

/*
  if (nNbrsA)
	{
    VRTRACE("\tA Neighborhoods:\n");
    for (Uint32 i=0; i<nNbrsA; i++)
		{
      VRTRACE("\t\tneighbor[%d]: ", i);
      nhA[i].Show(dc);
      VRTRACE("\n");
    }			
    VRTRACE("\n");
  }

  if (nNbrsB)
	{
    VRTRACE("\tB Neighborhoods:\n");
    for (Uint32 i=0; i<nNbrsB; i++)
		{
      VRTRACE("\t\tneighbor[%d]: ", i);
      nhB[i].Show(dc);
      VRTRACE("\n");
    }
    VRTRACE("\n");
  }
*/
}
#endif

/*
static vrEdge *Separate1(vrHalfEdge *from, vrHalfEdge *to)
{
  ASSERT(from);
  ASSERT(to);

  VRTRACE("\t\tSeparate1\n");

  vrHalfEdge *he = from->Prev();
  if (he->isNullEdge() && he->isNullStrut())
	{
ASSERT(0);
		VRTRACE("\t\t\tfrom->Prev is nullEdge or nullStrut\n");
    if (he == he->GetEdgeHe(HE2))
    // look at orientation
		{
			VRTRACE("\t\t\tfrom->Prev is from->Prev->GetEdgeHe(HE2) -- from = from->Prev()\n");
      from = he->Prev();
    }
  }

  he = to->Prev();
  if (he->isNullEdge() && he->isNullStrut())
	{
ASSERT(0);
		VRTRACE("\t\t\tto->Prev is nullEdge or nullStrut\n");
    if (he == he->GetEdgeHe(HE1))
		{
			VRTRACE("\t\t\tto->Prev is to->Prev->GetEdgeHe(HE1) -- to = to->Prev()\n");
      to = he->Prev();
    }
  }
  
  if (from->GetVertex() != to->GetVertex())
	{
ASSERT(0);
		VRTRACE("\t\t\tfromvert != tovert\n");
    if (from->Prev() == to->Prev()->GetMate())
		{
			VRTRACE("\t\t\tfromPrev == toPrevMate-->from=fromPrev\n");
      from = from->Prev();
    } else if (from->Prev()->GetVertex() == to->GetVertex())
		{
			VRTRACE("\t\t\tfromPrevVert == toVert-->from=fromPrev\n");
      from = from->Prev();
    } else if (to->Prev()->GetVertex() == from->GetVertex())
		{
			VRTRACE("\t\t\tfromPrevVert == fromVert-->to=toPrev\n");
      to = to->Prev();
    }
  }
 
  ASSERT(from->GetSolid() == to->GetSolid());
  to->GetSolid()->lmev(from, to, *from->GetVertex());

  return from->Prev()->GetEdge();
}

static vrEdge *Separate2(vrHalfEdge *he, SFBool orient)
{
  ASSERT(he);

  VRTRACE("\t\tSeparate2\n");

  if (he->Prev()->isNullEdge())
	{
ASSERT(0);
		VRTRACE("\t\t\the->Prev->isNullEdge\n");
    if(((he->Prev() == he->Prev()->GetEdgeHe(HE1)) && orient) ||
       ((he->Prev() == he->Prev()->GetEdgeHe(HE2)) && !orient))
    {
			VRTRACE("\t\t\the=he->Prev\n");
      he = he->Prev();
    }
  }
  
  he->GetSolid()->lmev(he, he, *he->GetVertex());
 
//  if (orient)
//	{
// Reverse the orientation if told to do so
//    vrEdge *e = he->Prev()->GetEdge();
//    e->SwapHes();
//  }
 
  return he->Prev()->GetEdge();
}
 
static SFBool GetOrientation(vrHalfEdge *ref, vrHalfEdge *he1, vrHalfEdge *he2)
{
  vrHalfEdge *mhe1, *mhe2;
  SFBool retcode=0;
  
  VRTRACE("\t\tGetOrientation\n");
  
  mhe1 = he1->GetMate()->Next();
  mhe2 = he2->GetMate()->Next();

  if (mhe1 != he2 && mhe2 == he1)
	{
    retcode = he2->isConvexEdge();
  } else
	{
    retcode = he1->isConvexEdge();
  }

  if (mhe1->isSectorWide(0) && ref->isSectorWide(0))
	{
    retcode = !retcode;
  }

  return !retcode;
}
*/

