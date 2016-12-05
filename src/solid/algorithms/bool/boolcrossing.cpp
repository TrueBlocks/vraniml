//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"
#include "BoolVertexClassify.h"

SFBool vrBoolVertVertClassifyRecord::PrepareNextCrossing(void)
{
	// We call this function each time we insert a null edge, 
	// therefor we can just look at sectors 0 and 1 and make 
	// sure that they form a valid crossing.  Note: a single
	// crossing may be valid

	// Remove non-intersecting sectors
	Uint32 n=0;
	for (Uint32 k=0;k<nSectors;k++)
	{
		if (sectors[k].intersects)
		{
			if (sectors[k].clPrevA == sectors[k].clPrevB)
			{
				sectors[k].intersects = BAD_CROSSING;
			}

			sectors[n] = sectors[k];
			n++;
		}
	}
	nSectors = n;

	if (nSectors>1)
	{
		if (op==vrUNION)
		{
			Uint32 n=0;
			for (Uint32 k=0;k<nSectors;k++)
			{
				if (sectors[k].intersects!=BAD_CROSSING)
				{
					sectors[n] = sectors[k];
					n++;
				}
			}
			nSectors = n;
		}
	}

	// move the first IN-OUT crossing in solid A to sector 0
	if (sectors[0].clNextA != OUT)
	{
		ShiftDown();
	}

	if (nSectors)
	{
		if (nSectors==1)
		{
			// check mates for coplaner
			SFVec3f normA = nhA[sectors[0].indexA].he->GetMate()->GetFaceNormal();
			SFVec3f normB = nhB[sectors[0].indexB].he->GetMate()->GetFaceNormal();

			sectors[0].onFace = FALSE;
			
			SFBool Ais180 = nhA[sectors[0].indexA].he->is180();
			SFBool Bis180 = nhB[sectors[0].indexB].he->is180();

			// At least one of these is a straight line
			ASSERT(Ais180 || Bis180);

			if (sectors[0].clPrevA == IN)
			{
				ASSERT(sectors[0].clNextA==OUT);
				if (sectors[0].intersects != BAD_CROSSING)
				{
					// IN-OUT | OUT-IN
					sectors[0].intersects = 1;
				} else
				{
					// IN-OUT | IN-OUT
					sectors[0].intersects = 2;

					if (!Bis180)
					{
						normB = nhB[sectors[0].indexB].he->Prev()->GetMate()->GetFaceNormal();
					} else if (!Ais180)
					{
						normA = nhA[sectors[0].indexA].he->Prev()->GetMate()->GetFaceNormal();
					}
				}
			} else
			{
				ASSERT(sectors[0].clPrevA == OUT);
				ASSERT(sectors[0].clNextA == IN);
				if (sectors[0].intersects != BAD_CROSSING)
				{
					// OUT-IN | IN-OUT
					sectors[0].intersects = 3;
				} else
				{
					// OUT-IN | OUT-IN
					sectors[0].intersects = 4;
				}
			}

			if (Colinear(normA, normB))
			{
				if (normA == normB)
				{
					sectors[0].onFace = SAME;
				} else
				{
					sectors[0].onFace = OPP;
					if (op != vrUNION)
					{
						if (sectors[0].intersects==2 || sectors[0].intersects==4)
						{
							nSectors = 0;
						}
					}
				}
			}

		} else
		{
			Uint32 n=0;
			for (Uint32 k=0;k<nSectors;k++)
			{
				if (sectors[k].intersects!=BAD_CROSSING)
				{
					sectors[n] = sectors[k];
					n++;
				}
			}
			nSectors = n;
			if (sectors[0].clNextA != OUT)
			{
				ShiftDown();
			}
			ASSERT(IsValidCrossing());
			/*
			while (!IsValidCrossing())
			{
				if (sectors[0].intersects==BAD_CROSSING)
				{
					FixSector(0);
				}
			
				if (sectors[1].intersects==BAD_CROSSING)
				{
					FixSector(1);
				}

				if (!IsValidCrossing())
				{
					ASSERT(0);
					//ShiftDown();
				}
			}
			*/
		}
	}

#ifdef _DEBUG
/*
if (nSectors)
{
	int group  = AfxGetApp()->GetProfileInt("Tests", "BoolLastGroup", 0);
	int testId = AfxGetApp()->GetProfileInt("Tests", "TestNum", 0);
	VRTRACE("// [%3d] %3d-%3d-%3d %d;", sectors[0].intersects, group, testId, op, sectors[0].onFace); //, Ais180, Bis180);
	nhA[sectors[0].indexA].he->GetVertex()->WriteNeighborhood();
	nhB[sectors[0].indexB].he->GetVertex()->WriteNeighborhood();
	VRTRACE(";");
	VRTRACE("\n");
	
	DEB(this, "");
}
*/
#endif

	return (nSectors>0);
}

#ifdef _DEBUG
void vrVertex::WriteNeighborhood(void)
{
	Uint32 cnt=0;
	vrHalfEdge *start = GetHe();
	vrHalfEdge *he = start;
	do
	{
		cnt++;
		he = he->GetMate()->Next();
		if (he->is180())
		{
			cnt++;
		}
	} while (he != start);

	VRTRACE("%d;", cnt+1);

	vrVertex *v = he->GetVertex();
	VRTRACE("%f %f %f;", v->x, v->y, v->z);

	start = GetHe();
	he = start;
	do
	{
		v = he->GetMate()->GetVertex();
		VRTRACE("%f %f %f;", v->x, v->y, v->z);
		he = he->GetMate()->Next();
		if (he->is180())
		{
			SFVec3f bi = he->Bisect();
			VRTRACE("%f %f %f;", bi.x, bi.y, bi.z);
		}
	} while (he != start);

	VRTRACE("%d;", cnt);
	start = GetHe();
	he = start;
	Uint32 i=0;
	do
	{
		Uint32 next = NextNum(i, cnt);
		VRTRACE("3 %d 0 %d;", i+1, next+1);
		i++;
		he = he->GetMate()->Next();
		if (he->is180())
		{
			next = NextNum(i, cnt);
			VRTRACE("3 %d 0 %d;", i+1, next+1);
			i++;
		}
	} while (he != start);
}
#endif

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
void vrBoolVertVertClassifyRecord::FindNextCrossing(vrHalfEdge **aHeadRes, vrHalfEdge **aTailRes, vrHalfEdge **bHeadRes, vrHalfEdge **bTailRes)
{
  vrHalfEdge *aHead=NULL, *aTail=NULL, *bHead=NULL, *bTail=NULL;

	if (nSectors > 1)
	{
	  ASSERT(sectors[1].clNextA != sectors[1].clPrevA);
	  ASSERT(sectors[1].clNextB != sectors[1].clPrevB);
	
		ASSERT(sectors[0].clPrevA == IN);
		ASSERT(sectors[0].clNextA == OUT);
		ASSERT(sectors[0].clPrevB == OUT);
		ASSERT(sectors[0].clNextB == IN);

		ASSERT(sectors[1].clPrevA == OUT);
		ASSERT(sectors[1].clNextA == IN);
		ASSERT(sectors[1].clPrevB == IN);
		ASSERT(sectors[1].clNextB == OUT);

		aHead = nhA[sectors[0].indexA].he;
		bHead = nhB[sectors[0].indexB].he;
		aTail = nhA[sectors[1].indexA].he;
		bTail = nhB[sectors[1].indexB].he;

		sectors[0].intersects=FALSE;
		sectors[1].intersects=FALSE;

	} else
	{
		ASSERT(nSectors==1);

	  ASSERT(sectors[0].clNextA != sectors[0].clPrevA);
	  ASSERT(sectors[0].clNextB != sectors[0].clPrevB);
	
		SFBool Ais180 = nhA[sectors[0].indexA].he->is180();
		SFBool Bis180 = nhB[sectors[0].indexB].he->is180();

		// At least one of these is a straight line
		ASSERT(Ais180 || Bis180);

		switch (sectors[0].intersects)
		{
		case 1:
			{
				ASSERT(sectors[0].clPrevA == IN);
				ASSERT(sectors[0].clNextA == OUT);
				ASSERT(sectors[0].clPrevB == OUT);
				ASSERT(sectors[0].clNextB == IN);

				aHead = nhA[sectors[0].indexA].he;
				bHead = nhB[sectors[0].indexB].he;

				ASSERT(aHead); ASSERT(bHead);
				if (Ais180 && Bis180)
				{
					if (op!=vrUNION)
					{
						aTail = aHead->GetMate()->Next();
						ASSERT(aTail==aHead->Prev()->GetMate()); // since Ais180 doesn't matter

						bTail = bHead;
					} else
					{
						aTail = aHead;
						
						bTail = bHead->GetMate()->Next();
						ASSERT(bTail==bHead->Prev()->GetMate()); // since Bis180 doesn't matter
					}
					if (sectors[0].onFace==OPP)
					{
						if (op!=vrUNION)
						{
							aTail = aHead;
							
							bTail = bHead->GetMate()->Next();
							ASSERT(bTail==bHead->Prev()->GetMate()); // since Bis180 doesn't matter
						} else
						{
							aTail = aHead->GetMate()->Next();
							ASSERT(aTail==aHead->Prev()->GetMate()); // since Ais180 doesn't matter

							bTail = bHead;
						}
					}
				} else if (Ais180)
				{
					aTail = aHead->GetMate()->Next();
					ASSERT(aTail==aHead->Prev()->GetMate()); // since Ais180 doesn't matter

					bTail = bHead->Prev()->GetMate();
				} else
				{
					aTail = aHead->GetMate()->Next();

					ASSERT(Bis180);
					bTail = bHead->GetMate()->Next();
					ASSERT(bTail==bHead->Prev()->GetMate()); // since Bis180 doesn't matter
				}
			}
			break;
		case 3:
			{
				ASSERT(sectors[0].clPrevA == OUT);
				ASSERT(sectors[0].clNextA == IN);
				ASSERT(sectors[0].clPrevB == IN);
				ASSERT(sectors[0].clNextB == OUT);

				aTail = nhA[sectors[0].indexA].he;
				bTail = nhB[sectors[0].indexB].he;

				ASSERT(aTail); ASSERT(bTail);
				if (Ais180 && Bis180)
				{
					if (op!=vrUNION)
					{
						aHead = aTail->Prev()->GetMate();
						ASSERT(aHead==aTail->GetMate()->Next()); // since Ais180 doesn't matter

						bHead = bTail;
					} else
					{
						aHead = aTail;
						
						bHead = bTail->Prev()->GetMate();
						ASSERT(bHead==bTail->GetMate()->Next()); // since Ais180 doesn't matter
					}
					if (sectors[0].onFace==OPP)
					{
						if (op!=vrUNION)
						{
							aHead = aTail;
							
							bHead = bTail->Prev()->GetMate();
							ASSERT(bHead==bTail->GetMate()->Next()); // since Ais180 doesn't matter
						} else
						{
							aHead = aTail->Prev()->GetMate();
							ASSERT(aHead==aTail->GetMate()->Next()); // since Ais180 doesn't matter

							bHead = bTail;
						}
					}
				} else if (Ais180)
				{
					aHead = aTail->GetMate()->Next();
					ASSERT(aHead==aTail->Prev()->GetMate()); // since Ais180 doesn't matter

					bHead = bTail->GetMate()->Next();
				} else
				{
					aHead = aTail->Prev()->GetMate();

					ASSERT(Bis180);
					bHead = bTail->Prev()->GetMate();
					ASSERT(bHead==bTail->GetMate()->Next()); // since Ais180 doesn't matter
				}
			}
			break;
		case 2:
			{
				ASSERT(sectors[0].clPrevA == IN);
				ASSERT(sectors[0].clNextA == OUT);
				ASSERT(sectors[0].clPrevB == IN);
				ASSERT(sectors[0].clNextB == OUT);

				aHead = nhA[sectors[0].indexA].he;
				bTail = nhB[sectors[0].indexB].he;

				aTail = aHead->GetMate()->Next();
				bHead = bTail->GetMate()->Next();
			}
			break;
		case 4:
			{
				ASSERT(sectors[0].clPrevA == OUT);
				ASSERT(sectors[0].clNextA == IN);
				ASSERT(sectors[0].clPrevB == OUT);
				ASSERT(sectors[0].clNextB == IN);

				aTail = nhA[sectors[0].indexA].he;
				bHead = nhB[sectors[0].indexB].he;

				aHead = aTail->GetMate()->Next();
				bTail = bHead->GetMate()->Next();
			}
			break;
		default:
			ASSERT(0);
		}
		
/*
#ifdef _DEBUG
SFBool s = afxTraceEnabled;
afxTraceEnabled=TRUE;

int group  = AfxGetApp()->GetProfileInt("Tests", "BoolLastGroup",     0);
int testId = AfxGetApp()->GetProfileInt("Tests", "TestNum",      0);
VRTRACE("// [%3d] %3d-%3d-%3d %d (%d-%d);", sectors[0].intersects, group, testId, op, sectors[0].onFace, Ais180, Bis180);
nhA[sectors[0].indexA].he->GetVertex()->WriteNeighborhood();
nhB[sectors[0].indexB].he->GetVertex()->WriteNeighborhood();
VRTRACE(";");
VRTRACE("\n");
afxTraceEnabled=s;
#endif		
*/

		// Won't need it anymore
		sectors[0].intersects=FALSE;
	}

	ASSERT(aHead && aTail && bHead && bTail);
	VRTRACE("\taHead: %d-%d-%d\n\taTail: %d-%d-%d\n"
		  "\tbHead: %d-%d-%d\n\tbTail: %d-%d-%d\n",
      (aHead)->Prev()->GetIndex(), (aHead)->GetIndex(), (aHead)->Next()->GetIndex(),
      (aTail)->Prev()->GetIndex(), (aTail)->GetIndex(), (aTail)->Next()->GetIndex(),
      (bHead)->Prev()->GetIndex(), (bHead)->GetIndex(), (bHead)->Next()->GetIndex(),
      (bTail)->Prev()->GetIndex(), (bTail)->GetIndex(), (bTail)->Next()->GetIndex());
	*aHeadRes = aHead;
	*aTailRes = aTail;
	*bHeadRes = bHead;
	*bTailRes = bTail;
}

SFBool vrBoolVertVertClassifyRecord::IsValidCrossing(void)
{
	if (sectors[0].intersects==BAD_CROSSING) return FALSE;
	if (sectors[1].intersects==BAD_CROSSING) return FALSE;

	ASSERT(sectors[0].clPrevA != sectors[0].clNextA);
	ASSERT(sectors[0].clPrevB != sectors[0].clNextB);
	ASSERT(sectors[0].clPrevA == sectors[0].clNextB);
	ASSERT(sectors[0].clNextA == sectors[0].clPrevB);

	ASSERT(sectors[1].clPrevA != sectors[1].clNextA);
	ASSERT(sectors[1].clPrevB != sectors[1].clNextB);
	ASSERT(sectors[1].clPrevA == sectors[1].clNextB);
	ASSERT(sectors[1].clNextA == sectors[1].clPrevB);

	// Only choices after above ASSERTS
	//       s0                 s1
	// valid
	//   IN-OUT OUT-IN     OUT-IN IN-OUT
	//   OUT-IN IN-OUT     IN-OUT OUT-IN
	//
	// invalid
	//   IN-OUT IN-OUT     IN-OUT IN-OUT
	//   OUT-IN IN-OUT     OUT-IN IN-OUT
	return (sectors[0].clNextA!=sectors[1].clNextA);
}

void vrBoolVertVertClassifyRecord::ShiftDown(void)
{
	sectors[nSectors] = sectors[0];
	for (Uint32 i=0;i<nSectors;i++)
	{
		sectors[i] = sectors[i+1];
	}
}

