static SFVec3f Project(vrTraverser *t, const SFVec3f& pt)
{
	vrBrowser *b = t->m_Browser;
	SFVec3f vec = pt;

	if (b)
	{
		vrRect2D viewport = t->GetViewport();
		// a normalized point centered around the center of the window
		vec = SFVec3f((2.0*pt.x - viewport.Width()) / viewport.Width(), (viewport.Height() - 2.0*pt.y) / viewport.Height(), 0);;

		// Distance of vec from center of window
		float dist = Length(vec);

		// This projects the point onto the hemi-sphere
		vec.z = ((dist < 1.0) ? cos((M_PI/2.0) * dist) : 0.0);

		vec = Normalize(vec);
	}

	return vec;
}

void vrSphereSensor::PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t)
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
				m_Offset = m_Rotation;
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
				//SFVec3f lastPoint = m_TrackPoint;
				
				// unconstrianed tackpoint
				SetTrackPoint(Project(t, pt));
				SendEventOut(VRML_TRACKPOINT_CHANGED_STR, &m_TrackPoint);
				
				// calc rotation
				SFVec3f delta = m_FirstPoint - m_TrackPoint;
				SFVec3f axis = CrossProduct(m_FirstPoint, m_TrackPoint);
				SFFloat angle = vrDeg2Rad(90.0) * Length(delta);
				if (delta.x>=0.0)
					angle = -angle;
				m_Rotation = SFRotation(axis, angle);
				if (m_AutoOffset)
				{
					m_Rotation += m_Offset;
				}

				SetRotation(m_Rotation);
				SendEventOut(VRML_ROTATION_CHANGED_STR, &m_Rotation);
			}
		}
		break;
		
	default:
		// do nothing
		break;
	}
}
