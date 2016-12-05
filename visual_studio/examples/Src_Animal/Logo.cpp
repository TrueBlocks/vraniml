#include "Stdafx.h"

void *Realloc(void *p, size_t size, const int line, const char *file)
{
#undef realloc
	return realloc(p, size);
}

vrTransform *makeV(vrAppearance *app)
{
	vrTransform *t = new vrTransform;
	t->SetName("V");
	
	MFVec2f V[2];
	V[0].AddValue(SFVec2f(0.00, 1.00));
	V[0].AddValue(SFVec2f(0.20, 1.00));
	V[0].AddValue(SFVec2f(0.60, 0.00));
	V[0].AddValue(SFVec2f(0.40, 0.00));
	V[0].AddValue(SFVec2f(0.00, 1.00));

	V[1].AddValue(SFVec2f(0.85, 1.00));
	V[1].AddValue(SFVec2f(1.05, 1.00));
	V[1].AddValue(SFVec2f(0.66, 0.00));
	V[1].AddValue(SFVec2f(0.56, 0.25));
	V[1].AddValue(SFVec2f(0.85, 1.00));

	for (int i=0;i<2;i++)
	{
		vrShape *shape = new vrShape;
		shape->SetAppearance(app);
		vrExtrusion *ext = new vrExtrusion;
		ext->SetCrossSection(V[i]);
		shape->SetGeometry(ext);
		vrTransform *tt = new vrTransform;
		char partname[256];
		sprintf(partname, "%s_%d", t->GetName(), i);
		tt->SetName(partname);
		tt->AddChild(shape);
		t->AddChild(tt);
	}

	t->SetRotation(SFRotation(xAxis, DEG2RAD(-75.0)));
	return t;
}

vrTransform *makeR(vrAppearance *app)
{
	vrTransform *t = new vrTransform;
	t->SetName("R");
	
	MFVec2f V[6];
	V[0].AddValue(SFVec2f(.00,1));
	V[0].AddValue(SFVec2f(.20,1));
	V[0].AddValue(SFVec2f(.20,0));
	V[0].AddValue(SFVec2f(.00,0));
	V[0].AddValue(SFVec2f(.00,1));

	V[1].AddValue(SFVec2f(.25,1));
	V[1].AddValue(SFVec2f(.55,1));
	V[1].AddValue(SFVec2f(.50,.8));
	V[1].AddValue(SFVec2f(.25,.8));
	V[1].AddValue(SFVec2f(.25,1));

	V[2].AddValue(SFVec2f(.50,.8));
	V[2].AddValue(SFVec2f(.55, 1));
	V[2].AddValue(SFVec2f(.75,.7));
	V[2].AddValue(SFVec2f(.70,.7));
	V[2].AddValue(SFVec2f(.50,.8));

	V[3].AddValue(SFVec2f(.25,.6));
	V[3].AddValue(SFVec2f(.50,.6));
	V[3].AddValue(SFVec2f(.55,.4));
	V[3].AddValue(SFVec2f(.25,.4));
	V[3].AddValue(SFVec2f(.25,.6));

	V[4].AddValue(SFVec2f(.55,.4));
	V[4].AddValue(SFVec2f(.50,.6));
	V[4].AddValue(SFVec2f(.75,.7));
	V[4].AddValue(SFVec2f(.70,.65));
	V[4].AddValue(SFVec2f(.55,.4));

	V[5].AddValue(SFVec2f(.25,.35));
	V[5].AddValue(SFVec2f(.44,.35));
	V[5].AddValue(SFVec2f(.79,0));
	V[5].AddValue(SFVec2f(.55,0));
	V[5].AddValue(SFVec2f(.25,.35));

	for (int i=0;i<6;i++)
	{
		vrShape *shape = new vrShape;
		shape->SetAppearance(app);
		vrExtrusion *ext = new vrExtrusion;
		ext->SetCrossSection(V[i]);
		shape->SetGeometry(ext);
		vrTransform *tt = new vrTransform;
		char partname[256];
		sprintf(partname, "%s_%d", t->GetName(), i);
		tt->SetName(partname);
		tt->AddChild(shape);
		t->AddChild(tt);
	}


	t->SetRotation(SFRotation(xAxis, DEG2RAD(-75.0)));
	return t;
}

vrTransform *makea(vrAppearance *app)
{
	vrTransform *t = new vrTransform;
	t->SetName("a");
	
	MFVec2f V[6];
	V[0].AddValue(SFVec2f(.00,.55));
	V[0].AddValue(SFVec2f(.35,.6));
	V[0].AddValue(SFVec2f(.485,.535));
	V[0].AddValue(SFVec2f(.3,.47));
	V[0].AddValue(SFVec2f(.00,.55));

	V[1].AddValue(SFVec2f(.35,.45));
	V[1].AddValue(SFVec2f(.5,.5));
	V[1].AddValue(SFVec2f(.5,.15));
	V[1].AddValue(SFVec2f(.35, .0));
	V[1].AddValue(SFVec2f(.35, .45));

	V[2].AddValue(SFVec2f(.4,-.0125));
	V[2].AddValue(SFVec2f(.5,.12));
	V[2].AddValue(SFVec2f(.6,.00));
	V[2].AddValue(SFVec2f(.5,-.10));
	V[2].AddValue(SFVec2f(.4,-.0125));

	V[3].AddValue(SFVec2f(.3,.02));
	V[3].AddValue(SFVec2f(.25,.02));
	V[3].AddValue(SFVec2f(.05,.3));
	V[3].AddValue(SFVec2f(.15,.3));
	V[3].AddValue(SFVec2f(.3,.3));
	V[3].AddValue(SFVec2f(.3,.02));

	for (int i=0;i<4;i++)
	{
		vrShape *shape = new vrShape;
		shape->SetAppearance(app);
		vrExtrusion *ext = new vrExtrusion;
		ext->SetCrossSection(V[i]);
		shape->SetGeometry(ext);
		vrTransform *tt = new vrTransform;
		char partname[256];
		sprintf(partname, "%s_%d", t->GetName(), i);
		tt->SetName(partname);
		tt->AddChild(shape);
		t->AddChild(tt);
	}

	t->SetRotation(SFRotation(xAxis, DEG2RAD(-75.0)));
	return t;
}

vrTransform *maken(vrAppearance *app)
{
	vrTransform *t = new vrTransform;
	t->SetName("n");
	
	MFVec2f V[3];
	V[0].AddValue(SFVec2f(.00, .6));
	V[0].AddValue(SFVec2f(.20, .6));
	V[0].AddValue(SFVec2f(.20, 0));
	V[0].AddValue(SFVec2f(.00, 0));
	V[0].AddValue(SFVec2f(.00, .6));

	V[1].AddValue(SFVec2f(.25, .6));
	V[1].AddValue(SFVec2f(.52, .6));
	V[1].AddValue(SFVec2f(.25, .4));
	V[1].AddValue(SFVec2f(.25, .6));

	V[2].AddValue(SFVec2f(.35, .39));
	V[2].AddValue(SFVec2f(.55, .54));
	V[2].AddValue(SFVec2f(.55, .0));
	V[2].AddValue(SFVec2f(.35, .0));
	V[2].AddValue(SFVec2f(.35, .39));

	for (int i=0;i<3;i++)
	{
		vrShape *shape = new vrShape;
		shape->SetAppearance(app);
		vrExtrusion *ext = new vrExtrusion;
		ext->SetCrossSection(V[i]);
		shape->SetGeometry(ext);
		vrTransform *tt = new vrTransform;
		char partname[256];
		sprintf(partname, "%s_%d", t->GetName(), i);
		tt->SetName(partname);
		tt->AddChild(shape);
		t->AddChild(tt);
	}


	t->SetRotation(SFRotation(xAxis, DEG2RAD(-75.0)));
	return t;
}

vrTransform *makei(vrAppearance *app)
{
	vrTransform *t = new vrTransform;
	t->SetName("i");
	
	MFVec2f V[2];
	V[0].AddValue(SFVec2f(.00, .6));
	V[0].AddValue(SFVec2f(.20, .6));
	V[0].AddValue(SFVec2f(.20, 0));
	V[0].AddValue(SFVec2f(.00, 0));
	V[0].AddValue(SFVec2f(.00, .6));

	for (int i=0;i<1;i++)
	{
		vrShape *shape = new vrShape;
		shape->SetAppearance(app);
		vrExtrusion *ext = new vrExtrusion;
		ext->SetCrossSection(V[i]);
		shape->SetGeometry(ext);
		vrTransform *tt = new vrTransform;
		char partname[256];
		sprintf(partname, "%s_%d", t->GetName(), i);
		tt->SetName(partname);
		tt->AddChild(shape);
		t->AddChild(tt);
	}

	t->SetRotation(SFRotation(xAxis, DEG2RAD(-75.0)));
	return t;
}

vrTransform *makeM(vrAppearance *app)
{
	vrTransform *t = new vrTransform;
	t->SetName("M");
	
	MFVec2f V[4];
	V[0].AddValue(SFVec2f(.00, 1));
	V[0].AddValue(SFVec2f(.20, 1));
	V[0].AddValue(SFVec2f(.20, 0));
	V[0].AddValue(SFVec2f(.00, 0));
	V[0].AddValue(SFVec2f(.00, 1));

	V[1].AddValue(SFVec2f(.25, 1));
	V[1].AddValue(SFVec2f(.75, .225));
	V[1].AddValue(SFVec2f(.60, .1));
	V[1].AddValue(SFVec2f(.40, .1));
	V[1].AddValue(SFVec2f(.25, .225));
	V[1].AddValue(SFVec2f(.25, 1));

	V[2].AddValue(SFVec2f(.75, 1));
	V[2].AddValue(SFVec2f(.75, .225));
	V[2].AddValue(SFVec2f(.50, .6));
	V[2].AddValue(SFVec2f(.75, 1));

	V[3].AddValue(SFVec2f(.80, 1));
	V[3].AddValue(SFVec2f(1.0, 1));
	V[3].AddValue(SFVec2f(1.0, 0));
	V[3].AddValue(SFVec2f(.80, 0));
	V[3].AddValue(SFVec2f(.80, 1));

	for (int i=0;i<4;i++)
	{
		vrShape *shape = new vrShape;
		shape->SetAppearance(app);
		vrExtrusion *ext = new vrExtrusion;
		ext->SetCrossSection(V[i]);
		shape->SetGeometry(ext);
		vrTransform *tt = new vrTransform;
		char partname[256];
		sprintf(partname, "%s_%d", t->GetName(), i);
		tt->SetName(partname);
		tt->AddChild(shape);
		t->AddChild(tt);
	}


	t->SetRotation(SFRotation(xAxis, DEG2RAD(-75.0)));
	return t;
}

vrTransform *makeL(vrAppearance *app)
{
	vrTransform *t = new vrTransform;
	t->SetName("L");
	
	MFVec2f V[2];
	V[0].AddValue(SFVec2f(.00, 1));
	V[0].AddValue(SFVec2f(.20, 1));
	V[0].AddValue(SFVec2f(.20, 0));
	V[0].AddValue(SFVec2f(.00, 0));
	V[0].AddValue(SFVec2f(.00, 1));

	V[1].AddValue(SFVec2f(.25, .1));
	V[1].AddValue(SFVec2f(.70, .1));
	V[1].AddValue(SFVec2f(.70, 0));
	V[1].AddValue(SFVec2f(.25, 0));
	V[1].AddValue(SFVec2f(.25, .1));

	for (int i=0;i<2;i++)
	{
		vrShape *shape = new vrShape;
		shape->SetAppearance(app);
		vrExtrusion *ext = new vrExtrusion;
		ext->SetCrossSection(V[i]);
		shape->SetGeometry(ext);
		vrTransform *tt = new vrTransform;
		char partname[256];
		sprintf(partname, "%s_%d", t->GetName(), i);
		tt->SetName(partname);
		tt->AddChild(shape);
		t->AddChild(tt);
	}


	t->SetRotation(SFRotation(xAxis, DEG2RAD(-75.0)));
	return t;
}

int rnd(int i)
{
	return rand()%i;
}
SFVec3f RandomAxis(void)
{
	return SFVec3f(rnd(100), rnd(100), rnd(100));
}
SFFloat RandomAngle(void)
{
	return DEG2RAD(360.0);
}

vrBrowser *b=NULL;
SFBool AddRandomSpinner(vrNode *node, void *data)
{
	if (node->GetName() && strcmp(node->GetName(), "TOP"))
	{
		if (node->IsKindOf(GETRUNTIME_CLASS(vrTransform)))
		{
			vrTimeSensor *ts = (vrTimeSensor*)data;
			ASSERT(ts->IsKindOf(GETRUNTIME_CLASS(vrTimeSensor)));

			vrOrientationInterpolator *ori = new vrOrientationInterpolator;
			char name[256];
			sprintf(name, "ORI_%d", ori);
			ori->SetName(name);
			SFVec3f axis = RandomAxis();
			SFFloat angle = RandomAngle();
			for (int i=0;i<5;i++)
			{
				SFFloat key = ((SFFloat)i) / 5.0;
				ori->AddKey(key);
				SFFloat ang = angle - (angle * ((4 - i) / 4.0));
				ori->AddKeyValue(SFRotation(axis, ang));
			}
			node->AddChild(ori);
			ts->AddRoute("fraction_changed", ori, "set_fraction");
			ori->AddRoute("value_changed", node, "set_rotation");
		}
	}
	return TRUE;
}

vrTransform *MakeLogo(vrAppearance *app, vrBrowser *browser)
{
	vrTransform *group = new vrTransform;
	
	vrMaterial *mat = new vrMaterial;
	mat->SetDiffuseColor(SFColor(0.75, 0.5, 1.0));
//	mat->SetSpecularColor(vrWhite*.2);
//	mat->SetShininess(0.157);
	app->SetMaterial(mat);
	app->SetName("APP");
	
	vrTransform *V = makeV(app);
	vrTransform *R = makeR(app);
	vrTransform *a = makea(app);
	vrTransform *n = maken(app);
	vrTransform *i = makei(app);
	vrTransform *M = makeM(app);
	vrTransform *L = makeL(app);

	V->SetTranslation(SFVec3f(-3.0, 0, 0));
	R->SetTranslation(SFVec3f(-1.9, 0, 0));
	a->SetTranslation(SFVec3f(-1.1, 0, 0));
	n->SetTranslation(SFVec3f(-.4, 0, 0));
	i->SetTranslation(SFVec3f(.3, 0, 0));
	M->SetTranslation(SFVec3f(.6, 0, 0));
	L->SetTranslation(SFVec3f(1.7, 0, 0));

	group->AddChild(V);
	group->AddChild(R);
	group->AddChild(a);
	group->AddChild(n);
	group->AddChild(i);
	group->AddChild(M);
	group->AddChild(L);

	group->SetTranslation(SFVec3f(.5,-1.2,0));
	group->SetScale(2.);
	group->SetRotation(SFRotation(xAxis, DEG2RAD(-82)));
	vrTransform *top = new vrTransform;
	top->SetName("TOP");
	top->AddChild(group);

	b = browser;
	
	vrTimeSensor *ts = new vrTimeSensor;
	ts->SetName("TS");
	ts->SetLoop(TRUE);
	SFTime t;
	t = 3.0;
	ts->SetCycleInterval(t);
	top->ForEvery(AddRandomSpinner, ts);
	top->AddChild(ts);

	b = NULL;

 	mat = new vrMaterial;
	mat->SetDiffuseColor(SFColor(0.75, 0.0, 1.0));
//	mat->SetSpecularColor(vrWhite*.2);
//	mat->SetShininess(0.157);
	vrAppearance *ap = new vrAppearance();
	ap->SetMaterial(mat);
	ap->SetName("AP");
	vrShape *shape = new vrShape;
	shape->SetAppearance(ap);
	vrCylinder *cc = new vrCylinder;
	cc->SetRadius(1.0);
	cc->SetHeight(.15);
	shape->SetGeometry(cc);

	vrTransform *cyl = new vrTransform;
	cyl->AddChild(shape);
	cyl->SetTranslation(SFVec3f(0,-1.25,-1));
	cyl->SetScale(SFVec3f(8.0, 1.0, 2.0));
	cyl->SetRotation(SFRotation(xAxis, DEG2RAD(8)));
	top->AddChild(cyl);

 	mat = new vrMaterial;
	mat->SetDiffuseColor(vrWhite);
	mat->SetEmissiveColor(vrWhite);
	//mat->SetSpecularColor(vrWhite);
	//mat->SetShininess(0.157);
	ap = new vrAppearance();
	ap->SetMaterial(mat);
	ap->SetName("AP1");
	shape = new vrShape;
	shape->SetAppearance(ap);
	cc = new vrCylinder;
	cc->SetRadius(1.1);
	cc->SetHeight(.12);
	shape->SetGeometry(cc);


	cyl = new vrTransform;
	cyl->AddChild(shape);
	cyl->SetTranslation(SFVec3f(0,-1.25,-1));
	cyl->SetScale(SFVec3f(8.0, 1.0, 2.0));
	cyl->SetRotation(SFRotation(xAxis, DEG2RAD(8)));
	top->AddChild(cyl);

	vrPositionInterpolator *pos = new vrPositionInterpolator;
	pos->SetName("POS");
	pos->AddKey(0.0); pos->AddKeyValue(SFVec3f(-6,-3,-32));
	pos->AddKey(0.2); pos->AddKeyValue(SFVec3f(-3,-2,-24));
	pos->AddKey(0.4); pos->AddKeyValue(SFVec3f(-0,-1,-12));
	pos->AddKey(0.6); pos->AddKeyValue(SFVec3f( 2,-.5,-4));
	pos->AddKey(0.8); pos->AddKeyValue(SFVec3f( 0, 0,  0));
	top->AddChild(pos);

	ts->AddRoute("fraction_changed", pos, "set_fraction");
	pos->AddRoute("value_changed", top, "set_translation");

	vrOrientationInterpolator *ori = new vrOrientationInterpolator;
	ori->SetName("ORI");
	ori->AddKey(0.0); ori->AddKeyValue(SFRotation(xAxis+zAxis, .6));
	ori->AddKey(0.2); ori->AddKeyValue(SFRotation(xAxis+zAxis, .5));
	ori->AddKey(0.4); ori->AddKeyValue(SFRotation(xAxis+zAxis, .3));
	ori->AddKey(0.6); ori->AddKeyValue(SFRotation(xAxis+zAxis, .2));
	ori->AddKey(0.8); ori->AddKeyValue(SFRotation(xAxis+zAxis, .0));
	top->AddChild(ori);

	ts->AddRoute("fraction_changed", ori, "set_fraction");
	ori->AddRoute("value_changed", top, "set_rotation");

	vrBackground *bk = new vrBackground();
	bk->AddSkyColor(SFColor(.57, .57, 1));
	top->AddChild(bk);
	browser->Bind(bk, TRUE);

	return top;
}