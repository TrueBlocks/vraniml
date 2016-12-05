#include "../stdafx.h"
#include "Tests.h"

static vrSolid *Top()
{
  SFVec3f vecs[] = 
    {
      SFVec3f( 3, .1, 0),
      SFVec3f( .1, 3, 0),
			SFVec3f( 3, 5.9, 0),
      SFVec3f( 5.9, 3, 0),
      SFVec3f( 3, .1, 0),
    };
  Int32 m = sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrYellow);
  return s;
}

static vrSolid *Front()
{
  SFVec3f vecs[] = 
    {
      SFVec3f( 6, 6, 0),
      SFVec3f( 6, 4, 0),
      SFVec3f( 4, 4, 0),
      SFVec3f( 5, 0, 0),
      SFVec3f( 1, 0, 0),
      SFVec3f( 2, 4, 0),
      SFVec3f( 0, 4, 0),
      SFVec3f( 0, 6, 0),
      SFVec3f( 3, 7.5, 0),
      SFVec3f( 6, 6, 0),
    };
  Int32 m = sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrDarkGreen);
  return s;
}

static vrSolid *Right()
{
  SFVec3f vecs[] = 
    {
      SFVec3f( 6, 6, 0),
      SFVec3f( 6, 4, 0),
      SFVec3f( 4, 4, 0),
      SFVec3f( 5, 0, 0),
      SFVec3f( 1, 0, 0),
      SFVec3f( 2, 4, 0),
      SFVec3f( 0, 4, 0),
      SFVec3f( 0, 6, 0),
      SFVec3f( 3, 7.5, 0),
      SFVec3f( 6, 6, 0),
    };
  Int32 m=sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrFirebrick);
  return s;
}

vrSolid *SweepIntersect(vrSolid *top, vrSolid *front, vrSolid *right, SFBool merge)
{
#define BIGEPS       (0.00001*100.0f)

  // Interesect front and right first
	SFVec3f minni, maxxi;
  SFVec3f front_extents = front->Extents(minni, maxxi);
  SFVec3f right_extents = right->Extents(minni, maxxi);

  Trans(front, 0.0f, 0.0f, right_extents.x*-.1);
  front->TranslationalSweep(front->findFace(0), SFVec3f(0.0f, 0.0f, right_extents.x*1.2));

  Rotate(right, -90.0f, YYY);
  right->TranslationalSweep(right->findFace(0), SFVec3f(front_extents.x*1.2, 0.0f, 0.0f));
  Trans(right, right_extents.x*-.1, 0.0f, right_extents.x);
  Trans(right, BIGEPS*10, BIGEPS*10, BIGEPS*10);

	if (top)
	{
		Rotate(top, 90, XXX);
		Trans(top, 0.0f, right_extents.y*1.1, 0);
		top->TranslationalSweep(top->findFace(0), SFVec3f(0, -right_extents.y*1.2, 0));
	}

	if (merge)
	{
		if (top)
		{
			front->Merge(top);
			delete top;
		}
		front->Merge(right);
		delete right;
		return front;
	} else
	{
		vrSolid *res=NULL;
		front->Intersection(right, &res);
		delete front;
		delete right;

		if (top)
		{
			vrSolid *res2;
			res->Intersection(top, &res2);
			delete top;
			delete res;
			return res2;
		}

		return res;
	}
	// never happens
	return NULL;
}

vrSolid *Part(void)
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

