#ifndef __3D_H3D
#define __3D_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

// Include basic data structures need by all classes.
// Note: This is the pre-compiled header
#include "Kramer.h"

// Include the browser class...
#include "Browser\Browser.h"

// ...all node classes...
#include "Nodes\AllNodes.h"

// ...and all traverser classes.
#include "Traversers\AllTraversers.h"

// ...and the solid modeling classes
#include "Solid\Solid.h"

// If we've defined ASSERT macro undefine it so other libs (i.e. MFC) will not complain
#ifdef ASSERT_DEFINED
#undef ASSERT
#undef VERIFY
#endif

#ifdef ENDL_DEFINED
#error
#undef endl
#endif

// Link in the library
#ifdef _DEBUG
#pragma comment(lib, "vranimld.lib")
#else
#pragma comment(lib, "vraniml.lib")
#endif

#ifdef VR_INCLUDE_OLD_NAMES
#include "OldNames.h"
#endif

#endif