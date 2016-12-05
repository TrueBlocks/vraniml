#include "stdafx.h"

#include "Textures.h"

//----------------------------------------------------------------------
//----------------------------------------------------------------------
IMPLEMENT_NODE(vrCheckedTexture, vrPixelTexture);

vrCheckedTexture::vrCheckedTexture(const SFColor& c1, const SFColor& c2) : 
	vrPixelTexture(32, 32, 4, GL_RGBA)
{
	SFInt32 *p = (SFInt32 *)m_ColorBuffer;
	ASSERT(p);

	for (int i=0; i < m_Width; i++)
	{
		for (int j=0; j < m_Height; j++)
		{
			if ((i ^ j) & 8)
			{
				*p = RGBA(c1);
			} else
			{
				*p = RGBA(c2);
			}
			p++;
		}
	}
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
IMPLEMENT_NODE(vrRampTexture, vrPixelTexture);

vrRampTexture::vrRampTexture(const SFColor& c1, const SFColor& c2) : 
	vrPixelTexture(128, 128, 4, GL_RGBA)
{
	SFInt32 *p = (SFInt32 *)m_ColorBuffer;
	ASSERT(p);

	vrColorInterpolator interp;
	interp.AddKey(0.0); interp.AddKeyValue(c1);
	interp.AddKey(0.33); interp.AddKeyValue((c1+c2)/2);
	interp.AddKey(0.5); interp.AddKeyValue(c2);
	interp.AddKey(0.75); interp.AddKeyValue(c1);
	interp.AddKey(1.0); interp.AddKeyValue(c2);

	for (int i=0; i < m_Width; i++)
	{
		SFFloat fraction = (SFFloat)i/(SFFloat)m_Width;
		SFColor color = interp.Evaluate(fraction);
		for (int j=0; j < m_Height; j++)
		{
			*p = RGBA(color);
			p++;
		}
	}
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
IMPLEMENT_NODE(vrCrossesTexture, vrPixelTexture);

vrCrossesTexture::vrCrossesTexture(const SFColor& c1, const SFColor& c2) : 
	vrPixelTexture(32, 32, 4, GL_RGBA)
{
	SFInt32 *p = (SFInt32 *)m_ColorBuffer;
	ASSERT(p);

	for (int i=0; i < m_Width; i++)
	{
		for (int j=0; j < m_Height; j++)
		{
			SFColor col = ((!(i%2) && !(j%2)) ? c1 : c2);
			*p = RGBA(col);
			p++;
		}
	}
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
IMPLEMENT_NODE(vrCircleTexture, vrPixelTexture);

vrCircleTexture::vrCircleTexture(const SFColor& c1, const SFColor& c2) : 
	vrPixelTexture(32, 32, 4, GL_RGBA)
{
	SFInt32 *p = (SFInt32 *)m_ColorBuffer;
	ASSERT(p);

	vrColorInterpolator interp;
	interp.AddKey(0.0); interp.AddKeyValue(c1);
	interp.AddKey(1.0); interp.AddKeyValue(c2);

	for (int i=0; i < m_Width; i++)
	{
		for (int j=0; j < m_Height; j++)
		{
			SFFloat wDist = fabs((SFFloat)i - (SFFloat)(m_Width>>1));
			SFFloat hDist = fabs((SFFloat)j - (SFFloat)(m_Height>>1));
			SFFloat fraction = sqrt(wDist*wDist + hDist*hDist) / 32.0;
			SFColor color = interp.Evaluate(fraction);
			*p = RGBA(color);
			p++;
		}
	}
}

