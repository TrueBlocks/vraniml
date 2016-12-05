#include "Kramer.h"
#include "ExternProtoUtils.h"

void Error(const SFString& str)
{
}

SFString newFilename(const SFString& filename)
{
	SFString newFile = filename;
	newFile.Replace(".wrl", ".wrl1");
	return newFile;
}

SFBool hasBadNewLines(const SFString& fileName)
{
	FILE *in = fopen((const char*)fileName, "rb");
	if (!in)
		return FALSE;
	int prev = -1;
	int val = getc(in);
	while (val != '\n' && val != EOF)
	{
		prev = val;
		val = getc(in);
	}
	fclose(in);
	return FALSE; //(prev != '\r');
}

SFString expandNewLines(const SFString& fileName)
{
	SFString newFile = fileName;
	if (hasBadNewLines(fileName))
	{
		newFile = newFilename(fileName);
		FILE *in = fopen((const char *)fileName, "r");
		FILE *out = fopen((const char *)newFile, "w");
		int val = getc(in);
		while (val != EOF)
		{
			if (val == '\n')
				putc('\r', out);
			putc(val, out);
			val = getc(in);
		}
		// write the EOF
		putc(val, out);
		fclose(out);
		fclose(in);
	}
	return newFile;
}

SFInt32 ScanToInterfaceStart(FILE *in)
{
	// scan for '['
	SFInt32 val = getc(in);
	while (val!=EOF && val!='[')
	{
		val = getc(in);
	}
	return val;
}

SFInt32 ScanToInterfaceEnd(FILE *in)
{
	// scan for ']'
	SFInt32 ins=1;
	SFInt32 val = getc(in);
	while (ins && val!=EOF)
	{
		if (val=='[')
			ins++;
		if (val==']')
			ins--;
		if (ins)
			val = getc(in);
	}
	return val;
}

SFInt32 ScanToBodyStart(FILE *in)
{
	SFInt32 val = getc(in);
	while (val != '{' && val!=EOF)
		val = getc(in);
	return val;
}

SFInt32 ScanToBodyEnd(FILE *in)
{
	// scan for '}'
	SFInt32 ins=1;
	SFInt32 val = getc(in);
	while (ins && val!=EOF)
	{
		if (val=='{')
			ins++;
		if (val=='}')
			ins--;
		if (ins)
			val = getc(in);
	}
	return val;
}

SFInt32 ScanToURLStart(FILE *in)
{
	SFInt32 val = getc(in);
	while (val != '[' && val != '\"' && val!=EOF)
		val = getc(in);
	return val;
}

SFInt32 ScanToURLEnd(FILE *in, SFInt32 which, MFString& urls)
{
	SFInt32 val = getc(in);

	SFInt32 endChar = which;
	if (which == '[')
	{
		endChar = ']';
		// skip to first string
		while (val != '\"' && val != EOF)
			val = getc(in);
		val = getc(in);
	}
	if (val == EOF)
		return val;

	SFString str;
	while (val != endChar && val != EOF)
	{
		if (which == '[' && val == '\"')
		{
			urls.AddValue(str);
			str = nullString;
			val = getc(in);
			// skip to next string
			while (val != '\"' && val != EOF)
			{
			  val = getc(in);
				if (val == endChar)
					return val;
			}
		} else
		{
  		str += val;
		}
		val = getc(in);
	}
	urls.AddValue(str);
	return val;
}

SFInt32 ScanForProtoByName(FILE *in, const SFString& protoName)
{
	SFInt32 fPos = 0;
	char buff[4096];
	while (fgets(buff, 4096, in))
	{
		SFString line = buff;
		SFInt32 find = line.Find("PROTO");
		if (find!=-1)
		{
			SFBool same = TRUE;
			line = line.Mid(find+6); // include space
			for (int i=0;i<protoName.Length();i++)
			{
				if (protoName[i]!=line[i])
				{
					same = FALSE;
					break;
				}
			}
			if (same)
			{
				// return to start of PROTO
				fseek(in, fPos+find, SEEK_SET);
				return fPos+find;
			}
		}
		fPos = ftell(in);
	}
	return 0;
}

SFBool GetProto(const SFString& fn, const SFString& protoName, SFString& protoText)
{
	protoText = "RESOLVED"; // new keyword RESOLVEDPROTO

  SFString f = fn;
	SFString local = vrCacheFile(f);
	if (local.Empty())
		return FALSE;
	SFString fileName = expandNewLines(local);
	FILE *in = fopen((const char *)fileName, "r+");
	if (!in)
		return FALSE;
	
	//SFInt32 fPos = ftell(in);
	SFInt32 protoStart = ScanForProtoByName(in, protoName);
	if (!protoStart)
	{ fclose(in); return FALSE; }
	
	SFInt32 val = ScanToInterfaceStart(in);
	if (val == EOF)
	{ fclose(in); return FALSE; }
	val = ScanToInterfaceEnd(in);
	if (val == EOF)
	{ fclose(in); return FALSE; }
	val = ScanToBodyStart(in);
	if (val == EOF)
	{ fclose(in); return FALSE; }
	val = ScanToBodyEnd(in);
	if (val == EOF)
	{ fclose(in); return FALSE; }
	SFInt32 protoEnd = ftell(in);

	fseek(in, protoStart, SEEK_SET);
	SFInt32 len = (protoEnd - protoStart);
	while (len)
	{
		SFInt32 val = fgetc(in);
		protoText += val;
		if (val == '\n')
			len--;
		len--;
	}
	fclose(in);
	return TRUE;
}

SFString GetResolvedProto(MFString& urls, const SFString& defName)
{
	SFString ret;
	for (int i=0;i<urls.GetCount();i++)
	{
		SFString url = urls[i];
		SFInt32 find = url.Find("#");
		SFString fileName;
		SFString protoName;
		if (find==-1)
		{
			fileName = url;
			protoName = defName;
		} else
		{
		  fileName = url.Left(find);
		  protoName = url.Mid(find+1);
		}
		if (protoName.Empty())
			protoName = defName;
		if (!fileName.Empty() && !protoName.Empty())
			if (GetProto(fileName, protoName, ret))
			{
				SFInt32 find = ret.Find("[");
				ASSERT(find!=-1);
				SFString beg = ret.Left(find+1);
				beg += "\n  field SFInt32 _?nFilenames ";
				char ss[10];
				sprintf(ss, "%d\n", urls.GetCount());
				beg += ss;
				SFString rest = ret.Mid(find+1);
				for (int i=0;i<urls.GetCount();i++)
				{
					beg += "  field SFString _?fileName";
					char ss[10];
					sprintf(ss, "_%d ", i);
					beg += ss;
					beg += ("\"" + urls[i] + "\"" + endl);
				}
				beg+=rest;
				return beg;
			}
	}
	return ret;
}

SFString resolveNextExtern(const SFString& filename, SFInt32 start)
{
	FILE *in = fopen((const char*)filename, "r+");
	assert(in);

	SFString str;
	fseek(in, start, SEEK_SET);
	// skip over EXTERNPROTO
	for (int i=0;i<11;i++)
		str += getc(in);
	assert(str=="EXTERNPROTO");
	
	SFInt32 startOfName = ftell(in)+1;
	
	SFInt32 val = ScanToInterfaceStart(in);
	if (val==EOF)
	{ fclose(in); return filename; }
	SFInt32 interfaceStart = ftell(in);

	SFInt32 len = (interfaceStart - startOfName);
	fseek(in, -len, SEEK_CUR);
	SFString protoName;
	for (i=0;i<len;i++)
		protoName += getc(in);
	protoName=protoName.Left(protoName.Length()-1);

	ASSERT(ftell(in)==interfaceStart);

	val = ScanToInterfaceEnd(in);
	if (val==EOF)
	{ fclose(in); return filename; }
	//SFInt32 interfaceEnd = ftell(in);

	// now search for location of EXTERNPROTO
	val = ScanToURLStart(in);
	if (val==EOF)
	{ fclose(in); return filename; }
	//SFInt32 urlStart = ftell(in);
	
	MFString urls;
	val = ScanToURLEnd(in, val, urls);
	if (val==EOF)
	{ fclose(in); return filename; }
	SFInt32 urlEnd = ftell(in);

	SFString newFile = newFilename(filename);
	FILE *out = fopen((const char*)newFile, "w");
	assert(out);
	fseek(out, 0, SEEK_SET);

	// write out leading stuff
	fseek(in, 0, SEEK_SET);
	len = (start - 0);
	while (len)
	{
		val = fgetc(in);
		fputc(val, out);
		if (val=='\n')
			len--;
		len--;
	}

//	fprintf(out, "\n#----------------\n");
//	fflush(out);
	
	// write out the EXTERNPROTO resolved
	SFString replace = GetResolvedProto(urls, protoName);
	if (replace!=nullString)
	{
		fprintf(out, "%s", (char *)replace);
	} else
	{
		fprintf(out, "Could not find EXTERN PROTOTYPE in:\n");
		for (int i=0;i<urls.GetCount();i++)
		{
			SFString url = urls[i];
			fprintf(out, "%s\n", (char *)url);
		}
	}
	fseek(in, urlEnd+1, SEEK_SET);

	// write out leading stuff
	val = fgetc(in);
	while (val != EOF)
	{
		fputc(val, out);
		val = fgetc(in);
	}

	fclose(out);
	fclose(in);

	return newFile;
}

SFBool hasExtern(const SFString& filename)
{
	FILE *in = fopen((const char*)filename, "r+");
	if (in)
	{
		fseek(in, 0, SEEK_SET);
		ASSERT(ftell(in)==0);
		SFInt32 fPos = 0;
		char s[4096];
		while (fgets(s, 4096, in))
		{
//ASSERT(ftell(in)>0);
			SFInt32 find = SFString(s).Find("EXTERNPROTO");
			if (find!=-1)
			{
				fclose(in);
				// Returns start of EXTERNPROTO line
				return fPos+find;
			}
			fPos = ftell(in);
		}
		fclose(in);
	}
	return FALSE;
}

SFString resolveExterns(SFString& filename)
{
	SFString tempFile = expandNewLines(filename);
	SFInt32 fPos = hasExtern(tempFile);
	while (fPos)
	{
		ASSERT(fPos>=0);
		SFString newFile = resolveNextExtern(tempFile, fPos);
		if (tempFile != filename)
		{
			SFString cmd = "erase " + tempFile;
			system((char *)cmd);
		}
		tempFile = newFile;
		fPos = hasExtern(tempFile);
	}
	return tempFile;
}
