#ifndef __EVENT_H3D
#define __EVENT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

/*----------------------------------------------------------------------
CLASS
	vrEvent

	Utility class to store event information as it is passed along
	routes.

DESCRIPTION
	<ul>
	Utility class to store information about events as they are passed
	along vrRoute's during an event cascade.
	</ul>

NOTES
	<ul>
	<li>Default constructor, copy constructor and equals operator are private
	so you may not make invalid copies of vrRoutes.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrEvent
{
public:
   //<doc>---------------------------------------------------------
	 //<dd> The destination node for this event.
	 //
	 // [default] NA
	 //
	 const vrNode   *m_Destination;

   //<doc>---------------------------------------------------------
	 //<dd> The ID of the field responding to this event.
	 //
	 // [default] NA
	 //
	 SFInt32         m_FieldID;

   //<doc>---------------------------------------------------------
	 //<dd> The value for the field responding to this event.
	 //<dd> Assumed that the void pointer points to the correct data type.
	 //
	 // [default] NA
	 //
   const void     *m_Value;

public:
   //<doc>---------------------------------------------------------
	 //<dd> Constructor.
	 //
	 // [in] dst: The destination node of this event.
	 // [in] fieldID: The field that should respond to this event.
	 // [in] data: Void pointer to data of the approriate type (as per the fieldID and the class type of dst).
	 //
	vrEvent(const vrNode *dst, SFInt32 fieldID, const void *data)
		{
			m_Destination = dst;
			m_FieldID     = fieldID;
			m_Value       = data;
		}
};

#endif