//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"

/*********************************************************************************/
static vrBoolopRecord bopRec;

SFBool vrSolid::BoolOp(vrSolid *A, vrSolid *B, vrSolid **result, SFInt32 operation, void *statRec)
{
  CHECK(A);
  CHECK(B);

  *result = NULL;

  A->SetFaceMarks(UNKNOWN);
  A->SetVertexMarks(UNKNOWN);
  B->SetFaceMarks(UNKNOWN);
  B->SetVertexMarks(UNKNOWN);

  A->SetMark(SOLID_A);
  B->SetMark(SOLID_B);
  
  LISTPOS fPos = A->faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = A->faces.GetNext(fPos);
    f->CalcEquation();
  }
  fPos = B->faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = B->faces.GetNext(fPos);
    f->CalcEquation();
  }

#ifdef _DEBUG
  /* Let's mark everything so we can distinguish it. */
  RENUM(vrFace,   0,   A->faces);
  RENUM(vrFace,   100, B->faces);
  RENUM(vrEdge,   0,   A->edges);
  RENUM(vrEdge,   100, B->edges);
  RENUM(vrVertex, 0,   A->verts);
  RENUM(vrVertex, 100, B->verts);
#endif

//	A->Write(NULL, TRUE);
//	B->Write(NULL, TRUE);

#ifdef _STATS
	bopRec.stats = (CStatistics *)statRec;
#endif
	
  /* Prepare the boolean operation record */
  bopRec.Reset(A, B, result, operation);

  DEBUG_MARKER("RESET");
  DEB(&bopRec, "After reset\n"); 

  bopRec.Generate();
	if (bopRec.quit) return TRUE;

#if 0 //def _DEBUG
		SFBool val=FALSE;
		if (val)
			afxTraceEnabled=TRUE;
#endif


  DEBUG_MARKER("GENERATE");
  DEB(&bopRec, "After generate\n"); 

  SFBool ret = TRUE;
	
	if (!bopRec.Classify())
	{
		if (bopRec.quit) return TRUE;

//    DEBUG_MARKER("CLASSIFY-FALSE");
//    DEB(&bopRec, "After classify -- returns FALSE -- trying LastDitch\n"); 

    ret = bopRec.LastDitch();

	  // Avoids unwanted assertions about NULL edges
		bopRec.Reset(NULL, NULL, result, operation);

//		DEBUG_MARKER("LAST DITCH");
//	  DEB(&bopRec, "After last ditch\n"); 

  } else
	{

//	  DEBUG_MARKER("CLASSIFY-TRUE");
//		DEB(&bopRec, "After classify -- returns TRUE\n"); 

    bopRec.Connect();

		if (bopRec.quit) return TRUE;

//		DEBUG_MARKER("CONNECT");
//		DEB(&bopRec, "After connect\n"); 

		bopRec.Finish();

		if (bopRec.quit) return TRUE;

	  // Avoids unwanted assertions about NULL edges
		bopRec.Reset(NULL, NULL, result, operation);

//		DEBUG_MARKER("FINISH");
//		DEB(&bopRec, "After finish\n"); 
	}

  if (ret)
	{
    bopRec.Complete();
//		DEBUG_MARKER("COMPLETE");
  }

//  DEBUG_MARKER("COMPLETELY COMPLETE");
//	DEB(&bopRec, "After completly complete\n"); 

  return ret;
}

void vrBoolopRecord::Complete(void)
{
  (*result)->Renumber();  // This is needed for some reason but I forget why 
	(*result)->RemoveCoplaneColine();
}

SFBool vrBoolopRecord::LastDitch(void)
{
#ifdef _DEBUG
//	A->SetColor(vrWhite);
//	B->SetColor(vrWhite);
#endif

  /* 
   * There was no intersection proper.  It is now the case that either
   * 
   *     1. A contains B proper
   *     2. B contains A proper
   *     3. A and B are identical
   *     4. A and B are completly seperate
   *
   * Each of these two cases is handled differently depending on the boolop
   */
  SFBool AcontainsB=FALSE;
  SFBool BcontainsA=FALSE;
  AcontainsB = A->Contains(B);
  if (AcontainsB)
	{
    // case 1 and case 3
    switch (op)
		{
    case vrUNION:
      *result = new vrSolid();
      (*result)->Merge(A);
      return TRUE;
    case vrINTERSECTION:
      *result = new vrSolid();
      (*result)->Merge(B);
      return TRUE;
    case vrDIFFERENCE:
			BcontainsA = B->Contains(A);
			if (BcontainsA)
			{
				// case 3: identical
				*result = NULL;
				return FALSE;
			} else
			{
				*result = new vrSolid();
				(*result)->Merge(A);
				return TRUE;
			}
    }
  }
  
  BcontainsA = B->Contains(A);
  if (BcontainsA)
	{
    /* case 2 */
    switch (op)
	{
    case vrUNION:
      *result = new vrSolid();
      (*result)->Merge(B);
      return TRUE;
    case vrINTERSECTION:
      *result = new vrSolid();
      (*result)->Merge(A);
      return TRUE;
    case vrDIFFERENCE:
      /* Kind of un-defined */
      *result = NULL;
      return FALSE;
    }
  } else
	{
    /* case 4 */
    switch (op) {
    case vrUNION:
      *result = new vrSolid();
      (*result)->Merge(A);
      (*result)->Merge(B);
      return TRUE;
    case vrINTERSECTION:
      *result = NULL;
      return FALSE;
    case vrDIFFERENCE:
      *result = new vrSolid();
      (*result)->Merge(A);
      return TRUE;
    }
  }
  
  return FALSE;
}

#ifdef _DEBUG
static char s[][20] = { "NONE", "UNION", "INTERSECTION", "DIFFERENCE" };

void vrBoolopRecord::Show1(vrDumpContext& dc) const
{
/*
  if (!traceContext)
		return;
*/

  VRTRACE("/********** operation: %s *****************************/\n", s[op]);
  
  VRTRACE("VertVertRecords\n");
  for (Uint32 i=0;i<nVertsV;i++) {
    vertsV[i].va->Show(dc);
    VRTRACE("\n");
    vertsV[i].vb->Show(dc);
    VRTRACE("\n");
  }
  
  VRTRACE("Verts of A to vrFace of B\n");
  for (i=0;i<nVertsA;i++) {
    vertsA[i].v->Show(dc);
    VRTRACE("\n");
    vertsA[i].f->Show(dc);
    VRTRACE("\n");
  }
  
  VRTRACE("Verts of B to vrFace of A\n");
  for (i=0;i<nVertsB;i++) {
    vertsB[i].v->Show(dc);
    VRTRACE("\n");
    vertsB[i].f->Show(dc);
    VRTRACE("\n");
  }
  
  if (!nFacesA) {
    
//  (e1)->GetHe(HE1)->cl,
//  (e1)->GetHe(HE2)->cl,
//  (e2)->GetHe(HE1)->cl,
//  (e2)->GetHe(HE2)->cl);

#undef DEBEDGES
#define DEBEDGES(ssss, e1, e2) \
do \
{ \
  VRTRACE("%s A:(%3d %3d) -- B:(%3d %3d)\n", \
  ssss, \
  (e1)->GetVertexIndex(HE1), \
  (e1)->GetVertexIndex(HE2), \
  (e2)->GetVertexIndex(HE1), \
  (e2)->GetVertexIndex(HE2)); \
} while (0);
 
    VRTRACE("NullEdges\n");
    ASSERT(nEdgesA == nEdgesB);
    for (i=0;i<nEdgesA;i++)
		{
      DEBEDGES("", edgesA[i], edgesB[i]);
    }

    VRTRACE("No faces\n");

  } else {
    
    VRTRACE("Null Edges are invalid\n");
    
    VRTRACE("NewFaces from A\n");
    for (i=0;i<nFacesA;i++) {
      facesA[i]->Show(dc);
    }
    
    VRTRACE("NewFaces from B\n");
    for (i=0;i<nFacesB;i++) {
      facesB[i]->Show(dc);
    }
  }
}

void vrBoolopRecord::Show(vrDumpContext& dc) const
{
/*
  if (!traceContext)
		return;
*/

  VRTRACE("/********** operation: %s *****************************/\n", s[op]);
  
  if (A) {
    VRTRACE("vrSolid A\n");
    A->Show(dc);
  } else {
    VRTRACE("A is NULL\n");
  }
  
  if (B) {
    VRTRACE("vrSolid B\n");
    B->Show(dc);
  } else {
    VRTRACE("B is NULL\n");
  }
  
  if (*result) {
    VRTRACE("vrSolid result\n");
    (*result)->Show(dc);
  } else {
    VRTRACE("result is NULL\n");
  }
  
  Show1(dc);
}
#endif
