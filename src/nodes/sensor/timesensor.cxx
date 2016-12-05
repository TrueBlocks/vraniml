void vrTimeSensor::Deactivate(void)
{
	SendEvents(vrNow());
	vrSensor::Deactivate();
}

//-----------------------------------------------------------------------------
void vrTimeSensor::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_CYCLEINTERVAL_STR)
		{
			// An active TimeSensor ignores SetCycleInterval events
			if (IsActive())
				return;

			SFTime interval = *((SFTime *)ev->m_Value);
			if (interval >= 0.0)
			{
				SetCycleInterval(*((SFTime *)ev->m_Value));
				SendEventOut(VRML_CYCLEINTERVAL_STR, &m_CycleInterval);
			}
		}
	// time dep stuff
	else if (ev->m_FieldID == VRML_STARTTIME_STR)
		{
			// An active TimeSensor ignores StartTime events
			if (IsActive())
				return;

			SetStartTime(*((SFTime *)ev->m_Value));
			SendEventOut(VRML_STARTTIME_STR, &m_StartTime);
		}
	else if (ev->m_FieldID == VRML_STOPTIME_STR)
		{
			// An active TimeSensor ignores StopTime events if the new stop time is too early
			SFTime stop = *((SFTime *)ev->m_Value);
			if (IsActive() && stop <= m_StartTime)
				return;

			SetStopTime(stop);
			SendEventOut(VRML_STOPTIME_STR, &m_StopTime);

			if (IsActive() && (stop >= m_StartTime) && (stop < vrNow()))
			{
				SendEvents(vrNow());
				m_IsActive = FALSE;
				SendEventOut(VRML_ISACTIVE_STR, &m_IsActive);
				m_Enabled = FALSE;
				SendEventOut(VRML_ENABLED_STR, &m_Enabled);
			}
		}
	else if (ev->m_FieldID == VRML_LOOP_STR)
		{
			SetLoop(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_LOOP_STR, &m_Loop);
		}
	else
		{
			vrSensor::ReceiveEventIn(ev);
		}
}

//-----------------------------------------------------------------------------
//
// After Annotated VRML 2.0 Reference Manual page 320
//
void vrTimeSensor::SendEvents(double now)
{
	m_Time = now;
	SendEventOut(VRML_TIME_STR, &m_Time);

	// Make sure we never exceed one if we're not looping.
	if (!m_Loop && now >= m_StartTime + m_CycleInterval)
		m_Fraction = 1.0;
	else
	{
		SFTime f;
		f = fmod(now - m_StartTime, m_CycleInterval);
		if (f == 0.0 && now > m_StartTime)
		{
			m_Fraction = 1.0;
		} else
		{
			m_Fraction = (SFFloat)(f / m_CycleInterval);
		}
	}
	SendEventOut(VRML_FRACTION_CHANGED_STR, &m_Fraction);
}
