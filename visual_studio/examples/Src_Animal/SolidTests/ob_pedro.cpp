#include "../stdafx.h"
#include "Tests.h"

vrSolid *Nose(void)
{
	vrSolid *s = new vrSolidCube(0.5f);
	Trans(s,  -0.25f, -0.25f, 0.0f);
	Sc(s,   0.125f, 0.75f, 1.0f);
	Rotate(s,  -15.0f, XXX);

	s->CalcPlaneEquations();
	s->Triangulate();

	return s;
}

vrSolid *Lips(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f(-1.0f,  0.8f,  0.0f),
      SFVec3f( 1.0f,  0.8f,  0.0f),
      SFVec3f( 2.0f,  1.0f,  0.0f),
      SFVec3f( 1.0f,  0.0f,  0.0f),
      SFVec3f(-1.0f,  0.0f,  0.0f),
      SFVec3f(-2.0f,  1.0f,  0.0f),
    };
  Int32 m = sizeof(vecs)/sizeof(SFVec3f);
	vrSolid *s = new vrSolidLamina(m , vecs);
	s->TranslationalSweep(s->findFace(0), SFVec3f(0.0f, 0.0f, 0.25f));
	Sc(s, 0.26f, 0.125f, 1.0f);

	s->CalcPlaneEquations();
	s->Triangulate();

	return s;
}

vrSolid *Hat(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f( 1.9f,  0.0f,  0.0f),
      SFVec3f( 2.0f,  0.2f,  0.0f),
      SFVec3f( 2.6f, -3.2f,  0.0f),
      SFVec3f( 4.6f, -3.2f,  0.0f),
      SFVec3f( 5.0f, -2.8f,  0.0f),
      SFVec3f( 4.6f, -3.3f,  0.0f),
      SFVec3f( 2.5f, -3.3f,  0.0f),
      SFVec3f( 1.9f, -0.1f,  0.0f),
      SFVec3f( 0.1f, -0.1f,  0.0f),
      SFVec3f( 0.1f,  0.0f,  0.0f),
    };
  Int32 n=sizeof(vecs)/sizeof(SFVec3f);
	vrSolid *s = new vrSolidLamina(n , vecs);
	Rotate(s, 90.0f, ZZZ);
	s->RotationalSweep(30);
	Rotate(s, -90.0f, ZZZ);
	Sc(s, 0.40f, 0.40f, 0.5f);
	Trans(s, 0.0f, 2.0f, -0.75f);

	s->CalcPlaneEquations();
	s->Triangulate();

	return s;
}

vrSolid *Pedro(void)
{
  vrSolidBall *head = new vrSolidBall(1.0f, 20, 20);
	head->CalcPlaneEquations();
	head->Triangulate();
  Sc(head, 1.0f, 1.7f, 1.0f);
  head->SetColor(vrYellow);

  vrSolidBall *eye1 = new vrSolidBall(0.18f, 15, 15);
	eye1->CalcPlaneEquations();
	eye1->Triangulate();
  Trans(eye1,  0.3f,  0.4f, .8f);
  eye1->SetColor(vrBlue);

  vrSolidBall *eye2 = new vrSolidBall(0.18f, 15, 15);
	eye2->CalcPlaneEquations();
	eye2->Triangulate();
  Trans(eye2, -0.3f,  0.4f, .8f);
  eye2->SetColor(vrBlue);

  vrSolid *lips = Lips();
  Trans(lips,  0.0f, -0.4f, .75f);
  lips->SetColor(vrRed);

  vrSolid *nose = Nose();
  Trans(nose,  0.0f, 0.0f, 0.75f);
  nose->SetColor(vrYellow);

  vrSolid *hat = Hat();
  Trans(hat,  0.0f, 0.0f, 0.70f);
  hat->SetColor(vrDimGray);

  eye1->Merge(eye2);
  delete eye2;
  eye1->Merge(lips);
  delete lips;
  eye1->Merge(nose);
  delete nose;
  Rotate(hat, -14.0f, XXX);
  Sc(hat, 0.8f, 0.8f, 0.8f);
  Trans(hat, 0.0f, 0.375f, 0.09f);

  eye1->Merge(hat);
  delete hat;

  eye1->Merge(head);
  delete head;

//  Rotate(eye1, 127.0f, YYY);

//  eye1->SetName("Pedro");
//	eye1->CalcPlaneEquations();
//	eye1->Triangulate();

	return eye1;
}

/*
vrSolid *PedroBool(void)
{
//	CStatistics stats;

  vrSolid *head = new vrSolidBall(1.0f, 20, 20);
  Sc(head, 1.0f, 1.7f, 1.0f);
  head->SetColor(vrYellow);

  vrSolidBall *eye1 = new vrSolidBall(0.18f, 15, 15);
  Trans(eye1,  0.3f,  0.4f, .94f);
  eye1->SetColor(vrBlue);

  vrSolidBall *eye2 = new vrSolidBall(0.18f, 15, 15);
  Trans(eye2, -0.3f,  0.4f, .94f);
  eye2->SetColor(vrBlue);

  vrSolid *lips = Lips();
  Trans(lips,  0.0f, -0.4f, .75f);
  lips->SetColor(vrRed);

  vrSolid *nose = Nose();
  Trans(nose,  0.0f, 0.0f, 0.75f);
  nose->SetColor(vrYellow);

  vrSolid *hat = Hat();
  Trans(hat,  0.0f, 0.0f, 0.70f);
  hat->SetColor(vrDimGray);
  Rotate(hat, -14.0f, XXX);
  Sc(hat, 0.8f, 0.8f, 0.8f);
  Trans(hat, 0.0f, 0.375f, 0.09f);

  vrSolid *res=NULL;

#if 1
	head->Difference(eye1, &res); //, &stats);
	head = res;
	head->Difference(eye2, &res); //, &stats);
	head = res;
  head->Union(lips, &res); //, &stats);
	head = res;
#else
  head->Merge(eye1);
  head->Merge(eye2);
  head->Merge(lips);
#endif
  head->Merge(nose);
  head->Merge(hat);

  Rotate(head, 127.0f, ZZZ);
//  head->SetName("Pedro");

	return head;
}
*/

vrSolid *RotSweep(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f(  0, .5, 0),
      SFVec3f(  1,  1, 0),
      SFVec3f(  0,  2, 0),
      SFVec3f(  1,  2, 0),
      SFVec3f(  1,2.5, 0),
      SFVec3f( .5,2.5, 0),
      SFVec3f( .5,  3, 0),
      SFVec3f(1.4,2.7, 0),
      SFVec3f(  2, .5, 0),
      SFVec3f(  1,  1, 0),
      SFVec3f(  0, .5, 0),
    };
  Int32 n=sizeof(vecs)/sizeof(SFVec3f);
	vrSolid *s = new vrSolidLamina(n , vecs);
	s->RotationalSweep(30);
	s->SetColor(vrGreen);
	for (int i=n-2;i<s->faces.GetCount();i+=n)
		s->findFace(i)->SetColor(vrRed);
	for (i=n-3;i<s->faces.GetCount();i+=n)
		s->findFace(i)->SetColor(vrRed);
	for (i=0;i<n;i++)
		s->findFace(i)->SetColor(vrBlue);
	Rotate(s, 45.0, YYY);
	Rotate(s, 45.0, ZZZ);
	Rotate(s, 180.0, XXX);
	Rotate(s, -15.0, YYY);
	s->CalcPlaneEquations();
	s->Triangulate();
	return s;
}

static SFVec3f vecs[] = 
{
	SFVec3f(0.0,  1.00,0), // V1 0, 5
	SFVec3f(0.2,  1.00,0),
	SFVec3f(0.6,  0.00,0),
	SFVec3f(0.4,  0.00,0),
	SFVec3f(0.0,  1.00,0),

	SFVec3f(0.85, 1.00,0), // V2 5, 5
	SFVec3f(1.05, 1.00,0),
	SFVec3f(0.66, 0.00,0),
	SFVec3f(0.56, 0.25,0),
	SFVec3f(0.85, 1.00,0),

	SFVec3f(1.20,1,0), // R1 10, 5
	SFVec3f(1.40,1,0),
	SFVec3f(1.40,0,0),
	SFVec3f(1.20,0,0),
	SFVec3f(1.20,1,0),

	SFVec3f(1.45,1,0), // R2 15, 5
	SFVec3f(1.75,1,0),
	SFVec3f(1.70,.8,0),
	SFVec3f(1.45,.8,0),
	SFVec3f(1.45,1,0),

	SFVec3f(1.70,.8,0),
	SFVec3f(1.75, 1,0),
	SFVec3f(1.95,.7,0),
	SFVec3f(1.90,.7,0),
	SFVec3f(1.70,.8,0),

	SFVec3f(1.45,.6,0),
	SFVec3f(1.70,.6,0),
	SFVec3f(1.75,.4,0),
	SFVec3f(1.45,.4,0),
	SFVec3f(1.45,.6,0),

	SFVec3f(1.75,.4,0),
	SFVec3f(1.70,.6,0),
	SFVec3f(1.95,.7,0),
	SFVec3f(1.90,.65,0),
	SFVec3f(1.75,.4,0),

	SFVec3f(1.45,.35,0),
	SFVec3f(1.64,.35,0),
	SFVec3f(1.99,0,0),
	SFVec3f(1.75,0,0),
	SFVec3f(1.45,.35,0),
};
static Int32 n=sizeof(vecs)/sizeof(SFVec3f);

vrSolid *Letter(int st, vrSolid *ss, const SFColor& col)
{	
	vrSolid *s = new vrSolidLamina(5, &vecs[st]);
	s->Revert();
	for (int i=0;i<10;i++)
		s->TranslationalSweep(s->findFace(0), SFVec3f(i*-.01, i*.02, -0.125f));
	s->SetColor(col);
	s->findFace(1)->SetColor(vrRed);
	if (ss)
		ss->Merge(s);
	return s;
}

vrSolid *TransSweep(void)
{
	vrSolid *v1 = Letter( 0, NULL, vrBlue+vrGreen);
	Letter( 5, v1, vrGrey); 
	Letter(10, v1, vrGreen); 
	Letter(15, v1, vrBlue); 
	Letter(20, v1, vrWhite); 
	Letter(25, v1, vrOrange); 
	Letter(30, v1, vrYellow); 
	Letter(35, v1, vrGrey); 

	return v1;
}