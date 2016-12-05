void vrSensor::Deactivate(void)
{
	m_IsActive = FALSE;
	SendEventOut(VRML_ISACTIVE_STR, &m_IsActive);
}

