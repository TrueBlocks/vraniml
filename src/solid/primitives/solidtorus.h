#ifndef __SOLIDTORUS_H3D
#define __SOLIDTORUS_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "SolidCircle.h"  

class LIBInterface wSolidTorus : public wSolidCircle
{
public:
                wSolidTorus (void);
                wSolidTorus (const wSolidTorus& a);
	wSolidTorus& operator=    (const wSolidTorus& a);

               ~wSolidTorus (void);
								wSolidTorus (SFFloat rd1, SFFloat rd2, Uint32 nf1, Uint32 nf2);
  vrNode    *Clone        (void) const;
};

#endif
