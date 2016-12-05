// For readability only
#define HUE        hsv.x
#define SATURATION hsv.y
#define VALUE      hsv.z
#define RED        rgb.x
#define GREEN      rgb.y
#define BLUE       rgb.z
#define UNDEFINED  500.0

//
// After Computer Graphics Principles and Practices -- page 592
//
SFVec3f toHSV(const SFColor& rgb)
{
	SFFloat max = MAX(RED,MAX(GREEN,BLUE));
	SFFloat min = MIN(RED,MIN(GREEN,BLUE));
	ASSERT(max>=0 && max<=1.0);
	ASSERT(min>=0 && min<=1.0);

	SFFloat delta = max - min;
	
	SFVec3f hsv;

	// value
	VALUE = max;
	
	// saturation
	if (max != 0)
	{
		SATURATION = delta / max;
	} else
	{
		SATURATION = 0;
	}

	// now hue
	if (SATURATION == 0)
	{
		// saturation is zero, hue is UNDEFINED
		HUE = UNDEFINED;
	} else
	{
		if (RED == max)
			HUE = (GREEN - BLUE) / delta;
		else if (GREEN == max)
			HUE = 2 + (BLUE - RED) / delta;
		else //if (BLUE == max)
			HUE = 4 + (RED - GREEN) / delta;
		HUE *= 60.0;
		if (HUE < 0)
			HUE += 360;
	}
	
	return hsv;
}

//
// After Computer Graphics Principles and Practices -- page 592
//
SFColor toRGB(const SFVec3f& hsvIn)
{
	SFColor rgb, hsv = hsvIn;
	
	if (SATURATION == 0)
	{
		if (HUE == UNDEFINED)
		{
			RED = VALUE;
			GREEN = VALUE;
			BLUE = VALUE;
			return rgb;
		}
		// error (if s==0, then h=UNDEF
		ASSERT(0);
	} else
	{
		if (HUE == 360)
			HUE = 0;
		HUE /= 60;
		SFInt32 i = floor(HUE);
		SFFloat f = HUE - i;
		SFFloat p = VALUE * (1 - (SATURATION));
		SFFloat q = VALUE * (1 - (SATURATION*f));
		SFFloat t = VALUE * (1 - (SATURATION*(1-f)));

		switch (i)
		{
		case 0:
			rgb = SFColor(VALUE,t,p);
			break;
		case 1:
			rgb = SFColor(q,VALUE,p);
			break;
		case 2:
			rgb = SFColor(p,VALUE,t);
			break;
		case 3:
			rgb = SFColor(p,q,VALUE);
			break;
		case 4:
			rgb = SFColor(t,p,VALUE);
			break;
		case 5:
			rgb = SFColor(VALUE,p,q);
			break;
		default:
			{ ASSERT(0); }
		}
	}
	return rgb;
}

SFColor vrColorInterpolator::Evaluate(SFFloat t) const
{
	int nKeys = m_Key.GetCount();
	ASSERT(nKeys == m_KeyValue.GetCount());
	
	if (t < m_Key[0])
		return m_KeyValue[0];
		
	if (t > m_Key[nKeys-1])
		return m_KeyValue[nKeys-1];

	// should use binary search
	for (int i=0;i<nKeys;i++)
	{
		if (t == m_Key[i])
		{
			return m_KeyValue[i];
		}
		if (m_Key[i] > t)
			break;
	}
	ASSERT(i<nKeys);
	ASSERT(i>0);

	// Interpolate in hsv color space
	SFColor rgb1 = m_KeyValue[i-1];
	SFColor rgb2 = m_KeyValue[i];

	SFVec3f hsv1 = toHSV(rgb1);
	SFVec3f hsv2 = toHSV(rgb2);

	if (hsv1.x==UNDEFINED || hsv2.x==UNDEFINED)
	{
		// Some colors don't translate well so just use rgb to interpolate
		return vrInterpolate(rgb1, rgb2,
											m_Key[i-1],
											m_Key[i],
											t);
	}

	SFVec3f hsvRet = vrInterpolate(hsv1, hsv2,
										m_Key[i-1],
										m_Key[i],
										t);
	SFColor col = toRGB(hsvRet);
	col.a = 1.0;
	return col;
}

