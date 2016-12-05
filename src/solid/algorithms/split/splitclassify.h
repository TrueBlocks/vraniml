#ifndef __SPLITCLASSIFY_H3D
#define __SPLITCLASSIFY_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

/*********************************************************************************/
class vrSplitNeighborhood
{
public:
  vrHalfEdge *sector;
  SFInt32      cl;

	void Show(vrDumpContext& dc) const;
};

/*********************************************************************************/
#define MAX_NEIGHBORS 20

class vrSplitClassifyRecord 
{
  vrPlane          SP;
  vrVertex            *v;                        /* vertex we are classifying */
  Uint32              nNbrs;                    /* number of neighborhoods */
  vrSplitNeighborhood  neighbors[MAX_NEIGHBORS]; /* neihgbors */
  vrSplitRecord       *spRec;                    /* Pointer to the split record */

public:
                vrSplitClassifyRecord            (void);
               ~vrSplitClassifyRecord            ();

  void   Reset                     (vrSplitRecord *spR);
  void   AddNeighborhood           (vrHalfEdge *he, SFInt32 cl);
  
  void   SetVertex                 (Uint32 i);
  
  /* For vertex/face classifier and split operation */
  void   GetNeighborhood           (void);
  void   ReclassifyOnSectors       (void);
  void   ReclassifyOnEdges         (void);
  void   InsertNullEdges           (void);
   
#ifdef _DEBUG
  void   Show                      (vrDumpContext& dc) const;
#endif
};

inline vrSplitClassifyRecord::vrSplitClassifyRecord(void)
{
  v      = NULL;

  spRec  = NULL;

  nNbrs  = 0;
}

inline vrSplitClassifyRecord::~vrSplitClassifyRecord() 
{
}

inline void vrSplitClassifyRecord::AddNeighborhood(vrHalfEdge *he, SFInt32 cl)
{
  ASSERT(nNbrs < MAX_NEIGHBORS);

  neighbors[nNbrs  ].sector = he;
  neighbors[nNbrs++].cl     = cl;
}

inline void vrSplitClassifyRecord::Reset(vrSplitRecord *spR)
{
  ASSERT(spR);

  spRec  = spR;
  SP     = spR->GetSplittingPlane();
  v      = NULL;

	nNbrs = 0;
}

inline void vrSplitClassifyRecord::SetVertex(Uint32 i)
{
  ASSERT(spRec);

  v     = spRec->GetVert(i);
  nNbrs = 0;
}

#endif
