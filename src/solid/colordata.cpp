//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Decls.h"

SFColor ColorData::GetColor(void) const
{
	ASSERT(type & COLOR);
/*
	SFInt32 offset = GetOffset(type, COLOR);
	ASSERT(offset+sizeof(SFColor)+8<=(size_t)size);

	SFColor *color = (SFColor *)&vals[offset];
	return *color;
*/
	return color;
}

SFVec3f ColorData::GetNormal(void) const
{
	ASSERT(type & NORMAL);
/*
	SFInt32 offset = GetOffset(type, NORMAL);
	ASSERT(offset+sizeof(SFVec3f)+8<=(size_t)size);

	SFVec3f *normal = (SFVec3f *)&vals[offset];
	return *normal;
*/
	return normal;
}

SFVec2f ColorData::GetTexCoord(void) const
{
	ASSERT(type & TEXCOORD);
/*
	SFInt32 offset = GetOffset(type, TEXCOORD);
	ASSERT(offset+sizeof(SFVec2f)+8<=(size_t)size);

	SFVec2f *coord = (SFVec2f *)&vals[offset];
	return *coord;
*/
	return texcoord;
}

void ColorData::SetColor(const SFColor& c)
{
/*
	ASSERT(type & COLOR);
	SFInt32 offset = GetOffset(type, COLOR);
	ASSERT(offset+sizeof(SFColor)+8<=(size_t)size);

	SFColor *color = (SFColor *)&vals[offset];
	*color = c;
*/
	type |= COLOR;
	color = c;
}

void ColorData::SetNormal(const SFVec3f& n)
{
/*
	ASSERT(type & NORMAL);
	SFInt32 offset = GetOffset(type, NORMAL);
	ASSERT(offset+sizeof(SFVec3f)+8<=(size_t)size);

	SFVec3f *normal = (SFVec3f *)&vals[offset];
	*normal = n;
*/
	type |= NORMAL;
	normal = n;
}

void ColorData::SetTexCoord(const SFVec2f& t)
{
/*
	ASSERT(type & TEXCOORD);
	SFInt32 offset = GetOffset(type, TEXCOORD);
	ASSERT(offset+sizeof(SFVec2f)+8<=(size_t)size);

	SFVec2f *coord = (SFVec2f *)&vals[offset];
	*coord = t;
*/
	type |= TEXCOORD;
	texcoord = t;
}

/*
ColorData *AddComponent(ColorData *data, SFInt32 t)
{
	// may already have room
	if (data->type & t)
		return data;

	SFInt32 oldType = data->type;
	SFInt32 newType = (oldType | t);

	SFColor color    = ((oldType & COLOR)    ? data->GetColor()    : 0.0);
	SFVec3f normal = ((oldType & NORMAL)   ? data->GetNormal()   : 0.0);
	SFVec2f coord  = ((oldType & TEXCOORD) ? data->GetTexCoord() : 0.0);

	// release previous data
	free(data);
	data = NULL;
	
	// allocate new data
	SFInt32 size = GetDataSize(newType);
	data = (ColorData*)malloc(size);
	data->size = size;
	data->type = newType;

	// copy existing data over to new position
	if (oldType & COLOR)
	{
		data->SetColor(color);
	}
	
	if (oldType & NORMAL)
	{
		data->SetNormal(normal);
	}
	
	if (oldType & TEXCOORD)
	{
		data->SetTexCoord(coord);
	}

	return data;
}

SFInt32 GetOffset(SFInt32 type, SFInt32 which)
{
	switch (which)
	{
	case NORMAL:
		// If color is present, skip over it, else 0
		return ((type & COLOR) ? sizeof(SFColor) : 0);;
	case TEXCOORD:
		// If color or normal or both are present, skip over them, else 0
		return ((type & COLOR) ? 
								((type & NORMAL) ? 
									sizeof(SFColor) + sizeof(SFVec3f) : 
									sizeof(SFColor)) :
						 ((type & NORMAL) ? 
								sizeof(SFVec3f) : 
								0));
	}
	ASSERT(which == COLOR);
	return 0;
}
*/
