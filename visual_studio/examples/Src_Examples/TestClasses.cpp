//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "Utils\Utility.h"

#include "TestClasses.h"

// For output
#ifdef _DEBUG
vrDumpContext tracer;
#endif
vrDumpContext dc;

void main(int argc, char *argv[])
{
	TestAllClasses();
}

// Test harness calls a single function to test
// each c++ class in the utility library.
void TestAllClasses(void)
{
	// Collection classes
	TestArrayBaseClass();
	TestArrayClass();
	TestIntrusiveListClass();
	TestListClass();
	TestRefCountListClass();
	TestSFStringClass();
	TestStackClass();
	TestRefCountStackClass();

	// Geometry classes
	TestBoundingBoxClass();
	TestImageClass();
	TestMatrixClass();
	TestPlaneClass();
	TestRayClass();
	TestRect2DClass();
	TestColorClass();
	TestVec2fClass();
	TestVec3fClass();
	TestRotationClass();

	// Utility classes
	TestDumpContextClass();
	TestTimeClass();
	TestUtilityFunctions();
	TestImageLib();

	// Test runtime type list
	TestRuntimeTypes();
}

// Test a generic array type
template<class TYPE>
void TestArray(TYPE a, TYPE b, TYPE c)
{
	// This is a basic array class.
	vrArrayBase<TYPE> intArray;

	intArray[0] = a;
	intArray[1] = b;
	intArray[2] = c;

	for (int i=0;i<intArray.GetCount();i++)
		dc << dc.Indent() << intArray[i] << " ";

	dc << endl;
}

void TestStringArray(SFString a, SFString b, SFString c)
{
	// This is a basic array class.
	MFString *intArray = new MFString;

	(*intArray)[0] = a;
	(*intArray)[1] = b;
	(*intArray)[2] = c;
	
	for (int i=0;i<intArray->GetCount();i++)
		dc << dc.Indent() << (*intArray)[i] << " ";

	MFString copy = *intArray;
	delete intArray;

	for (i=0;i<copy.GetCount();i++)
		dc << dc.Indent() << copy[i] << " ";

	dc << endl;
}

void TestArrayBaseClass(void)
{
	dc << "TestArrayBaseClass...\n";
	dc.m_nIndents++;
	
	TestArray<SFBool> (0, 0, 1);
	TestArray<SFInt32>(1, 2, 3);
	TestArray<SFFloat>(0.1, 1.1, 1.2);;
	TestArray<SFVec2f>(-2, 2, 0);
	TestArray<SFVec3f>(-2, 2, 0);
	TestArray<SFColor>(vrRed, vrGreen, vrBlue);
	TestArray<SFRotation>(defRotation, SFRotation(xAxis, 0), SFRotation(yAxis, 2));
	TestArray<vrMatrix>(IdentityMatrix(), ScaleMatrix(2), MirrorX());
	
	// String Class is special because of memory allocation issues
	TestStringArray("Hello", "World", "Hello\n\t\tThere");

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestArrayClass(void)
{
	dc << "\nTestArrayClass...\n";
	dc.m_nIndents++;
	// vrArrays can be treated like any C++ data type in that they
	// support the common mathematical operators '+', '-', '*' and '/'.

	// Note: could have used MFFloat instead.
	vrArray<SFFloat> floatArray1;
	floatArray1[0] = 1.0;
	floatArray1[1] = 2.0;
	floatArray1[2] = 3.0;
	for (int i=0;i<floatArray1.GetCount();i++)
		dc << dc.Indent() << floatArray1[i];
	dc << endl;

	// Note: could have used vrArray<SFFloat> instead.
	MFFloat floatArray2;
	floatArray2[0] = 3.0;
	floatArray2[1] = 2.0;
	floatArray2[2] = 1.0;
	for (i=0;i<floatArray2.GetCount();i++)
		dc << dc.Indent() << floatArray2[i];
	dc << endl;

	MFFloat result;
	result = floatArray1 + floatArray2;
	for (i=0;i<result.GetCount();i++)
		dc << dc.Indent() << result[i];
	dc << endl;

	// OUTPUT:
	// 1.0 2.0 3.0
	// 3.0 2.0 1.0
	// 4.0 4.0 4.0
	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

// Test class for IntrusiveList test
class A
{
public:
	A *next;
	A *prev;
	int data;
	A(int d) { data = d; }
};
void TestIntrusiveListClass(void)
{
	dc << "\nTestIntrusiveListClass...\n";
	dc.m_nIndents++;

	// A simple linked list.  Items added to the vrIntrusiveList must
	// possess next and prev pointers.
	vrIntrusiveList<A*> Alist;
	Alist.AddTail(new A(1));
	Alist.AddTail(new A(2));
	Alist.AddTail(new A(3));

	LISTPOS pos = Alist.GetHeadPosition();
	while (pos)
	{
		A *a = Alist.GetNext(pos);
		dc << dc.Indent() << a->data;
		Alist.RemoveAt(a);
		delete a;
	}
	dc << endl;

	// OUTPUT
	// 1 2 3
	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

template<class TYPE>
void TestList(TYPE a, TYPE b, TYPE c)
{
	// This is just a basic linked list class:
	vrList<TYPE> list;

	list.AddTail(a);
	list.AddTail(b);
	list.AddTail(c);

	// Iteration is accomplished identically to the MFC.
	LISTPOS pos = list.GetHeadPosition();
	while (pos)
		dc << dc.Indent() << list.GetNext(pos) << " ";
	dc << endl;
}

void TestListClass(void)
{
	dc << "\nTestListClass...\n";
	dc.m_nIndents++;

	TestList<SFBool> (0, 0, 1);
	TestList<SFInt32>(1, 2, 3);
	TestList<SFFloat>(0.1, 1.1, 1.2);;
	TestList<SFVec2f>(-2, 2, 0);
	TestList<SFVec3f>(-2, 2, 0);
	TestList<SFColor>(vrRed, vrGreen, vrBlue);
	TestList<SFRotation>(defRotation, SFRotation(xAxis, 0), SFRotation(yAxis, 2));
	TestList<vrMatrix>(IdentityMatrix(), ScaleMatrix(2), MirrorX());
	TestList<SFString>("Hello", "World", "Hello\n\t\tThere");

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

#include "TestNodes.cxx"

void TestRefCountListClass(void)
{
	dc << "\nTestRefCountListClass...\n";
	dc.m_nIndents++;

	// This is just a basic linked list class for reference counted objects:
	vrRefCountList<SFNode> nodeList;

	nodeList.AddTail(new vrCone("Cone"));
	nodeList.AddTail(new vrCylinder("Cylinder"));
	vrBox *box = new vrBox("Box");
	nodeList.AddTail(box);
	nodeList.AddTail(box);  // reference counted twice

	// Iteration is accomplished identically to the MFC.
	LISTPOS pos = nodeList.GetHeadPosition();
	while (pos)
	{
		SFNode node = nodeList.GetNext(pos);
		// apply an operation to the node
		ApplyOperation(node);
	}

	// To cleanup the list use the vrDelete macro:
	pos = nodeList.GetHeadPosition();
	while (pos)
	{
		SFNode node = nodeList.GetNext(pos);
		dc << dc.Indent() << node->GetName() << endl;
		// Only delete if no longer referenced
		vrDELETE(node);
	}
	nodeList.RemoveAll();

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestSFStringClass(void)
{
	dc << "\nTestSFStringClass...\n";
	dc.m_nIndents++;

	// Use SFStrings as you would any string class
	SFString string = "This is a string";
	// Find returns -1 if search string is not found.
	ASSERT(string.Find(".")==-1);
	dc << dc.Indent() << string << ":\tFind(\".\"): " << string.Find(".") << endl;

	// Add a period.
	string += ".";
	// Now it is found.
	ASSERT(string.Find(".")!=-1);
	dc << dc.Indent() << string << ":\tFind(\".\"): " << string.Find(".") << endl;

	// Assignment
	SFString str1 = string;
	// Equality (many other operators are available also).
	ASSERT(str1 == string);

	// Use 'nullString' or Empty to test for empty strings
	SFString defaultString;
	ASSERT(defaultString == nullString);
	ASSERT(defaultString.Empty());

	string.ToUpper();
	dc << dc.Indent() << string << endl;

	string.ToLower();
	dc << dc.Indent() << string << endl;

	string.Reverse();
	dc << dc.Indent() << string << endl;

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

template<class TYPE>
void TestStack(TYPE a, TYPE b, TYPE c)
{
	// A simple stack of integers.
	vrStack<TYPE> stack;
	stack.Push(a);
	stack.Push(b);
	stack.Push(c);

	while (!stack.Empty())
		dc << dc.Indent() << stack.Pop() << " ";
	dc << endl;
}

void TestStackClass(void)
{
	dc << "\nTestStackClass...\n";
	dc.m_nIndents++;

	TestStack<SFBool> (0, 0, 1);
	TestStack<SFInt32>(1, 2, 3);
	TestStack<SFFloat>(1.0, 1.1, 1.2);;
	TestStack<SFVec2f>(-2, 2, 0);
	TestStack<SFVec3f>(-2, 2, 0);
	TestStack<SFColor>(vrRed, vrGreen, vrBlue);
	TestStack<SFRotation>(defRotation, SFRotation(xAxis, 0), SFRotation(yAxis, 2));
	TestStack<vrMatrix>(IdentityMatrix(), ScaleMatrix(2), MirrorX());
	TestStack<SFString>("Hello", "World", "Hello\n\t\tThere");

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestRefCountStackClass(void)
{
	dc << "\nTestRefCountStackClass...\n";
	dc.m_nIndents++;

	// A reference counting stack.
	vrRefCountStack<SFNode> nodeStack;
	nodeStack.Push(new vrCone("Cone"));
	nodeStack.Push(new vrBox("Box"));
	SFNode cyl = new vrCylinder("Cylinder");
	nodeStack.Push(cyl);
	nodeStack.Push(cyl);  // reference count twice.

	// Deletes the Sphere first.
	while (nodeStack.Peek())
	{
		SFNode node = nodeStack.Pop();
		dc << dc.Indent() << node->GetName() << endl;
		if (!node->IsReferenced())
			delete node;
		node = NULL;
	}

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestBoundingBoxClass(void)
{
	dc << "\nTestBoundingBoxClass...\n";
	dc.m_nIndents++;

	// To add values to a bounding box:
	vrBoundingBox box;
	box.Include(SFVec3f(-1.0));
	box.Include(SFVec3f(1.0));

	ASSERT(box.IsInside(SFVec3f(0.0)) == TRUE);
	ASSERT(box.IsInside(SFVec3f(4.0)) == FALSE);

	dc << dc.Indent() << box.GetMin() << ":" << box.GetMax() << 
		":\t\tIsInside(0): " << box.IsInside(SFVec3f(0.0)) << endl;

	dc << dc.Indent() << box.GetMin() << ":" << box.GetMax() << 
		":\t\tIsInside(4): " << box.IsInside(SFVec3f(4.0)) << endl;

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestImageClass(void)
{
	dc << "\nTestImageClass...\n";
	dc.m_nIndents++;

	// To read a texture file for example:
	SFImage image(4, 4, 3);
	if (vrReadTextureImage(image, "..\\sample worlds\\texture\\earth.jpg"))
	{
		dc << dc.Indent() << image;
	} else
		dc << dc.Indent() << "Could not open texture file\n";

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void ShowMatrix(const SFString& msg, const vrMatrix& mat)
{
	dc.m_nDigits = 4;
	dc << dc.Indent() << msg << "\n";
	dc.m_nIndents++;
	dc << dc.Indent() << mat;

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestMatrixClass(void)
{
	dc << "\nTestMatrixClass...\n";
	dc.m_nIndents++;

	// Use the vrMatrix class to perform various matrix related operations:
	vrMatrix rot = RotationZMatrix(vrDeg2Rad(180.0));
	ShowMatrix("RotationZMatrix:", rot);

	SFVec3f rotated = rot * xAxis;
	ASSERT(rotated == -xAxis);

	vrMatrix scale = ScaleMatrix(2.0);
	ShowMatrix("ScaleMatrix:", scale);

	SFVec3f scaled = scale * xAxis;
	ASSERT(scaled == xAxis*2.0);

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestPlaneClass(void)
{
	dc << "\nTestPlaneClass...\n";
	dc.m_nIndents++;

	// Can be used for various calculations:
	vrPlane plane1(xAxis, 1.0);
	dc << dc.Indent() << "Plane1: " << plane1 << endl;

	vrPlane plane2(yAxis, 1.0);
	dc << dc.Indent() << "Plane2: " << plane2 << endl;

	// The intersection of two planes is a ray:
	vrRay intersection = plane1.Intersect(plane2);
	dc << dc.Indent() << "intersection(plane1, plane2):\n\t\t" << intersection << endl;

	// The distance of a point to a plane:
	SFFloat distance = plane1.GetDistance(origin);
	ASSERT(distance == 1.0);
	dc << dc.Indent() << "distance(plane1, origin): " << distance << endl;

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestRayClass(void)
{
	dc << "\nTestRayClass...\n";
	dc.m_nIndents++;

	// A vrRay can be used to calculate intersections for visiblity
	// calculations or plane intersections (among other things):
	SFNode model = new vrBox;

	// a bounding box from some VRML model
	vrBoundingBox box = model->GetBoundingBox(); 
	vrRay lineOfSite = GetLineOfSite();

	dc << dc.Indent() << "Bounding Box: " << box << endl;
	dc << dc.Indent() << "LineofSite: " << lineOfSite << endl;

	if (box.Intersect(lineOfSite))
		{ dc << dc.Indent() << "Ray hits bounding box" << endl; }
	else
		{ dc << dc.Indent() << "Ray does not hit bounding box" << endl; }

	vrPlane plane1(xAxis, 1.0);
	vrPlane plane2(yAxis, 1.0);

	dc << dc.Indent() << "Plane1: " << plane1 << endl;
	dc << dc.Indent() << "Plane2: " << plane2 << endl;

	// The intersection of two planes is a ray:
	vrRay intersection = plane1.Intersect(plane2);
	dc << dc.Indent() << "intersection: " << intersection << endl;

	delete model;
	
	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestRect2DClass(void)
{
	dc << "\nTestRect2DClass...\n";
	dc.m_nIndents++;

	// This class has various uses:
	SFNode model = new vrBox;
	
	// Get a bounding box from some VRML model.
	vrBoundingBox box = model->GetBoundingBox();

	vrRect2D front = box.GetFront();
	vrRect2D side = box.GetSide();
	vrRect2D top = box.GetTop();

	dc << dc.Indent() << "box:  \t" << box << endl;
	dc << dc.Indent() << "front:\t" << front << endl;
	dc << dc.Indent() << "front:\t" << side << endl;
	dc << dc.Indent() << "front:\t" << top << endl;

	delete model;

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestColorClass(void)
{
	dc << "\nTestColorClass...\n";
	dc.m_nIndents++;

	// You can add and subtract and multiply colors to your delight.
	dc << dc.Indent() << "Red:\t" << vrRed << endl;
	dc << dc.Indent() << "Green:\t" << vrGreen << endl;

	SFColor lightRedishGreen = (vrRed + vrGreen) / 4.0;
	dc << dc.Indent() << "(R+G)/4:\t" << lightRedishGreen << endl;

	SFColor grey = (vrWhite * .5);
	dc << dc.Indent() << "grey:\t" << grey << endl;

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestVec2fClass(void)
{
	dc << "\nTestVec2fClass...\n";
	dc.m_nIndents++;

	// This is just a simple vector class.  You can treat vectors (both
	// 2D and 3D) as basic C++ types.  2D vectors are promoted to 3D vectors
	// if need be.  Also, SFFloats are promoted to 2D or 3D vectors if needed.
	
	SFVec2f vec1(1.0, 1.0);
	// construct from a float
	SFVec2f vec2(2.0); 

	// Treat them as basic data types.
	SFVec2f vec3 = vec2 + vec1;

	dc << dc.Indent() << "vec1:\t" << vec1 << endl;
	dc << dc.Indent() << "vec2:\t" << vec2 << endl;
	dc << dc.Indent() << "v1+v2:\t" << vec3 << endl;

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestVec3fClass(void)
{
	dc << "\nTestVec3fClass...\n";
	dc.m_nIndents++;

	// This is just a simple vector class.  You can treat vectors (both
	// 2D and 3D) as basic C++ types.  2D vectors are promoted to 3D vectors
	// if need be.  Also, SFFloats are promoted to 2D or 3D vectors if needed.
	
	SFVec3f vec1(1.0, 1.0, 1.0);
	// construct from a float
	SFVec3f vec2(2.0);

	SFVec3f vec3 = vec2 + vec1;
	
	dc << dc.Indent() << "vec1:\t" << vec1 << endl;
	dc << dc.Indent() << "vec2:\t" << vec2 << endl;
	dc << dc.Indent() << "v1+v2:\t" << vec3 << endl;

	// Treat them as a basic data type.
	ASSERT((SFVec3f(0) + SFVec3f(1) / 2.0) == SFVec3f(.5));

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestRotationClass(void)
{
	dc << "\nTestRotationClass...\n";
	dc.m_nIndents++;

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestDumpContextClass(void)
{
	dc << "\nTestDumpContextClass...\n";
	dc.m_nIndents++;

#if 0
	// First create the output device and attach it to the vrDumpContext...
	FILE *file = fopen("file.txt", "w");
	ASSERT(file);
	vrDumpContext dc(file);

	// ... and then start writing
	dc << 1 << " is the loneliest number.\n";

	// Increase indent level
	dc.m_nIndents++;

	// Write indented text
	dc << dc.Indent() << "This is indented\n";

	// Close and Flush
	dc.Close();
#endif

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestTimeClass(void)
{
	dc << "\nTestTimeClass...\n";
	dc.m_nIndents++;

	// This class allows calculations on time values:
	vrTime time1 = vrNow();

	// wait around a while....
	for (int i=0;i<1000000;i++)
		if (!(i%50000))
			dc << ".";
	dc << endl;
	
	vrTime time2 = vrNow();

	ASSERT(time2 > time1); // comparison
	ASSERT((time2-time1) > 0.0); // subtraction, conversion to double

	dc.m_nDigits = 2;
	dc << dc.Indent() << "time1:\t" << time1 << endl;
	dc << dc.Indent() << "time2:\t" << time2 << endl;
	dc << dc.Indent() << "(t1>t2):\t" << (time1>time2) << endl;
	dc << dc.Indent() << "(t2>t1):\t" << (time2>time1) << endl;
	
	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestUtilityFunctions(void)
{
	dc << "\nTestUtilityFunctions...\n";
	dc.m_nIndents++;

	dc << dc.Indent() << "MIN(1,0):\t" << MIN(1,0) << endl;
	dc << dc.Indent() << "MAX(1,0):\t" << MAX(1,0) << endl;

	vrMatrix A = ScaleMatrix(-4);
	vrMatrix B = ScaleMatrix(4);
	dc << dc.Indent() << "A: " << A << " B: " << B << " vrSwap(A, B) " << endl;
	vrSwap(A,B);
	dc << dc.Indent() << "A: " << A << " B: " << B;

	dc << dc.Indent() << "vrClamp(10, 1, 2):\t" << vrClamp(10, 1, 2) << endl;
	dc << dc.Indent() << "vrClamp(10, 11, 21):\t" << vrClamp(10, 11, 21) << endl;
	dc << dc.Indent() << "vrInRange(10, 1, 2)\t" << vrInRange(10, 1, 2) << endl;
	dc << dc.Indent() << "vrInRange(1.5, 1., 2.)\t" << vrInRange(1.5, 1., 2.) << endl;

	dc << dc.Indent() << "vrInterpolate(0,5,0,1,.5):\t" << vrInterpolate(0,5,0,1,.5) << endl;
	dc << dc.Indent() << "vrInterpolate(0.,5.,0,1,.5):\t" << vrInterpolate(0.,5.,0,1,.5) << endl;
	dc << dc.Indent() << "vrInterpolate(SFVec3f(0),SFVec3f(5),0,1,.5):\t" << vrInterpolate(SFVec3f(0),SFVec3f(5),0,1,.5) << endl;

	dc << dc.Indent() << "vrCompare(1, 1.1, .5):\t" << vrCompare(1, 1.1, .5) << endl;
	dc << dc.Indent() << "vrCompare(1, 1.1, .05):\t" << vrCompare(1, 1.1, .05) << endl;
	dc << dc.Indent() << "vrCompare(1, 0.9, .05):\t" << vrCompare(1, 0.9, .05) << endl;

	dc << dc.Indent() << "vrEquals(1, 1.1, .5):\t" << vrEquals(1, 1.1, .5) << endl;
	dc << dc.Indent() << "vrEquals(1, 1.1, .05):\t" << vrEquals(1, 1.1, .05) << endl;
	dc << dc.Indent() << "vrEquals(1, 0.9, .05):\t" << vrEquals(1, 0.9, .05) << endl;

	dc << dc.Indent() << "vrDeg2Rad(180.0):\t" << vrDeg2Rad(180.0) << endl;
	dc << dc.Indent() << "vrRad2Deg(M_PI):\t" << vrRad2Deg(M_PI) << endl;

	dc << dc.Indent() << "vrPow2LT(127):\t" << vrPow2LT(127) << endl;
	dc << dc.Indent() << "vrPow2LT(129):\t" << vrPow2LT(129) << endl;
	dc << dc.Indent() << "vrPow2LT(128, 32):\t" << vrPow2LT(129, 32) << endl;

	SFString file = "example.exe";
	dc << dc.Indent() << "vrCacheFile(\"example.exe\"):\t" << vrCacheFile(file) << endl;
}

void TestImage(SFImage& img, const SFString& remoteFile)
{
#if 0
	SFString val = remoteFile;
	SFString inName = vrCacheFile(val);

	inputStream in(inName) ;
	if (!in.isOpen())
		return;

	BitmapImage image;

	ImageType type = GetStreamImageType(in);
	if (type == UnknownImage)
    return;
	if (type == GifImage)
  {
		printf("GIF not supported\n");
		return;
	}

	VERIFY(ReadImage(in, image, NULL, NULL) == type);

	// Create the image data after filtering the texture to a suitable
	// 'nxm' size where 'n' and 'm' are both powers of 2
	ASSERT(img.m_Width);
	ASSERT(img.m_Height);
	ASSERT(img.m_nComponents); // == 3);
	ASSERT(img.m_ColorData);

	img.m_Width       = vrPow2LT(image.Width(), img.m_Width);
	img.m_Height      = vrPow2LT(image.Height(), img.m_Height);
	SFInt32 bc = image.BitCount();
	img.m_nComponents = ((bc==24) ? 3 : ((bc==16) ? 2 : 1));
	ASSERT(img.m_nComponents >0 && img.m_nComponents < 4);
	long size = img.m_Width * img.m_Height * img.m_nComponents;
	unsigned char *p = (unsigned char *)img.m_ColorData;

#if 0
	// Filter the leadtools image to the size needed by OpenGL
	int ret = L_ResampleBitmap(pBitmap, img.m_Width, img.m_Height);
//			ret = L_SaveBitmap("\\test.jpg", pBitmap, fileInfo.Format, fileInfo.BitsPerPixel, 2);

	// Flip it over since it's upside down -- don't know why but it is
	L_FlipBitmap(pBitmap);
#endif

	memcpy(img.m_ColorData, image.ImageData(), size);
#endif
}

void TestImageLib(void)
{
	dc << "\nTestImageLib...\n";
	dc.m_nIndents++;

	SFImage image(5,5,3);
	
	if (vrReadTextureImage(image, "test.jpg"))
		dc << image << endl;
	else
		dc << "Could not open file: test.jpg\n";

	if (vrReadTextureImage(image, "test.bmp"))
		dc << image << endl;
	else
		dc << "Could not open file: test.bmp\n";

//	if (vrReadTextureImage(image, "test.png"))
//		dc << image << endl;
//	else
//		dc << "Could not open file: test.png\n";

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();

	dc.m_nIndents--;
}

void TestRuntimeTypes(void)
{
	vrBox box;
	ASSERT(box.IsKindOf(GETRUNTIME_CLASS(vrBaseNode)));
	ASSERT(box.IsKindOf(GETRUNTIME_CLASS(vrNode)));
	ASSERT(box.IsKindOf(GETRUNTIME_CLASS(vrBox)));
	ASSERT(!box.IsKindOf(GETRUNTIME_CLASS(vrCone)));
	
	// Listing all known types
	vrClassTypeList *list = vrGetClassTypeList();
	ASSERT(list);
	LISTPOS pos = list->GetHeadPosition();
	while (pos)
	{
		vrRuntimeClass *pClass = list->GetNext(pos);
		SFString className = pClass->ClassName();
		dc << "Class: " << className << " --> Searching: ";
		if (vrLookupBuiltin(className))
			dc << "Found " + className << endl;
		else
			ASSERT(0);

		// Create one instance of the node to create fields
		if (pClass->m_CreateFunc)
		{
			vrBaseNode *node = (pClass->m_CreateFunc)();
			
			// List fields if any
			vrFieldList *fList = pClass->GetFieldList();
			if (fList)
			{
				LISTPOS fPos = fList->GetHeadPosition();
				while (fPos)
				{
					vrField *field = fList->GetNext(fPos);
					dc << "\tField: " << GetEventTypeName(field->GetEventType()) <<  " " 
															<< GetFieldTypeName(field->GetType()) << " "
															<< field->GetName() << " " << endl;


				}
			} else
			{
				dc << "\tNo fields"endl;
			}
			delete node;
		}
	}

	dc << dc.Indent() << "Hit enter..." << endl;
	getch();
	// Try to create a new class

}
