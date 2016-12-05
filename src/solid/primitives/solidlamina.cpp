//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "SolidLamina.h"

SFNode vrSolidLamina::Clone(void) const
{
  return new vrSolidLamina(*this);
}
