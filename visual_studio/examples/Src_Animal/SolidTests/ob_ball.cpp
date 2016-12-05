#include "../stdafx.h"
#include "Tests.h"

template<class T>
inline T RandomValue(T a, T b)
{
  T range = (T)fabs(a - b);
  return (rand() / RAND_MAX) * range + ((a < b) ? a : b);
}

vrSolid *Ball(long test, long n)
{
  SFFloat rad=10.0f;

  vrSolid *s1;
	if (test >= 6)
	{
		// Use Pedro
		test -= 6;
		switch (test)
		{
		case 0:
		default:
			s1 = Pedro();
			Sc(s1, 4.0f, 4.0f, 4.0f);
			break;
		}
	} else
	{
		s1 = new vrSolidBall(rad, 15, 15);
	}
	s1->SetColor(vrGreen);
  
  SFVec3f v(1.0f, 0.0f, 0.0f);

  for (long i=0;i<n;i++)
	{
CWaitCursor wc;
		vrMatrix M;
    vrMatrix N;
if (test == 0)
{
// works
    SFFloat aa = RandomValue(0.f, 360.0f);
		M = RotationXMatrix(vrDeg2Rad(aa));
    N = RotationYMatrix(i/(SFFloat)n);
} else if (test == 1)
{
// works -- performance measure test
    M = RotationXMatrix((SFFloat)cos(vrDeg2Rad(360.0f/(SFFloat)n)));
    N = RotationYMatrix((SFFloat)sin(vrDeg2Rad(-360.0f/(SFFloat)n)));
} else if (test == 2)
{
//  works
    M = RotationXMatrix(vrDeg2Rad(360.0f/(SFFloat)n));
    N = RotationYMatrix(vrDeg2Rad(-360.0f/(SFFloat)n));
} else if (test == 3)
{
// works
		M = IdentityMatrix();
    N = RotationYMatrix(vrDeg2Rad(360.0f/(SFFloat)n));
} else if (test == 4)
{
// works
		M = TranslationMatrix(i/(SFFloat)n);
    N = RotationYMatrix(0.0f);
} else
{
// fails
    SFFloat aa = RandomValue(0.f, 360.0f);
    SFFloat bb = -RandomValue(0.f, 360.0f);
		M = RotationXMatrix(vrDeg2Rad(aa));
    N = RotationYMatrix(vrDeg2Rad(bb));
}
    v = M * v;
    v = N * v;
		vrPlane p(v, (rad/n)*i+0.25f);
		vrSolid *a=NULL, *b=NULL;
		s1->Split(p, &a, &b);//
		if (a && b)
		{
		  ASSERT(a);
			ASSERT(b);
			a->SetColor(vrYellow);
			b->SetColor(vrBlue);
	
			b->SetColor(vrRed); //colorMap[i]);
			
			if (AfxGetApp()->GetProfileInt("Tests", "SplitMoveIn", FALSE))
			{
				SFVec3f v = -p.GetNormal();
				v = (v * 3.0f);
				b->TransformGeometry(TranslationMatrix(v));
			} else
			{
				SFVec3f v = p.GetNormal();
				v = (v * 3.0f);
				b->TransformGeometry(TranslationMatrix(v));
			}
			
			a->Merge(b);
			s1 = a;
		}
  }

  ASSERT(s1);
//  s1->Scale(0.15f);
  Trans(s1, -1.0f, -1.0f, 0.0f);
//  s1->SetName("Crazy Ball");

  return s1;
}

/*
vrSolid *Ball1(void)
{
  SFFloat rad=10.0;
  Int32 n=40;

  vrSolid *s1  = SolidBall(rad, 15, 15);
  vrSolid *res=NULL;
  
  SFVec3f vs[] = {
    SFVec3f(1.0, 0.0, 0.0),
    SFVec3f(0.0, 1.0, 0.0),
    SFVec3f(0.0, 0.0, 0.0)
  }; 

  SFFloat dd = (rad/(SFFloat)n);

  for (Int32 j=0;j<2;j++) {
    for (Int32 i=0;i<n;i++) {
//      printf("%f %f %f %f\n", vs[j].x, vs[j].y, vs[j].z, -(rad/2.0) + (dd*i));
      res = SplitIt(s1, CPlaneBase(vs[j], -(rad/2.0) + (dd*i)), colorMap[i]);
      s1 = res;
    }
  }

	ASSERT(res);
  return res;
}
*/