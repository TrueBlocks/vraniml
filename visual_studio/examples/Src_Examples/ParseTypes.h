#ifndef _PARSETYPES_H
#define _PARSETYPES_H

// Single Field Standin Types
#define Int32   SFInt32
#define Float   SFFloat
#define Time    SFTime
#define Bool    SFBool

// Single Field Vector Standin Types
typedef struct
{
public:
	SFString v;
} String;
typedef struct
{
public:
	SFVec2f v;
} Vec2;
typedef struct
{
public:
	SFVec3f v;
} Vec3;
typedef struct
{
public:
	SFRotation v;
} Rot;
typedef struct
{
public:
	SFColor v;
} Color;
typedef struct
{
public:
	SFImage img;
	MFInt32 colors;
} Image;

template <class SINGLE, class MUTLI>
class Array
{
public:
	MUTLI array;
	void Clear(void)
		{
			array.Clear();
		}
	SFInt32 GetCount(void) const
		{
			return array.GetCount();
		}
	void AddValue(SINGLE val)
		{
			array.AddValue(val);
		}

  SINGLE operator[](SFInt32 index)
		{
			return array[index];
		}
};
typedef Array<SFInt32,    MFInt32>    Int32Array;
typedef Array<SFFloat,    MFFloat>    FloatArray;
typedef Array<SFVec2f,    MFVec2f>    Vec2Array;
typedef Array<SFVec3f,    MFVec3f>    Vec3Array;
typedef Array<SFRotation, MFRotation> RotArray;
typedef Array<SFColor,    MFColor>    ColorArray;

class StringArray : public Array<SFString, MFString>
{
public:
	void Clear(void)
		{
			array.Clear();
		}
};
//typedef Array<SFString,   MFString>   StringArray;

#define CLEAR(a) \
	{ \
		a = NULL; \
		yylval.stringVal = NULL; \
	}

#define CLEARSTRING(aa) \
	{ \
		if (aa) \
			free(aa); \
		aa = NULL; \
		yylval.stringVal = NULL; \
	}

#define CLEARARRAY(a) \
	{ \
		if (a) \
			a->Clear(); \
		a = NULL; \
		yylval.stringVal = NULL; \
	}

#endif