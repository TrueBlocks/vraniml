#ifndef _H_FIELDVAL
#define _H_FIELDVAL

/* Generated by Parser -- Do not change -- See tokens.h */
#define	SFBOOL	   258
#define	SFINT32	   259
#define	SFFLOAT	   260
#define	SFTIME	   261
#define	SFSTRING	 263
#define	SFVEC2F	   264
#define	SFVEC3F	   265
#define	SFCOLOR	   266
#define	SFROTATION 267
#define	SFIMAGE	   268
#define	MFINT32	   269
#define	MFFLOAT	   270
#define	MFSTRING	 271
#define	MFVEC2F	   272
#define	MFVEC3F	   273
#define	MFCOLOR	   274
#define	MFROTATION 275
#define	SFNODE	   289
#define	MFNODE	   290

//class	SFNode;
//class	MFNode;
class MFString;
typedef double SFTime;

union UL_Interface _fieldValUnion
{
public:
	_fieldValUnion(){boolVal=NULL;}
	SFBool      *boolVal;
	SFInt32     *intVal;
	SFFloat     *floatVal;
	SFTime      *timeVal;
	SFString    *stringVal;
	SFVec2f     *vec2Val;
	SFVec3f     *vec3Val;
	SFColor     *colorVal;
	SFRotation  *rotVal;
	SFImage     *imageVal;
	MFInt32     *intArray;
	MFFloat     *floatArray;
	MFString    *stringArray;
	MFVec2f     *vec2Array;
	MFVec3f     *vec3Array;
	MFColor     *colorArray;
	MFRotation  *rotArray;
	void        *voidPtr; // for unknown types
};

class vrDumpContext;
class vrFieldList;

#endif