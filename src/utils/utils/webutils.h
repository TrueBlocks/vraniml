#ifndef __WEB_H3D
#define __WEB_H3D
//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//<doc>
// Make sure the given 'remoteFilename' is on the local machine.
// Return the name of the local file (which is created in the
// application's current working directory).
//
// [out] remoteFilename: Name of the file to fetch from the network (if necassary).
//
// Note: remoteFilename may already be local in which case this function returns immediatly.
// Note: The name CacheFile is currently a misnomer.  The function
//       does not really cache the file on the local disc.  All
//       it does it copy the file locally.  In the future this
//       function will indeed cache files making access to remote
//       internet files faster.
extern SFString UL_Interface vrCacheFile(SFString& remoteFilename, SFInt32 mode=1);

//-------------------------------------------------------------------------
//<doc>
// Returns TRUE if the given filename is a remote filename.
extern SFBool UL_Interface vrIsNetworkFile(const SFString& remoteFilename);

//-------------------------------------------------------------------------
//<nodoc>
// Expands a path to include full path resolution
extern SFString UL_Interface vrExpandPath(const SFString& s);

//-------------------------------------------------------------------------
//<doc>
// Returns TRUE if the given name is a valid VRML name
extern SFBool UL_Interface vrIsValidName(const SFString& name);

#endif