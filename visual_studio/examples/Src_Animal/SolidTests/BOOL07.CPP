#include "..\stdafx.h"

#include "Tests.h"

static vrSolid *Big()
{
  vrSolid *s = new vrSolidCube(1.0f);
  s->SetColor(vrRed);
  return s;
}

vrSolid *Block(void)
{
	vrSolid *s = new vrSolidCube(0.5f);
  Sc(s, 3.0f, 1.0f, 1.0f);
	vrSolid *s1 = new vrSolidCube(0.5f);
  Sc(s1, 1.0f, 3.0f, 1.0f);
	Trans(s1, 0.1f, 0.1f, 0.1f);

	return Union(s, s1);
}

static vrSolid *Little(Int32 i)
{
  Float trans[][3] =
	{
    {  0.25f,  0.25f, -1.00f },  // no intersection
    {  0.25f,  0.25f, -0.50f },  // on the face
    {  0.25f,  0.25f, -0.25f },  // intersects one face
    {  0.25f,  0.25f,  0.00f },  // inside (one face intersection)
    {  0.25f,  0.25f,  0.25f },  // inside (no face intersections)
    {  0.25f,  0.25f,  0.00f },  // inside (two face intersections)
    {  0.25f,  0.25f, -0.15f },  // through
  };

  vrSolid *s = Block();
  s->SetColor(vrGreen);

	if (AfxGetApp()->GetProfileInt("Tests", "BoolLastRotate", FALSE))
	{
		if (AfxGetApp()->GetProfileInt("Tests", "BoolLastCenter", FALSE))
		{
			RotCenter(s, 45.0f, ZZZ);
		} else
		{
			Rotate(s, 45.0f, ZZZ);
		}
	}

  Trans(s, trans[i][0], trans[i][1], trans[i][2]);
	//Float sc=1.0f;
	switch (i)
	{
		case 0: case 1: case 2: case 5: 
			Sc(s, 1.0f, 1.0f, 2.0f);
			break;
		case 6: 
			Sc(s, 1.0f, 1.0f, 4.0f);
			break;
	}

  return s;
}

static vrSolid *DoTest(long op, Int32 i, Int32 allTests, Float trans[][3])
{
  vrSolid *s1 = NULL;
  vrSolid *s2 = NULL;
  vrSolid *s3 = NULL;
  vrSolid *s4 = NULL;
  vrSolid *s5 = NULL;
  vrSolid *sss = NULL;

  switch (op)
	{
  case 0:
    sss = Big();
    s5 = Little(i);
    sss->Merge(s5);
    s2 = sss;
    delete s5;
    break;
  case 1: 
    s2 = Inter (Big(), Little(i));
    break;
  case 2: 
    s2 = Union (Big(), Little(i));
    break;
  case 3: 
    s2 = Diff  (Big(), Little(i)); 
    break;
  case 4: 
    s1 = Inter (Big(), Little(i));
    s2 = Union (Big(), Little(i));
    s3 = Diff  (Big(), Little(i)); 
    s4 = Big();
    s5 = Little(i);
    s4->Merge(s5);
    delete s5;
    break;
  }
  
  if (s1 && s3 && s4)
	{
    s1->TransformGeometry(TranslationMatrix(SFVec3f(0.0f, -3.0f, 0.0f)));
    s3->TransformGeometry(TranslationMatrix(SFVec3f(0.0f,  3.0f, 0.0f)));
    s4->TransformGeometry(TranslationMatrix(SFVec3f(0.0f,  6.0f, 0.0f)));
    s2->Merge(s1);
    s2->Merge(s3);
    s2->Merge(s4);
    delete s1;
    delete s3;
    delete s4;
  }
  
  if (allTests) 
		s2->TransformGeometry(TranslationMatrix(SFVec3f(trans[i][0], trans[i][1], trans[i][2])));
  return s2;
}

vrSolid *Blocks(vrBoolTestRecord *rec)
{
  Float trans[][3] =
	{
    {  3.75f,  0.00f,  0.00f },
    {  2.50f,  0.00f,  0.00f },
    {  1.25f,  0.00f,  0.00f },
    {  0.00f,  0.00f,  0.00f },
    { -1.25f,  0.00f,  0.00f },
    { -2.50f,  0.00f,  0.00f },
    { -3.75f,  0.00f,  0.00f },
  };
	{
		trans[0][0] =  7.25f; trans[0][1] = 0.00f; trans[0][2] = 0.00f;
		trans[1][0] =  5.00f;  trans[1][1] = 0.00f; trans[1][2] = 0.00f;
		trans[2][0] =  2.50f; trans[2][1] = 0.00f; trans[2][2] = 0.00f;
		trans[3][0] =  0.00f; trans[3][1] = 0.00f; trans[3][2] = 0.00f;
		trans[4][0] = -2.50f; trans[4][1] = 0.00f; trans[4][2] = 0.00f;
		trans[5][0] = -5.00f; trans[5][1] = 0.00f; trans[5][2] = 0.00f;
		trans[6][0] = -7.25f; trans[6][1] = 0.00f; trans[6][2] = 0.00f;
	}

  // These tests have no vert/vert intersections
  vrSolid *s=NULL, *s1=NULL;

  switch(rec->testId)
	{
  case 0:
  case 1:
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
		s = DoTest(rec->op, rec->testId, FALSE, trans); 
    break;
  case 7:
    {
AfxGetApp()->WriteProfileInt("Tests", "TestNum", 0);
			s = DoTest(rec->op, 0, TRUE, trans);
			for (int j=1;j<rec->testId;j++)
			{
AfxGetApp()->WriteProfileInt("Tests", "TestNum", j);
				s1 = DoTest(rec->op, j, TRUE, trans);
				s->Merge(s1);
				delete s1;
			}
		}
    break;
  default:
    {
      Int32 bad=0;
      ASSERT(bad);
    }
  }

  ASSERT(s);

  return s;
}

