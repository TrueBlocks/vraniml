#include "..\stdafx.h"

#include "Tests.h"
#include "../BoolTestDialog.h"

vrSolid *NoVertVertTests1(vrBoolTestRecord *rec);
vrSolid *NoVertVertTests2(vrBoolTestRecord *rec);
vrSolid *NoVertVertTests3(vrBoolTestRecord *rec);
vrSolid *VertVertTests1  (vrBoolTestRecord *rec);
vrSolid *VertVertTests2  (vrBoolTestRecord *rec);
vrSolid *VertVertTests3  (vrBoolTestRecord *rec);
vrSolid *VertVertTests4  (vrBoolTestRecord *rec);
vrSolid *VertVertTests5  (vrBoolTestRecord *rec);
vrSolid *BigBallTests    (vrBoolTestRecord *rec);
vrSolid *Blocks          (vrBoolTestRecord *rec);
vrSolid *BoolTest12      (vrBoolTestRecord *rec);
vrSolid *BoolTest13      (vrBoolTestRecord *rec);
vrSolid *BoolTest14      (vrBoolTestRecord *rec);

vrBoolTestRecord *r;
long op;

SFBool Working(long group)
{
if (AfxGetApp()->GetProfileInt("Tests", "Working", FALSE))
{
	return TRUE;
}

long id = AfxGetApp()->GetProfileInt("Tests", "TestNum", 0);

//	if (group == 1)
//	{
//		if (id == 1 && op == UNION) return FALSE;
//		if (id == 3 && op == UNION) return FALSE;
//		if (id == 5 && op == UNION) return FALSE;
//	}
//	if (group == 6)
//	{
//		if (id == 1 && op == UNION) return FALSE;
//	}
//	if (group == 7)
//	{
//		if (id == 1 && op == UNION) return FALSE;
//		if (id == 6 && op == UNION) return FALSE;
//	}
//	if (group == 8)
//	{
//		if (id == 0 && op == UNION) return FALSE;
//		if (id == 1 && op == UNION) return FALSE;
//		if (id == 6 && op == UNION) return FALSE;
//	}
	if (group == 9)
	{
//		if (id == 0 && op == UNION) return FALSE;
		if (id == 2 && op == vrINTERSECTION) return FALSE;
		if (id == 2 && op == vrUNION) return FALSE;
		if (id == 2 && op == vrDIFFERENCE) return FALSE;
	}
	if (group == 11)
	{
		if (id == 1) return FALSE;
		if (id == 5) return FALSE;
		if (id == 6) return FALSE;
	}
	if (group == 12)
	{
		if (op == vrUNION) return FALSE;
		if (id == 5) return FALSE;
	}
	if (group == 13)
	{
		if (id == 1) return FALSE;
		if (id == 3 && op == vrINTERSECTION) return FALSE;
		if (id == 5) return FALSE;
	}
	return TRUE;
}

vrSolid *BoolTests(vrBoolTestRecord *rec)
{
r = rec;

	AfxGetApp()->WriteProfileInt("Tests", "BoolLastCenter", rec->center);
	AfxGetApp()->WriteProfileInt("Tests", "BoolLastRotate", rec->rotate);
	AfxGetApp()->WriteProfileInt("Tests", "BoolLastWide",   rec->wide);
	
	switch (rec->group)
	{
	case 0: 
	case 1: 
	case 2: 
		return NoVertVertTests1(rec);
	case 3: 
	case 4: 
		return NoVertVertTests2(rec);
	case 5:
		return NoVertVertTests3(rec);
	case 6:
		return VertVertTests1(rec);
	case 7:
		return VertVertTests2(rec);
	case 8:
		return VertVertTests3(rec);
	case 9:
		return VertVertTests4(rec);
	case 10:
		return BoolTest12(rec);
		break;
	case 11:
		return BoolTest14(rec);
		break;
	case 12:
		return BoolTest13(rec);
		break;
	case 13:
		return Blocks(rec);
	case 14:
		return VertVertTests5(rec); //BigBallTests(rec);
	}
	return NULL;
}

#ifdef STATS
CStatistics stats;
#endif

vrSolid *Inter(vrSolid *s1, vrSolid *s2)
{
op=vrINTERSECTION;
if (!Working(r->group)) return new vrSolidBall(0.5f, 5, 5);

  vrSolid *res = NULL;

#ifdef STATS
  s1->Intersection(s2, &res, &stats);
#else
  s1->Intersection(s2, &res, NULL);
#endif

  if (!res) {
    res = new vrSolidCube(0.1f);
    res->SetColor(vrCadetBlue);
  }

  if (res != s1 && res != s2)
	{
		delete s1;
		delete s2;
	} else
	{
		res->SetColor(vrYellow);
	}
  return res;
}

vrSolid *Union(vrSolid *s1, vrSolid *s2)
{
op=vrUNION;
if (!Working(r->group)) return new vrSolidBall(0.5f, 5, 5);

  vrSolid *res = NULL;

#ifdef STATS
  s1->Union(s2, &res, &stats);
#else
  s1->Union(s2, &res, NULL);
#endif

  if (!res) {
    res = new vrSolidCube(0.1f);
    res->SetColor(vrCadetBlue);
  }

  if (res != s1 && res != s2)
	{
		delete s1;
		delete s2;
	} else
	{
		res->SetColor(vrYellow);
	}
  return res;
}

vrSolid *Diff(vrSolid *s1, vrSolid *s2)
{
op=vrDIFFERENCE;
if (!Working(r->group)) return new vrSolidBall(0.5f, 5, 5);

  vrSolid *res = NULL;

#ifdef STATS
  s1->Difference(s2, &res, &stats);
#else
  s1->Difference(s2, &res, NULL);
#endif

  if (!res) {
    res = new vrSolidCube(0.1f);
    res->SetColor(vrCadetBlue);
  }

  if (res != s1 && res != s2)
	{
		delete s1;
		delete s2;
	} else
	{
		res->SetColor(vrYellow);
	}

  return res;
}

