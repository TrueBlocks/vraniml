#if 0
#define N 10

vrTransform *Spinner(SFInt32 i,SFInt32 n,SFColor  color)
{
	char ss[10];
	sprintf(ss,"%d_%d",i,n);
	SFString tags = ss;
	vrTimeSensor *ts = new vrTimeSensor;
	ts->SetName("TS"+tags);
	ts->SetLoop(TRUE);
	ts->SetCycleInterval(4.0);
//	ts->Enable(TRUE);
	vrOrientationInterpolator *ori = new vrOrientationInterpolator;
	ori->SetName("ORI"+tags);
	ori->AddKey(0);    
	ori->AddKeyValue(SFRotation(i,1,0,(M_PI*2)*(i/(double)N)-M_PI));
	ori->AddKey(0.5);
	ori->AddKeyValue(SFRotation(0,i,0,(M_PI*2)*(i/(double)N)));
	ori->AddKey(1.0);
	ori->AddKeyValue(SFRotation(0,1,i,(M_PI*2)*(i/(double)N)+M_PI));
	ts->AddRoute("fraction_changed", ori, "set_fraction");
	vrTransform *t = new vrTransform;
	t->AddChild(ori);
	t->AddChild(ts);
	t->SetName("T"+tags);
	ori->AddRoute("value_changed", t, "set_rotation");
	t->SetRotation(SFRotation(1,0,i/21.,(2*M_PI*((double)i)/(double)N)));
	vrShape *shape = new vrShape;
	vrCone *cone = new vrCone;
	cone->SetHeight(3);
	cone->SetBottomRadius(.2);
	shape->AddChild(cone);
	vrAppearance *app = new vrAppearance;
	vrMaterial *mat = new vrMaterial;
	mat->SetDiffuseColor(color*((i+1)/(double)N));//colorMap[(i%20)+1]);
	app->AddChild(mat);
	shape->AddChild(app);
	t->AddChild(shape);
	return t;
}

void main(int argc, char *argv[])
{
	vrBrowser b;

	vrTransform *group = new vrTransform;
	group->SetTranslation(SFVec3f(0,-1,0));
	for (int i=1;i<=N;i++)
	{
		vrTransform *t = Spinner(i,N,vrRed+vrYellow);
		group->AddChild(t);
	}
	b.AddChild(group);

	group = new vrTransform;
	group->SetTranslation(1);
	for (i=1;i<=N;i++)
	{
		vrTransform *t = Spinner(i,N+N,vrGreen+vrBlue);
		group->AddChild(t);
	}
	b.AddChild(group);

	group = new vrTransform;
	group->SetTranslation(-1);
	for (i=1;i<=N;i++)
	{
		vrTransform *t = Spinner(i,0,vrBlue+vrRed+vrWhite);
		group->AddChild(t);
	}
	b.AddChild(group);

	vrWriteTraverser wt;
	wt.SetFilename("D:\\test.wrl");
	b.Traverse(&wt);
}
#endif

#include "stdio.h"
#include "stdlib.h"

#include "vraniml.h"

void main(int argc, char *argv[])
{
	vrBrowser b;

	vrTimeSensor *ts = new vrTimeSensor;
	ts->Reference();
	ts->SetCycleInterval(5.0);

	vrShape *shape = new vrShape;
	vrAppearance *app = new vrAppearance;
	vrMaterial *mat = new vrMaterial;
	mat->SetDiffuseColor(vrRed);
	app->SetMaterial(mat);
	
	vrBox *box = new vrBox;

	shape->SetAppearance(app);
	shape->SetGeometry(box);

	vrOrientationInterpolator *ori = new vrOrientationInterpolator;
	ori->AddKey(0);   ori->AddKeyValue(SFRotation(0, 1, 0, 0));
	ori->AddKey(.5);  ori->AddKeyValue(SFRotation(1, 1, 0, 1.57));
	ori->AddKey(1);   ori->AddKeyValue(SFRotation(0, 1, 0, 1.5));

	vrTransform *trans = new vrTransform;
	trans->AddChild(ts);
	trans->AddChild(ori);
	trans->AddChild(shape);

	b.AddChild(trans);

	ts->SetName("TS");
	ori->SetName("ORI");
	trans->SetName("TRANS");
	
	b.AddRoute(ts, "fraction_changed", ori, "set_fraction");
	b.AddRoute(ori, "value_changed",   trans, "set_rotation");

	vrWriteTraverser wt;
	b.Traverse(&wt);
}

