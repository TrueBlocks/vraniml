#ifndef _EXTERNPROTO_H
#define _EXTERNPROTO_H

// Resolves all extern protos in a file and returns the name
// of a file that will contain the resolved externs
SFString resolveExterns(SFString& filename);

// Returns TRUE if the given file has an EXTERNPROTO
SFBool hasExtern(const SFString& filename);

#endif

