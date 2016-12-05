#include "stdio.h"
#include "stdlib.h"
#include "direct.h"
#include "assert.h"
#include "errno.h"

#define ASSERT assert
#define MAX_GROUPS 100
extern SFString groups[MAX_GROUPS];
extern SFBool   groupsOn[MAX_GROUPS];
extern SFString groupDirs[MAX_GROUPS];
extern SFInt32  nGroups;
extern SFString outputDir;

void Init(void);
SFInt32 FindGroup(const SFString& group);
void SetOn(const SFString& group);
void SetOff(const SFString& group);
void AddGroup(const SFString& line);
void DoIt(char *str);
SFInt32 DoReplace(SFString& dir);
void PrettyPrint(SFString& line);
SFInt32 Parse(char *buffer, SFString& line);

#define vrCOMMENT     0
#define vrON          1
#define vrOFF         2
#define vrGROUP       3
#define vrPRETTY      4
#define vrOUTPUTDIR   5
#define vrNONE        6
#define vrIF0         7
#define vrENDIF       8


