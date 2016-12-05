typedef union {
	Int32       *intVal;
	Float       *floatVal;
	Time        *timeVal;
	char        *stringVal;
	Vec2        *vec2Val;
	Vec3        *vec3Val;
	Color       *colorVal;
	Rot         *rotVal;
	Image       *imageVal;
	Int32Array  *intArray;
	FloatArray  *floatArray;
	StringArray *stringArray;
	Vec2Array   *vec2Array;
	Vec3Array   *vec3Array;
	ColorArray  *colorArray;
	RotArray    *rotArray;
} YYSTYPE;
#define	SFBOOL	258
#define	SFINT32	259
#define	SFFLOAT	260
#define	SFTIME	261
#define	IDENTIFIER	262
#define	SFSTRING	263
#define	SFVEC2F	264
#define	SFVEC3F	265
#define	SFCOLOR	266
#define	SFROTATION	267
#define	SFIMAGE	268
#define	MFINT32	269
#define	MFFLOAT	270
#define	MFSTRING	271
#define	MFVEC2F	272
#define	MFVEC3F	273
#define	MFCOLOR	274
#define	MFROTATION	275
#define	FIELD	276
#define	EVENTIN	277
#define	EVENTOUT	278
#define	EXPOSEDFIELD	279
#define	DEF	280
#define	USE	281
#define	PROTO	282
#define	EXTERNPROTO	283
#define	RESOLVEDPROTO	284
#define	IS	285
#define	ROUTE	286
#define	TO	287
#define	NULLNODE	288
#define	SFNODE	289
#define	MFNODE	290


extern YYSTYPE yylval;
