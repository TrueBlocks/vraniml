//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Windows.h"

#include "ActionTraverser.h"
#include "Browser\Browser.h"
#include "Nodes\AllNodes.h"

IMPLEMENT_NODE(vrActionTraverser, vrTraverser);

// This support class is used to activate and de-activate sensors
class SensorActivateData
{
	SensorActivateData();
public:
	SensorActivateData(SFBool o, vrTraverser *t, vrGroupingNode *p, SFBool mode, const SFVec3f& pp)
		{ onOff = o; traverser = t; parent = p; mouseMode = mode; pt = pp;}
	SFBool onOff;
	SFInt32 mouseMode;
	vrTraverser *traverser;
	vrGroupingNode *parent;
	SFVec3f pt;
};

vrAnchor *anchor=NULL;
SFBool ActivateSensor(SFNode node, void *data)
{
	SensorActivateData *ad = (SensorActivateData *)data;
	vrGroupingNode *parent = ad->parent;
	vrBrowser *browser = ad->traverser->m_Browser;
	SFInt32 mouseMode = ad->mouseMode;
	SFVec3f pt = ad->pt;

	if (!parent)
	{
		if (node->IsKindOf(GETRUNTIME_CLASS(vrPointingDeviceSensor)) || 
					node->IsKindOf(GETRUNTIME_CLASS(vrAnchor)))
		{
			SendMessage((HWND)ad->traverser->m_hWnd, VRANIML_SENSOR, NULL, 0);
		}
		if (node->IsKindOf(GETRUNTIME_CLASS(vrTouchSensor)))
		{
			vrTouchSensor *sensor = (vrTouchSensor *)node;
			if (sensor->IsOver())
			{
				SFBool isOver = FALSE;
				sensor->SetIsOver(isOver);
				node->SendEventOut(VRML_ISOVER_STR, &isOver); 
			}
		}
		return TRUE;
	} else
	{
		if (node->IsKindOf(GETRUNTIME_CLASS(vrPointingDeviceSensor)) || 
					node->IsKindOf(GETRUNTIME_CLASS(vrAnchor)))
		{
			SendMessage((HWND)ad->traverser->m_hWnd, VRANIML_SENSOR, (WPARAM)node, 0);
		}
	}
	
	if (node->IsKindOf(GETRUNTIME_CLASS(vrPointingDeviceSensor)) && parent->IsParentOf(node))
	{
		vrPointingDeviceSensor *sensor = (vrPointingDeviceSensor *)node;
		if (sensor->GetEnabled())
			sensor->PointerEvent(mouseMode, pt, ad->traverser);
	} else if (mouseMode == MOUSE_MOVE)
	{
		// If it's a touch sensor that is not Over then let 'em know
		if (node->IsKindOf(GETRUNTIME_CLASS(vrTouchSensor)))
		{
			vrTouchSensor *sensor = (vrTouchSensor *)node;
			SFBool isOver = FALSE;
			sensor->SetIsOver(isOver);
			node->SendEventOut(VRML_ISOVER_STR, &isOver); 
		}
	}
	
	if (mouseMode == MOUSE_UP)
	{
		if (node->IsKindOf(GETRUNTIME_CLASS(vrAnchor)) && node == parent)
		{
			// Other sensors lower in the Anchor should take precedence
			SFNode s = node->FindByType(GETRUNTIME_CLASS(vrTouchSensor));
			// If no lower sensor or the anchor is not the direct parent of the sensor
			if (!s || !parent->IsParentOf(s))
			{
				anchor = (vrAnchor*)node;
				browser->SetSelection(NULL);
			}
		} else if (node->IsKindOf(GETRUNTIME_CLASS(vrPointingDeviceSensor)))
		{
			vrPointingDeviceSensor *sensor = (vrPointingDeviceSensor *)node;
			if (sensor->IsActive())
				sensor->PointerEvent(mouseMode, pt, ad->traverser);
		}
	}
	return TRUE;
}

void vrActionTraverser::PreTraverse()
{
	if (anchor)
	{
		// Because the load will delete all children of the browser
		// we must insure that this anchor does not get deleted when
		// the anchor is loaded, so reference it and delete it ourselves
		// if necassary
		vrAnchor *a = anchor;
		anchor = NULL;
		a->Reference();
		a->PointerEvent(0,0.0,this);
		if (a->Dereference())
			delete a;
	}
	anchor = NULL;
}

void vrActionTraverser::PostTraverse()
{
}

void vrActionTraverser::Pick(const vrBrowser *browser)
{
}

#include "RenderTraverser.h"
void vrActionTraverser::Traverse(const vrBrowser *node)
{
	// assume there are no sensors and then find them as the 
	// scene graph is traversed.  Since the only time any mouse
	// messages will get through is after an image is on the
	// screen this should work OK.
	hasSensor = FALSE;
	TraverseChildren(node);
}

SFBool vrActionTraverser::ProcessUserMessage(const vrUserMessage& msg)
{
	// If there are no sensors then dont bother handling any mouse messages
	if (!hasSensor) return FALSE;
	
	switch (msg.message_id)
	{
	case WM_MOUSEMOVE:
		{
			vrGroupingNode *captured = m_Browser->GetSelection();
			vrGroupingNode *sel = NULL;
			if (captured)
			{
				sel = captured;
			} else
			{
				sel = m_Browser->PickScene(msg.point);
			}
			if (sel)
			{
				ASSERT(sel && sel->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)));
				SensorActivateData ad(TRUE, this, sel, MOUSE_MOVE, msg.point);
				sel->ForEvery(ActivateSensor, &ad);
				m_Browser->SetSelection(captured);
				return TRUE;
			}
			
			// nothing is over
			SensorActivateData ad(TRUE, this, NULL, MOUSE_MOVE, msg.point);
			m_Browser->ForEvery(ActivateSensor, &ad);

			return FALSE;
		}
		break;
	case WM_LBUTTONDOWN:
		{
			vrGroupingNode *sel = m_Browser->PickScene(msg.point);
			if (sel)
			{
				SetCapture((HWND)m_hWnd);
				ASSERT(sel && sel->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)));
				SensorActivateData ad(TRUE, this, sel, MOUSE_DOWN, msg.point);
				sel->ForEvery(ActivateSensor, &ad);
				return TRUE;
			}
			
			// nothing is picked
			return FALSE;
		}
		break;
	case WM_LBUTTONUP:
		{
			// Every pointing device sensor becomes inactive when mouse comes up
			vrGroupingNode *sel = m_Browser;
			if (m_Browser->GetSelection())
			{
				sel = m_Browser->GetSelection();
				m_Browser->SetSelection(NULL);
			}
			SensorActivateData ad(FALSE, this, sel, MOUSE_UP, msg.point);
			m_Browser->ForEvery(ActivateSensor, &ad);
			ReleaseCapture();
			// need to allow for release capture
			return FALSE;
		}
		break;
	}

	return FALSE;
}

vrActionTraverser::vrActionTraverser(vrBrowser *b, void *h) : vrTraverser(b, h)
{
	hasSensor = FALSE;
}

// Time Dependant nodes
void vrActionTraverser::Traverse(const vrMovieTexture *node)
{
	// no children
}

void vrActionTraverser::Traverse(const vrAudioClip *node)
{
	vrAudioClip *ac = (vrAudioClip *)node;
	
	if (ac->GetDuration() <= 0)
	{
		 ac->LoadData(NULL);
	}
	
	SFTime now = vrNow();
	
	vrEvent event(0,0,0);
	
	if (ac->IsActive())
	{
		if (ac->GetLoop())
		{ 
			//should we have a test to tell the GLTraverser that it is time to play from the begining?
			//we hope to be able to querry the hardware to see if the buffer is being played. if not
			//then we must add our own variable
		} else
		{  //not looping
				if (
				    ((ac->GetStopTime() > ac->GetStartTime()) && (now >= ac->GetStopTime())) ||
						(now >= (ac->GetStartTime() + (ac->GetDuration() / ac->GetPitch())))
						)
				{
					ac->SetIsActive(FALSE);
					SFBool isActive = ac->IsActive();
					ac->SendEventOut(VRML_ISACTIVE_STR, &isActive);
				}
		}
	} else
	{
		if (now >= ac->GetStartTime())
		{
 			SFBool a =  ac->GetLoop() && (ac->GetStartTime() >= ac->GetStopTime());
			SFBool b =  ac->GetLoop() && (ac->GetStopTime() > ac->GetStartTime()) && (ac->GetStopTime() >= now);
			SFBool c = !ac->GetLoop() && 
										(now >= ac->GetStartTime() && ac->GetStartTime() != 0) && 
										(now < ac->GetStartTime() + ac->GetDuration());

// 			SFBool a =  ac->GetLoop() && (ac->GetStartTime() >= ac->GetStopTime());
//			SFBool b =  ac->GetLoop() && (ac->GetStopTime() > ac->GetStartTime()) && (ac->GetStopTime() >= now);
//			SFBool c = !ac->GetLoop() && (now>=ac->GetStartTime()) && (now<ac->GetStopTime());
			if ( a || b || c)
			{
				// should these values be at m_StartTime
				ac->SetIsActive(TRUE);
				SFBool isActive = ac->IsActive();
				ac->SendEventOut(VRML_ISACTIVE_STR, &isActive);
			}
		}
	}
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrSound *node)
{
	if (node->GetSource())
		Traverse(node->GetSource());
}

//----------------------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrTimeSensor *node)
{
	// If the sensor is disabled do nothing
	if (!node->GetEnabled())
		return;
		
	vrTimeSensor *ts = (vrTimeSensor *)node;
	
	SFTime now = vrNow();
	
	vrEvent event(0,0,0);
	
	if (ts->IsActive())
	{
		// Timer is active, see if we turn off....
		if (ts->GetStopTime() > ts->GetStartTime() && now >= ts->GetStopTime())
		{
			// ...Turn off send remaining message first
			ts->SendEvents(now);
			SFBool enabled = FALSE;
			event = vrEvent(node, VRML_ENABLED_STR, &enabled);
			ts->ReceiveEventIn(&event);
		} else
		{
			// Check for cycle
			SFFloat lastFraction = ts->GetFraction();
			ts->SendEvents(now);
			SFFloat newFraction = ts->GetFraction();
			
			if (lastFraction > newFraction || newFraction == 1.0)
			{
				// This is the completion of a cycle
				if (ts->GetLoop())
				{
					ts->SetCycleTime(now);
					SFTime time = ts->GetCycleTime();
					ts->SendEventOut(VRML_CYCLETIME_STR, &time);
					// If there is a jump in the time this may be it.
					//if (newFraction == 1.0)
					//{
					ts->SetFraction(0.0);
					SFFloat fraction = ts->GetFraction();
					ts->SendEventOut(VRML_FRACTION_CHANGED_STR, &fraction);
					//}
				} else
				{
					// deactivate, but don't disable
					ts->SetIsActive(FALSE);
					SFBool isActive = ts->IsActive();
					ts->SendEventOut(VRML_ISACTIVE_STR, &isActive);
				}
			}
		} 
	} else
	{
		// Timer is inactive, check for looping
		if (now >= ts->GetStartTime())
		{
 			SFBool a =  ts->GetLoop() && (ts->GetStartTime() >= ts->GetStopTime());
			SFBool b =  ts->GetLoop() && (ts->GetStopTime() > ts->GetStartTime()) && (ts->GetStopTime() >= now);
			SFBool c = !ts->GetLoop() && 
										(now >= ts->GetStartTime() && ts->GetStartTime() != 0) && 
										(now < ts->GetStartTime() + ts->GetCycleInterval() );
			// || now <= (ts->GetStartTime() + ts->GetCycleInterval())));
			if ( a || b || c)
			{
				// should these values be at m_StartTime
				ts->SetIsActive(TRUE);
				SFBool isActive = ts->IsActive();
				ts->SendEventOut(VRML_ISACTIVE_STR, &isActive);

				ts->SendEvents(now);

				ts->SetCycleTime(now);
				SFTime time = ts->GetCycleTime();
				ts->SendEventOut(VRML_CYCLETIME_STR, &time);
			}
		}
	}
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrScript *node)
{
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrGroupingNode *node)
{
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrAnchor *node)
{
	hasSensor = TRUE;
	
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrBillboard *node)
{
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrCollision *node)
{
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrGroup *node)
{
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrTransform *node)
{
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrInline *node)
{
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrViewpoint *node)
{
	SFInt32 pending = node->IsBound();
	if (pending && pending != TRUE)
	{
		ASSERT(pending == PENDING_BIND || pending == PENDING_UNBIND);
		m_Browser->Bind((vrViewpoint*)node, ((pending == PENDING_BIND) ? TRUE : FALSE));
	}
	
//	if (node->IsBound())
//		((vrViewpoint*)node)->m_ParentTransform = Invert(GetTotalTransformation());
}

void vrActionTraverser::Traverse(const vrLOD *node)
{
	// Actions should effects all children of LOD's even inactive ones
	for (int i=0;i<node->GetNLevels();i++)
	{
		node->GetLevel(i)->Traverse(this);
	}

	vrViewpoint *vp = m_Browser->GetViewpoint();
	if (vp)
	{
		SFVec3f userLoc = vp->GetPosition();
		vrMatrix mat = GetTotalTransformation();
		//SFVec3f trans(mat.vals[3][0], mat.vals[3][1], mat.vals[3][2]);

		SFVec3f center = node->GetCenter(); // + trans;
		center = mat * center;
		SFVec3f diff = center - userLoc;
		SFFloat dist = Length(diff);
		// Need to set the active level based on distance as specified
		// in the range field
		SFFloat rangeStart = -FLT_MAX;
		SFInt32 index = -1;
		for (int i=0;i<node->GetNRanges();i++)
		{
 			SFFloat rangeEnd = node->GetRange(i);
			if (dist >= rangeStart && dist < rangeEnd)
			{
				index = MIN((SFInt32)i, node->GetNLevels());
				((vrLOD *)node)->SetActiveLevel(index);
				if (index!=1)
				{
					printf("");
				}

				break;
			}
			rangeStart = rangeEnd;
		}
		if (index==-1)
		{
			((vrLOD *)node)->SetActiveLevel(node->GetNLevels()-1);
		}
	}
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrSwitch *node)
{
	// Actions should effects all children of Switch's even inactive ones
	for (int i=0;i<node->GetNChoices();i++)
	{
		node->GetChoice(i)->Traverse(this);
	}
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrSensor *node)
{
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrProximitySensor *node)
{
	vrEvent event(0,0,0);
	vrProximitySensor *ps = (vrProximitySensor *)node;
	
	if (ps->GetEnabled())
	{
		vrViewpoint *vp = m_Browser->GetViewpoint();
		if (vp)
		{
			SFVec3f userLoc = vp->GetPosition();
			vrMatrix mat = GetTotalTransformation();
			SFVec3f trans(mat.vals[3][0], mat.vals[3][1], mat.vals[3][2]);

			SFVec3f center = ps->GetCenter() + trans;
			SFVec3f diff = center - userLoc;
			SFFloat dist = Length(diff);
			SFVec3f size = ps->GetSize();

			SFBool wasInside = ps->IsActive();
			SFBool isInside = (dist < size.x || dist < size.y || dist < size.z);

			if (wasInside)
			{
				if (!isInside)
				{
					SFBool isActive = FALSE;
					ps->SetIsActive(isActive);
					ps->SendEventOut(VRML_ISACTIVE_STR, &isActive);

					SFTime time = vrNow();
					ps->SetEnterTime(time);
					ps->SendEventOut(VRML_EXITTIME_STR, &time);
				}
			} else
			{
				if (isInside)
				{
					SFBool isActive = TRUE;
					ps->SetIsActive(isActive);
					ps->SendEventOut(VRML_ISACTIVE_STR, &isActive);

					SFTime time = vrNow();
					ps->SetEnterTime(time);
					ps->SendEventOut(VRML_ENTERTIME_STR, &time);
				}
			}
		}
	}
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrVisibilitySensor *node)
{
}

//-------------------------------------------------------------------
//
// The action traverse needs to keep track of the existance of 
// pointing device sensors so it picks the scene if the mouse
// goes down.
//
//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrCylinderSensor *node)
{
	hasSensor = TRUE;
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrPlaneSensor *node)
{
	hasSensor = TRUE;
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrSphereSensor *node)
{
	hasSensor = TRUE;
}

//-------------------------------------------------------------------
void vrActionTraverser::Traverse(const vrTouchSensor *node)
{
	hasSensor = TRUE;
}

