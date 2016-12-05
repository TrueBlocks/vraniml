#include "../stdafx.h"
#include "Tests.h"

static vrSolid *Top()
{
  SFVec3f vecs[30];
  Int32 m=4, n=m-1;

  vecs[n--] = SFVec3f( 0.0f,  0.0f,  0.0f);
  vecs[n--] = SFVec3f( 1.0f,  0.0f,  0.0f);
  vecs[n--] = SFVec3f( 1.0f,  1.0f,  0.0f);
  vecs[n--] = SFVec3f( 0.0f,  1.0f,  0.0f);

  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrFirebrick);
  return s;
}

static vrSolid *Front()
{
  SFVec3f vecs[] = 
    {
      SFVec3f( 0.0f,  0.0f,   0.0f),
      SFVec3f( 1.0f,  2.5f,   0.0f),
      SFVec3f( 0.0f,  2.5f,   0.0f),
      SFVec3f( 0.0f,  3.0f,   0.0f),
      SFVec3f( 4.0f,  3.0f,   0.0f),
      SFVec3f( 4.0f,  2.5f,   0.0f),
      SFVec3f( 3.0f,  2.5f,   0.0f),
      SFVec3f( 4.0f,  0.0f,   0.0f),
      SFVec3f( 3.5f,  0.0f,   0.0f),
      SFVec3f( 3.0f,  2.0f,   0.0f),
      SFVec3f( 1.0f,  2.0f,   0.0f),
      SFVec3f( 0.5f,  0.0f,   0.0f),
    };
  Int32 m = sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrSeaGreen);
  return s;
}

static vrSolid *Right()
{
  SFVec3f vecs[] = 
    {
      SFVec3f( 0.0f,  0.0f,   0.0f),
      SFVec3f( 0.5f,  2.5f,   0.0f),
      SFVec3f( 0.0f,  2.5f,   0.0f),
      SFVec3f( 0.0f,  3.0f,   0.0f),
      SFVec3f( 8.0f,  3.0f,   0.0f),
      SFVec3f( 8.0f,  2.5f,   0.0f),
      SFVec3f( 7.5f,  2.5f,   0.0f),
      SFVec3f( 8.0f,  0.0f,   0.0f),
      SFVec3f( 7.0f,  0.0f,   0.0f),
      SFVec3f( 6.5f,  2.0f,   0.0f),
      SFVec3f( 1.5f,  2.0f,   0.0f),
      SFVec3f( 1.0f,  0.0f,   0.0f),
    };
  Int32 m=sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrNavyBlue);
  return s;
}

vrSolid *Table(void)
{
  vrSolid *top   = NULL; //Top();
  vrSolid *front = Front();
  vrSolid *right = Right();
  vrSolid *thing = SweepIntersect(top, front, right, FALSE);

  top   = NULL; //Top();
  front = Front();
  right = Right();
  vrSolid *doc   = SweepIntersect(top, front, right, TRUE);

  if (thing)
	{
		SFVec3f minni, maxxi;
		SFVec3f front_extents = thing->Extents(minni, maxxi);
		Trans(doc, 0, front_extents.y*1.7, 0);

		thing->Merge(doc);
		delete doc;

	} else
	{
		thing = Front();
		thing->Merge(Right());
	}

  Rotate(thing, -45, YYY);
	thing->CalcPlaneEquations();
	thing->Triangulate();
	
	return thing;
}

