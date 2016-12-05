#ifndef __TIME_H3D
#define __TIME_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include <sys/timeb.h>

/*----------------------------------------------------------------------
CLASS
	vrTime

	For doing time calculations.

DESCRIPTION
	<ul>
	The vrTime class manages the time.  This is used mostly
	by the vrBrowser class to initiate vrTimeSensor events.
	</ul>

NOTES
	<ul>
	</ul>

EXAMPLE CODE
	<pre>
	// This class allows calculations on time values:
	vrTime time1 = vrNow();

	// wait around a while....
	
	vrTime time2 = vrNow();

	ASSERT(time2 > time1); // comparison
	ASSERT((time2-time1) > 0.0); // subtraction, conversion to double
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class UL_Interface vrTime
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>Number of seconds since 12:00am January 1, 1970.
	// [default:] 0
	//
	long m_Seconds;

  //<doc>------------------------------------------------------------
  // <dd>Millionths of a second (only acurate to 1,000 of a second).
	// [default:] 0
	//
	long m_uSeconds;

public:

  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrTime(void)
		{
			m_Seconds  = 0;
			m_uSeconds = 0;
		}

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	vrTime(const vrTime& t)
		{
			m_Seconds  = t.m_Seconds;
			m_uSeconds = t.m_uSeconds;
		}

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] secs: Number of seconds since 1/1/1970.
	// [in] usecs: Number of milliseconds.
	//
	vrTime(long secs, long usecs)
		{
			m_Seconds  = secs;
			m_uSeconds = usecs;
		}

  //<nodoc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] secs: Number of seconds since 1/1/1970.
	//
//	vrTime(double secs)
//		{
//			m_Seconds  = secs;
//			m_uSeconds = 0;
//		}

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	vrTime& operator=(const vrTime& t)
		{
			m_Seconds  = t.m_Seconds; 
			m_uSeconds = t.m_uSeconds;
			return *this;
		}

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	vrTime& operator=(double t)
		{
			m_Seconds  = (long)t; // truncate
			m_uSeconds = (t - m_Seconds) / 1000000.0;
			return *this;
		}

  //<doc>------------------------------------------------------------
  // <dd>Adds two vrTime values together.
	//
	// [in] t1: The first time.
	// [in] t2: The second time.
	//
	friend vrTime UL_Interface operator+(const vrTime& t1, const vrTime& t2)
		{
			vrTime t;
			t.m_uSeconds = t1.m_uSeconds + t2.m_uSeconds;

			if(t.m_uSeconds >= 1000000)
			{
				t.m_uSeconds -= 1000000;
				t.m_Seconds = t1.m_Seconds + t2.m_Seconds + 1;
			} else
			{
				t.m_Seconds = t1.m_Seconds + t2.m_Seconds;
				if((t.m_Seconds >= 1) && ((t.m_uSeconds < 0)))
				{
					t.m_Seconds--;
					t.m_uSeconds += 1000000;
				}
			}
			return t;
		}

  //<doc>------------------------------------------------------------
  // <dd>Subtracts two vrTime values.
	//
	// [in] t1: The first time.
	// [in] t2: The second time.
	//
	friend vrTime UL_Interface operator-(const vrTime& t1, const vrTime& t2)
		{
			vrTime t;
			t.m_uSeconds = t1.m_uSeconds - t2.m_uSeconds;

			if(t.m_uSeconds < 0)
			{
				t.m_uSeconds += 1000000;
				t.m_Seconds = t1.m_Seconds - t2.m_Seconds - 1;
			} else
			{
				 t.m_Seconds = t1.m_Seconds - t2.m_Seconds;
			}
			return t;
		}

  //<doc>------------------------------------------------------------
  // <dd>Casts a vrTime value to a double.
	//
	operator double(void) const
		{
			return ((double)m_Seconds + ((double)m_uSeconds / 1000000.0));
		}

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if this object is earlier than the query time q.
	//
	// [in] q: The query time.
	//
	SFBool operator>(const vrTime& q) const
		{
			return ((m_Seconds > q.m_Seconds) ||
							((m_Seconds == q.m_Seconds) && (m_uSeconds > q.m_uSeconds)));
		}

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if this object is later than the query time q.
	//
	// [in] q: The query time.
	//
	SFBool operator<(const vrTime& q) const
		{
			return ((m_Seconds < q.m_Seconds) ||
							((m_Seconds == q.m_Seconds) && (m_uSeconds < q.m_uSeconds)));
		}

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if this object is earlier than or equal to the query time q.
	//
	// [in] q: The query time.
	//
	SFBool operator>=(const vrTime& q) const
		{
			return ((m_Seconds >= q.m_Seconds) ||
							((m_Seconds == q.m_Seconds) && (m_uSeconds >= q.m_uSeconds)));
		}

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if this object is later than or equal to the query time q.
	//
	// [in] q: The query time.
	//
	SFBool operator<=(const vrTime& q) const
		{
			return ((m_Seconds <= q.m_Seconds) ||
							((m_Seconds == q.m_Seconds) && (m_uSeconds <= q.m_uSeconds)));
		}

  //<doc>------------------------------------------------------------
  // <dd>Equality operator.
	//
	// [in] q: The query time.
	//
	SFBool operator==(const vrTime& q)
		{
			return ((m_Seconds == q.m_Seconds) && 
							(m_uSeconds == q.m_uSeconds));
		}

  //<doc>------------------------------------------------------------
  // <dd>Inequality operator.
	//
	// [in] q: The query time.
	//
	SFBool operator!=(const vrTime& q)
		{
			return !operator==(q);
		}

  //<doc>------------------------------------------------------------
  // <dd>Current time of day (in seconds since 12:00am January 1, 1970).
	//
	// <dd><B><I>Note:</B></I> Syntactic sugar for vrTime::Now is <B>vrNow</B> macro.
	static vrTime Now(void)
		{
			struct timeb _t;
			ftime(&_t);
			return vrTime(_t.time, _t.millitm * 1000);
		}
};

#define vrNow vrTime::Now
//#define SFTime vrTime
typedef double	  SFTime;

#endif