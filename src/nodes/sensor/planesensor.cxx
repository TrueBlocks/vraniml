SFFloat Aspect(const vrRect2D& rect)
{
	return (rect.Width() / rect.Height());
}

static SFVec3f Project(vrTraverser *t, const SFVec3f& pt)
{
	vrBrowser *b = t->m_Browser;
	SFVec3f vec = pt;

	if (b)
	{
		vrRect2D viewport = t->GetViewport();
		// a normalized point centered around the center of the window
		vec = SFVec3f((2.0*pt.x - viewport.Width()) / viewport.Width(), (viewport.Height() - 2.0*pt.y) / viewport.Height(), 0);
		SFFloat aspect = Aspect(viewport);
		vec *= 4;
		if (aspect>1.0)
		{
			vec.x *= aspect;
		} else
		{
			vec.y *= aspect;
		}
	}
	return vec;
}

void vrPlaneSensor::PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t)
{
	ASSERT(GetEnabled());

	switch (mode)
	{
	case MOUSE_UP:
		{
			SFBool val = FALSE;
			SetIsActive(val);
			SendEventOut(VRML_ISACTIVE_STR, &val); 
			if (m_AutoOffset)
			{
				m_Offset = m_Translation;
				SendEventOut(VRML_OFFSET_STR, &m_Offset); 
			}
		}
		break;

	case MOUSE_DOWN:
		{
			SFBool val = TRUE;
			SetIsActive(val);
			SendEventOut(VRML_ISACTIVE_STR, &val);
			m_FirstPoint = Project(t, pt);
		}
		break;

	case MOUSE_MOVE:
		{
			if (IsActive())
			{
				// unconstrianed tackpoint
				SetTrackPoint(Project(t, pt));
				SendEventOut(VRML_TRACKPOINT_CHANGED_STR, &m_TrackPoint);
				
				// calc translation
				m_Translation = m_TrackPoint - m_FirstPoint;
				if (m_AutoOffset)
				{
					m_Translation += m_Offset;
				}

				// now clamp as per max/min
				SFVec3f maxPos = GetMaxPosition();
				SFVec3f minPos = GetMinPosition();
				if (!IsDefault("maxPosition"))
				{
					if (minPos.x <= maxPos.x)
						m_Translation.x = MIN(maxPos.x, m_Translation.x);
					if (minPos.y <= maxPos.y)
						m_Translation.y = MIN(maxPos.y, m_Translation.y);
				}
				if (!IsDefault("minPosition"))
				{
					if (minPos.x <= maxPos.x)
						m_Translation.x = MAX(minPos.x, m_Translation.x);
					if (minPos.y <= maxPos.y)
						m_Translation.y = MAX(minPos.y, m_Translation.y);
				}
				ASSERT(m_Translation.z==0.0);
				
				SetTranslation(m_Translation);
				SendEventOut(VRML_TRANSLATION_CHANGED_STR, &m_Translation);
			}
		}
		break;
		
	default:
		// do nothing
		break;
	}
}
