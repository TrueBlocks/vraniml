//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid\Solid.h"
#include "Solid\Face.h"

void vrFace::RemoveColinearVerts(LISTPOS& ePos)
{
	LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);
		
		vrHalfEdge *start = l->halfedges.GetHead();

		vrHalfEdge *he    = start;

		vrVertex *prev = he->Prev()->GetVertex();
		vrVertex *v = he->GetVertex();

		do
		{
			vrVertex *next = he->Next()->GetVertex();

			// If both sides of the edge are colinear then we can remove it
			if (he->GetMate() &&
					(he->Prev()->GetMate() == he->GetMate()->Next()) && 
					Colinear(*prev, *v, *next))
			{
				vrHalfEdge *n = he->Next();
				//vrFace *f2 = he->GetMateFace();
					
				// Before removing the halfedges make sure nothing is pointing to it.
				if ((vrEdge*)ePos==he->GetEdge())
				{
					GetSolid()->edges.GetNext(ePos);
				}
				if (he == start || he->GetMate() == start)
				{
					if (he->GetMate() == he->Prev())
					{
						start = he->Prev()->Prev();
					} else
					{
						start = he->Prev();
					}
				}

				// Now remove the colinearity
				GetSolid()->lkev(he, he->GetMate());

				//prev = prev; // keep checking from prev
				v = next;
				he = n;

				ASSERT(start->GetVertex()!=(vrVertex*)DELETED);
			} else
			{
				he = he->Next();
				prev = v;
				v = next;
			}
		} while (he != start);
	}
}

void vrSolid::RemoveCoplaneColine(void)
{
	return;
}

/*
//afxTraceEnabled=TRUE;
//DEB(this, "solid");

	// Make sure face equations are calced
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
//		if (!f->calced) f->CalcEquation();
		f->CalcEquation();
	}

	// Look at each edge and remove coplanarities
	// Note: it is assumed that removing a co-planar face does not
	//       cause a previously checked edges to become an edge across
	//       two coplanar faces (therefor we only need to spin through 
	//       the list of edges once).
DEB(this, "solid");
	LISTPOS ePos = edges.GetHeadPosition();
	while (ePos)
	{
	  vrEdge *e = edges.GetNext(ePos);
		
		vrHalfEdge *he1 = e->GetHe(HE1);
		vrHalfEdge *he2 = e->GetHe(HE2);

		if (he1 && he2)
		{
			vrVertex   *v1  = he1->GetVertex();
			vrVertex   *v2  = he2->GetVertex();

			vrFace *f1 = he1->GetFace();
			vrFace *f2 = he2->GetFace();
			
			SFVec3f n1 = f1->GetNormal();
			SFVec3f n2 = f2->GetNormal();
			ASSERT(n1==Normalize(n1));
			ASSERT(n2==Normalize(n2));

			if (Colinear(n1, n2) && (n1 != -n2))
			{ 
				if (f1 != f2)
				{
					lkef(he1, he2);
				} else
				{
					if (he1->isNullStrut())
					{
						ASSERT(he2->isNullStrut());
						// Remove the null strut
						if (he1->Next() == he2)
						{
							lkev(he2, he1);
						} else
						{
							lkev(he1, he2);
						}
					} else
					{
						//VRTRACE("***************************************************\n");
						//VRTRACE("Coplanarity at edge %d\n", e->GetIndex());
						DEBHE(he1, "");
						DEBHE(he2, "");
						DEB(f1, "f1");
						DEB(f2, "f2");
						//					ASSERT(0);
						DEB(f1, "f1");
						//VRTRACE("***************************************************");
					}
				}

				f1->CalcEquation();
	//			ASSERT(f1->isPlanar());

				f1->RemoveColinearVerts(ePos);
			}
		}
  }
DEB(this, "solid");
  
	// Spin through one more time to remove colinear verts in faces that were not
	// processed above.
	fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		f->RemoveColinearVerts(fPos); // Note: fPos will never cause an edge skip
#ifdef _DEBUG
		//f->SetColor(colorMap[f->GetIndex()%MAX_COLORS]);
#endif
	}
DEB(this, "solid");

	return;
}
*/

/*
//********************************************************************
SFBool vrSolid::hasCoplanarFaces(void) const
{
	LISTPOS ePos = edges.GetHeadPosition();
	while (ePos)
	{
	  vrEdge *e = edges.GetNext(ePos);
		
		if (!e->GetHe(HE1)->isNullEdge())
		{
			ASSERT(e->GetHe(HE1)->GetFace() != e->GetHe(HE2)->GetFace());

			SFVec3f n1 = e->GetHe(HE1)->GetFaceNormal();
			SFVec3f n2 = e->GetHe(HE2)->GetFaceNormal();
			ASSERT(n1==Normalize(n1));
			ASSERT(n2==Normalize(n2));
			if (Colinear(n1, n2) && (n1 != -n2))
			{ 
				return TRUE;
			}
		}
	}
	return FALSE;
}

void vrSolid::RemoveCoplanarFaces(void)
{
  vrFace *f2;
  vrHalfEdge *he;
  
  LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
    //
    // We assume that faces that are not BRAND_NEW or ALTERED have
    // already been checked.  This will lower the number of
    // coplanar checks we have to perform.
    //
//  	if (f->Marked2(ALTERED) || f->Marked2(BRANDNEW))
    if (f->hasCoplanarNeighbor(&f2, &he)) 
		{
      DEB(f, "\tf is coplanar with f2");
      DEB(f2, "\tf2 will be removed");
      vrFace *next;
			f->RemoveCoplanarFace(f2, he, &next);
      CHECK(this);
    }
  }
}

//********************************************************************
SFBool vrFace::hasCoplanarNeighbor(vrFace **faceOut, vrHalfEdge **heOut) const
{
  vrHalfEdge *he = lout->GetFirstHe();
  vrHalfEdge *first = he;
  vrHalfEdge *next;
  vrFace *f2;
//  SFVec3f n1, n2;
//  SFFloat d1, d2;

//  n1 = GetNormal();
//  d1 = GetD();
  
  do {
    next = he->Next();
    
    f2 = he->GetMateFace();
//    n2 = f2->GetNormal();
//    d2 = f2->GetD();

//    if ((n1 == n2)) {
//      if (vrCompare(d1, d2) == 0) {
      if (isCoplanar(f2)) {
			  if (!he->isNullStrut()) {
				  if (faceOut) *faceOut = f2;
				  if (heOut)   *heOut   = he;
				  return TRUE;
			  }
      }
//      }
//    }
    he = next;
  } while (he != first);
  
  VRTRACE("\n\n");

  if (faceOut) *faceOut = NULL;
  if (heOut)   *heOut   = NULL;
  return FALSE;
}

#define DEBHE(a, b)

void vrFace::RemoveCoplanarFace(vrFace *f2, vrHalfEdge *he, vrFace **nextOut)
{
  ASSERT(f2);
  ASSERT(he);
  ASSERT(nextOut);
  ASSERT(he->GetMateFace() == f2);
  
  DEB(this, "\t\tThis face before removal");

  if (f2 == this)
	{
    VRTRACE("\t\t(f2 == this)\n\t\t"
          "Calling lkemr(%d %d)\n\t\tmate: ", he->GetMate()->GetIndex(), he->GetIndex());
    DEBHE(he->GetMate(), "\t\the: ");
    DEBHE(he, "\n");
    solid->lkemr(he->GetMate(), he);
    AdjustOuterLoop();
  } else
	{
    VRTRACE("\t\t(f2 != this)\n\t\t"
          "Calling kef(%d, %d, %d)\n\t\tf2->index: %d\n\t\the->Next(): ", 
      f2->GetIndex(), he->Next()->GetIndex(), he->GetMate()->Next()->GetIndex(), f2->GetIndex());
    DEBHE(he->Next(), "\n\t\the->mate->next: ");
    DEBHE(he->GetMate()->Next(), "\n");
    solid->kef(f2->GetIndex(), he->GetIndex(), he->GetMate()->GetIndex());
  }
  
  DEB(this, "This face after removal");
  CalcEquation();
  ASSERT(isPlanar());
  
  if (hasCoplanarNeighbor(&f2, &he)) {
    // the recursive 'nextOut' here does not get used...
		VRTRACE("\t\tRecursing to take care of others....\n");
    RemoveCoplanarFace(f2, he, nextOut);
  }
  
  // ...Becuase it is overwritten upon return, here.
  *nextOut = Next();
}

void vrFace::AdjustOuterLoop(void)
{
  SFBool done=FALSE;
  
  // make the most outer loop of the face the lout, we assume here
  // that if an adjustment is made the loops are correctly oriented.
  // That is: It is not the case that an old inner loop is backwards.

  DEB(this, "AdjustOuterLoop: this face");

  if (nLoops() == 1) {
    lout = GetFirstLoop();
    return;
  }

  while (!done) {
    done=TRUE;
    LISTPOS lPos = loops.GetHeadPosition();
		while (lPos);
		{
			vrLoop *l = loops.GetNext(lPos);
      // Look at each loop that is not the outer loop...
      if (l != lout) 
			{
        DEB(lout, "lout");
        DEB(l,    "l");
        vrVertex *v = lout->GetFirstHe()->GetVertex();
        vrIntersectRecord rec;
        SFInt32 drop = GetDominantComp(GetNormal());
        if (l->Contains(v, drop, rec)) 
				{
          VRTRACE("l contains the vertex from lout -- changing lout\n");
          done=FALSE;
          lout = l;
          DEB(this, "this face after alteration");
          break;
        } else 
				{
          VRTRACE("l does not contain the vertex from lout\n");
        }
      }
    }
  }
}

SFBool vrFace::isCoplanar(vrFace *f2) const
{
  SFVec3f n1    = GetNormal();
  SFVec3f n2    = f2->GetNormal();
  SFVec3f cross = CrossProduct(n1, n2);

  if (CloseEnough(cross)) {
    VRTRACE("Found coplanarity\n");
    DEB(this, "checking this face");
    DEB(f2, "against this face");
    VRTRACE("Normal of this:        %3.8f %3.8f %3.8f\n", n1.x, n1.y, n1.z);
    VRTRACE("Normal of f2:          %3.8f %3.8f %3.8f\n", n2.x, n2.y, n2.z);
    VRTRACE("Cross prod of normals: %3.8f %3.8f %3.8f\n", cross.x, cross.y, cross.z);
    VRTRACE("isCoplanar: %d\n", CloseEnough(cross));
  }
   
  return CloseEnough(cross);
}
*/