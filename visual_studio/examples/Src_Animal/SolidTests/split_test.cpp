#include "../stdafx.h"
#include "Tests.h"

vrSolid *Blade(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f( 2.00f,   2.00f,  0.0f),
      SFVec3f( 2.00f,  -2.00f,  0.0f),
      SFVec3f(-2.00f,  -2.00f,  0.0f),
      SFVec3f(-2.00f,   2.00f,  0.0f)
    };

  Int32 m=sizeof(vecs)/sizeof(SFVec3f);
  return new vrSolidLamina(m, vecs);
}

vrSolid *Test9Solid(void)
{
  SFVec3f vecs[] = 
    {
      SFVec3f(0.0f, 0.0f, 0.0f),
      SFVec3f(0.0f, 2.0f, 0.0f),
      SFVec3f(1.0f, 1.0f, 0.0f),
      SFVec3f(2.0f, 2.0f, 0.0f),
      SFVec3f(2.0f, 0.0f, 0.0f),
	};

  Int32 m=sizeof(vecs)/sizeof(SFVec3f);

  vrSolid *s = new vrSolidLamina(m, vecs);
  s->TranslationalSweep(s->findFace(0), SFVec3f(0.0f, 0.0f, 4.0f));
  s->SetColor(vrBlue);
  s->findFace(0)->SetColor(vrGreen);

  return s;
}

vrSolid *SplitIt(vrSolid *s, const vrPlane& pl, vrSolid *blade)
{
	vrSolid *A=NULL, *B=NULL;
	
	s->Split(pl, &A, &B);

	if (!A || !B)
	{
		if (blade)
			s->Merge(blade);
		return s;
	} else
	{
		A->SetColor(vrYellow);
		B->SetColor(vrBlue);
		SFVec3f v = -pl.GetNormal();
		A->TransformGeometry(TranslationMatrix(v));

		A->Merge(B);
		if (blade)
			A->Merge(blade);

		A->CalcPlaneEquations();
		A->Triangulate();
	}

	return A;
}

vrSolid *SplitTests(int test, SFBool merge) //vrLine **normal, 
{
	if (test==15)
	{
extern vrSolid *Primitives();
		return Primitives();
	}
	
	int faceID = 0;

  SFVec3f tr(0.0f);
	
	vrSolid *blade = Blade();

	vrSolid *s;
	if (test < 9)
	{
		s = new vrSolidCube(1.0f);
	} else
	{
		{
			s = Test9Solid();
			switch (test)
			{
				case 9:
					blade->TransformGeometry(RotationXMatrix(vrDeg2Rad(90.0f)));
					blade->TransformGeometry(TranslationMatrix(SFVec3f(0.0f, 1.0f, 0.0f)));
					break;
				case 10:
					blade->TransformGeometry(RotationXMatrix(vrDeg2Rad(90.0f)));
					blade->TransformGeometry(TranslationMatrix(SFVec3f(0.0f, 2.0f, 0.0f)));
					break;
				case 11:
					blade->TransformGeometry(RotationYMatrix(vrDeg2Rad(90.0f)));
					blade->TransformGeometry(TranslationMatrix(SFVec3f(1.0f, 0.0f, 0.0f)));
					break;
				case 12:
					blade->TransformGeometry(RotationYMatrix(vrDeg2Rad(90.0f)));
					blade->TransformGeometry(RotationZMatrix(vrDeg2Rad(45.0f)));
					blade->TransformGeometry(TranslationMatrix(SFVec3f(2.0f, 0.0f, 0.0f)));
					break;
				case 13:
					blade->TransformGeometry(RotationYMatrix(vrDeg2Rad(90.0f)));
					blade->TransformGeometry(RotationZMatrix(vrDeg2Rad(45.0f)));
					blade->TransformGeometry(TranslationMatrix(SFVec3f(2.0f, 0.0f, 0.0f)));
					faceID = 1;
					break;
				case 14:
					blade->TransformGeometry(RotationYMatrix(vrDeg2Rad(90.0f)));
					blade->TransformGeometry(RotationZMatrix(vrDeg2Rad(45.0f)));
					blade->TransformGeometry(TranslationMatrix(SFVec3f(2.01f, 0.0f, 0.0f)));
					break;
			}
		}
	}

	switch (test)
	{
	case 1:
		// drop through -- splitting plane touches a face, solid same side as plane normal
		faceID = 1;
	case 0:
		// splitting plane touches a face, solid opposite side of plane normal
		break;
	case 2:
		// splitting plane intersects edges proper (no special cases)
		blade->TransformGeometry(TranslationMatrix(SFVec3f(0.0f, 0.0f, 0.5f)));
		break;
	case 3:
		// splitting plane intersects four verticies, two at each opposite corner of cube
		blade->TransformGeometry(RotationXMatrix(vrDeg2Rad(45.0f)));
		break;
	case 4:
		// splitting plane intersects four verticies, two at each opposite corner of cube
		blade->TransformGeometry(RotationXMatrix(vrDeg2Rad(75.0f)));
		break;
	case 5:
		// drop through -- solid on same side as splitting plane normal
		faceID = 1;
	case 6:
		{
			// splitting plane intersects two verticies on one edge of the cube
			blade->TransformGeometry(RotationXMatrix(vrDeg2Rad(45.0f)));
			SFVec3f v(1.0f, 1.0f, 0.0f);
			blade->TransformGeometry(TranslationMatrix(v));
		}
		break;
	case 7:
		// drop through -- solid on same side as splitting plane normal
		faceID = 1;
	case 8:
		{
			// splitting plane intersects one verticies on one corner of the cube
			blade->TransformGeometry(RotationXMatrix(vrDeg2Rad(45.0f)));
			SFVec3f v(1.0f, 1.0f, 0.0f);
			blade->TransformGeometry(TranslationMatrix(v));
			blade->TransformGeometry(RotationZMatrix(vrDeg2Rad(5.0f)));
			v = SFVec3f(-0.0041875f, -0.0041875f, 0.0f);
			blade->TransformGeometry(TranslationMatrix(v));
		}
		break;
	}

	vrFace *f = blade->findFace(faceID);
//  ASSERT_MEMORY(f);
  
  /* Calculate the cutting plane */
  f->CalcEquation();
  vrPlane pl(f->GetNormal(), f->GetD());

	s->SetColor(vrRed);
	blade->SetColor(vrGreen);

	if (merge)
	{
		s->Merge(blade);
		delete blade;
		return s;
	} else
	{
		return SplitIt(s, pl, blade);
	}
}

vrSolid *Prims(void)
{
	vrSolid *s1, *s2;
  s1 = new vrSolidCircle(0.0f, 0.0f, 1.0f, 1.0f, 3);
  Trans(s1, -6.5f, 0.0f, 0.0f);
  s1->SetColor(vrGrey);

  s2 = new vrSolidCircle(0.0f, 0.0f, 1.0f, 1.0f, 8);
  Trans(s2, -4.0f, 0.0f, 0.0f);
  s2->SetColor(vrRed);
	s1->Merge(s2);
	delete s2;

  s2 = new vrSolidCube(1.0f);
  Trans(s2, -2.3f, -0.5f, 0.0f);
  s2->SetColor(vrGreen);
  s1->Merge(s2);
  delete s2;

  s2 = new vrSolidCylinder(1.0f, 2.0f, 21);
  s2->SetColor(vrBlue);
  s1->Merge(s2);
  delete s2;

  s2 = new vrSolidCylinder(1.0f, 2.0f, 3);
  Trans(s2, 2.0f, 0.0f, 0.0f);
  s2->SetColor(vrCyan);
  s1->Merge(s2);
  delete s2;

  s2 = new vrSolidBall(.7f, 10, 10);
  Trans(s2, 4.2f, 0.0f, 0.0f);
  s2->SetColor(vrYellow);
  s1->Merge(s2);
  delete s2;

  s2 = new vrSolidTorus(1.4f, .5f, 10, 10);
  Trans(s2, 6.0f, 0.0f, 0.0f);
  s2->SetColor(vrMagenta);
	s2->Revert();
  s1->Merge(s2);
  delete s2;

  return s1;
}

vrSolid *Primitives(void)
{
  vrSolid *s1 = Prims();
	s1->CalcPlaneEquations();
	s1->Triangulate();
	vrSolid *blade = Blade();
	blade->SetColor(vrGreen);
	blade->TransformGeometry(RotationXMatrix(vrDeg2Rad(90.0f)));
	Trans(blade, 0, .25, 0);
	Sc(blade, 4, 1, 1);
	vrSolid *s2 = SplitIt(s1, vrPlane(0.0f, -1.0f, 0.0f, 0.25f), blade);
	s2->CalcPlaneEquations();
	s2->Triangulate();
//	s1 = SplitIt(s2, vrPlane(1.0f, -1.0f, 0.0f, 0.25f), NULL);
  return s2;
}

