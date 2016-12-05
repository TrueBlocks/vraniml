#ifndef __DECLS_H3D
#define __DECLS_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#pragma warning(disable: 4275)

typedef unsigned int Uint32;

//#define ENABLE_UNDO 1
#undef ENABLE_UNDO

#define DEB(th, msg)
#define DEBUG_MARKER(a)

#if defined(LIB3D)
#ifdef _DEBUG
	#undef DEB
	#undef DEBUG_MARKER
// turn these on if you need them
	#define DEBUG_MARKER(a)
	#define DEB(th, msg)
//	#define DEBUG_MARKER(a) { VRTRACE("/*******"); VRTRACE((a)); VRTRACE("*******/\n"); }
//	#define DEB(th, msg)    { extern vrDumpContext dc; traceContext = &dc; VRTRACE(msg); VRTRACE("\n"); (th)->Show(dc); }
#endif
#endif

class vrRenderTraverser;
class vrSolid;
class vrFace;
class vrEdge;
class vrVertex;
class vrLoop;
class vrHalfEdge;
#ifdef ENABLE_UNDO
class vrEulerOp;
#endif

/*********************************************************************/
#ifdef ERROR
#undef ERROR 
#endif
#define ERROR   0
#define SUCCESS 1

/* Marks for mark1 */
#undef IN
#undef OUT
#define ON     0
#define ABOVE   1
#define BELOW  -1

/* Marks for mark2 */
#define UNKNOWN        (1 << 1)
#define BRANDNEW       (1 << 2)
#define VISITED        (1 << 3)
#define ALTERED        (1 << 4)
#define CREASE         (1 << 12)  // edges that are creased are marked
#define PARTIAL_NORMAL (1 << 13)  // some verts have both 'creased' and 'uncreased' edges impinging
#define INVISIBLE      (1 << 15)
#define DELETED        0xdddddddd

#define POINT_SET      (1 << 20) 
#define LINE_SET       (1 << 21)
#define FACE_SET       (POINT_SET | LINE_SET)

#define CALCED         (1 << 25)

#define SOLID_NONE 0
#define SOLID_A    11
#define SOLID_B    12

/* Boolean set operations */
#define  vrUNION         1
#define  vrINTERSECTION  2
#define  vrDIFFERENCE    3

#ifdef _DEBUG
//Boolean HeChecks(vrHalfEdge *he1, vrHalfEdge *he2, char *s);
//#define HECHECK HeChecks
#define HECHECK(a, b, c)
#else
#define HECHECK(a, b, c)
#endif

#define PER_FACE            1
#define PER_VERTEX          2
#define PER_VERTEX_PER_FACE 3

typedef struct _colorData
{
public:
#define COLOR         0x1                         // | COLOR   |
#undef NORMAL
#define NORMAL        0x2                         // | NORMAL  |
#define TEXCOORD      0x4                         // | TEXUTRE |
#define COLORNORMAL   (COLOR  | NORMAL)           // | COLOR   | NORMAL   |
#define COLORTEXTURE  (COLOR  | TEXCOORD)         // | COLOR   | TEXCOORD |
#define NORMALTEXTURE (NORMAL | TEXCOORD)         // | NORMAL  | TEXCOORD |
#define ALL           (COLOR | NORMAL | TEXCOORD) // | COLOR   | NORMAL   | TEXCOORD |
	SFInt32 type;
//	SFInt32 size;
//	SFFloat vals[1]; // caution: variable length data
	SFColor   color;
	SFVec3f normal;
	SFVec2f texcoord;

	void SetNormal   (const SFVec3f& n);
	void SetColor    (const SFColor& c);
	void SetTexCoord (const SFVec2f& t);

	SFVec3f GetNormal   (void) const;
	SFColor   GetColor    (void) const;
	SFVec2f GetTexCoord (void) const;
} ColorData;
//ColorData *AddComponent(ColorData *d, SFInt32 t);

inline SFInt32 GetDataSize(SFInt32 type)
{
//	SFInt32 size = 8;
	
//	size += ((COLOR    & type) ?  sizeof(SFColor)   : 0);
//	size += ((NORMAL   & type) ?  sizeof(SFVec3f) : 0);
//	size += ((TEXCOORD & type) ?  sizeof(SFVec2f) : 0);

// return size;
	return sizeof(ColorData);
}

#ifdef _DEBUG
#define CHECK(a) (a)->Verify()
#define EULER_CHECK(a) { if (check_eulers) CHECK(a); }
#else
#define CHECK(a)
#define EULER_CHECK(a)
#endif

typedef SFFloat (*PFF)(SFFloat);

#endif