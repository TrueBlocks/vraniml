#ifndef __VEC3F_H3D
#define __VEC3F_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

class vrMatrix;
#include "vec2f.h"

/*----------------------------------------------------------------------
CLASS
	SFVec3f

	Represents a 3d vector.

DESCRIPTION
	<ul>
	Represents the SFVec3f field as defined in VRML.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// This is just a simple vector class.  You can treat vectors (both
	// 2D and 3D) as basic C++ types.  2D vectors are promoted to 3D vectors
	// if need be.  Also, SFFloats are promoted to 2D or 3D vectors if needed.
	
	SFVec3f vec1(1.0, 1.0, 1.0);
	// construct from a float
	SFVec3f vec2(2.0);

	SFVec3f vec3 = vec2 + vec1;
	
	// Treat them as a basic data type.
	ASSERT((SFVec3f(0) + SFVec3f(1) / 2.0) == SFVec3f(.5));
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class SFVec3f
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The x, y and z components of the vector.
	// [default:] (0.0,0.0,0.0)
	//
  SFFloat x, y, z;
  
public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	SFVec3f           (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	SFVec3f           (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~SFVec3f           (void);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] f1: Value for x component.
	// [in] f2: Value for y component.
	// [in] f3: Value for z component.
	//
	SFVec3f           (SFFloat f1, SFFloat f2, SFFloat f3);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] f: Value for both x and y components.
	//
	SFVec3f           (SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] v: An SFVec2f value promoted to 3 dimensions (z = 0.0)
	//
	SFVec3f           (const SFVec2f& v);

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	SFVec3f&  operator=         (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Access operator for component assignment.
	//
	// [in] i: Index into the vector (0 = x, 1 = y, 2 = z).
	//
	SFFloat&  operator[]        (SFInt32 i);

  //<doc>------------------------------------------------------------
  // <dd>Access operator for read only.
	//
	// [in] i: Index into the vector (0 = x, 1 = y, 2 = z).
	//
	const  SFFloat&  operator[]        (SFInt32 i) const;

  //<doc>------------------------------------------------------------
  // <dd>Unary addition.
	//
	SFVec3f   operator+         (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Unary negation.
	//
	SFVec3f   operator-         (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Add given vector to this vector.
	//
	// [in] v: The vector to add.
	//
	SFVec3f&  operator+=        (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Subtract given vector to this vector.
	//
	// [in] v: The vector to subtract.
	//
	SFVec3f&  operator-=        (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Multiply given vector to this vector.
	//
	// [in] v: The vector to multiply.
	//
	SFVec3f&  operator*=        (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Multiply this vector by a scalar.
	//
	// [in] s: The scalar to multiply by.
	//
	SFVec3f&  operator*=        (SFFloat s);

  //<doc>------------------------------------------------------------
  // <dd>Divide this vector by a scalar.
	//
	// [in] s: The scalar to divide by.
	//
	SFVec3f&  operator/=        (SFFloat s);

	// friends
  //<doc>------------------------------------------------------------
  // <dd>Project the given vector on the given plane returning values in floats.
	//
	// [in] v: The vector to project.
	// [out] f1: The first component of the result of the projection.
	// [out] f2: The second component of the result of the projection.
	// [in] which: One of 0, 1, or 2 representing X, Y and Z axis respectively.
	//
	friend void      GetProjectedVerts (const SFVec3f& v, SFFloat *f1, SFFloat *f2, SFInt32 which);

  //<doc>------------------------------------------------------------
  // <dd>Return the projection of vector v onto vector u.
	//
	// [in] v: The vector to project.
	// [in] u: The vector to project onto.
	//
	friend SFVec3f   Projection        (const SFVec3f& v, const SFVec3f& u);

  //<doc>------------------------------------------------------------
  // <dd>Return the orthographic projection of vector v onto vector u.
	//
	// [in] v: The vector to project orthographically.
	// [in] u: The vector to project orthographically onto.
	//
	friend SFVec3f   OrthoProjection   (const SFVec3f& v, const SFVec3f& u);

  //<doc>------------------------------------------------------------
  // <dd>Add two vectors.
	//
	friend SFVec3f   operator+         (const SFVec3f& v1, const SFVec3f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Subtract two vectors.
	//
	// [in] v1: The first vector.
	// [in] v2: The second vector.
	//
	friend SFVec3f   operator-         (const SFVec3f& v1, const SFVec3f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Multiply two vectors.
	//
	// [in] v1: The first vector.
	// [in] v2: The second vector.
	//
	friend SFVec3f   operator*         (const SFVec3f& v1, const SFVec3f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Multiply a vector by a scalar.
	//
	// [in] v: The vector.
	// [in] f: The scalar.
	//
	friend SFVec3f   operator*         (const SFVec3f& v,  SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Multiply a vector by a scalar.
	//
	// [in] f: The scalar.
	// [in] v: The vector.
	//
	friend SFVec3f   operator*         (SFFloat f,         const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Multiply a vector by a matrix - returns transformed vector.
	//
	// [in] m: The matrix to transform the vector by.
	// [in] v: The vector to be transformed.
	//
	friend SFVec3f   operator*         (const vrMatrix& m,  const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Divide a vector componentwise by another vector.
	//
	// [in] v1: The first vector.
	// [in] v2: The second vector.
	//
	friend SFVec3f   operator/         (const SFVec3f& v1, const SFVec3f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Divide a vector by a scalar.
	//
	// [in] v: The vector.
	// [in] f: The scalar.
	//
	friend SFVec3f   operator/         (const SFVec3f& v1, SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if two vectors are identical.
	//
	// [in] v1: The first vector.
	// [in] v2: The second vector.
	//
	friend SFBool    operator==        (const SFVec3f& v1, const SFVec3f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if two vectors are different.
	//
	// [in] v1: The first vector.
	// [in] v2: The second vector.
	//
	friend SFBool    operator!=        (const SFVec3f& v1, const SFVec3f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Return a normalized version of the given vector.
	//
	// [in] v: The vector to normalize.
	//
	friend SFVec3f   Normalize         (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Return the dot product of two vectors.
	//
	// [in] v1: The first vector.
	// [in] v2: The second vector.
	//
	friend SFFloat   DotProduct        (const SFVec3f& v1, const SFVec3f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Return the cross product of two vectors.
	//
	// [in] v1: The first vector.
	// [in] v2: The second vector.
	//
	friend SFVec3f   CrossProduct      (const SFVec3f& v1, const SFVec3f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Return the distance between two points in 3-space (always positive).
	//
	// [in] p1: The first point.
	// [in] p2: The second point.
	//
	friend SFFloat   Distance          (const SFVec3f& p1, const SFVec3f& p2);

  //<doc>------------------------------------------------------------
  // <dd>Return the signed distance between the line represented by p1 and p2 and the point p3.
	//
	// [in] p1: The start of the line.
	// [in] p2: The end of the line.
	// [in] p1: The point to measure to.
	//
	friend SFFloat   SignedDistance    (const SFVec3f& p1, const SFVec3f& p2, const SFVec3f& dir);

  //<doc>------------------------------------------------------------
  // <dd>Return the magnitude (length) of the given vector.
	//
	// [in] v: The vector to measure.
	//
	friend SFFloat   Magnitude         (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Return the magnitude (length) of the given vector.
	//
	// [in] v: The vector to measure.
	//
	friend SFFloat   Length            (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Rotate a plane (represented by the plane's normal vector) by the given matrix.
	// <dd>Returns the rotated normal.
	//
	// [in] m: The matrix to transform the normal by.
	// [in] v: The normal to be rotated.
	//
	friend SFVec3f   PlaneRotate       (const vrMatrix& m,  const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Return the absolute value of the vector.
	//
	// [in] v: The vector.
	//
	friend SFVec3f   AbsoluteVal       (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Return the vector that is not larger than the candidate in any component.
	//
	// [in] min: The minimum values for each of the three components of the candidate vector 'v'.
	// [in] v: The vector.
	//
	friend void      Minimize          (SFVec3f& min,      const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Return the vector that is not smaller than the candidate in any component.
	//
	// [in] max: The minimum values for each of the three components of the candidate vector 'v'.
	// [in] v: The vector.
	//
	friend void      Maximize          (SFVec3f& max,      const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Return the component of the vector that is largest in absolute value.
	//
	// [in] v: The vector.
	//
	friend SFInt32   GetDominantComp   (const SFVec3f& v);
};

//-------------------------------------------------------------
inline SFVec3f::SFVec3f() 
{  
	// random filled.
}

inline SFVec3f::SFVec3f(const SFVec3f& v) 
{ 
  x = v.x; 
	y = v.y; 
	z = v.z; 
}

inline SFVec3f::~SFVec3f() 
{ 
}

inline SFVec3f& SFVec3f::operator=(const SFVec3f& v)
{
  x = v.x; 
	y = v.y; 
	z = v.z; 
	return *this;
}

//-------------------------------------------------------------
inline SFVec3f::SFVec3f(SFFloat f1, SFFloat f2, SFFloat f3) 
{ 
  x = f1;
	y = f2;
	z = f3; 
}

inline SFVec3f::SFVec3f(SFFloat f) 
{ 
  x = f;
	y = f;
	z = f; 
}

//-------------------------------------------------------------
inline SFFloat& SFVec3f::operator[] (SFInt32 i)
{
	if (i == 0)      return x;
  else if (i == 1) return y;
  else	             return z;
}

inline const SFFloat& SFVec3f::operator[] (SFInt32 i) const
{
	if (i == 0)      return x;
  else if (i == 1) return y;
  else	             return z;
}

inline SFVec3f SFVec3f::operator+ () const
{
  return *this;
}

inline SFVec3f SFVec3f::operator- () const
{
  return SFVec3f(-x, -y, -z);
}

inline SFVec3f& SFVec3f::operator+= (const SFVec3f& v)
{
  x += v.x;  
	y += v.y;  
	z += v.z;
  return *this;
}

inline SFVec3f& SFVec3f::operator-= (const SFVec3f& v)
{
  x -= v.x;  
	y -= v.y;  
	z -= v.z;
  return *this;
}

inline SFVec3f& SFVec3f::operator*= (SFFloat f)
{
  x *= f;  
	y *= f;  
	z *= f;
  return *this;
}

inline SFVec3f& SFVec3f::operator/= (SFFloat f)
{
  x /= f;  
	y /= f;  
	z /= f;
  return *this;
}

inline SFVec3f& SFVec3f::operator*= (const SFVec3f& v)
{
  x *= v.x;  
	y *= v.y;  
	z *= v.z;
  return *this;
}

inline SFVec3f operator+ (const SFVec3f& v1, const SFVec3f& v2)
{
  return SFVec3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline SFVec3f operator- (const SFVec3f& v1, const SFVec3f& v2)
{
  return SFVec3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

inline SFVec3f operator* (const SFVec3f& v1, const SFVec3f& v2)
{
  return SFVec3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

inline SFVec3f operator* (const SFVec3f& v1, SFFloat f)
{
  return SFVec3f(v1.x * f, v1.y * f, v1.z * f);
}

inline SFVec3f operator* (SFFloat f, const SFVec3f& v2)
{
  return v2 * f;
}

inline SFVec3f operator/ (const SFVec3f& v1, const SFVec3f& v2)
{
  return SFVec3f(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

inline SFVec3f operator/ (const SFVec3f& v1, SFFloat f)
{
  return SFVec3f(v1.x / f, v1.y / f, v1.z / f);
}

inline SFBool operator== (const SFVec3f& v1, const SFVec3f& v2)
{
  return 
    (fabs(v1.x-v2.x) < 0.00001) && 
		  (fabs(v1.y-v2.y) < 0.00001) && 
		  (fabs(v1.z-v2.z) < 0.00001);
}

inline SFBool operator!= (const SFVec3f& v1, const SFVec3f& v2)
{
  return !(operator==(v1, v2));
}

//-------------------------------------------------------------
inline SFFloat Magnitude(const SFVec3f& v) 
{
  return (SFFloat)sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

inline SFFloat Length(const SFVec3f& v) 
{
  return Magnitude(v);
}

inline SFFloat Distance(const SFVec3f& v1, const SFVec3f& v2) 
{
  return Magnitude(v2 - v1);
}

inline SFVec3f Normalize(const SFVec3f& v1)
{
  return v1 / Magnitude(v1);
}

//-------------------------------------------------------------
inline SFFloat DotProduct(const SFVec3f& v1, const SFVec3f& v2)
{
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline SFVec3f CrossProduct(const SFVec3f& v1, const SFVec3f& v2)
{
  return SFVec3f(v1.y * v2.z - v1.z * v2.y,
		              v1.z * v2.x - v1.x * v2.z,
		              v1.x * v2.y - v1.y * v2.x);
}

//-------------------------------------------------------------
inline SFVec3f GetDirectionCosines (const SFVec3f& v1)
{
  SFFloat len = Magnitude(v1);

  if (len)
    return SFVec3f(v1.x/len, v1.y/len, v1.z/len);
  else
    return SFVec3f(0.0f);
}

inline SFVec3f AbsoluteVal(const SFVec3f& v)
{
	return SFVec3f((SFFloat)fabs(v.x), (SFFloat)fabs(v.y), (SFFloat)fabs(v.z));
}

inline SFInt32 GetDominantComp(const SFVec3f& v)
{
  SFVec3f vv = AbsoluteVal(v);
  if (vv.y > vv.x)
	{
    if (vv.z > vv.y)
      return 2;
    return 1;
  } else
	{
    if (vv.z > vv.x)
      return 2;
  }

  return 0;
}

inline SFBool Colinear(const SFVec3f& v1, const SFVec3f& v2, SFVec3f *cross=NULL)
{
	// Determine if two vectors are co-linear (and return their cross product)
	SFVec3f c = CrossProduct(v1, v2);
	SFBool ret = (c == SFVec3f(0.0f));
	if (cross) *cross = c;
	return ret;
}

#define defRotation (SFRotation(0, 0, 1, 0))
#define zAxis       (SFVec3f(0,0,1))
#define yAxis       (SFVec3f(0,1,0))
#define xAxis       (SFVec3f(1,0,0))
#define xyz1        (SFVec3f(1,1,1))
#define origin      (SFVec3f(0,0,0))

#endif
