#include "../stdafx.h"
#include "Tests.h"

vrSolid *Top()
{
  SFVec3f vecs[30];
  Int32 m=4, n=m-1;

  vecs[n--] = SFVec3f( 0.0f,  0.0f,  0.0f);
  vecs[n--] = SFVec3f( 1.0f,  0.0f,  0.0f);
  vecs[n--] = SFVec3f( 1.0f,  1.0f,  0.0f);
  vecs[n--] = SFVec3f( 0.0f,  1.0f,  0.0f);

  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrRed);
  return s;
}

vrSolid *Front()
{
/*
  SFVec3f vecs[] = 
    {
      SFVec3f( 0.0f,  1.0f,   0.0f),
      SFVec3f( 0.5f,  1.0f,   0.0f),
      SFVec3f( 0.5f,  0.5f,   0.0f),
      SFVec3f( 1.0f,  0.5f,   0.0f),
      SFVec3f( 1.0f,  0.0f,   0.0f),
      SFVec3f( 0.8f,  0.4f,   0.0f),
      SFVec3f( 0.7f,  0.35f,  0.0f),
      SFVec3f( 0.6f,  0.1f,   0.0f),
      SFVec3f( 0.4f,  0.1f,   0.0f),
      SFVec3f( 0.4f,  0.5f,   0.0f),
      SFVec3f( 0.2f,  0.5f,   0.0f),
      SFVec3f( 0.2f,  0.1f,   0.0f),
      SFVec3f( 0.0f,  0.1f,   0.0f),
    };
*/
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
/*
  SFVec3f vecs[] = 
    {
			SFVec3f(-3.252f, -3.501f, 0.0f),
			SFVec3f(-3.252f, -2.954f, 0.0f),
			SFVec3f(-2.182f, -2.801f, 0.0f),
			SFVec3f(-1.571f, -2.276f, 0.0f),
			SFVec3f( 0.611f, -1.772f, 0.0f),
			SFVec3f( 0.938f, -2.013f, 0.0f),
			SFVec3f( 1.309f, -1.466f, 0.0f),
			SFVec3f( 2.750f, -1.466f, 0.0f),
  		SFVec3f( 2.750f, -3.501f, 0.0f),
			SFVec3f(-3.252f, -3.501f, 0.0f),
		};
*/
  Int32 m = sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrGreen);
  return s;
}

vrSolid *Right()
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
/*
  SFVec3f vecs[] = 
    {
			SFVec3f(-3.252f,  -3.501f,  0.0f),
			SFVec3f( 2.750f,  -3.501f,  0.0f),
			SFVec3f( 2.750f,  -1.466f,  0.0f),
			SFVec3f(-3.252f,  -1.466f,  0.0f),
		};
*/
  Int32 m=sizeof(vecs)/sizeof(SFVec3f);

  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrBlue);
  return s;
}

vrSolid *Part(void)
{
  vrSolid *top   = Top();
  vrSolid *front = Front();
  vrSolid *right = Right();

  vrSolid *thing = SweepIntersect(top, front, right);

  if (thing)
	{
		SFVec3f minni, maxxi;
		SFVec3f front_extents = thing->Extents(minni, maxxi);

		vrSolid *f2 = Front();
	  Trans(f2,  0.0f, maxxi.y-1, 0.0f);
    thing->Merge(f2);
    delete f2;

	  vrSolid *r2 = Right();
		Rotate(r2, 90.0f, YYY);
		Trans(r2,  0.0f, maxxi.y-1, 0.0f);
		thing->Merge(r2);
		delete r2;

	  vrSolid *t2 = Top();
//		Rotate(r2, 90.0f, YYY);
		Trans(t2,  0.0f, maxxi.y-1, 0.0f);
		thing->Merge(t2);
		delete t2;

	} else
	{
		thing = Front();
		thing->Merge(Right());
	}

  thing->CalcPlaneEquations();
	thing->Triangulate();
	
	return thing;
}

