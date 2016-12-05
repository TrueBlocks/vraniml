//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "..\Utility.h"

#include "Dump.h"

#if defined(LIBUTIL)
#ifdef _DEBUG
// dump context for VRTRACE macro -- only used in _DEBUG in the DLL build
vrDumpContext *traceContext=NULL;
#endif
#endif

static char    indents[128];
static char    dumpBuffer[1024];

vrDumpContext::vrDumpContext(FILE* file)
{
	m_File     = file;
	m_nIndents = 0;
	m_TabStop  = 4;
	m_TabChar  = ' ';
	m_Verbose  = FALSE;
	m_nDigits  = 0;
	m_PerRow   = 4;
	m_Suppress = FALSE;
}

vrDumpContext::~vrDumpContext()
{
	Close();
}

vrDumpContext::vrDumpContext(const vrDumpContext& dc)
{
	// Can't do it
	ASSERT(0);
}

void vrDumpContext::operator=(const vrDumpContext& dc)
{
	// Can't do it
	ASSERT(0);
}

char *vrDumpContext::Indent(void) const
{
	int n=0;
	for (int i=0;i<m_nIndents;i++)
	{
		for (int j=0;j<m_TabStop;j++)
		{
			indents[n] = m_TabChar;
			n = MIN(127, ++n);
		}
	}

	indents[n] = '\0';
	return indents;
}

void vrDumpContext::Close(void)
{
	Flush();
	
	if (m_File && 
				m_File != stdout && 
				m_File != stderr)
	{
		fclose(m_File);
	}
	m_File=NULL;
}

vrDumpContext& vrDumpContext::operator<<(const SFString& val)
{
	if (!val.Empty())
		OutputString((const char *)SFString(val));
	
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(char c)
{
	sprintf(dumpBuffer, "%d", (int)c);
	OutputString(dumpBuffer);

	return *this;
}

vrDumpContext& vrDumpContext::operator<<(short s)
{
	sprintf(dumpBuffer, "%u", (unsigned int)s);
	OutputString(dumpBuffer);

	return *this;
}

vrDumpContext& vrDumpContext::operator<<(unsigned int u)
{
	sprintf(dumpBuffer, "0x%X", u);
	OutputString(dumpBuffer);

	return *this;
}

vrDumpContext& vrDumpContext::operator<<(long l)
{
	sprintf(dumpBuffer, "% 5ld", l);
	OutputString(dumpBuffer);

	return *this;
}

vrDumpContext& vrDumpContext::operator<<(int n)
{
	sprintf(dumpBuffer, "% 5d", n);
	OutputString(dumpBuffer);

	return *this;
}

char *Digits(int digits)
{
	static char fmt[40];
	if (digits)
	{
	  sprintf(fmt, "%%%d.%df", digits, digits);
	} else
	{
	  sprintf(fmt, "%%g");
	}
	return fmt;
}

vrDumpContext& vrDumpContext::operator<<(float f)
{
	sprintf(dumpBuffer, Digits(m_nDigits), f);
	OutputString(dumpBuffer);
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(double d)
{
	sprintf(dumpBuffer, Digits(m_nDigits), d);
	OutputString(dumpBuffer);
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const SFVec2f& vec)
{ 
	*this << vec.x << " " << vec.y;
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const SFVec3f& vec)
{ 
	*this << vec.x << " " << vec.y << " " << vec.z;
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const SFColor& col)
{ 
	*this << col.x << " " << col.y << " " << col.z;
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const SFRotation& vec)
{ 
	*this << vec.x << " " << vec.y << " " << vec.z << " " << vec.w;
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const SFImage& img)
{ 
	long w = img.m_Width;
	long h = img.m_Height;

	*this << Indent() << w << " " << h << " " << img.m_nComponents << endl;

	const unsigned char *p = (const unsigned char *)img.m_ColorData;
	if (img.m_ColorData)
	{	
		m_nIndents++;
		for (int i=0;i<w;i++)
		{
			*this << Indent();
			for (int j=0;j<h;j++)
			{
				*this << " 0x";
				for (int i=0;i<img.m_nComponents;i++)
				{
					sprintf(dumpBuffer, "%02X", p[i]);
					*this << dumpBuffer; 
				}
				p += img.m_nComponents;
			}
			*this << "\n";
		}
		m_nIndents--;
	}

	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const vrBoundingBox& val)
{
	sprintf(dumpBuffer, "%f %f %f --> %f %f %f", 
						val.GetMin().x, val.GetMin().y, val.GetMin().z,
						val.GetMax().x, val.GetMax().y, val.GetMax().z);
	OutputString(dumpBuffer);
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const vrPlane& val)
{
	sprintf(dumpBuffer, "%f %f %f %f", 
						val.GetNormal().x,
						val.GetNormal().y,
						val.GetNormal().z,
						val.GetD());
	OutputString(dumpBuffer);
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const vrRay& val)
{
	sprintf(dumpBuffer, "%f %f %f --> %f %f %f", 
						val.m_Loc.x, val.m_Loc.y, val.m_Loc.z,
						val.m_Dir.x, val.m_Dir.y, val.m_Dir.z);
	OutputString(dumpBuffer);
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const vrRect2D& val)
{
	sprintf(dumpBuffer, "%f %f %f %f", 
						val.left, val.top, val.right, val.bottom);
	OutputString(dumpBuffer);
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const vrTime& val)
{
	*this << (float)(double)val;
	return *this;
}

vrDumpContext& vrDumpContext::operator<<(const vrMatrix& mat)
{ 
	*this << "Matrix:\n";
	m_nIndents++;
	for (int i=0;i<4;i++)
	{
		SFRotation vec(mat.vals[i][0], mat.vals[i][1], mat.vals[i][2], mat.vals[i][3]);
		*this << Indent() << "[ " << vec << " ]\n";
	}
	m_nIndents--;
	*this << "\n";
	
	return *this;
}

void vrDumpContext::OutputString(const char *s)
{
	if (m_Suppress)
		return;
		
	if (!m_File)
		m_File = stdout;  // use stdout by default

	if (m_File)
		fprintf(m_File, "%s", s);

	return;
}

void vrDumpContext::Flush()
{
	if (m_File)
		fflush(m_File);
}

SFBool vrDumpContext::SetFilename(const SFString& filename)
{
	m_File = fopen(filename, "w");
	return (SFBool)m_File;
}
