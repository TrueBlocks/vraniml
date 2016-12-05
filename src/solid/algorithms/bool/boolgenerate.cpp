//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"

/*********************************************************************/
void vrBoolopRecord::Generate()
{
  /*
   * It is assumed here that all faces of both solids are maximal (i.e.
   * all coplanar neighbooring faces have been combined and all inessential
   * edges have been removed.
   */
  nVertsV = nVertsA = nVertsB = 0;
  
#ifdef _STATS
	if (stats) stats->gen.edgesA += A->edges.GetCount();
	if (stats) stats->gen.edgesB += B->edges.GetCount();
	if (stats) stats->gen.facesA += A->faces.GetCount();
	if (stats) stats->gen.facesB += B->faces.GetCount();
#endif

  /* Check each edge of solid A against all faces of solid B */
  LISTPOS ePos = A->edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = A->edges.GetNext(ePos);
		e->SetMark(UNKNOWN);
    ProcessEdge(B, e);
  }

  /* Check each edge of solid B against all faces of solid A */
  ePos = B->edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = B->edges.GetNext(ePos);
		e->SetMark(UNKNOWN);
    ProcessEdge(A, e);
  }

  return;
}

/*********************************************************************************/
void vrBoolopRecord::ProcessEdge(vrSolid *s, vrEdge *e)
{
  VRTRACE("\n/*==========================================*/\n");
  /* Check each face of this solid against the given edge */
  LISTPOS fPos = s->faces.GetHeadPosition();
  while (fPos)
	{
		vrFace *f = s->faces.GetNext(fPos);
    DoGenerate(e, f);
  }
  VRTRACE("/*<<<<<=====================================*/\n");
}

void vrBoolopRecord::DoGenerate(vrEdge *e, vrFace *f)
{
  /* The solid with which we are processing edges (the one to which 'e' belongs). */
  vrSolid *edgeSolid = e->GetSolid();
  vrSolid *faceSolid = f->GetSolid();
  
  ASSERT(faceSolid != edgeSolid);

  /* Calc the distance from both of the edge's vertex to the face... */
  SFFloat d1, d2;
  vrVertex *v1  = e->GetVertex(HE1);          
  vrVertex *v2  = e->GetVertex(HE2);
  d1           = f->GetDistance(*v1);                 
  d2           = f->GetDistance(*v2);
  SFInt32 s1     = vrCompare(d1, 0.0f);       
  SFInt32 s2     = vrCompare(d2, 0.0f);

  SFBool BvsA = faceSolid->Marked(SOLID_A);

  VRTRACE("e [%d %d] f %d (%d) --> ", 
	 e->GetVertexIndex(HE1), e->GetVertexIndex(HE2), f->GetIndex(), BvsA);

#ifdef _STATS
	if (stats) stats->gen.tests++;
#endif

  /* ...if the verts are on opposite sides then the edge intersects the face */
  if (s1 == -1 && s2 == 1 || s1 == 1 && s2 == -1)
	{
#ifdef _STATS
		if (stats) stats->gen.edgefacecross++;
#endif

    vrIntersectRecord rec;

    /* Calc the intersection point */
    SFFloat t   = d1 / (d1 - d2);
    SFVec3f pt = *v1 + t * (*v2 - *v1);
    vrVertex v(pt);

    /* Figure out what type of intersection.... */
    if (f->Contains(&v, rec))
		{
#ifdef _STATS
			if (stats) stats->gen.ef_contains++;
#endif

      /* Split the edge at the intersection point... */
      //vrVertex *temp = edgeSolid->lmev(e->GetHe(HE1), e->GetHe(HE2)->Next(), pt);
      edgeSolid->lmev(e->GetHe(HE1), e->GetHe(HE2)->Next(), pt);
      
      switch (rec.GetType())
			{
      case FACE_HIT:
#ifdef _STATS
				if (stats) stats->gen.ef_facehits++;
#endif
				/* The edge intersects the face proper, save the intersection point and the face */
				VRTRACE("vrFace hit! --> ");
				AddVertFace(e->GetVertex(HE1), f, BvsA);
				break;

      case EDGE_HIT:
//ASSERT(0);
#ifdef _STATS
				if (stats) stats->gen.ef_edgehits++;
#endif
				/* the edge hits an edge of the face's solid, split that edge, add both new verts */
				VRTRACE("Edge hit! --> ");
				faceSolid->lmev(rec.GetHe(), rec.GetHe()->GetMate()->Next(), pt);
				AddVertVert(e->GetVertex(HE1), rec.GetHe()->GetVertex(), BvsA);
				break;

      case VERTEX_HIT:
#ifdef _STATS
				if (stats) stats->gen.ef_verthits++;
#endif
				/* 
    		 * The edge hits a vertex of this solid, no splitting necassary, just 
				 * make a new vertex and add it to the list.
				 */
				VRTRACE("Vertex hit! --> ");
				AddVertVert(e->GetVertex(HE1), rec.GetVertex(), BvsA);
				break;

      default:
				{
				  // Should not happen
					//Uint32 implementation_error=0;
	  			ASSERT(0);
				}

      } /* end switch */

      ProcessEdge(faceSolid, e->GetHe(HE1)->Prev()->GetEdge());

    } else
		{
			if (rec.GetType() == INSIDE_LOOP_NO_HIT)
			{
#ifdef _STATS
				if (stats) stats->gen.ef_loophits++;
#endif
      	VRTRACE("Opp no hit. --> INSIDE_LOOP_HIT");
			} else
			{
      	VRTRACE("Opp no hit. --> outside lout");
			}
    }
  } else
	{
		if (s1 == 0)
		{ 
      VRTRACE("VertOnFace(%d) --> ", v1->GetIndex());
      VertexOnFace(v1, f); 
      if (s2 == 0)
			{
				VRTRACE("\n\t");
      }
    }

    if (s2 == 0)
		{
      VRTRACE("VertOnFace(%d) --> ", v2->GetIndex());
      VertexOnFace(v2, f); 
    }
  }

  VRTRACE("\n");
}

void vrBoolopRecord::VertexOnFace(vrVertex *v, vrFace *f)
{
#ifdef _STATS
	if (stats) stats->gen.vertonface++;
#endif
  vrSolid *faceSolid = f->GetSolid();

  vrIntersectRecord rec;

  SFBool BvsA = faceSolid->Marked(SOLID_A);

  if (f->Contains(v, rec))
	{
#ifdef _STATS
		if (stats) stats->gen.ef_contains++;
#endif

    switch (rec.GetType())
		{
    case FACE_HIT:
#ifdef _STATS
			if (stats) stats->gen.vf_facehits++;
#endif
      VRTRACE("vrFace hit! --> ");
      AddVertFace(v, f, BvsA);
      break;
    case EDGE_HIT:
#ifdef _STATS
			if (stats) stats->gen.vf_edgehits++;
#endif
      VRTRACE("Edge hit! --> ");
      faceSolid->lmev(rec.GetHe(), rec.GetHe()->GetMate()->Next(), *v);
      AddVertVert(v, rec.GetHe()->GetVertex(), BvsA);
      break;
    case VERTEX_HIT:
#ifdef _STATS
			if (stats) stats->gen.vf_verthits++;
#endif
      VRTRACE("Vertex hit! --> ");
      AddVertVert(v, rec.GetVertex(), BvsA);
      break;
    default:
      {
				// Should not happen
				//Uint32 implementation_error=0;
				ASSERT(0);
      }
    }
  } else
	{
    if (rec.GetType() == INSIDE_LOOP_NO_HIT)
		{
#ifdef _STATS
			if (stats) stats->gen.vf_loophits++;
#endif
    	VRTRACE("Opp no hit. --> INSIDE_LOOP_HIT");
		} else
		{
     	VRTRACE("Opp no hit. --> outside lout");
		}
  }
}

void vrBoolopRecord::AddVertFace(vrVertex *v, vrFace *f, SFBool BvsA)
{
#ifdef _STATS
	if (stats) stats->gen.vf_calls++;
#endif

  ASSERT(v);
  ASSERT(f);

  v->SetMark(ON);
  f->SetMark1(ON);
  
  if (BvsA)
	{
    for (Uint32 i=0;i<nVertsB;i++)
		{
      if (vertsB[i].v == v && vertsB[i].f == f)
			{
				VRTRACE("present VF (%d %d)", v->GetIndex(), f->GetIndex());
				return;
      }
    }
#ifdef _STATS
    if (stats) stats->gen.vf_addsB++;
#endif

    ASSERT(nVertsB < MAX_ON_VERTS);
    vertsB[nVertsB  ].v = v;
    vertsB[nVertsB++].f = f;
    VRTRACE("adding VF (B: %d, A: %d)", v->GetIndex(), f->GetIndex());
  } else
	{
    for (Uint32 i=0;i<nVertsA;i++)
		{
      if (vertsA[i].v == v && vertsA[i].f == f)
			{
				VRTRACE("present VF (%d %d)", v->GetIndex(), f->GetIndex());
				return;
      }
    }
#ifdef _STATS
    if (stats) stats->gen.vf_addsA++;
#endif
    ASSERT(nVertsA < MAX_ON_VERTS);
    vertsA[nVertsA  ].v = v;
    vertsA[nVertsA++].f = f;
    VRTRACE("adding VF (A: %d B: %d)", v->GetIndex(), f->GetIndex());
  }
}

/*********************************************************************************/
void vrBoolopRecord::AddVertVert(vrVertex *v1, vrVertex *v2, SFBool BvsA)
{
#ifdef _STATS
	if (stats) stats->gen.vv_calls++;
#endif
 
   ASSERT(v1);
  ASSERT(v2);

  v1->SetMark(ON);
  v2->SetMark(ON);

  ASSERT(nVertsV < MAX_ON_VERTS);

  if (BvsA)
	{
    for (Uint32 i=0;i<nVertsV;i++)
		{
      if ((vertsV[i].vb == v1) && (vertsV[i].va == v2))
			{
				VRTRACE("present VV (%d %d)", v1->GetIndex(), v2->GetIndex());
				return;
      }
    }
#ifdef _STATS
    if (stats) stats->gen.vv_addsB++;
#endif
    vertsV[nVertsV  ].va = v2;
    vertsV[nVertsV++].vb = v1;
    VRTRACE("adding VV (B: %d A: %d)", v2->GetIndex(), v1->GetIndex());
  } else
	{
    for (Uint32 i=0;i<nVertsV;i++)
		{
      if ((vertsV[i].vb == v2) && (vertsV[i].va == v1))
			{
				VRTRACE("present VV (%d %d)", v1->GetIndex(), v2->GetIndex());
				return;
      }
    }
#ifdef _STATS
    if (stats) stats->gen.vv_addsA++;
#endif
    vertsV[nVertsV  ].va = v1;
    vertsV[nVertsV++].vb = v2;
    VRTRACE("adding VV (A: %d B: %d)", v1->GetIndex(), v2->GetIndex());
  }
}
