#include "../stdafx.h"
#include "Tests.h"

SFFloat func(SFFloat z)
{
  return z-3;
}

SFFloat func1(SFFloat z)
{
  return z*z;
}

#define N 25
#define M 4

vrSolid *Twist2(void)
{
  SFVec3f vecs[] = 
    {
			SFVec3f(1.000,0.000,0.0),
			SFVec3f(0.866,-0.500,0.0),
			SFVec3f(0.500,-0.866,0.0),
			SFVec3f(0.000,-1.000,0.0),
			SFVec3f(-0.500,-0.866,0.0),
			SFVec3f(-0.866,-0.500,0.0),
			SFVec3f(-1.000,0.000,0.0),
			SFVec3f(-0.866,0.500,0.0),
			SFVec3f(-0.500,0.866,0.0),
			SFVec3f(0.000,1.000,0.0),
			SFVec3f(0.500,0.866,0.0),
			SFVec3f(0.866,0.500,0.0),
			SFVec3f(1.000,0.000,0.0),
    };
  Int32 m = sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->SetColor(vrGreen);
	Sc(s, .2, .2, 1);

  for (int i=0;i<N;i++)
		s->TranslationalSweep(s->findFace(0), .07*zAxis);

	// color one row of faces of the sweep as red.
	for (i=2;i<s->faces.GetCount();i+=m)
	{	
		vrFace *face = s->findFace(i);
		if (face)
			face->SetColor(vrRed);
		face = s->findFace(i+1);
		if (face)
			face->SetColor(vrRed);
	}
		
  Sc(s, 0.8f, 0.8f, 0.8f);
  Rotate(s, 56.0f, YYY);
  Rotate(s, 7.0f, XXX);

  s->Twist(func);

  return s;
}

vrSolid *Arm(const SFVec3f& loc, const SFColor& color)
{
  vrSolid *s = new vrSolidCylinder(1.0f, 1.0f, M);
  for (int i=0;i<N;i++)
		s->TranslationalSweep(s->findFace(0), -zAxis);
  s->TransformGeometry(TranslationMatrix(loc));
	s->SetColor(color);
	s->MarkCreases(vrDeg2Rad(360/(M-1)));
	s->CalcPlaneEquations();
	s->Twist(func1);
	return s;
}

vrSolid *Twist(void)
{
  vrSolid *s1 = Arm(2 * yAxis, vrRed);

  vrSolid *s2 = Arm(-2 * yAxis, vrGreen);
  s1->Merge(s2);
  delete s2;
  
  s2 = Arm(-2 * xAxis, vrBlue);
  s1->Merge(s2);
  delete s2;

  s2 = Arm(2 * xAxis, vrYellow);
  s1->Merge(s2);
  delete s2;

  s1->Twist(func);
  s1->CalcPlaneEquations();
	s1->Triangulate();
  
  Sc(s1, 0.8f, 0.8f, 0.8f);
  Rotate(s1, 90.0f, YYY);
  Rotate(s1, 45.0f, XXX);
  
  return s1;
}

