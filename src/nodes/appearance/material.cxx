SFColor vrMaterial::GetAmbientColor(void) const
{
	return SFColor(m_DiffuseColor.x * m_AmbientIntensity, 
								m_DiffuseColor.y * m_AmbientIntensity, 
								m_DiffuseColor.z * m_AmbientIntensity);
}
