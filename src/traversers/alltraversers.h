#ifndef __ALLTRAVERSERSERS_H3D
#define __ALLTRAVERSERSERS_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "Traversers\WriteTraverser.h"
#include "Traversers\ActionTraverser.h"

#ifdef FULL_VERSION // full version supports rendering
#include "Traversers\D3DTraverser.h"
#include "Traversers\OGLTraverser.h"
#include "Traversers\ValidateTraverser.h"
#endif

#endif