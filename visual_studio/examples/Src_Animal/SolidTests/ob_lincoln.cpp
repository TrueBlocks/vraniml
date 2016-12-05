#include "../stdafx.h"
#include "Tests.h"

static vrSolid *Top()
{
  /* Unused */
  SFVec3f vecs[30];
  Int32 m=4, n=m-1;

  vecs[n--] = SFVec3f( 0.0f,  0.0f,  0.0f);
  vecs[n--] = SFVec3f( 1.0f,  0.0f,  0.0f);
  vecs[n--] = SFVec3f( 1.0f,  1.0f,  0.0f);
  vecs[n--] = SFVec3f( 0.0f,  1.0f,  0.0f);

  vrSolid *s = new vrSolidLamina(m, vecs);
  s->CalcPlaneEquations();
	s->Triangulate();
	s->SetColor(vrRed);
  return s;
}

static vrSolid *Notch()
{
  SFVec3f vecs[] = 
    {
      SFVec3f( 0.5f,  1.0f,   0.9f),
      SFVec3f( 0.8f,  0.7f,   0.9f),
      SFVec3f( 3.2f,  0.7f,   0.9f),
      SFVec3f( 3.5f,  1.0f,   0.9f),
      SFVec3f( 4.0f,  1.0f,   0.9f),
      SFVec3f( 4.0f, -1.0f,   0.9f),
      SFVec3f( 3.5f, -1.0f,   0.9f),
      SFVec3f( 3.2f, -0.7f,   0.9f),
      SFVec3f( 0.8f, -0.7f,   0.9f),
      SFVec3f( 0.5f, -1.0f,   0.9f),
      SFVec3f( 0.0f, -1.0f,   0.9f),
      SFVec3f( 0.0f,  1.0f,   0.9f),
    };
  Int32 m = sizeof(vecs)/sizeof(SFVec3f);
  vrSolid *s = new vrSolidLamina(m, vecs);
  s->CalcPlaneEquations();
	s->Triangulate();
  s->SetColor(vrGreen);
  return s;
}

static vrSolid *Circ()
{
  vrSolid *s = new vrSolidCircle(0.0f, 0.0f, 0.9f, 0.0f, 30);
  s->CalcPlaneEquations();
	s->Triangulate();
  s->SetColor(vrBlue);
  return s;
}

vrSolid *SmallLog(void)
{
  vrSolid *front = Notch();
  vrSolid *right = Circ();

  vrSolid *thing = SweepIntersect(NULL, front, right, FALSE);

  thing->CalcPlaneEquations();
	thing->Triangulate();
  thing->SetColor(vrCadetBlue);
  
//  thing->SetName("SmallLog");
  return thing;
}

vrSolid *MediumLog(void)
{
  vrSolid *notch1 = SmallLog();
  vrSolid *notch2 = SmallLog();
  vrSolid *tube = Circ();

  Rotate(tube, -90.0f, YYY);
  tube->TranslationalSweep(tube->findFace(1), SFVec3f(6.0f, 0.0f, 0.0f));
  Trans(tube, 0.0f, 0.0f, 1.8f);
  Trans(notch1, -4.01f, 0.0f, 0.0f);
  Trans(notch2, 6.01f, 0.0f, 0.0f);
  tube->Merge(notch1);
  delete notch1;
  tube->Merge(notch2);
  delete notch2;

  Trans(tube, -3.0f, 0.0f, -1.5f);

  tube->CalcPlaneEquations();
	tube->Triangulate();
  tube->SetColor(vrMagenta);

//  tube->SetName("MedLog");
  return tube;
}


