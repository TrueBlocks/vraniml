void vrMovieTexture::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_URL_STR)
		{
			SetUrl(*((MFString *)ev->m_Value));
			SendEventOut(VRML_URL_STR, &m_Url);
		}
	else if (ev->m_FieldID == VRML_SPEED_STR)
		{
			SetSpeed(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_SPEED_STR, &m_Speed);
		}
	// timeDep stuff
	else if (ev->m_FieldID == VRML_STARTTIME_STR)
		{
			SetStartTime(*((SFTime *)ev->m_Value));
			SendEventOut(VRML_STARTTIME_STR, &m_StartTime);
		}
	else if (ev->m_FieldID == VRML_STOPTIME_STR)
		{
			SetStopTime(*((SFTime *)ev->m_Value));
			SendEventOut(VRML_STOPTIME_STR, &m_StopTime);
		}
	else if (ev->m_FieldID == VRML_LOOP_STR)
		{
			SetLoop(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_LOOP_STR, &m_Loop);
		}
}
