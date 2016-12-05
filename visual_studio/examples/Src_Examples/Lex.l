%{

#include "Parser.h"
#include "Tokens.h"

int yywrap()
{
		BEGIN INITIAL;
		return 1;
}

void CleanupParser(void)
{
			if (yy_current_buffer)
				yy_delete_buffer( yy_current_buffer );
			yy_current_buffer = NULL;
			yyin     = NULL;
			yy_init  = 1;
			yy_start = 0;
			GetParser()->Clear();
}

#define RETURN(token) \
	BEGIN PARSING_NODE; \
	GetParser()->nextFieldType = 0; \
	return (token);

	/* Static data to avoid re-creating these for every token */
static Int32       sInt32;
static Float       sFloat;
static Time        sTime;
static Vec2        sVec2;
static Vec3        sVec3;
static Color       sColor;
static Rot         sRot;
static Image       sImage;
static String      sString;
static Int32Array  sInt32Array;
static FloatArray  sFloatArray;
static Vec2Array   sVec2Array;
static Vec3Array   sVec3Array;
static ColorArray  sColorArray;
static RotArray    sRotArray;
static StringArray sStringArray;

	/* Grab a single data item */
#define GRABSINGLE(mem, type, val) \
	ASSERT(!yylval.stringVal); \
	(mem) = &s##type; \
	*(mem) = (val);

	/* Grab a single string */
#define GRABSINGLESTRING(mem, type, val) \
	(mem) = strdup(val);

	/* Grab a single vector, color or rotation */
#define GRABSINGLEVEC(mem, type, val) \
	ASSERT(!yylval.stringVal); \
	(mem) = &s##type; \
	(mem)->v = (val);

	/* Grab a single array element */
#define GRABARRAYELEMENT(mem, type, val, ret) \
	if (GetParser()->needsClear) \
		{ mem = NULL; } \
	GetParser()->needsClear = FALSE; \
	if (GetParser()->multiField) \
	{ \
		if (!(mem)) \
		{ \
			(mem) = &s##type; \
		} \
		(mem)->AddValue((val)); \
	} else \
	{ \
		(mem) = &s##type; \
		(mem)->AddValue((val)); \
		RETURN((ret)); \
	}
	
%}

	/* Parser states */
%x PARSING_NODE
%x SEARCH_BOOL
%x SEARCH_INT32
%x SEARCH_FLOAT
%x SEARCH_TIME
%x SEARCH_STRING
%x SEARCH_VEC2
%x SEARCH_VEC3
%x SEARCH_COLOR
%x SEARCH_ROTATION
%x SEARCH_IMAGE
%x SEARCH_MINT32
%x SEARCH_MFLOAT
%x SEARCH_MSTRING
%x SEARCH_MVEC2
%x SEARCH_MVEC3
%x SEARCH_MCOLOR
%x SEARCH_MROTATION
%x PARSING_STRING
%x PARSING_MSTRING
%x PARSING_IMAGE

	/* Types */
float     (-?(([0-9]+)|([0-9]+\.)|([0-9]*\.?[0-9]+)([eE][+\-]?[0-9]+)?)) 
int       (-?([0-9]+)|(0[xX][0-9a-fA-F]*))
ws        ([ \t\r\n,]|(#.*))+
wsnnl     ([ \t\r,]|(#.*))
firstChar ([^\x30-\x39\x00-\x20\x22\x23\x27\x2b-\x2e\x5b-\x5d\x7b\x7d\x7f])
restChars ([^\x00-\x20\x22\x23\x27\x2c\x2e\x5b-\x5d\x7b\x7d\x7f])

%%

%{
  /* enter a new state based on the next field type */
		switch (GetParser()->nextFieldType)
		{
      case SFBOOL:     BEGIN SEARCH_BOOL;      break;
      case SFINT32:    BEGIN SEARCH_INT32;     break;
      case SFFLOAT:    BEGIN SEARCH_FLOAT;     break;
      case SFTIME:     BEGIN SEARCH_TIME;      break;
      case SFSTRING:   BEGIN SEARCH_STRING;    break;
      case SFVEC2F:    BEGIN SEARCH_VEC2;      break;
      case SFVEC3F:    BEGIN SEARCH_VEC3;      break;
      case SFCOLOR:    BEGIN SEARCH_COLOR;     break;
      case SFROTATION: BEGIN SEARCH_ROTATION;  break;
      case SFIMAGE:    BEGIN SEARCH_IMAGE;     break;

      case MFINT32:    BEGIN SEARCH_MINT32;    break;
      case MFFLOAT:    BEGIN SEARCH_MFLOAT;    break;
      case MFSTRING:   BEGIN SEARCH_MSTRING;   yylval.stringArray = NULL; break;
      case MFVEC2F:    BEGIN SEARCH_MVEC2;     break;
      case MFVEC3F:    BEGIN SEARCH_MVEC3;     break;
      case MFCOLOR:    BEGIN SEARCH_MCOLOR;    break;
      case MFROTATION: BEGIN SEARCH_MROTATION; break;

      case SFNODE:     GetParser()->nextFieldType = 0;     return SFNODE;
      case MFNODE:     GetParser()->nextFieldType = 0;     return MFNODE;
      
      case 0:          break;
      default:         GetParser()->Error("bad field type"); break;
    }
%}

<INITIAL>"#VRML V2.0 utf8".*\n{wsnnl}* {
		BEGIN PARSING_NODE;
		yylval.stringVal = NULL;
}

<PARSING_NODE>PROTO {
		return PROTO;
}

<PARSING_NODE>EXTERNPROTO {
		return EXTERNPROTO;
}

<PARSING_NODE>RESOLVEDPROTO {
		return RESOLVEDPROTO;
}

<PARSING_NODE>DEF {
		return DEF;
}

<PARSING_NODE>USE {
		return USE;
}

<PARSING_NODE>TO {
		return TO;
}

<PARSING_NODE>IS {
		return IS;
}

<PARSING_NODE>ROUTE {
		return ROUTE;
}

<PARSING_NODE>NULL {
		return NULLNODE;
}

<PARSING_NODE>eventIn {
		return EVENTIN;
}

<PARSING_NODE>eventOut {
		return EVENTOUT;
}

<PARSING_NODE>field {
		return FIELD;
}

<PARSING_NODE>exposedField {
		return EXPOSEDFIELD;
}

<PARSING_NODE>{firstChar}{restChars}* {
		GRABSINGLESTRING(yylval.stringVal, String, yytext);
		return IDENTIFIER;
}

<SEARCH_BOOL,SEARCH_INT32,SEARCH_FLOAT,SEARCH_STRING,SEARCH_TIME,SEARCH_IMAGE,SEARCH_VEC2,SEARCH_VEC3,SEARCH_COLOR,SEARCH_ROTATION>IS {
		BEGIN PARSING_NODE;
		GetParser()->nextFieldType = 0;
		yyless(0);
}

<SEARCH_MINT32,SEARCH_MFLOAT,SEARCH_MSTRING,SEARCH_MVEC2,SEARCH_MVEC3,SEARCH_MCOLOR,SEARCH_MROTATION>IS {
		BEGIN PARSING_NODE;
		GetParser()->nextFieldType = 0;
		yyless(0);
}

<SEARCH_MINT32,SEARCH_MFLOAT,SEARCH_MSTRING,SEARCH_MVEC2,SEARCH_MVEC3,SEARCH_MCOLOR,SEARCH_MROTATION>\[ {
		if (GetParser()->multiField) 
			GetParser()->Error("second '[' encountered while parsing MF field"); 
		GetParser()->multiField = TRUE;
		GetParser()->needsClear = TRUE;
}

<SEARCH_MINT32,SEARCH_MFLOAT,SEARCH_MSTRING,SEARCH_MVEC2,SEARCH_MVEC3,SEARCH_MCOLOR,SEARCH_MROTATION>\] {
		if (!GetParser()->multiField)
				GetParser()->Error("']' encountered while not parsing MF field"); 
		if (GetParser()->needsClear)
				yylval.stringVal = NULL;
		int fieldType = GetParser()->nextFieldType;
		GetParser()->multiField = FALSE;
		RETURN(fieldType);
}
				      
		/* single fields */
<SEARCH_BOOL>TRUE {
		GRABSINGLE(yylval.intVal, Int32, TRUE);
		RETURN(SFBOOL);
}

<SEARCH_BOOL>FALSE {
		GRABSINGLE(yylval.intVal, Int32, FALSE);
		RETURN(SFBOOL);
}

<SEARCH_INT32>{int} {
		GRABSINGLE(yylval.intVal, Int32, atoi(yytext));
		RETURN(SFINT32);
}

<SEARCH_FLOAT>{float} {
		GRABSINGLE(yylval.floatVal, Float, (float)atof(yytext));
		RETURN(SFFLOAT);
}

<SEARCH_TIME>{float} {
		GRABSINGLE(yylval.timeVal, Time, (float)atof(yytext));
		RETURN(SFTIME);
}
	       
		/* string field */
<SEARCH_STRING>\" {
		yylval.stringVal = NULL;
		BEGIN PARSING_STRING;
}

<SEARCH_STRING>[^ \"\t\r\,\n]+ {
		GetParser()->Error("String missing open-quote");
		RETURN(SFSTRING);
}
	
<PARSING_STRING>\\\" {
}

<PARSING_STRING>[^\"\n]+ {
		GRABSINGLESTRING(yylval.stringVal, String, yytext);
}

<PARSING_STRING>\" {
		RETURN(SFSTRING);
}

		/* image field */
<SEARCH_IMAGE>{int}{ws}{int} {
		int w, h;
		sscanf(yytext, "%d %d %d", &w, &h);
		GetParser()->nComponentsNeeded = 1+w*h;
		GetParser()->nComponentsFound = 0;                          
		yylval.imageVal = &sImage;
		yylval.imageVal->img.m_Width = w;
		yylval.imageVal->img.m_Height = h;
		yylval.imageVal->img.m_nComponents = 0;

		BEGIN PARSING_IMAGE;
}

<PARSING_IMAGE>{int} {
		GetParser()->nComponentsFound++;
		int x;
		if (GetParser()->nComponentsFound==1)
		{
				sscanf(yytext, "%d", &x);
				yylval.imageVal->img.m_nComponents = x;
		} else
		{
				sscanf(yytext, "%x", &x);
				yylval.imageVal->colors.AddValue(x);
		}
		if (GetParser()->nComponentsFound == GetParser()->nComponentsNeeded)
		{
				RETURN(SFIMAGE);
		}
}

		/* single vector fields */
<SEARCH_VEC2>{float}{ws}{float} {
		SFVec2f v;
		sscanf(yytext, "%f %f", &v.x, &v.y);
		GRABSINGLEVEC(yylval.vec2Val, Vec2, v);
		RETURN(SFVEC2F);
}

<SEARCH_VEC3>{float}{ws}{float}{ws}{float} {
		SFVec3f v;
		sscanf(yytext, "%f %f %f", &v.x, &v.y, &v.z);
		GRABSINGLEVEC(yylval.vec3Val, Vec3, v);
		RETURN(SFVEC3F);
}

<SEARCH_COLOR>{float}{ws}{float}{ws}{float} {
		SFColor v;
		sscanf(yytext, "%f %f %f", &v.x, &v.y, &v.z);
		GRABSINGLEVEC(yylval.colorVal, Color, v);
		RETURN(SFCOLOR);
}

<SEARCH_ROTATION>{float}{ws}{float}{ws}{float}{ws}{float} {
		SFRotation v;
		sscanf(yytext, "%f %f %f %f", &v.x, &v.y, &v.z, &v.w);
		GRABSINGLEVEC(yylval.rotVal, Rot, v);
		RETURN(SFROTATION);
}

		/* multi fields */
<SEARCH_MINT32>{int} {
		int v;
		sscanf(yytext, "%d", &v);
		GRABARRAYELEMENT(yylval.intArray, Int32Array, v, MFINT32);
}

<SEARCH_MFLOAT>{float} {
		float v;
		sscanf(yytext, "%f", &v);
		GRABARRAYELEMENT(yylval.floatArray, FloatArray, v, MFFLOAT);
}

		/* multi string field */
<SEARCH_MSTRING>\"# {
		GetParser()->viewpoint = TRUE;
		if (!yylval.stringArray)
		{
				sStringArray.Clear();
				yylval.stringArray = &sStringArray;
		}
		BEGIN PARSING_MSTRING;
}

<SEARCH_MSTRING>\" {
		if (!yylval.stringArray)
		{
				sStringArray.Clear();
				yylval.stringArray = &sStringArray;
		}
		BEGIN PARSING_MSTRING;
}

<SEARCH_MSTRING>[^ \[\]\"\t\r\,\n]+ {
		GetParser()->Error("String missing open-quote");
		RETURN(MFSTRING);
}

<PARSING_MSTRING>\\\" {
}

<PARSING_MSTRING>[^\"]+ {
		GetParser()->needsClear = FALSE;
		assert(yylval.stringArray);
		if (GetParser()->viewpoint)
		{
				char tmp[255];
				sprintf(tmp, "#%s", yytext);
				yylval.stringArray->AddValue(tmp);
				GetParser()->viewpoint = FALSE;
		} else
		{
				yylval.stringArray->AddValue(yytext);
		}
}

<PARSING_MSTRING>\" {
		if (GetParser()->multiField)
		{
				BEGIN SEARCH_MSTRING;
		} else
		{
				RETURN(MFSTRING);
		}
}

		/* Multi vector fields */
<SEARCH_MVEC2>{float}{ws}{float} {
		SFVec2f v;
		sscanf(yytext, "%f %f", &v.x, &v.y);
		GRABARRAYELEMENT(yylval.vec2Array, Vec2Array, v, MFVEC2F);
}

<SEARCH_MVEC3>{float}{ws}{float}{ws}{float} {
		SFVec3f v;
		sscanf(yytext, "%f %f %f", &v.x, &v.y, &v.z);
		GRABARRAYELEMENT(yylval.vec3Array, Vec3Array, v, MFVEC3F);
}

<SEARCH_MCOLOR>{float}{ws}{float}{ws}{float} {
		SFColor v;
		sscanf(yytext, "%f %f %f", &v.x, &v.y, &v.z);
		GRABARRAYELEMENT(yylval.colorArray, ColorArray, v, MFCOLOR);
}

<SEARCH_MROTATION>{float}{ws}{float}{ws}{float}{ws}{float} {
		SFRotation v;
		sscanf(yytext, "%f %f %f %f", &v.x, &v.y, &v.z, &v.w);
		GRABARRAYELEMENT(yylval.rotArray, RotArray, v, MFROTATION);
}

<*>{wsnnl}+	;

<*>{wsnnl}*\n{wsnnl}* {
		GetParser()->curLine++;
}

<*>. {
		return yytext[0];
}
