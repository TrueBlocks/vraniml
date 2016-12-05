#ifndef __INTERSECT_H3D
#define __INTERSECT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

enum { NO_HIT=0, FACE_HIT, VERTEX_HIT, EDGE_HIT, INSIDE_LOOP_NO_HIT };

/***********************************************************************/
/*
 * Records information about an intersection calculation
 */
class vrIntersectRecord
{

private:
  vrHalfEdge *he;
  vrVertex   *v;
  Uint32    type;

public:
            vrIntersectRecord (void);
           ~vrIntersectRecord () {};

  /* Mutators */
  void      RecordHit       (vrHalfEdge *he, vrVertex *v, Uint32 type);

  /* Inspectors */
  vrVertex   *GetVertex       (void)                                     const;
  vrHalfEdge *GetHe           (void)                                     const;
  Uint32    GetType         (void)                                     const;

#ifdef _DEBUG
	void      Show            (vrDumpContext& dc)                                     const;
#endif
};

inline vrIntersectRecord::vrIntersectRecord(void)
{
  he = NULL; 
  v = NULL; 
  type = NO_HIT; 
}

inline void vrIntersectRecord::RecordHit(vrHalfEdge *hehe, vrVertex *vv, Uint32 t)
{
  type = t;

  switch (type) {
  case FACE_HIT:
    he = NULL;
    v = NULL;
    break;
  case VERTEX_HIT:
    ASSERT(vv);
    v = vv;
    he = NULL;
    break;
  case EDGE_HIT:
    ASSERT(hehe);
    he = hehe;
    v = NULL;
    break;
  case INSIDE_LOOP_NO_HIT:
    ASSERT(!vv);
    ASSERT(!hehe);
    he = NULL;
    v = NULL;
    break;
  default:
    {
      // Should not happen
			//Uint32 invalid_hit_type=0;
      ASSERT(0);
    }
  }
}

inline vrVertex *vrIntersectRecord::GetVertex(void) const
{
  ASSERT(v);
  return v;
}

inline vrHalfEdge *vrIntersectRecord::GetHe(void) const
{
  ASSERT(he);
  return he;
}

inline Uint32 vrIntersectRecord::GetType(void) const
{
  return type;
}

#endif
