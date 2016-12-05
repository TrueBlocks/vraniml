//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "Utils\Utility.h"

#include "TestParser.h"
#include "Parser.h"

#ifdef _DEBUG
vrDumpContext tracer;
#endif
vrDumpContext dc;

extern int yyparse();
extern FILE *yyin;
void CleanupParser(void);
int cnt=0;

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

class vrDumpConsole: public vrConsole
{
public:
	vrDumpContext *dc;
	vrDumpConsole(vrDumpContext *d=NULL)
		{ dc = d; }
	void Error(const SFString& msg)
		{
			if (dc)
				*dc << msg;
		}
	void Message(const SFString& msg)
		{
			if (dc)
				*dc << msg;
		}
};

void main(int argc, char *argv[])
{
int n=1;
	for (int i=0;i<n;i++)
	{
cnt=0;
//		dc << i;
//		vrWindowsConsole console;
		vrDumpConsole console(&dc);
		GetParser()->console = &console;
		TestParser(argc, argv);
	}
}

void Doit(const SFString& fileName)
{
	if (fileName.Find(".wrl") == -1)
	{
//		SFString ss = "d:\\Worlds\\" + s.Mid(3);
//		_mkdir((const char *)ss);
		return;
	}
	
//	vrParser::PushNameSpace("TOP");

	int len = fileName.Length();
	SFString s = fileName.Right(MIN(len, 40));
	SFString ss(' ', MAX(40-len, 0));
	SFString str;
	if (s[1] != ':')
		str += "...";
	str += (s + ss);
static int ii=0;
ii++;
	dc << "[" << ii << "]Parsing " << str << ":\t";

#ifdef _DEBUG
	tracer << "\n//--------------------------------------------------\n";
	tracer << "****Parsing " << fileName << "\n";
#endif
	FILE *in  = fopen((const char *)fileName, "r");
	ASSERT(in);
	CleanupParser();
	GetParser()->top = new vrNode;
	GetParser()->top->SetClassName("Top");
	yyin = in;

  yyparse();

	delete GetParser()->top;
	GetParser()->top = NULL;
	GetParser()->nodeStack.RemoveAll();
//	ASSERT(GetParser()->protoStack.Peek());
//	ASSERT(GetParser()->protoStack.GetCount()==54);

	dc << GetParser()->curLine << " lines\r";
	cnt += GetParser()->curLine;

	CleanupParser();

//	vrParser::PopNameSpace();
extern void ClearNamedNodes(void);
	ClearNamedNodes();

	fseek(in, 0, SEEK_SET);
	if (in && in != stdin)
		fclose(in);
}

int TestParser(int argc, char *argv[])
{
SFBool sm        = 1;
SFBool large     = 0;
SFBool verylarge = 0;

PushNameSpace("TOP");
	vrTime start = vrNow();

#ifdef _DEBUG
	tracer.SetFilename("out.wrl");
	tracer.m_Suppress=TRUE;
#endif

	dc << "Parsing " << "standardNodes.wrl" << endl;
	FILE *in  = fopen((const char *)"standardNodes.wrl", "r");
	ASSERT(in);
	CleanupParser();
	GetParser()->top = NULL;
	yyin = in;
  yyparse();
	GetParser()->nodeStack.RemoveAll();
	fseek(in, 0, SEEK_SET);
	if (in && in != stdin)
		fclose(in);
#ifdef _DEBUG
tracer.m_Suppress=FALSE;
#endif

//	Doit("d:\\3dapps\\3d\\utils\\examples\\test4.wrl");

if (verylarge)
{
	Doit("d:\\3dapps\\3d\\utils\\examples\\test4.wrl");
	Doit("d:\\3dapps\\3d\\utils\\examples\\test.wrl");
	Doit("d:\\3dapps\\3d\\utils\\examples\\test1.wrl");
	Doit("d:\\3dapps\\3d\\utils\\examples\\test2.wrl");
}

if (sm)
{
	// Annotated VRML 2.0 Reference Manual
	Doit("d:\\worlds\\books\\annotated\\egs\\adclip.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\anchor.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\appr.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\bckgd.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\blbrd.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\box.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\cllson.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\clrnter.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\color.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\cone.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\crdntrp.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\cylinder.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\cylnsen.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\drlt.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\elgrid.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\extrsn.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\fntsty.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\fog.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\grndplne.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\group.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\imgtexe.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\indxfst.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\indxlst.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\inline.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\lod.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\material.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\mvtexe.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\navinfo.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\normal.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\nrmlntr.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\orntrpl.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\plansnb.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\pntlt.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\pointst.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\posntrp.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\proxsn.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\scalntp.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\script.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\shape.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\sound.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\sphrb.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\sphrsnb_bad.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\sphrsnb.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\sptlt.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\switch.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\texcrdb.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\text.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\texxf.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\timesnb.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\viewpnt.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\vissn.wrl");
	Doit("d:\\worlds\\books\\annotated\\egs\\wrldnfo.wrl");
	Doit("d:\\worlds\\books\\");
	Doit("d:\\worlds\\books\\annotated\\");
	Doit("d:\\worlds\\books\\annotated\\samples\\");
	Doit("d:\\worlds\\books\\annotated\\samples\\chpbdy.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\chprtr.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex10.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex12.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex13.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex17.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex18.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex2.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex3.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex4.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex5.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex6.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\ex9.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\rfrmtl.wrl");
	Doit("d:\\worlds\\books\\annotated\\samples\\rotor.wrl");

	// VRML 2.0 Sourcebook
	Doit("d:\\worlds\\books\\");
	Doit("d:\\worlds\\books\\sourcebook\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch02\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch02\\02fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig06.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig07.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch03\\03fig10.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig06a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig06b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig07.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig08a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig08b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig10.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch04\\04fig11.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\05fig03b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\05fig04b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\05fig05b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\05fig06b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\05fig07b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\05fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\05fig10.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch05\\05fig11.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig04b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig05b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig06b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig07b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig10.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig11.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch06\\06fig12.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig04b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig05b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig06b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig07b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig08b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig10.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig11.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig12a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig12b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch07\\07fig13.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch08\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch08\\08fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch08\\08fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch08\\08fig06.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch08\\08fig07.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig06.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig07.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig07.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig10.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch11\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch11\\11fig01a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch11\\11fig01b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch11\\11fig01c.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch11\\11fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch11\\11fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch11\\11fig04.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch12\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch12\\12fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch12\\12fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch12\\12fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch12\\arch.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch12\\archrow.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\13fig10.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\13fig11.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\13fig12.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\13fig13.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\13fig14.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\13fig15.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\13fig16.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\vault.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch14\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch14\\14fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch14\\14fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch14\\14fig04a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch14\\14fig04b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch14\\14fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch14\\14fig06.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch14\\ribbon.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig07.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig10.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig11.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig12.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig13.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig14.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig15.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig16.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch16\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch16\\16fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch16\\16fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch16\\16fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch16\\16fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch16\\16fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch16\\16fig06.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch16\\16fig07.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig04a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig04b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig04c.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig04d.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig05d.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig06b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig07b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig08b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig09b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig10c.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig11b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig12b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig14b.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig19b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig20b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig21.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig22b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig23b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig24.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig25b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig26b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig26c.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig21.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig22.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig23.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig24a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig24b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig25a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig25b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig26.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\19fig27.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\colca1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch19\\colsmth.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig06a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig06b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig07.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig11a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig11b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig12.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig13a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig13b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig13c.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig15a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig15b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig16a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig16b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig16c.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig17a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig17b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\mesh.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\spheres.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\vault.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\vaulted.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch21\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch21\\21fig04a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch21\\21fig04b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch21\\21fig04c.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch21\\21fig04d.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch21\\21fig05.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch22\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch22\\22fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch22\\22fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch22\\22fig03c.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig02a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig02b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig02c.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig02d.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig03a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig03b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig03c.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\23fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch23\\fogworld.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\24fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\24fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\24fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\sndmark.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig06.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig07.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig10.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig11.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\ddoor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\dfloor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\droom.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\dwall.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\dwall2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\torch1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\torch2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\torch3.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\torches.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\26fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\26fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\26fig06a.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\26fig06b.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\26fig07.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\ddoor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\dfloor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\droom.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\dwall.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\dwall2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\torch1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\torch2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\torch3.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\torches.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\ddoor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\dfloor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\droom.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\dwall.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\dwall2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\torch1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\torch2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\torch3.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\torches.wrl");
	
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\28fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\28fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\ddoor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\dfloor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\dngnwrld.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\droom.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\dwall.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\dwall2_bad.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\dwall2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\torch1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\torch2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\torch3.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\torches.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\29fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\ddoor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\dfloor.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\droom.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\dwall.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\dwall2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\torch1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\torch2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\torch3.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\torches.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch30\\");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch08\\08fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch08\\08fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch09\\09fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig06.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig08.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig09.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig11.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch10\\10fig12.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch13\\13fig17.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch18\\18fig27.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch22\\22fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\24fig04.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\24fig05.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\24fig06.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch25\\25fig12.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch26\\dungeon.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\27fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\27fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch27\\27fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch28\\dungeon.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch29\\dungeon.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch30\\30fig01.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch30\\30fig03.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch30\\30fig04.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch15\\15fig17.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch17\\17fig13.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig10.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch20\\20fig14.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch24\\24fig07.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch30\\30fig02.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\book\\win\\ch30\\30fig05.wrl");

	// VRaniML Tests
	Doit("d:\\Great Hill Corporation");
	Doit("d:\\Great Hill Corporation\\VRaniML");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance\\appearance.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance\\appearance2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance\\material.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance\\pixeltexture.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance\\texturedbox.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance\\texturetransform.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance\\texturetransform1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\appearance\\texturetransform2.wrl");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\bindable");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\bindable\\background.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\bindable\\fog.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\bindable\\viewpoints.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\bindable\\viewpoints1.wrl");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\common");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\common\\pointlight.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\common\\shape.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\common\\sound.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\common\\spotlight1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\common\\spotlight2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\common\\worldinfo.wrl");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\defuse");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\defuse\\defuse1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\defuse\\defuse2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\defuse\\defuse3.wrl");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\box.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\box1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\box2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\box3.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\cone.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\cone1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\cylinder.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\cylinder1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\elevationgrid.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\faceset1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\inline.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\lineset.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\lineset1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\pointset.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\pointset1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\sphere.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\sphere1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\sphere2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\geometry\\textures.wrl");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\anchor.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\anchor1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\anchor2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\anchor3.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\anchor4.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\billboard.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\billboard1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\billboard2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\lod.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\grouping\\switch.wrl");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\interpolator");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\interpolator\\coordinterpolator.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\interpolator\\interpolators.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\interpolator\\orientationinterpolator.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\interpolator\\positioninterpolator.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\interpolator\\scalarinterpolator.wrl");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\proto");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\proto\\prototest1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\proto\\prototest2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\proto\\prototest3.wrl");

	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\sensor");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\sensor\\planesensor1.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\sensor\\planesensor2.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\sensor\\planesensor3.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\sensor\\proximitysensor.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\sensor\\timesensor.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\sensor\\touchsensor.wrl");
	Doit("d:\\Great Hill Corporation\\VRaniML\\Sample Worlds\\sensor\\touchsensor1.wrl");
}

if (large)
{
	Doit("d:\\worlds\\books\\sourcebook\\software\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\03couch2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\03hamer1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\03trunk1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\03wlamp4.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\04frplc2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\05sword3.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\06door1.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\07mtlstr.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3name3d\\objects\\win\\08pilstr.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\autos\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\autos\\jetta\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\autos\\jetta\\jetta_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\autos\\lincoln\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\autos\\lincoln\\lincln_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\autos\\ls400\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\autos\\ls400\\ls400_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\damon\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\damon\\dam_m_2.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\damon\\damon_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\female\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\female\\ruth_2_bad.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\female\\ruth_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\frank\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\frank\\frankm_2_bad.wrl");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\frank\\frankm_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\male\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\male\\dmnbod_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\ray\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\avatars\\ray\\ray_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\products\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\products\\amp\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\products\\amp\\amptst_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\products\\bigscrn\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\products\\bigscrn\\bigtvm_2.wrl");

	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\products\\hp4\\");
	Doit("d:\\worlds\\books\\sourcebook\\software\\3rddim\\win\\products\\hp4\\hp4_2.wrl");
}
	vrTime stop = vrNow();
	double diff = stop - start;
	dc << "\n\nLines:      " << cnt << "\n"; 
	dc << "Elapsed:    " << diff << "\n"; 
	dc << "Speed:      " << cnt/diff << " lines per sec\n\n"; 
//	dc << cnt << ";" << diff << ";" << cnt/diff << "\n"; 

//vrDumpString ds;
//ds << cnt/diff << endl;
//fprintf(stderr, "%s", ds.string);

//PopNameSpace();

	return 1;
}

SFString lastName;
vrBaseNode *CreateNode(void)
{
	vrNode *node = new vrNode;
	node->SetClassName(lastName);
	return node;
}

PFNV FindCreateFunc(const SFString& nodeType)
{
	vrRuntimeClass *pClass = Lookup(nodeType);
	if (!pClass)
		return NULL;
		
	if (pClass->m_CreateFunc)
		return pClass->m_CreateFunc;
	
	lastName = nodeType;
	return CreateNode;
}

vrBaseNode *vrParser::CreateNewNode(const SFString& nodeName)
{
	PFNV CreateFunc = FindCreateFunc(nodeName);
	if (CreateFunc)
	{
		return (CreateFunc)();
	}
	return NULL;
}

