#ifndef __BOOLFACEVERT_H3D
#define __BOOLFACEVERT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#define MAX_NEIGHBORS 20
class vrBoolopRecord;

/*********************************************************************************/
class vrVFNeighborhood 
{
public:
  vrHalfEdge *sector;
  SFInt32      cl;
	SFBool    intersects;

	void Show(vrDumpContext& dc) const;
};

class vrBoolVertFaceClassifyRecord
{
  vrPlane       SP;
  vrVertex         *v;
  vrFace           *f;
  vrBoolopRecord   *bopRec;
  SFBool          isB;
  SFInt32            op;

	Uint32           nNbrs;
  vrVFNeighborhood  neighbors[MAX_NEIGHBORS];

public:
         vrBoolVertFaceClassifyRecord (void);
        ~vrBoolVertFaceClassifyRecord (void);

  void   Reset                       (vrBoolopRecord *bopR);
  void   VF_Classify                 (Uint32 i, SFBool isB);
  
private:
  void   SetVertexFace               (Uint32 i, SFBool isB);
  void   VF_GetNeighborhood          (void);
  void   VF_ReclassifyOnSectors      (void);
  void   VF_ReclassifyOnEdges        (void);
  void   VF_InsertNullEdges          (void);
	void   ShiftDown                 (void);
	SFBool PrepareNextCrossing       (void);
	void   FindNextCrossing          (vrHalfEdge **head, vrHalfEdge **tail);
	void   Seperate                  (vrHalfEdge *head, vrHalfEdge *tail);
   
  void   VF_AddNeighborhood          (vrHalfEdge *he, SFInt32 cl);
  
#ifdef _DEBUG
  void   Show                        (vrDumpContext& dc) const;
#endif
};

inline vrBoolVertFaceClassifyRecord::vrBoolVertFaceClassifyRecord(void)
{
  v      = NULL;
  f      = NULL;

  bopRec = NULL;
  isB = (SFBool)-1;

	nNbrs = 0;
}

inline vrBoolVertFaceClassifyRecord::~vrBoolVertFaceClassifyRecord() 
{
}

inline void vrBoolVertFaceClassifyRecord::Reset(vrBoolopRecord *bopR)
{
  ASSERT(bopR);

  bopRec = bopR;
  op     = bopR->GetOperation();
  v      = NULL;
  f      = NULL;

	nNbrs = 0;
}

inline void vrBoolVertFaceClassifyRecord::VF_AddNeighborhood(vrHalfEdge *he, SFInt32 cl)
{
  ASSERT(nNbrs < MAX_NEIGHBORS);

  neighbors[nNbrs  ].sector     = he;
  neighbors[nNbrs  ].cl         = cl;
  neighbors[nNbrs++].intersects = TRUE;
}

#endif