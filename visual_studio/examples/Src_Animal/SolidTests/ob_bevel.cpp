#include "../stdafx.h"
#include "Tests.h"

vrSolid *SolidBevel(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f(0.000f,  0.000f,  0.0f),
      SFVec3f(0.300f,  0.000f,  0.0f),
      SFVec3f(0.200f,  0.050f,  0.0f),
      SFVec3f(0.200f,  0.075f,  0.0f),
      SFVec3f(0.225f,  0.100f,  0.0f),
      SFVec3f(0.075f,  0.100f,  0.0f),
      SFVec3f(0.100f,  0.075f,  0.0f),
      SFVec3f(0.100f,  0.050f,  0.0f),
    };

  Int32 m=sizeof(vecs)/sizeof(SFVec3f);

  vrSolid *s = new vrSolidLamina(m, vecs);
  s->TranslationalSweep(s->findFace(1), SFVec3f(0.0f, 0.0f, 0.4f));
  Trans(s, -0.150f, -0.050f, 0.0f);
  Sc(s, 3.0f, 3.0f, 3.0f);

	s->findFace(0)->SetColor(vrGreen);

	s->CalcPlaneEquations();
//s->MarkCreases(vrDeg2Rad(1.0));
	s->Triangulate();
	s->Revert();
  s->SetColor(vrBlue);

  return s;
}


