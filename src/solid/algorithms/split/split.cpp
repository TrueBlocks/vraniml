//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Split.h"

vrSplitRecord spRec;

SFBool vrSolid::Split(const vrPlane& SP, vrSolid **Above, vrSolid **Below)
{
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
    f->CalcEquation();
  }

  spRec.Reset(SP, this, Above, Below);
  
  SetFaceMarks(UNKNOWN);
  SetVertexMarks(UNKNOWN);

  DEB(&spRec, "upon creation\n");

  spRec.Generate();
  DEB(&spRec, "after generate\n");

  if (!spRec.Classify()) 
	{
	  DEB(&spRec, "classify returns false\n");
    return FALSE;
  } 
  DEB(&spRec, "after classify\n");

  spRec.Connect();
  DEB(&spRec, "after connect\n");

  spRec.Finish();
  DEB(&spRec, "upon finish\n");

  spRec.Complete();
  DEB(&spRec, "Completely complete\n");

#ifdef _DEBUG
  if (*Above) CHECK((*Above));
  if (*Below) CHECK((*Below));
#endif

	return TRUE;
}

void vrSplitRecord::AddVert(vrVertex *v)
{
  ASSERT(v);

  if (v->IsMarked(ON)) 
    return;

  v->SetMark(ON);

  ASSERT(nVerts < MAX_ON_VERTS);
  verts[nVerts++] = v;
}

void vrSplitRecord::Complete(void)
{
  /* Perhaps these next two a just for debugging but I can't remember. */
  (*A)->Renumber();
  (*B)->Renumber();

	(*A)->RemoveCoplaneColine();
	(*B)->RemoveCoplaneColine();
}

#ifdef _DEBUG
void vrSplitRecord::Verify(void) const
{
  if (s)
	{
    CHECK(s);
  }

  if (*A)
	{
    CHECK(*A);
  }

  if (*B)
	{
    CHECK(*B);
  }

  if (!nFaces)
	{
    for (Uint32 i=0;i<nEdges;i++)
		{
      CHECK(edges[i]);
    }
  } else {
    for (Uint32 i=0;i<nFaces;i++)
		{
      CHECK(faces[i]);
    }
  }
}

void vrSplitRecord::Show(vrDumpContext& dc) const
{
  if (s)
	{
    DEB(s, "vrSolid s");
  }

  if (*A)
	{
    DEB(*A, "vrSolid A");
  }

  if (*B)
	{
    DEB(*B, "vrSolid B");
  }

  VRTRACE("Verts\n");
  for (Uint32 i=0;i<nVerts;i++)
	{
    DEB(verts[i], "");
    VRTRACE("\n");
  }

  VRTRACE("Edges\n");
  for (i=0;i<nEdges;i++)
	{
    DEB(edges[i], "");
  }

  VRTRACE("Faces\n");
  for (i=0;i<nFaces;i++)
	{
    DEB(faces[i], "");
  }
}
#endif

