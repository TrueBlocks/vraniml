#ifndef __BOOLVERTVERT_H3D
#define __BOOLVERTVERT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

/*********************************************************************************/
#define MAX_SECTORS 100
#define BAD_CROSSING 12

class vrVVNeighborhood 
{
public:
  vrHalfEdge *he;
  SFVec3f    vNext;
  SFVec3f    vPrev;
  SFVec3f    vCross;
	long       fromBisect;

	void Show(vrDumpContext& dc) const;
};

class vrSector 
{
public:
  Uint32  indexA;
  SFInt32   clPrevA;
  SFInt32   clNextA;

  Uint32  indexB;
  SFInt32   clPrevB;
  SFInt32   clNextB;

  SFInt32   intersects;
#define SAME 1
#define OPP  2
  SFBool onFace;

	void Show(vrDumpContext& dc) const;
};

class vrBoolVertVertClassifyRecord
{
  vrPlane       SP;
  vrVertex         *v;                    /* vertex we are classifying */
  vrVertex         *v2;                   /* vertex we are classifying */
  vrBoolopRecord   *bopRec;               /* Pointer to the set operation record */
  SFBool          isB;
  SFInt32            op;

	Uint32           nNbrsA;
	vrVVNeighborhood  nhA[MAX_SECTORS];
	
	Uint32           nNbrsB;
	vrVVNeighborhood  nhB[MAX_SECTORS];

	Uint32           nSectors;
 	vrSector          sectors[MAX_SECTORS];

public:
                vrBoolVertVertClassifyRecord(void);
               ~vrBoolVertVertClassifyRecord(void);

  void   Reset                      (vrBoolopRecord *bopR);
  void   VV_Classify                (Uint32 i);
  
  /* For vertex/vertex classifier */
private:
  void    SetVertexVertex           (Uint32 i);
  Uint32  Preprocess                (vrVertex *v, SFBool isA);
  void    GetNeighborhood           (void);

  void    ReclassifyOnSectors       (void);
  void    ReclassifyOnEdges         (void);
	void    ReclassifyDoublyOnEdges   (Uint32 i);
	void    ReclassifySinglyOnEdges   (Uint32 i);

  void    InsertNullEdges           (void);
		void    FindNextCrossing          (vrHalfEdge **aHead, vrHalfEdge **aTail, vrHalfEdge **bHead, vrHalfEdge **bTail);
			SFBool PrepareNextCrossing       (void);
//			void		FixSector                 (Uint32 k);
			SFBool IsValidCrossing           (void);
			void    ShiftDown                 (void);
		void    Seperate                  (vrHalfEdge *aHead, vrHalfEdge *aTail, vrHalfEdge *bHead, vrHalfEdge *bTail);

	void    AddSector                 (Uint32 i, Uint32 j);
	void    AddNeighbor               (vrHalfEdge *he, const SFVec3f& vP, const SFVec3f& vN, SFBool isB, long fromBisect);

#ifdef _DEBUG
  void    Show                      (vrDumpContext& dc) const;
  void    Show1                     (vrDumpContext& dc) const;
#endif
};

inline vrBoolVertVertClassifyRecord::vrBoolVertVertClassifyRecord(void)
{
  v      = NULL;
  v2     = NULL;

  bopRec = NULL;
  isB = (SFBool)-1;

	nNbrsA = 0;
	nNbrsB = 0;
	nSectors = 0;
}

inline vrBoolVertVertClassifyRecord::~vrBoolVertVertClassifyRecord() 
{
}

inline void vrBoolVertVertClassifyRecord::Reset(vrBoolopRecord *bopR)
{
  ASSERT(bopR);

  bopRec = bopR;
  op     = bopR->GetOperation();
  v      = NULL;
  v2     = NULL;

	nNbrsA = nNbrsB = nSectors = 0;

#ifdef _DEBUG
	for (int j=0;j<MAX_SECTORS;j++)
	{
		// Blow away all data in the arrays to make it easier to see problems when debugging
		nhA[j].he = (vrHalfEdge*)DELETED;
		nhB[j].he = (vrHalfEdge*)DELETED;
		sectors[j].indexA = sectors[j].indexB = DELETED;
	}
#endif

}

inline void vrBoolVertVertClassifyRecord::SetVertexVertex(Uint32 i)
{
  ASSERT(bopRec);

  v     = bopRec->GetVertVertA(i);
  v2    = bopRec->GetVertVertB(i);
}

extern SFBool  SectorTest       (vrVVNeighborhood *nhi, vrVVNeighborhood *nhj);
#define DEBI(th, msg) { vrDumpContext dc; extern SFInt32 indents; indents=3; (th)->Show(&dc); indents=0; }

#endif