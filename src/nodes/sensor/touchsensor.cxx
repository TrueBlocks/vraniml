#include "Browser\Browser.h"
void vrTouchSensor::PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t)
{
	ASSERT(GetEnabled());

	SFBool val = TRUE;
	
	switch (mode)
	{
	case MOUSE_UP:
		{
			SFTime now = vrNow();
			SetTouchTime(now);
			SendEventOut(VRML_TOUCHTIME_STR, &now); 
			val = FALSE;
		}
		// drop through

	case MOUSE_DOWN:
		SetIsActive(val);
		SendEventOut(VRML_ISACTIVE_STR, &val); 
		break;

	case MOUSE_MOVE:
		{
			SetIsOver(val);
			SendEventOut(VRML_ISOVER_STR, &val); 
		}
		break;

	default:
		// do nothing
		break;
	}
}
