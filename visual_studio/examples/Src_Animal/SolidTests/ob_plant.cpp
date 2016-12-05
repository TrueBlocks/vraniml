#include "../stdafx.h"
#include "Tests.h"

vrSolid *Plant(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f(0.05f, 0.6f, 0.0f),
      SFVec3f(0.4f,  0.6f, 0.0f),
      SFVec3f(0.6f,  1.0f, 0.0f),
      SFVec3f(1.2f,  1.0f, 0.0f),
      SFVec3f(1.4f,  0.6f, 0.0f),
      SFVec3f(1.75f, 0.6f, 0.0f),
      SFVec3f(1.8f,  0.2f, 0.0f),
      SFVec3f(1.4f,  0.2f, 0.0f),
      SFVec3f(1.3f,  0.4f, 0.0f),
      SFVec3f(1.4f,  0.3f, 0.0f),
      SFVec3f(1.2f,  0.3f, 0.0f),
      SFVec3f(1.2f,  0.2f, 0.0f),
      SFVec3f(0.4f,  0.2f, 0.0f),
      SFVec3f(0.4f,  0.3f, 0.0f),
      SFVec3f(0.3f,  0.4f, 0.0f),
      SFVec3f(0.2f,  0.3f, 0.0f),
      SFVec3f(0.2f,  0.3f, 0.0f),
      SFVec3f(0.2f,  0.2f, 0.0f),
      SFVec3f(0.0f,  0.2f, 0.0f),
    };
  Int32 m=sizeof(vecs)/sizeof(SFVec3f);

// The calls to Rotation'x'CMatrix take radians.  So this
// test case works but only by accident!
  vrSolid *s = new vrSolidCircle(0.0f, 0.2f, 0.125f, 0.0f, 10);
  s->TransformGeometry(RotationYMatrix(90.0f));
  s->ArcSweep(s->findFace(0), m, vecs);
  vrSolid *s1 = new vrSolidCircle(0.0f, 0.2f, 0.125f, 0.0f, 10);
  s1->TransformGeometry(RotationYMatrix(90.0f));
  s1->ArcSweep(s1->findFace(0), m, vecs);
  s1->TransformGeometry(RotationYMatrix(35.0f));
  vrSolid *s2 = new vrSolidCircle(0.0f, 0.2f, 0.125f, 0.0f, 10);
  s2->TransformGeometry(RotationYMatrix(90.0f));
  s2->ArcSweep(s2->findFace(0), m, vecs);
  s2->TransformGeometry(RotationYMatrix(70.0f));
  vrSolid *s3 = new vrSolidCircle(0.0f, 0.2f, 0.125f, 0.0f, 10);
  s3->TransformGeometry(RotationYMatrix(90.0f));
  s3->ArcSweep(s3->findFace(0), m, vecs);
  s3->TransformGeometry(RotationYMatrix(105.0f));
  vrSolid *s4 = new vrSolidCircle(0.0f, 0.2f, 0.125f, 0.0f, 10);
  s4->TransformGeometry(RotationYMatrix(90.0f));
  s4->ArcSweep(s4->findFace(0), m, vecs);
  s4->TransformGeometry(RotationYMatrix(145.0f));
  s->Merge(s1);
  delete s1;
  s->Merge(s2);
  delete s2;
  s->Merge(s3);
  delete s3;
  s->Merge(s4);
  delete s4;
  s->SetColor(vrGreen);

  Sc(s, 0.25f, 0.75f, 0.25f);
  Trans(s, 0.0f, -2.5f, 0.0f);

//	s->SetName("Plant");
	s->CalcPlaneEquations();
	s->Triangulate();
  s->SetColor(vrGreen);

  return s;
}

