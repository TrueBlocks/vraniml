SFFloat vrScalarInterpolator::Evaluate(SFFloat t) const
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

	return vrInterpolate(m_KeyValue[i-1],
											m_KeyValue[i],
											m_Key[i-1],
											m_Key[i],
											t);
}
