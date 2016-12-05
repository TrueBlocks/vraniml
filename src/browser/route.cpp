//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Route.h"
#include "Nodes\Node.h"

// static to keep track of the number of routes.
// Note: This fails if we create 4 GB routes (which will never-ever happen)
SFInt32 vrRoute::m_nRoutes = 0;

vrRoute::vrRoute(SFNode src, SFInt32 srcFieldID, SFNode dst, SFInt32 dstFieldID, int internal) 
{
	m_Source      = src;
	m_Destination = dst;
	m_SrcFieldID  = srcFieldID;
	m_DstFieldID  = dstFieldID;

	m_Internal    = internal;
	m_RouteID     = m_nRoutes++;
}

vrRoute::~vrRoute(void)
{
	if (m_Source) 
		m_Source->RemoveRoute(this);
}

SFString vrRoute::GetFieldName(SFInt32 which) const
{
	if (which==0)
	{
		ASSERT(m_Source);
		return m_Source->GetFieldName(m_SrcFieldID);
	}
	ASSERT(which==1);
	ASSERT(m_Destination);
	return m_Destination->GetFieldName(m_DstFieldID);
}

SFInt32 vrRoute::GetFieldType(SFInt32 which) const
{
	if (which==0)
	{
		ASSERT(m_Source);
		return m_Source->GetFieldType(m_SrcFieldID);
	}
	ASSERT(which==1);
	ASSERT(m_Destination);
	return m_Destination->GetFieldType(m_DstFieldID);
}

SFString vrRoute::GetNodeName(SFInt32 which) const
{
	if (which==0)
	{
		ASSERT(m_Source && !m_Source->GetName().Empty());
		return m_Source->GetName();
	}
	ASSERT(which==1);
	ASSERT(m_Destination && !m_Destination->GetName().Empty());
	return m_Destination->GetName();
}

SFBool vrRoute::IsValid(void) const
{
	if (m_Source && 
			m_Destination && 
			m_SrcFieldID != 0 && 
			m_DstFieldID != 0)
	{
 		SFInt32 srcFieldType = GetFieldType(0);
		SFInt32 dstFieldType = GetFieldType(1);

		// special cases to be a little lienient
		if (srcFieldType == SFFLOAT && dstFieldType == SFTIME)
			return TRUE;
		if (srcFieldType == SFTIME && dstFieldType == SFFLOAT)
			return TRUE;
		if (srcFieldType == SFBOOL && dstFieldType == SFINT32)
			return TRUE;
		if (srcFieldType == SFINT32 && dstFieldType == SFBOOL)
			return TRUE;
		
 		return (GetFieldType(0) == GetFieldType(1));
	}
	return FALSE;
}

