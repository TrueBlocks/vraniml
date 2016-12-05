//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "SolidTorus.h"

wSolidTorus::wSolidTorus(void) : wSolidCircle()
{
}

wSolidTorus::wSolidTorus(const wSolidTorus& a) : wSolidCircle(a)
{
}

wSolidTorus::wSolidTorus(SFFloat rd1, SFFloat rd2, Uint32 nf1, Uint32 nf2) : wSolidCircle(0.0f, rd1, rd2, 0.0f, nf2)
{
  RotationalSweep(nf1);
//  CHECK(this);
}

wSolidTorus::~wSolidTorus(void)
{
}

wSolidTorus& wSolidTorus::operator=(const wSolidTorus& a)
{
  wSolidCircle::operator=(a);
  return *this;
}

SFNode wSolidTorus::Clone(void) const
{
  return new wSolidTorus(*this);
}
