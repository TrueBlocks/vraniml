vrPixelTexture::vrPixelTexture(SFInt32 width, SFInt32 height, SFInt32 nComponents, SFInt32 format) : vrNode()
{
	m_RepeatS     = TRUE;
	m_RepeatT     = TRUE;
	m_Width       = width;
	m_Height      = height;
	m_NComponents = nComponents;
	m_Format      = format;
	m_ColorBuffer = NULL;
	
	long size = width * height * nComponents;
	if (size)
	{
		m_ColorBuffer = (char *)malloc(size);
	}

	if (GetRuntimeClass()->Reference()==2)
	{
		//	AddExposedField(VRML_IMAGE_STR);
	}
}

void vrPixelTexture::AllocateSpace(void)
{
	if (m_ColorBuffer)
		free(m_ColorBuffer);
	m_ColorBuffer = NULL;

	long size = m_Width * m_Height * 4; //m_NComponents;
	if (size)
	{
		m_ColorBuffer = (char *)malloc(size);
		memset(m_ColorBuffer, 0, size);
	}
	m_nPixels = 0;
}

void vrPixelTexture::AddPixel(SFInt32 i)
{ 
//	SFInt32 nPixels = m_Width * m_Height * m_NComponents;
	if (!m_ColorBuffer)
		AllocateSpace();
	
	switch (m_NComponents)
	{
		case 1:
			{
				char *array = (char *)m_ColorBuffer; 
				array[m_nPixels++] = i;
			}
			break;
		case 3:
		case 4:
			{
				long *array = (long *)m_ColorBuffer; 
				array[m_nPixels++] = i;
			}
			break;
	}
#ifdef _DEBUG
	long size = m_Width * m_Height * m_NComponents;
	ASSERT(m_nPixels<=size);
#endif
}

void *vrPixelTexture::AddToArray(SFInt32 v, void *vArray, SFInt32 size)
{
//	long *newArray = (long *)m_ColorBuffer;
//	newArray[size] = v;
//	return newArray;
	return vArray;
}

