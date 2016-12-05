//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#ifndef _TESTUTIL_H
#define _TESTUTIL_H

// A seperate test function for each class
void TestAllClasses         (void);

// Collection classes
void   TestArrayBaseClass     (void);
void   TestArrayClass         (void);
void   TestIntrusiveListClass (void);
void   TestListClass          (void);
void   TestRefCountListClass  (void);
void   TestSFStringClass      (void);
void   TestStackClass         (void);
void   TestRefCountStackClass (void);

// Geometry classes
void   TestBoundingBoxClass   (void);
void   TestImageClass         (void);
void   TestMatrixClass        (void);
void   TestPlaneClass         (void);
void   TestRayClass           (void);
void   TestRect2DClass        (void);
void   TestColorClass         (void);
void   TestVec2fClass         (void);
void   TestVec3fClass         (void);
void   TestRotationClass      (void);

// Utility classes
void   TestDumpContextClass   (void);
void   TestTimeClass          (void);
void   TestUtilityFunctions   (void);
void   TestImageLib           (void);

// Runtime typing
void   TestRuntimeTypes       (void);

#include "TestNode.h"

// Support function does nothing
inline void ApplyOperation(SFNode n)
{
	// Anything you choose here.
}

// Support function does nothing
inline vrRay GetLineOfSite(void)
{
	// Line from 0,0,-10 to origin
	return vrRay(SFVec3f(0,0,-10), zAxis);
}

extern vrDumpContext dc;
#include "conio.h"

#include "TestNode.h"

#endif