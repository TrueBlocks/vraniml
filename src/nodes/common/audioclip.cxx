#include "Browser\Browser.h"

void vrAudioClip::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_PITCH_STR)
		{
			// Pitch change is ignored for active audio clips
			if (!IsActive())
			{
				SetPitch(*((SFFloat *)ev->m_Value));
				SendEventOut(VRML_PITCH_STR, &m_Pitch);
			}
		}
	else if (ev->m_FieldID == VRML_URL_STR)
		{
			SetUrl(*((MFString *)ev->m_Value));
			ClearData();
			SendEventOut(VRML_URL_STR, &m_Url);
		}
	else if (ev->m_FieldID == VRML_DESCRIPTION_STR)
		{
			SetDescription(*((SFString *)ev->m_Value));
			SendEventOut(VRML_DESCRIPTION_STR, &m_Description);
		}
	// SFTime dep stuff follows
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
			// An active TimeSensor ignores StopTime events
			if (IsActive())
				return;

			SFTime stop = *((SFTime *)ev->m_Value);
			if (stop >= m_StartTime)
			{
				SetStopTime(*((SFTime*)ev->m_Value));
				SendEventOut(VRML_STOPTIME_STR, &m_StopTime);
				
				if (m_StopTime < vrNow())
				{
					m_IsActive = FALSE;
					SendEventOut(VRML_ISACTIVE_STR, &m_IsActive);
				}
			}
		}
	else if (ev->m_FieldID == VRML_LOOP_STR)
		{
			SetLoop(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_LOOP_STR, &m_Loop);
		}
}

void vrAudioClip::ClearData(void)
{
//	if (m_Buffer)
//	{
//		m_Buffer->Release();
//		m_Buffer=NULL;
//	}

//	if (m_Buffer3D)
//	{
//		m_Buffer3D->Release();
//		m_Buffer3D=NULL;
//	}

	 m_Duration = -1;
}


void vrAudioClip::LoadData(IDirectSound *lpDS)
{
	// read the .wav or .midi (type I) file
	// send a Duration changed event

//	ClearData();
	
//	SFInt32 n = 0;
//	while (n < GetNUrls() && !m_Buffer )
//	{
//		char *filename = GetUrl(n++);
//		SFString local = vrCacheFile(filename, 1);
//		if (!local.Empty())
//		{
//			m_Buffer = LoadWave(lpDS, local);
//		}
//	}

//	if (m_Buffer)
//	{
//		m_Buffer->QueryInterface(IID_IDirectSound3DBuffer,(void**)&m_Buffer3D);
//	}

	m_Duration = 1;
} 
