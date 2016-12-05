//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid.h"

/*
SFBool vrSolid::BoolOp(vrSolid *A, vrSolid *B, vrSolid **R, long op, void *statRec)
{
	A->Merge(B);
	*R = A;
	return TRUE;
}
*/

SFBool vrSolid::Union(vrSolid *B, vrSolid **result, void *statRec)
{
  return BoolOp(this, B, result, vrUNION, statRec);
}

SFBool vrSolid::Intersection(vrSolid *B, vrSolid **result, void *statRec)
{
  return BoolOp(this, B, result, vrINTERSECTION, statRec);
}

SFBool vrSolid::Difference(vrSolid *B, vrSolid **result, void *statRec)
{
  return BoolOp(this, B, result, vrDIFFERENCE, statRec);
}

/*
SFBool vrSolid::Split(const vrPlane& SP, vrSolid **Above, vrSolid **Below)
{
	return TRUE;
}
*/
