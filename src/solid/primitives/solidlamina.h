#ifndef __SOLIDLAMINA_H3D
#define __SOLIDLAMINA_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "..\Solid.h"

class vrSolidLamina : public vrSolid
{
public:
  vrSolidLamina(void);
  vrSolidLamina(const vrSolidLamina& a);
  vrSolidLamina& operator=(const vrSolidLamina& a);

  vrSolidLamina(Uint32 n, SFVec3f vecs[]);
  ~vrSolidLamina(void);
  SFNode Clone(void) const;
};

inline vrSolidLamina::vrSolidLamina(void) : vrSolid()
{
}

inline vrSolidLamina::vrSolidLamina(const vrSolidLamina& a) : vrSolid(a)
{
}

inline vrSolidLamina::vrSolidLamina(Uint32 n, SFVec3f vecs[]) : vrSolid(vecs[0].x, vecs[0].y, vecs[0].z)
{
	for (Uint32 i=1;i<n;i++)
	{
		smev(0, i-1, vecs[i].x, vecs[i].y, vecs[i].z);
	}
	smef(0, n-1, 0);
}

inline vrSolidLamina::~vrSolidLamina(void)
{
}

inline vrSolidLamina& vrSolidLamina::operator=(const vrSolidLamina& a)
{
  ASSERT(0);
  return *this;
}

#endif
