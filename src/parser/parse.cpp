
/*  A Bison parser, made from parse.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

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



#include "Parser.h"
#include "Parse.cxx"
extern void yyerror(const char *msg);
#pragma warning(disable:4701)

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

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		150
#define	YYFLAG		-32768
#define	YYNTBASE	41

#define YYTRANSLATE(x) ((unsigned)(x) <= 290 ? yytranslate[x] : 80)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,    40,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    36,     2,    37,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    38,     2,    39,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     3,     6,     8,    10,    12,    14,    17,    19,
    20,    25,    27,    29,    31,    32,    35,    36,    37,    48,
    49,    50,    61,    62,    66,    67,    70,    74,    75,    81,
    85,    86,    92,    93,    99,   101,   102,   108,   109,   110,
   119,   120,   123,   127,   131,   132,   138,   142,   143,   149,
   153,   162,   163,   169,   170,   173,   175,   177,   179,   180,
   184,   186,   188,   190,   192,   194,   196,   198,   200,   202,
   204,   206,   208,   210,   212,   214,   216,   218,   221,   224,
   228,   231,   235,   237,   240,   242,   246,   247
};

static const short yyrhs[] = {    42,
     0,     0,    43,    42,     0,    44,     0,    47,     0,    70,
     0,    45,     0,    26,     7,     0,    71,     0,     0,    25,
     7,    46,    71,     0,    49,     0,    63,     0,    52,     0,
     0,    47,    48,     0,     0,     0,    27,     7,    50,    36,
    56,    37,    51,    38,    55,    39,     0,     0,     0,    29,
     7,    53,    36,    56,    37,    54,    38,    55,    39,     0,
     0,    48,    45,    42,     0,     0,    61,    56,     0,    22,
     7,     7,     0,     0,    22,     7,     7,    58,    77,     0,
    23,     7,     7,     0,     0,    23,     7,     7,    59,    77,
     0,     0,    21,     7,     7,    60,    76,     0,    57,     0,
     0,    24,     7,     7,    62,    76,     0,     0,     0,    28,
     7,    64,    36,    66,    37,    65,    76,     0,     0,    67,
    66,     0,    22,     7,     7,     0,    23,     7,     7,     0,
     0,    21,     7,     7,    68,    76,     0,    21,     7,     7,
     0,     0,    24,     7,     7,    69,    76,     0,    24,     7,
     7,     0,    31,     7,    40,     7,    32,     7,    40,     7,
     0,     0,     7,    72,    38,    73,    39,     0,     0,    74,
    73,     0,    57,     0,    47,     0,    70,     0,     0,     7,
    75,    76,     0,     3,     0,     4,     0,     5,     0,     8,
     0,     6,     0,     9,     0,    10,     0,    11,     0,    12,
     0,    13,     0,    14,     0,    15,     0,    16,     0,    17,
     0,    18,     0,    19,     0,    20,     0,    34,    44,     0,
    34,    33,     0,    34,    30,     7,     0,    35,    78,     0,
    35,    30,     7,     0,    77,     0,    30,     7,     0,    44,
     0,    36,    79,    37,     0,     0,    44,    79,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    89,    94,    96,    99,   101,   102,   106,   108,   114,   116,
   120,   125,   127,   128,   131,   133,   136,   140,   142,   148,
   152,   154,   160,   162,   165,   167,   171,   177,   181,   183,
   188,   192,   194,   199,   203,   205,   210,   214,   219,   223,
   228,   230,   233,   239,   244,   249,   251,   256,   261,   263,
   271,   282,   287,   292,   294,   297,   299,   300,   301,   305,
   311,   316,   321,   326,   331,   336,   341,   346,   351,   356,
   362,   367,   372,   377,   382,   387,   392,   397,   399,   401,
   406,   408,   413,   416,   423,   425,   428,   430
};

static const char * const yytname[] = {   "$","error","$undefined.","SFBOOL",
"SFINT32","SFFLOAT","SFTIME","IDENTIFIER","SFSTRING","SFVEC2F","SFVEC3F","SFCOLOR",
"SFROTATION","SFIMAGE","MFINT32","MFFLOAT","MFSTRING","MFVEC2F","MFVEC3F","MFCOLOR",
"MFROTATION","FIELD","EVENTIN","EVENTOUT","EXPOSEDFIELD","DEF","USE","PROTO",
"EXTERNPROTO","RESOLVEDPROTO","IS","ROUTE","TO","NULLNODE","SFNODE","MFNODE",
"'['","']'","'{'","'}'","'.'","vrmlScene","statements","statement","nodeStatement",
"rootNodeStatement","@1","protoStatement","protoStatements","proto","@2","@3",
"resolvedexternproto","@4","@5","protoBody","interfaceDeclarations","restrictedInterfaceDeclaration",
"@6","@7","@8","interfaceDeclaration","@9","externproto","@10","@11","externInterfaceDeclarations",
"externInterfaceDeclaration","@12","@13","routeStatement","node","@14","nodeBody",
"nodeBodyElement","@15","fieldValue","isMapping","mfnodeStatement","nodes",""
};
#endif

static const short yyr1[] = {     0,
    41,    42,    42,    43,    43,    43,    44,    44,    45,    46,
    45,    47,    47,    47,    48,    48,    50,    51,    49,    53,
    54,    52,    55,    55,    56,    56,    57,    58,    57,    57,
    59,    57,    60,    57,    61,    62,    61,    64,    65,    63,
    66,    66,    67,    67,    68,    67,    67,    69,    67,    67,
    70,    72,    71,    73,    73,    74,    74,    74,    75,    74,
    76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
    76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
    76,    76,    76,    77,    78,    78,    79,    79
};

static const short yyr2[] = {     0,
     1,     0,     2,     1,     1,     1,     1,     2,     1,     0,
     4,     1,     1,     1,     0,     2,     0,     0,    10,     0,
     0,    10,     0,     3,     0,     2,     3,     0,     5,     3,
     0,     5,     0,     5,     1,     0,     5,     0,     0,     8,
     0,     2,     3,     3,     0,     5,     3,     0,     5,     3,
     8,     0,     5,     0,     2,     1,     1,     1,     0,     3,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     2,     2,     3,
     2,     3,     1,     2,     1,     3,     0,     2
};

static const short yydefact[] = {     2,
    52,     0,     0,     0,     0,     0,     0,     1,     2,     4,
     7,     5,    12,    14,    13,     6,     9,     0,    10,     8,
    17,    38,    20,     0,     3,    54,     0,     0,     0,     0,
     0,    59,     0,     0,     0,    57,    56,    58,     0,    54,
    11,    25,    41,    25,     0,     0,     0,     0,     0,    53,
    55,     0,     0,    35,    25,     0,     0,     0,     0,     0,
    41,     0,     0,    61,    62,    63,    65,    64,    66,    67,
    68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
     0,     0,     0,    60,    83,    33,    27,    30,     0,    18,
    26,     0,     0,     0,     0,    39,    42,    21,     0,    84,
     0,    79,    78,     0,    87,    85,    81,     0,     0,     0,
    36,     0,    45,    43,    44,    48,     0,     0,     0,    80,
    82,    87,     0,    34,    29,    32,     0,    15,     0,     0,
    40,    15,    51,    88,    86,    37,    15,     0,     0,    46,
    49,     0,    16,     2,    19,    22,    24,     0,     0,     0
};

static const short yydefgoto[] = {   148,
     8,     9,    10,    11,    27,    12,   138,    13,    28,   112,
    14,    30,   118,   139,    53,    54,   109,   110,   108,    55,
   127,    15,    29,   117,    60,    61,   129,   130,    16,    17,
    18,    39,    40,    46,    84,    85,   107,   123
};

static const short yypact[] = {    56,
-32768,    42,    43,    44,    66,    67,    71,-32768,    56,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,    50,-32768,-32768,
-32768,-32768,-32768,    58,-32768,    48,    93,    68,    72,    74,
    98,-32768,   102,   104,   106,-32768,-32768,-32768,    75,    48,
-32768,   -12,    73,   -12,    83,    18,   109,   110,   111,-32768,
-32768,   112,    84,-32768,   -12,   113,   115,   116,   117,    88,
    73,    89,   120,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   121,    34,    32,-32768,-32768,-32768,    99,   100,   124,-32768,
-32768,   125,   126,   127,   129,-32768,-32768,-32768,    97,-32768,
   131,-32768,-32768,   132,    40,-32768,-32768,    18,   114,   114,
-32768,   103,   -17,-32768,-32768,    69,    18,   105,   133,-32768,
-32768,    40,   108,-32768,-32768,-32768,    18,    17,    18,    18,
-32768,    17,-32768,-32768,-32768,-32768,   -11,    36,   107,-32768,
-32768,   118,-32768,    56,-32768,-32768,-32768,   142,   147,-32768
};

static const short yypgoto[] = {-32768,
    -9,-32768,   -80,    10,-32768,   -25,    12,-32768,-32768,-32768,
-32768,-32768,-32768,    19,   -36,    14,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    91,-32768,-32768,-32768,    46,   123,
-32768,   119,-32768,-32768,   -28,   -96,-32768,    31
};


#define	YYLAST		159


static const short yytable[] = {    25,
    36,   103,   106,   -47,   -47,   -47,   -47,    62,    33,    34,
    35,    52,   125,   126,    36,     4,     5,     6,    91,   -47,
    64,    65,    66,    67,   122,    68,    69,    70,    71,    72,
    73,    74,    75,    76,    77,    78,    79,    80,     1,    37,
     1,   122,     1,     4,     5,     6,     1,    81,    19,    20,
    21,    82,    83,    37,    32,   -23,     2,     3,     2,     3,
     2,   104,     1,   101,     2,     3,   102,   105,    33,    34,
    35,    38,    22,    23,     4,     5,     6,    24,     7,   124,
     2,     3,     4,     5,     6,    38,     7,    26,   131,   -50,
   -50,   -50,   -50,    56,    57,    58,    59,    31,   136,     1,
   140,   141,   137,    42,    45,   -50,   137,    43,    47,    44,
    48,   137,    49,    50,    63,    86,    87,    88,    89,    92,
    90,    93,    94,    95,    96,    98,    99,   100,   -28,   -31,
   111,   113,   114,   115,   147,   116,   119,   120,   121,   133,
   128,   149,   132,    81,   135,   145,   150,   144,   143,    41,
   142,    97,   134,     0,     0,     0,   146,     0,    51
};

static const short yycheck[] = {     9,
    26,    82,    83,    21,    22,    23,    24,    44,    21,    22,
    23,    24,   109,   110,    40,    27,    28,    29,    55,    37,
     3,     4,     5,     6,   105,     8,     9,    10,    11,    12,
    13,    14,    15,    16,    17,    18,    19,    20,     7,    26,
     7,   122,     7,    27,    28,    29,     7,    30,     7,     7,
     7,    34,    35,    40,     7,    39,    25,    26,    25,    26,
    25,    30,     7,    30,    25,    26,    33,    36,    21,    22,
    23,    26,     7,     7,    27,    28,    29,     7,    31,   108,
    25,    26,    27,    28,    29,    40,    31,    38,   117,    21,
    22,    23,    24,    21,    22,    23,    24,    40,   127,     7,
   129,   130,   128,    36,     7,    37,   132,    36,     7,    36,
     7,   137,     7,    39,    32,     7,     7,     7,     7,     7,
    37,     7,     7,     7,    37,    37,     7,     7,    30,    30,
     7,     7,     7,     7,   144,     7,    40,     7,     7,     7,
    38,     0,    38,    30,    37,    39,     0,   138,   137,    27,
   132,    61,   122,    -1,    -1,    -1,    39,    -1,    40
};

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not __GNUC__ */
#if HAVE_ALLOCA_H
#include <alloca.h>
#else /* not HAVE_ALLOCA_H */
#ifdef _AIX
 #pragma alloca
#else /* not _AIX */
char *alloca ();
#endif /* not _AIX */
#endif /* not HAVE_ALLOCA_H */
#endif /* not __GNUC__ */

extern int yylex();
extern void yyerror();

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug=1;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "\nEntering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  if (yychar==IDENTIFIER)
				fprintf (stderr, "Next token is %d (%s)**[%s", yychar, yytname[yychar1], yylval.stringVal);
			else
				fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);

	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;

#ifdef LIB3D
	yylval.stringVal = NULL;
#endif

#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 8:
{
					GetParser()->UseDefinedNode(yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 10:
{
					/* Define the next node */
					GetParser()->DefineCurrentNode(yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 11:
{
			;
    break;}
case 17:
{
					GetParser()->BeginPrototype(yyvsp[0].stringVal, FALSE);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 18:
{
			;
    break;}
case 19:
{
					GetParser()->EndPrototype();
			;
    break;}
case 20:
{
					GetParser()->BeginPrototype(yyvsp[0].stringVal, 2);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 21:
{
			;
    break;}
case 22:
{
					GetParser()->EndPrototype();
			;
    break;}
case 27:
{
					GetParser()->DeclareInterface(vrField::eventIn, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					//	CLEARSTRING($2); 
					//	CLEARSTRING($3);
			;
    break;}
case 28:
{
					GetParser()->DeclareInterface(vrField::eventIn, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal); 
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 29:
{
			;
    break;}
case 30:
{
					GetParser()->DeclareInterface(vrField::eventOut, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					// CLEARSTRING($2);
					// CLEARSTRING($3);
			;
    break;}
case 31:
{
					GetParser()->DeclareInterface(vrField::eventOut, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal); 
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 32:
{
			;
    break;}
case 33:
{
					GetParser()->nextFieldType = GetParser()->DeclareInterface(vrField::field, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 34:
{
			;
    break;}
case 36:
{
					GetParser()->nextFieldType = GetParser()->DeclareInterface(vrField::exposedField, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 37:
{
			;
    break;}
case 38:
{
					GetParser()->BeginPrototype(yyvsp[0].stringVal, TRUE);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 39:
{
					GetParser()->SetCurrentFieldName("");
					GetParser()->nextFieldType = MFSTRING;
			;
    break;}
case 40:
{
					GetParser()->EndPrototype();
			;
    break;}
case 43:
{
					GetParser()->DeclareInterface(vrField::eventIn, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 44:
{
					GetParser()->DeclareInterface(vrField::eventOut, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 45:
{
					GetParser()->nextFieldType = GetParser()->DeclareInterface(vrField::field, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 46:
{
			;
    break;}
case 47:
{
					GetParser()->DeclareInterface(vrField::field, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 48:
{
					GetParser()->nextFieldType = GetParser()->DeclareInterface(vrField::exposedField, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 49:
{
			;
    break;}
case 50:
{
					GetParser()->DeclareInterface(vrField::exposedField, yyvsp[-1].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-1].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 51:
{ 
					GetParser()->AddRoute(yyvsp[-6].stringVal, yyvsp[-4].stringVal, yyvsp[-2].stringVal, yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[-6].stringVal); 
					CLEARSTRING(yyvsp[-4].stringVal); 
					CLEARSTRING(yyvsp[-2].stringVal); 
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 52:
{
					GetParser()->BeginNode(yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 53:
{
					GetParser()->EndNode();
			;
    break;}
case 59:
{
					GetParser()->BeginField(yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 60:
{
					GetParser()->EndField();
			;
    break;}
case 61:
{
					AddSingleField(yyvsp[0].intVal);
					CLEAR(yyvsp[0].intVal);
			;
    break;}
case 62:
{
					AddSingleField(yyvsp[0].intVal);
					CLEAR(yyvsp[0].intVal);
			;
    break;}
case 63:
{
					AddSingleField(yyvsp[0].floatVal);
					CLEAR(yyvsp[0].floatVal);
			;
    break;}
case 64:
{
					AddSingleField(yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 65:
{
					AddSingleField(yyvsp[0].timeVal);
					CLEAR(yyvsp[0].timeVal);
			;
    break;}
case 66:
{
					AddSingleField(yyvsp[0].vec2Val);
					CLEAR(yyvsp[0].vec2Val);
			;
    break;}
case 67:
{
					AddSingleField(yyvsp[0].vec3Val);
					CLEAR(yyvsp[0].vec3Val);
			;
    break;}
case 68:
{
					AddSingleField(yyvsp[0].colorVal);
					CLEAR(yyvsp[0].colorVal);
			;
    break;}
case 69:
{
					AddSingleField(yyvsp[0].rotVal);
					CLEAR(yyvsp[0].rotVal);
			;
    break;}
case 70:
{
					AddSingleFieldImage(yyvsp[0].imageVal);
					yyvsp[0].imageVal->colors.Clear();
					CLEAR(yyvsp[0].imageVal);
			;
    break;}
case 71:
{
					AddMultiField(yyvsp[0].intArray);
					CLEARARRAY(yyvsp[0].intArray);
			;
    break;}
case 72:
{
					AddMultiField(yyvsp[0].floatArray);
					CLEARARRAY(yyvsp[0].floatArray);
			;
    break;}
case 73:
{
					AddMultiField(yyvsp[0].stringArray);
					CLEARARRAY(yyvsp[0].stringArray);
			;
    break;}
case 74:
{
					AddMultiField(yyvsp[0].vec2Array);
					CLEARARRAY(yyvsp[0].vec2Array);
			;
    break;}
case 75:
{
					AddMultiField(yyvsp[0].vec3Array);
					CLEARARRAY(yyvsp[0].vec3Array);
			;
    break;}
case 76:
{
					AddMultiField(yyvsp[0].colorArray);
					CLEARARRAY(yyvsp[0].colorArray);
			;
    break;}
case 77:
{
					AddMultiField(yyvsp[0].rotArray);
					CLEARARRAY(yyvsp[0].rotArray);
			;
    break;}
case 80:
{
					GetParser()->MapFieldName(yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 82:
{
					GetParser()->MapFieldName(yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
case 84:
{
					GetParser()->MapFieldName(yyvsp[0].stringVal);
					CLEARSTRING(yyvsp[0].stringVal);
			;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}


void yyerror(const char *msg)
{
	GetParser()->Error(msg);
}
