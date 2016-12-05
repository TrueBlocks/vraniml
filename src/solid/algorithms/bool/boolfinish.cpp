//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"

/*********************************************************************/
void vrBoolopRecord::Finish(void)
{
#ifdef _DEBUG
	if (!nFacesA)
	{
		A->Merge(B);
		*result = A;
		return;
	}
#endif
  ASSERT(nFacesA);

  CHECK(A);
	CHECK(B);
	
	for (Uint32 i=0; i<nFacesA; i++)
	{
#if 0
    /* 
     * Both FirstLoop and SecondLoop have the identical number of 
     * verts in the identical locations.
     * However SecondLoop is probably the outer loop at this point
     * and lmfkrh will ASSERT if given the face's lout.  So 
     * check for the condition and re-assign the lout if needed.
     * Do this for the NULL faces in both A and B.
     */
    if (facesA[i]->GetFirstLoop() == facesA[i]->GetLoopOut())
		{
      VRTRACE("changing outer loop for NULL facesA\n");
      facesA[i]->SetLoopOut(facesA[i]->GetSecondLoop());
    }
    facesA[nFacesA+i] =  A->lmfkrh(facesA[i]->GetFirstLoop());

    if (facesB[i]->GetFirstLoop() == facesB[i]->GetLoopOut())
		{
      VRTRACE("changing outer loop for NULL FacesB\n");
      facesB[i]->SetLoopOut(facesB[i]->GetSecondLoop());
    }
    facesB[nFacesB+i] =  B->lmfkrh(facesB[i]->GetFirstLoop());
#else
    facesA[nFacesA+i] =  A->lmfkrh(facesA[i]->GetSecondLoop());
    facesB[nFacesB+i] =  B->lmfkrh(facesB[i]->GetSecondLoop());
if (noVV)
{
	vrSwap(facesA[i], facesA[nFacesA+i]); 
	vrSwap(facesB[i], facesB[nFacesA+i]); 
}
#endif
  }
  
//  DEB(this, "this after lmfkrh's");

  *(result) = new vrSolid();

  switch (op)
	{
  case vrUNION:
    for (i=0; i<nFacesA; i++)
		{
      A->MoveFace(facesA[i], *(result));
      B->MoveFace(facesB[i], *(result));
    }
    (*result)->Cleanup();
    
    /* glue null faces */
    for (i=0; i<nFacesA; i++)
		{
      (*result)->lkfmrh(facesA[i], facesB[i]);
      (*result)->LoopGlue(facesA[i]);
    }
    break;
    
  case vrINTERSECTION:
    for (i=0; i<nFacesA; i++)
		{
      A->MoveFace(facesA[i+nFacesA], *(result));
      B->MoveFace(facesB[i+nFacesB], *(result));
    }
    
    (*result)->Cleanup();
    
    /* glue null faces */
    for (i=0; i<nFacesA; i++)
		{
      (*result)->lkfmrh(facesA[nFacesA+i], facesB[nFacesA+i]);
      (*result)->LoopGlue(facesA[nFacesA+i]);
    }
    break;
    
  case vrDIFFERENCE:
    /* create temporary solid */
    vrSolid *tmpSolid = new vrSolid();
    for (i=0; i<nFacesA; i++)
		{
      VRTRACE("Moving faces\n");
      A->MoveFace(facesA[i], *(result));
      B->MoveFace(facesB[i+nFacesB], tmpSolid);
    }
	    
    DEB((*result), "result after movefaces");
    DEB(tmpSolid, "tmpSolid after movefaces");

    /* revert the topology */
    VRTRACE("Reverting tmpSolid\n");
    tmpSolid->Revert();
    
    (*result)->Merge(tmpSolid);
    delete tmpSolid;
    
    (*result)->Cleanup();
    
    /* glue null faces */
    for (i=0; i<nFacesA; i++)
		{
      (*result)->lkfmrh(facesA[i], facesB[nFacesA+i]);
      (*result)->LoopGlue(facesA[i]);
    }
    break;
  }
  
//	DEB((*result), "result after Finish");

  A->Cleanup();
  B->Cleanup();
  return;
}

