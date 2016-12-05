SFColor vrLight::GetAmbientColor(void) const
{ 
	return m_Color * m_AmbientIntensity;
}

SFColor vrLight::GetDiffuseColor(void) const
{
	return m_Color * m_Intensity;
}

SFColor vrLight::GetSpecularColor(void) const
{
	return m_Color * m_Intensity;
}

SFInt32 vrLight::lightIDs[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

SFInt32 vrLight::AllocateLightID(void) const
{
	for (int i=0;i<8;i++)
	{
		if (!lightIDs[i])
		{
			lightIDs[i]=1;
			return i;
		}
	}
	return -1;
}

void vrLight::FreeLightID(SFInt32 id)
{
	if (m_LightID!=-1)
	{
		ASSERT(id==m_LightID);
		lightIDs[id]=0;
	}
}

