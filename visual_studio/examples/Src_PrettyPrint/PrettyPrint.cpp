#include "vraniml.h"
#include "PrettyPrint.h"

void main(int argc, char *argv[])
{
	Init();

	// Time the parsing
	vrTime start = vrNow();

	FILE *in = fopen("src_prettyprint\\test.dat", "r");
	if (in)
	{
		SFBool skip = FALSE;
		char buffer[4096];
		while (fgets(buffer, 4096, in))
		{
			SFString line;
			SFInt32 type = Parse(buffer, line);
			switch (type)
			{
			case vrIF0:
				skip = TRUE;
				break;
			case vrENDIF:
				skip = FALSE;
				break;
			case vrCOMMENT:
				break;
			case vrON:
				if (!skip)
					SetOn(line);
				break;
			case vrOFF:
				if (!skip)
					SetOff(line);
				break;
			case vrGROUP:
				if (!skip)
					AddGroup(line);
				break;
			case vrPRETTY:
				if (!skip)
					PrettyPrint(line);
				break;
			case vrOUTPUTDIR:
				outputDir = line;
				break;
			case vrNONE:
				break;
			default:
				ASSERT(0);
			}
		}

		vrTime stop = vrNow();
		double diff = stop - start;

		vrDumpContext dc;
		dc << "Start time: " << start << "\n"; 
		dc << "Stop time:  " << stop << "\n"; 
		dc << "Elapsed:    " << diff << "\n"; 
	}
}

#include "stdio.h"
#include "stdlib.h"
#include "direct.h"
#include "assert.h"
#include "errno.h"

#define ASSERT assert
#define MAX_GROUPS 100
SFString groups[MAX_GROUPS];
SFBool   groupsOn[MAX_GROUPS];
SFString groupDirs[MAX_GROUPS];
SFInt32  nGroups=0;

void Init(void)
{
	for (int i=0;i<MAX_GROUPS;i++)
	{
		groupsOn[i] = FALSE;
		groups[i] = "";
		groupDirs[i] = "";
	}
}

SFInt32 FindGroup(const SFString& group)
{
	for (int i=0;i<nGroups;i++)
		if (groups[i] == group)
			return i;
	return -1;
}

void SetOn(const SFString& group)
{
	SFInt32 find = FindGroup(group);
	if (find!=-1)
		return;
	groupsOn[nGroups]  = TRUE;
	groups[nGroups++] = group;
}

void SetOff(const SFString& group)
{
	SFInt32 find = FindGroup(group);
	if (find!=-1)
		return;
	groupsOn[nGroups]  = FALSE;
	groups[nGroups++] = group;
}

void AddGroup(const SFString& line)
{
	SFInt32 find = line.Find(" ");
	ASSERT(find != -1);
	SFString group = line.Left(find);
	SFString dir   = line.Mid(find+1);

	find = FindGroup(group);
	if (find!=-1)
		groupDirs[find] = dir;
	else
	{
		groups[nGroups]      = group;
		groupsOn[nGroups]    = TRUE;
		groupDirs[nGroups++] = dir;
	}
}

void DoIt(char *str);
SFInt32 DoReplace(SFString& dir) // and do replace
{
	for (int i=0;i<nGroups;i++)
	{
		if (dir.Find(groups[i])!=-1)
		{
			dir.ReplaceAll(groups[i], groupDirs[i]);
			return i;
		}
	}
	return -1;
}

void PrettyPrint(SFString& line)
{
	SFInt32 find = DoReplace(line);
	ASSERT(find!=-1);
	if (groupsOn[find])
		DoIt((char *)line);
}

SFString outputDir = "d:";

SFInt32 Parse(char *buffer, SFString& line)
{
	line = buffer;
	SFInt32 find = line.Find(" ");
	line.ReplaceAll("\r\n", "");
	line.ReplaceAll("\r", "");
	line.ReplaceAll("\n", "");

	if (line == "#if 0")
		return vrIF0;
	else if (line == "#endif")
		return vrENDIF;
	else if (line.Left(1) == "#")
		return vrCOMMENT;
	else if (line.Left(2) == "on")
	{
		ASSERT(find==2);
		line = line.Mid(find+1);
		return vrON;
	} else if (line.Left(3) == "off")
	{
		ASSERT(find==3);
		line = line.Mid(find+1);
		return vrOFF;
	} else if (line.Left(5) == "group")
	{
		ASSERT(find==5);
		line = line.Mid(find+1);
		return vrGROUP;
	} else if (line.Left(6) == "pretty")
	{
		ASSERT(find==6);
		line = line.Mid(find+1);
		return vrPRETTY;
	} else if (line.Left(9) == "outputDir")
	{
		ASSERT(find==9);
		line = line.Mid(find+1);
		return vrOUTPUTDIR;
	}

	return vrNONE;
}

#include "Windows.h"
class vrWindowsConsole : public vrConsole
{
public:
	HWND hWnd;
	vrWindowsConsole(HWND wnd=NULL) { hWnd = wnd; }
	void Error(const SFString& msg)
		{
 			MessageBox(hWnd, (const char *)msg, "Parse Error", MB_OK);
		}
};

void DoIt(char *filename)
{
	if (!strstr(filename, ".wrl"))
	{
		char sss[1000];
		strcpy(sss, (char*)outputDir);
		strcat(sss, filename+2);
#ifdef _DEBUG
		SFInt32 ret = _mkdir(sss);
#else
		_mkdir(sss);
#endif
		ASSERT(ret==0 || errno==EEXIST);
		return;
	}
	
	printf("pretty printing %s\n", filename);

	vrBrowser browser;
	vrWindowsConsole console;
	browser.m_Console = &console;
	browser.ReadURL(filename);

	vrWriteTraverser wt(NULL,NULL);
	wt.SetTabStop(2);
	char ssss[512];
	strcpy(ssss, (char*)outputDir);
	strcat(ssss, filename+2);
	wt.SetFilename(ssss);
	browser.Traverse(&wt);
}
