#include "../stdafx.h"
#include "Tests.h"

vrSolid *Body(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f(0.05f,  0.6f, 0.0f),
      SFVec3f(0.4f,  0.6f, 0.0f),
      SFVec3f(0.6f,  1.0f, 0.0f),
      SFVec3f(1.2f,  1.0f, 0.0f),
      SFVec3f(1.4f,  0.6f, 0.0f),
      SFVec3f(1.75f,  0.6f, 0.0f),
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
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->TranslationalSweep(s->findFace(0), SFVec3f(0.0f, 0.0f, 0.9f));

	s->CalcPlaneEquations();
	s->Triangulate();

  s->SetColor(vrRed);

  return s;
}

vrSolid *Window(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f(0.45f,  0.6f, -0.02f),
      SFVec3f(0.65f,  0.95f, -0.02f),
      SFVec3f(1.15f,  0.95f, -0.02f),
      SFVec3f(1.35f,  0.6f, -0.02f),
    };
  Int32 m=sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->TranslationalSweep(s->findFace(0), SFVec3f(0.0f, 0.0f, 0.96f));

	s->CalcPlaneEquations();
	s->Triangulate();

  s->SetColor(vrBlue);

  return s;
}

vrSolid *Wheel(void)
{
  vrSolid *s = new vrSolidCylinder(0.2f, 0.2f, 20);
	s->CalcPlaneEquations();
	s->Triangulate();
  s->SetColor(vrDimGray);

  vrSolid *s1 = new vrSolidCylinder(0.1f, 0.2f, 20);
	s1->CalcPlaneEquations();
	s1->Triangulate();
  s1->SetColor(vrWhite);

  vrMatrix m;
  m.vals[3][2] = -0.05f;
  s1->TransformGeometry(m);
  s->Merge(s1);

  delete s1;

  return s;
}

vrSolid *Car(void)
{
  vrSolid *s1 = Body();

  vrSolid *s2 = Window();
	s1->Merge(s2);
	delete s2;

  s2 = Wheel();
  vrMatrix m = TranslationMatrix(SFVec3f(0.3f, 0.2f, -0.15f));
  s2->TransformGeometry(m);
  s1->Merge(s2);
  delete s2;

  s2 = Wheel();
  m = RotationYMatrix(vrDeg2Rad(180.0f));
  s2->TransformGeometry(m);
  m = TranslationMatrix(SFVec3f(0.3f, 0.2f, 1.05f));
  s2->TransformGeometry(m);
  s1->Merge(s2);
  delete s2;

  s2 = Wheel();
  m = RotationYMatrix(vrDeg2Rad(180.0f));
  s2->TransformGeometry(m);
  m = TranslationMatrix(SFVec3f(1.4f, 0.2f, 1.05f));
  s2->TransformGeometry(m);
  s1->Merge(s2);
  delete s2;

  s2 = Wheel();
  m = TranslationMatrix(SFVec3f(1.4f, 0.2f, -0.15f));
  s2->TransformGeometry(m);
  s1->Merge(s2);
  delete s2;


	Trans(s1, -1.0f, -0.5f, -0.5f);
  Sc(s1, 2.0f, 2.0f, 2.0f);

  return s1;
}
