//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"
#include "BoolFaceClassify.h"
#include "BoolVertexClassify.h"

static vrBoolVertVertClassifyRecord vRec;
static vrBoolVertFaceClassifyRecord fRec;

/*********************************************************************/
SFBool vrBoolopRecord::Classify(void)
{
  nEdgesA = nEdgesB = 0;

noVV = (!(SFBool)nVertsV);

  fRec.Reset(this);
  DEBUG_MARKER("Vertex/Face Classifiers (VertFaces for A)");
  for (Uint32 i=0;i<nVertsA;i++)
	{
    fRec.VF_Classify(i, FALSE);
  }

  DEBUG_MARKER("Vertex/Face Classifiers (VertFaces for B)");
  for (i=0;i<nVertsB;i++)
	{
    fRec.VF_Classify(i, TRUE);
  }

#ifdef _DEBUG
//	if (AfxGetApp()->GetProfileInt("Debug", "SpecialCaseMessageBox", FALSE) && nVertsV)
//	{
//		AfxMessageBox("Bool --> Vertex-Vertex Classification");
//	}
#endif

#ifdef _DEBUG
//SFBool s = afxTraceEnabled;
//afxTraceEnabled=AfxGetApp()->GetProfileInt("Debug", "VertTrace", FALSE);
#endif

  vRec.Reset(this);
  DEBUG_MARKER("Vertex/Vertex Classifier");
  for (i=0;i<nVertsV;i++)
	{
    vRec.VV_Classify(i);
  }
DEB(this, "After");
#ifdef _DEBUG
//afxTraceEnabled=s;
#endif

#ifdef _DEBUG
  for (Uint32 k=0;k<nEdgesA;k++)
	{
    // Make sure all edges are consistantly oriented
//    ASSERT(edgesA[k]->GetHe(HE1)->cl == OUT);
//    ASSERT(edgesA[k]->GetHe(HE2)->cl == IN);
//    ASSERT(edgesB[k]->GetHe(HE1)->cl == OUT);
//    ASSERT(edgesB[k]->GetHe(HE2)->cl == IN);
  }
#endif

#ifdef _STATS
	if (stats) stats->cl.nVertsA += nVertsA;
	if (stats) stats->cl.nVertsB += nVertsB;
	if (stats) stats->cl.nVertsV += nVertsV;
	if (stats) stats->cl.nEdgesA += nEdgesA;
	if (stats) stats->cl.nEdgesB += nEdgesB;
#endif


  nVertsA = nVertsB = nVertsV = 0;

  return (nEdgesA > 2); //(nEdgesA != 0);
}

void vrBoolopRecord::AddEdgeA(vrEdge *e)
{
  ASSERT(e);
  ASSERT(nEdgesA < MAX_NULL_EDGES);
  edgesA[nEdgesA++] = e;
}

void vrBoolopRecord::AddEdgeB(vrEdge *e)
{
  ASSERT(e);
  ASSERT(nEdgesB < MAX_NULL_EDGES);
  edgesB[nEdgesB++] = e;
}

