#ifndef __USERMESSAGE_H3D
#define __USERMESSAGE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

class LIBInterface vrUserMessage
{
public:
	vrUserMessage(SFInt32 id, SFInt32 w, SFInt32 l, const SFVec3f& p)
		{
			message_id = id; wParam = w; lParam = l; point = p;
		}
	SFInt32 message_id;
	SFInt32 wParam;
	SFInt32 lParam;
	SFVec3f point;
};

#endif