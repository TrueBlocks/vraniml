#ifndef __DUMP_H3D
#define __DUMP_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

/*----------------------------------------------------------------------
CLASS
	vrDumpContext

	Utility class for dumping data to an output device.

DESCRIPTION
	<ul>
	The vrDumpContext class aids in writing data to an output
	device.  It is modeled after the CDumpContext from the MFC
	and is used in exactly the same way.
	</ul>

NOTES
	<ul>
	<li>Using the default constructor with a NULL argument will
	cause the vrDumpContext to write to standard output (stdout).</li>
	</ul>

EXAMPLE CODE
	<pre>
	// First create the output device and attach it to the vrDumpContext...
	FILE *file = fopen("file.txt", "w");
	ASSERT(file);
	vrDumpContext dc(file);

	// ... and then start writing
	dc << 1 << " is the loneliest number.\n";

	// Increase indent level
	dc.m_nIndents++;

	// Write indented text
	dc << dc.Indent() << "This is indented\n";

	// Close and Flush
	dc.Close();
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class UL_Interface vrDumpContext
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>Output device.
	// [default:] stdout
	//
	FILE*   m_File;

public:
  //<doc>------------------------------------------------------------
	// <dd>Current indentation level.
	// [default:] 0
	//
	SFInt32 m_nIndents;

  //<doc>------------------------------------------------------------
  // <dd>The character to use for indentation.
	// [default:] space
	//
	char    m_TabChar;

  //<doc>------------------------------------------------------------
	// <dd>Number of 'm_TabChar' characters to write at each indent.
	// [default:] 4
	//
	SFInt32 m_TabStop;

  //<doc>------------------------------------------------------------
  // <dd>Enable verbose output.
	// [default:] FALSE
	//
	SFBool  m_Verbose;

  //<doc>------------------------------------------------------------
	// <dd>Number of digits for display of floating point numbers
	// [default:] 0 implies use of standard C++ formatting for floats.
	//
	SFInt32 m_nDigits;

  //<doc>------------------------------------------------------------
	// <dd>Number of values to display per row (for multi valued fields).  Items are seperated by one m_TabChar character.
	// [default:] 4
	//
	SFInt32 m_PerRow;

  //<doc>------------------------------------------------------------
	// <dd>If TRUE then all output is suppressed
	// [default:] FALSE
	//
	SFBool m_Suppress;

public:

	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	// [in] file: a FILE handle to the file used as the output device. 
	//            May be NULL in which case stdout is used.
	//
	vrDumpContext (FILE* file = NULL);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual       ~vrDumpContext (void);

  //<doc>------------------------------------------------------------
	// <dd>Flush the output device.
	//
	virtual void   Flush         (void);

  //<doc>------------------------------------------------------------
	// <dd>Closes the output device.
	//
	virtual void   Close         (void);

  //<doc>------------------------------------------------------------
	// <dd>Returns a string of m_nIndents*m_TabStop characters of type m_TabChar.
	//
	virtual char  *Indent        (void) const;

  //<doc>------------------------------------------------------------
	// <dd>Set the file into which to write the dump.  Returns TRUE if the file was opened.
	//
	// [in] filename: the name of the file to open.
	//
	virtual SFBool SetFilename   (const SFString& filename);

  //<doc>------------------------------------------------------------
	// <dd>Write a string to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const SFString& val);

//  //<nodoc>------------------------------------------------------------
//	// <dd>Write a character string to the output device.
//	//
//	// [in] val: the value to write out.
//	//
//	vrDumpContext& operator<<    (char  *val);

  //<doc>------------------------------------------------------------
	// <dd>Write a single character to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (char   val);

  //<doc>------------------------------------------------------------
	// <dd>Write a short to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (short  val);

  //<doc>------------------------------------------------------------
	// <dd>Write an unsigned int to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (unsigned int val);

  //<doc>------------------------------------------------------------
	// <dd>Write a long (SFBool, SFInt32) to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (long   val);

  //<doc>------------------------------------------------------------
	// <dd>Write a float (SFFloat) to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (float  val);

  //<doc>------------------------------------------------------------
	// <dd>Write a double to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (double val);

  //<doc>------------------------------------------------------------
	// <dd>Write a int to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (int    val);

//  //<nodoc>------------------------------------------------------------
//	// <dd>Write a void pointer (in hex) to the output device.
//	//
//	// [in] val: the value to write out.
//	//
//	vrDumpContext& operator<<    (const void* val);

  //<doc>------------------------------------------------------------
	// <dd>Write an SFVec2f to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const SFVec2f& val);

  //<doc>------------------------------------------------------------
	// <dd>Write an SFVec3f to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const SFVec3f& val);

  //<doc>------------------------------------------------------------
	// <dd>Write an SFColor to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const SFColor& val);

  //<doc>------------------------------------------------------------
	// <dd>Write an SFRotation to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const SFRotation& val);

  //<doc>------------------------------------------------------------
	// <dd>Write an SFImage to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const SFImage& val);

  //<doc>------------------------------------------------------------
	// <dd>Write a vrMatrix to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const vrMatrix& val);

  //<doc>------------------------------------------------------------
	// <dd>Write a vrBoundingBox to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const vrBoundingBox& val);

  //<doc>------------------------------------------------------------
	// <dd>Write a vrPlane to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const vrPlane& val);

  //<doc>------------------------------------------------------------
	// <dd>Write a vrRay to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const vrRay& val);

  //<doc>------------------------------------------------------------
	// <dd>Write a vrRect2D to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const vrRect2D& val);

  //<doc>------------------------------------------------------------
	// <dd>Write a vrTime to the output device.
	//
	// [in] val: the value to write out.
	//
	vrDumpContext& operator<<    (const vrTime& val);


  //<nodoc>------------------------------------------------------------
	// <dd>Copy constructor (ASSERTS if used).
	//
	vrDumpContext (const vrDumpContext& src);
	
  //<nodoc>------------------------------------------------------------
	// <dd>Equals operator (ASSERTS if used).
	//
	void           operator=     (const vrDumpContext& src);

private:
	virtual void   OutputString  (const char *s);
};

#if defined(LIBUTIL) || defined(LIB3D)
#define endl "\n" // for convienience only
#endif

#if defined(LIBUTIL) || defined(LIB3D)

// Define a VRTRACE macro for use by the DLL only
#ifdef _DEBUG
extern UL_Interface vrDumpContext *traceContext;
inline void UL_Interface xTrace(char *fmt, ...)
{
	if (!traceContext)
		return;

	va_list args;
	va_start(args, fmt);
	char szBuffer[512];
	vsprintf(szBuffer, fmt, args);
	*traceContext << traceContext->Indent() << szBuffer;
	va_end(args);
}
#define VRTRACE ::xTrace

#else // ifdef _DEBUG

inline void UL_Interface xTrace(char *fmt, ...) { }
#undef VRTRACE
#define VRTRACE  1 ? (void)0 : ::xTrace

#endif // ifdef _DEBUG

#endif // ifdef LIBUTIL, LIB3D

/*----------------------------------------------------------------------
CLASS
	vrDumpString

	Utility class for dumping data to an output string.

DESCRIPTION
	<ul>
	The vrDumpString class aids in writing data to an output
	string.
	</ul>

NOTES
	<ul>
	</ul>

EXAMPLE CODE
	<pre>
	// Use just like a string or a dump context...
	vrDumpString ds;
	ds.string += "-->";
	ds << "This is test: " << 1 << endl;
	ds.string += "-->";
	ds << "This is test: " << 2 << endl;
	ds.string += "-->";
	ds << "This is test: " << 3 << endl;
	
	vrDumpContext dc;
	dc << ds.string;

	// OUTPUT:
	-->This is test 1
	-->This is test 2
	-->This is test 3
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class UL_Interface vrDumpString : public vrDumpContext
{
public:
  //<doc>------------------------------------------------------------
	// <dd>The string to accumulate user input.  Public for easy access.
	//
	// [default] nullString
	//
	SFString string;

  //<nodoc>------------------------------------------------------------
	// <dd>Override to eliminate the creation of an output file.
	//
	// [in] filename: Unused.
	//
	SFBool SetFilename(const SFString& filename)
		{
			m_File=NULL;
			return TRUE;
		}

  //<nodoc>------------------------------------------------------------
	// <dd>Override to accumulate the string.
	//
	// [in] s: the string to add to this dumpstring.
	//
	void OutputString(const char *s)
		{
			string += s;
			return;
		}
};

#endif