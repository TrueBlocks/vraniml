#include "../stdafx.h"
#include "Tests.h"

/*********************************************************************/
vrSolid *SplitRoom(vrSolid *s, const vrPlane& p)
{
  vrSolid *a, *b;
  s->Split(p, &a, &b);

  Trans(a, 0.0f, 0.0f, 1.0f);
  Rotate(a, -25.0f, YYY);
  Trans(a, 0.0f, 0.0f, -1.0f);

  Trans(b, 0.0f, 0.0f, 1.0f);
  Rotate(b, 25.0f, YYY);
  Trans(b, 0.0f, 0.0f, -1.0f);

//  CHECK(a);
//  CHECK(b);

  a->Merge(b);
  delete b;

//  CHECK(a);

  return a;
}

vrSolid *RoofSection()
{
  vrSolid *s =  new vrSolidCircle(0.0f, 0.0f, 1.0f, 0.0f, 3);
  Rotate(s, -90.0f, XXX);
  Trans(s, 0.5f, 0.0f, 0.0f);
  Rotate(s, 15.0f, ZZZ);
  Trans(s, -1.4488904476f, 0.0f, 0.0f);
//  s->TranslationalSweep(s->findFace(0), SFVec3f(0.0f, -0.2f, 0.0f));
  return s;
}

vrSolid *Roof()
{
  vrSolid *left = RoofSection();
  Rotate(left, -90.0f, YYY);
  vrSolid *back = RoofSection();
  Rotate(back, 90.0f, YYY);
  vrSolid *right = RoofSection();
  Rotate(right, 180.0f, YYY);
  vrSolid *front = RoofSection();
  Rotate(front, -90.0f, YYY);
  
  left->Merge(back);
  delete back;
  left->Merge(right);
  delete right;
  left->Merge(front);
  delete front;
  return left;
}

vrSolid *Wall()
{
  vrSolid *s = new vrSolidCube(1.0f);
  Sc(s, 1.0f, 1.0f, 0.1f);
  Rotate(s, 90.0f, YYY);
  Trans(s, 1.0f, 0.0f, -0.5f);
  Sc(s, 1.0f, 2.0f, 2.0f);
  return s;
}

vrSolid *Walls()
{
  vrSolid *s1 = Wall();
  vrSolid *s2 = Wall();
  Sc(s2, 1.0f, 1.0f, 0.9f);
  Rotate(s2, 90.0f, YYY);
  vrSolid *s3 = Wall();
  Rotate(s3, 180.0f, YYY);
  vrSolid *s4 = Wall();
  Sc(s4, 1.0f, 1.0f, 0.9f);
  Rotate(s4, -90.0f, YYY);

  s1->Merge(s2);
  delete s2;
  s1->Merge(s3);
  delete s3;
  s1->Merge(s4);
  delete s4;

  return s1;
}

vrSolid *Floor()
{
  vrSolid *s = new vrSolidCube(1.0f);
  Sc(s, 1.9f, 0.1f, 1.9f);
  Trans(s, -0.95f, 0.0f, -0.95f);
  return s;
}

vrSolid *Room(void)
{
  vrSolid *rs[5];
  Int32 n=0;

  rs[n++] = Roof();
  Trans(rs[0], 0.0f, 2.0f, 0.0f);
  vrSolid *w = Walls();
  rs[0]->Merge(w);
  delete w;
  
  vrSolid *f = Floor();
  Trans(f, 0.0f, 0.1f, 0.0f);
  rs[0]->Merge(f);
  delete f;

//  rs[n] = SplitIt(rs[n-1], CPlaneBase(-1.0f,  1.0f,  0.0f,  0.2f), vrRed);     
//	n++;
//  rs[n] = SplitIt(rs[n-1], CPlaneBase( 1.0f,  1.0f,  0.0f,  0.2f), vrBlue);    
	//n++;
//  rs[n] = SplitIt(rs[n-1], CPlaneBase( 0.0f, -1.0f,  0.0f,  3.0f), vrGreen);   
	//n++;
//  rs[n] = SplitIt(rs[n-1], CPlaneBase( 1.0f,  0.0f,  0.0f,  0.0f), vrYellow);  
	//n++;
//  rs[n] = SplitIt(rs[n-1], CPlaneBase( 0.0f,  0.0f,  1.0f,  0.0f), vrMagenta);

  Trans(rs[n], 0.0f, -0.75f, 0.0f);
  Sc(rs[n], 1.0f, 0.4f, 1.0f);
  
  return rs[n];
}
