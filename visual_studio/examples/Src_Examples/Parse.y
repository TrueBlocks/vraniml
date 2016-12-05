%{

#include "Parser.h"
#include "Parse.cxx"
extern void yyerror(const char *msg);

%}

%union {
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
};

%type <intVal>      SFBOOL
%type <intVal>      SFINT32
%type <floatVal>    SFFLOAT
%type <timeVal>     SFTIME
%type <stringVal>   IDENTIFIER
%type <stringVal>   SFSTRING
%type <vec2Val>     SFVEC2F
%type <vec3Val>     SFVEC3F
%type <colorVal>    SFCOLOR
%type <rotVal>      SFROTATION
%type <imageVal>    SFIMAGE
%type <intArray>    MFINT32
%type <floatArray>  MFFLOAT
%type <stringArray> MFSTRING
%type <vec2Array>   MFVEC2F
%type <vec3Array>   MFVEC3F
%type <colorArray>  MFCOLOR 
%type <rotArray>    MFROTATION

%token IDENTIFIER

%token FIELD
%token EVENTIN
%token EVENTOUT
%token EXPOSEDFIELD

%token DEF
%token USE
%token PROTO
%token EXTERNPROTO
%token RESOLVEDPROTO
%token IS
%token ROUTE
%token TO

%token NULLNODE

%token SFBOOL
%token SFINT32
%token SFFLOAT
%token SFTIME
%token SFSTRING
%token SFVEC2F
%token SFVEC3F
%token SFCOLOR
%token SFROTATION
%token SFIMAGE
%token SFNODE

%token MFINT32
%token MFFLOAT
%token MFSTRING
%token MFVEC2F
%token MFVEC3F
%token MFCOLOR
%token MFROTATION
%token MFNODE

%%

	/*- The whole VRML file -*/
vrmlScene:
			statements
	;

	/*- Statements -*/
statements:
	  /* Empty is OK */
	| statement statements
	;

statement:
	  nodeStatement
	|	protoStatement
	|	routeStatement
	;

	/*- Nodes -*/
nodeStatement:
			rootNodeStatement
	|	USE IDENTIFIER	{
					GetParser()->UseDefinedNode($2);
					CLEARSTRING($2);
			}
	;

rootNodeStatement:
			node
	|	DEF IDENTIFIER {
					/* Define the next node */
					GetParser()->DefineCurrentNode($2);
					CLEARSTRING($2);
			} node {
			}
	;

	/*- PROTO's -*/
protoStatement:
			proto
	|	externproto
	|	resolvedexternproto
	;

protoStatements:
			/* Empty */
	| protoStatement protoStatements
	;

proto:
			PROTO IDENTIFIER	{
					GetParser()->BeginPrototype($2, FALSE);
					CLEARSTRING($2);
			}	'[' interfaceDeclarations ']'
			{
			} '{' protoBody '}'
			{
					GetParser()->EndPrototype();
			}
	;

resolvedexternproto:
			RESOLVEDPROTO IDENTIFIER	{
					GetParser()->BeginPrototype($2, 2);
					CLEARSTRING($2);
			}	'[' interfaceDeclarations ']'
			{
			} '{' protoBody '}'
			{
					GetParser()->EndPrototype();
			}
	;

protoBody:
			/* Empty */
	| protoStatements rootNodeStatement statements
	; 

interfaceDeclarations:
			/* Empty */
	| interfaceDeclaration interfaceDeclarations
	;

	/* for scripts only */
restrictedInterfaceDeclaration:
			EVENTIN IDENTIFIER IDENTIFIER {
					GetParser()->DeclareInterface(vrField::eventIn, $2, $3);
					//	CLEARSTRING($2); 
					//	CLEARSTRING($3);
			}
	| EVENTIN IDENTIFIER IDENTIFIER {
					GetParser()->DeclareInterface(vrField::eventIn, $2, $3);
					CLEARSTRING($2); 
					CLEARSTRING($3);
			} isMapping {
			}
	| EVENTOUT IDENTIFIER IDENTIFIER {
					GetParser()->DeclareInterface(vrField::eventOut, $2, $3);
					// CLEARSTRING($2);
					// CLEARSTRING($3);
			}
	| EVENTOUT IDENTIFIER IDENTIFIER {
					GetParser()->DeclareInterface(vrField::eventOut, $2, $3);
					CLEARSTRING($2); 
					CLEARSTRING($3);
			} isMapping {
			}
	| FIELD IDENTIFIER IDENTIFIER {
					GetParser()->nextFieldType = GetParser()->DeclareInterface(vrField::field, $2, $3);
					CLEARSTRING($2);
					CLEARSTRING($3);
			}
		fieldValue {
			}
	;

interfaceDeclaration:
			restrictedInterfaceDeclaration
	|	EXPOSEDFIELD IDENTIFIER IDENTIFIER {
					GetParser()->nextFieldType = GetParser()->DeclareInterface(vrField::exposedField, $2, $3);
					CLEARSTRING($2);
					CLEARSTRING($3);
			}
			fieldValue {
			}
	; 

externproto:
			EXTERNPROTO IDENTIFIER	{
					GetParser()->BeginPrototype($2, TRUE);
					CLEARSTRING($2);
			}						
			'[' externInterfaceDeclarations ']' {
					GetParser()->SetCurrentFieldName("");
					GetParser()->nextFieldType = MFSTRING;
			}
			fieldValue {
					GetParser()->EndPrototype();
			}
	;

externInterfaceDeclarations:
			/* Empty */
	| externInterfaceDeclaration externInterfaceDeclarations
	; 

externInterfaceDeclaration:
			EVENTIN IDENTIFIER IDENTIFIER {
					GetParser()->DeclareInterface(vrField::eventIn, $2, $3);
					CLEARSTRING($2);
					CLEARSTRING($3);
			}
	| EVENTOUT IDENTIFIER IDENTIFIER {
					GetParser()->DeclareInterface(vrField::eventOut, $2, $3);
					CLEARSTRING($2);
					CLEARSTRING($3);
			}
	|	FIELD IDENTIFIER IDENTIFIER {
					GetParser()->nextFieldType = GetParser()->DeclareInterface(vrField::field, $2, $3);
					CLEARSTRING($2);
					CLEARSTRING($3);
			}
			fieldValue {
			}
	|	FIELD IDENTIFIER IDENTIFIER {
					GetParser()->DeclareInterface(vrField::field, $2, $3);
					CLEARSTRING($2);
					CLEARSTRING($3);
			}
	|	EXPOSEDFIELD IDENTIFIER IDENTIFIER {
					GetParser()->nextFieldType = GetParser()->DeclareInterface(vrField::exposedField, $2, $3);
					CLEARSTRING($2);
					CLEARSTRING($3);
			}
			fieldValue {
			}
	|	EXPOSEDFIELD IDENTIFIER IDENTIFIER {
					GetParser()->DeclareInterface(vrField::exposedField, $2, $3);
					CLEARSTRING($2);
					CLEARSTRING($3);
			}
	;

	/*- ROUTE statement -*/
routeStatement:
			ROUTE IDENTIFIER '.' IDENTIFIER TO IDENTIFIER '.' IDENTIFIER { 
					GetParser()->AddRoute($2, $4, $6, $8);
					CLEARSTRING($2); 
					CLEARSTRING($4); 
					CLEARSTRING($6); 
					CLEARSTRING($8);
			}
	; 

	/*- Node -*/
node:
			IDENTIFIER	{
					GetParser()->BeginNode($1);
					CLEARSTRING($1);
			}
			'{' nodeBody '}'	{
					GetParser()->EndNode();
			}
	;

nodeBody:
			/* Empty */
	| nodeBodyElement nodeBody
	;

nodeBodyElement:
	 	restrictedInterfaceDeclaration
	|	protoStatement
	|	routeStatement
	|	IDENTIFIER {
					GetParser()->BeginField($1);
					CLEARSTRING($1);
			}
			fieldValue {
					GetParser()->EndField();
			}
	;

	/*--*/
fieldValue:
			SFBOOL {
					AddSingleField($1);
					CLEAR($1);
			}
	|	SFINT32
			{
					AddSingleField($1);
					CLEAR($1);
			}
	| SFFLOAT
			{
					AddSingleField($1);
					CLEAR($1);
			}
	|	SFSTRING
			{
					AddSingleField($1);
					CLEARSTRING($1);
			}
	|	SFTIME
			{
					AddSingleField($1);
					CLEAR($1);
			}
	|	SFVEC2F
			{
					AddSingleField($1);
					CLEAR($1);
			}
	|	SFVEC3F
			{
					AddSingleField($1);
					CLEAR($1);
			}
	| SFCOLOR
			{
					AddSingleField($1);
					CLEAR($1);
			}
	|	SFROTATION
			{
					AddSingleField($1);
					CLEAR($1);
			}
	|	SFIMAGE
			{
					AddSingleFieldImage($1);
					$1->colors.Clear();
					CLEAR($1);
			}
	|	MFINT32
			{
					AddMultiField($1);
					CLEARARRAY($1);
			}
	|	MFFLOAT
			{
					AddMultiField($1);
					CLEARARRAY($1);
			}
	|	MFSTRING
			{
					AddMultiField($1);
					CLEARARRAY($1);
			}
	|	MFVEC2F
			{
					AddMultiField($1);
					CLEARARRAY($1);
			}
	|	MFVEC3F
			{
					AddMultiField($1);
					CLEARARRAY($1);
			}
	|	MFCOLOR
			{
					AddMultiField($1);
					CLEARARRAY($1);
			}
	|	MFROTATION
			{
					AddMultiField($1);
					CLEARARRAY($1);
			}
	|	SFNODE
			nodeStatement
	|	SFNODE
			NULLNODE
	|	SFNODE IS IDENTIFIER
			{
					GetParser()->MapFieldName($3);
					CLEARSTRING($3);
			}
	|	MFNODE
			mfnodeStatement
	|	MFNODE IS IDENTIFIER
			{
					GetParser()->MapFieldName($3);
					CLEARSTRING($3);
			}
 | isMapping
	;

isMapping:
	IS IDENTIFIER
			{
					GetParser()->MapFieldName($2);
					CLEARSTRING($2);
			}

mfnodeStatement:
			nodeStatement
	|	'[' nodes ']'
	;

nodes:
			/* Empty */
	|	nodeStatement nodes
	;

%%

void yyerror(const char *msg)
{
	GetParser()->Error(msg);
}
