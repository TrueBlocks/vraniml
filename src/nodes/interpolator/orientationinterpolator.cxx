SFRotation vrOrientationInterpolator::Evaluate(SFFloat t) const
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

	// Do this cause something is wrong with just useing a SFRotation
	SFVec3f axisFrom = m_KeyValue[i-1];
	SFVec3f axisTo   = m_KeyValue[i];
	SFVec3f axis     = vrInterpolate(axisFrom, axisTo, 
																		m_Key[i-1], m_Key[i], t);

	SFFloat angleFrom = m_KeyValue[i-1].w;
	SFFloat angleTo   = m_KeyValue[i].w;
	SFFloat angle     = vrInterpolate(angleFrom, angleTo, 
																		m_Key[i-1], m_Key[i], t);

	return SFRotation(axis, angle);
}

