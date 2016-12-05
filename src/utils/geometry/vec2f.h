#ifndef __VEC2F_H3D
#define __VEC2F_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

/*----------------------------------------------------------------------
CLASS
	SFVec2f

	Represents a 2d vector.

DESCRIPTION
	<ul>
	Represents the SFVec2f field as defined in VRML.
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
	
	SFVec2f vec1(1.0, 1.0);
	// construct from a float
	SFVec2f vec2(2.0); 

	// Treat them as basic data types.
	SFVec2f vec3 = vec2 + vec1;
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class SFVec2f
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The x and y components of the vector.
	// [default:] (0.0,0.0)
	//
  SFFloat x, y;
  
public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	SFVec2f           (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	SFVec2f           (const SFVec2f& v);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~SFVec2f           (void);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] f: Value for both x and y components.
	//
	SFVec2f           (SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] f1: Value for x component.
	// [in] f2: Value for y component.
	//
	SFVec2f           (SFFloat f1, SFFloat f2);

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	SFVec2f&  operator=         (const SFVec2f& v);

  //<doc>------------------------------------------------------------
  // <dd>Access operator used for componentwise assignment.
	//
	// [in] i: Index into the vector (0 = x, 1 = y).
	//
	SFFloat&  operator[]        (SFInt32 i);

  //<doc>------------------------------------------------------------
  // <dd>Access operator used for read only.
	//
	// [in] i: Index into the vector (0 = x, 1 = y).
	//
  const  SFFloat&  operator[]        (SFInt32 i) const;

  //<doc>------------------------------------------------------------
  // <dd>Unary addition.
	//
	SFVec2f   operator+         (void) const;

  //<doc>------------------------------------------------------------
  // <dd>unary negation.
	//
	SFVec2f   operator-         (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Add given vector to this vector.
	//
	// [in] v: The vector to add.
	//
	SFVec2f&  operator+=        (const SFVec2f& v);

  //<doc>------------------------------------------------------------
  // <dd>Subtract given vector from this vector.
	//
	// [in] v: The vector to subtract.
	//
	SFVec2f&  operator-=        (const SFVec2f& v);

  //<doc>------------------------------------------------------------
  // <dd>Multiply this vector by given vector.
	//
	// [in] v: The vector to multiply by.
	//
	SFVec2f&  operator*=        (const SFVec2f& v);

  //<doc>------------------------------------------------------------
  // <dd>Multiply this vector by given scalar.
	//
	// [in] s: The scalar to multiply by.
	//
	SFVec2f&  operator*=        (SFFloat s);

  //<doc>------------------------------------------------------------
  // <dd>Divide this vector by given scalar.
	//
	// [in] s: The scalar to divide by.
	//
	SFVec2f&  operator/=        (SFFloat s);

  //<doc>------------------------------------------------------------
  // <dd>Add two vectors.
	//
	// [in] v1: The first vector.
	// [in] v2: The first vector.
	//
	friend SFVec2f   operator+         (const SFVec2f& v1, const SFVec2f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Subtract two vectors.
	//
	// [in] v1: The first vector.
	// [in] v2: The first vector.
	//
	friend SFVec2f   operator-         (const SFVec2f& v1, const SFVec2f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Multiply two vectors.
	//
	// [in] v1: The first vector.
	// [in] v2: The first vector.
	//
	friend SFVec2f   operator*         (const SFVec2f& v1, const SFVec2f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Multiply vector by scalar.
	//
	// [in] v: The vector.
	// [in] f: The scalar.
	//
	friend SFVec2f   operator*         (const SFVec2f& v,  SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Multiply vector by scalar.
	//
	// [in] f: The scalar.
	// [in] v: The vector.
	//
	friend SFVec2f   operator*         (SFFloat f,         const SFVec2f& v);

  //<doc>------------------------------------------------------------
  // <dd>Divide vector by vector.
	//
	// [in] v1: The first vector.
	// [in] v2: The first vector.
	//
	friend SFVec2f   operator/         (const SFVec2f& v1, const SFVec2f& v2);

  //<doc>------------------------------------------------------------
  // <dd>Divide vector by scalar.
	//
	// [in] v: The vector.
	// [in] f: The scalar.
	//
	friend SFVec2f   operator/         (const SFVec2f& v, SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Nomalize the given vector.
	//
	// [in] v: The vector to normalize.
	//
	friend SFVec2f   Normalize         (const SFVec2f& v);
};

//-------------------------------------------------------------
inline SFVec2f::SFVec2f() 
{  
	// random filled.
}

inline SFVec2f::SFVec2f(const SFVec2f& v) 
{ 
  x = v.x; 
	y = v.y; 
}

inline SFVec2f::~SFVec2f() 
{ 
}

inline SFVec2f& SFVec2f::operator=(const SFVec2f& v)
{
  x = v.x; 
	y = v.y; 
	return *this;
}

//-------------------------------------------------------------
inline SFVec2f::SFVec2f(SFFloat f1, SFFloat f2) 
{ 
  x = f1;
	y = f2;
}

inline SFVec2f::SFVec2f(SFFloat f) 
{ 
  x = f;
	y = f;
}

//-------------------------------------------------------------
inline SFFloat& SFVec2f::operator[] (SFInt32 i)
{
	if (i == 0)      return x;
  else	             return y;
}

inline const SFFloat& SFVec2f::operator[] (SFInt32 i) const
{
	if (i == 0)      return x;
  else	             return y;
}

inline SFVec2f SFVec2f::operator+ () const
{
  return *this;
}

inline SFVec2f SFVec2f::operator- () const
{
  return SFVec2f(-x, -y);
}

inline SFVec2f& SFVec2f::operator+= (const SFVec2f& v)
{
  x += v.x;  
	y += v.y;  
  return *this;
}

inline SFVec2f& SFVec2f::operator-= (const SFVec2f& v)
{
  x -= v.x;  
	y -= v.y;  
  return *this;
}

inline SFVec2f& SFVec2f::operator*= (SFFloat f)
{
  x *= f;  
	y *= f;  
  return *this;
}

inline SFVec2f& SFVec2f::operator/= (SFFloat f)
{
  x /= f;  
	y /= f;  
  return *this;
}

inline SFVec2f& SFVec2f::operator*= (const SFVec2f& v)
{
  x *= v.x;  
	y *= v.y;  
  return *this;
}

inline SFVec2f operator+ (const SFVec2f& v1, const SFVec2f& v2)
{
  return SFVec2f(v1.x + v2.x, v1.y + v2.y);
}

inline SFVec2f operator- (const SFVec2f& v1, const SFVec2f& v2)
{
  return SFVec2f(v1.x - v2.x, v1.y - v2.y);
}

inline SFVec2f operator* (const SFVec2f& v1, const SFVec2f& v2)
{
  return SFVec2f(v1.x * v2.x, v1.y * v2.y);
}

inline SFVec2f operator* (const SFVec2f& v1, SFFloat f)
{
  return SFVec2f(v1.x * f, v1.y * f);
}

inline SFVec2f operator* (SFFloat f, const SFVec2f& v2)
{
  return v2 * f;
}

inline SFVec2f operator/ (const SFVec2f& v1, const SFVec2f& v2)
{
  return SFVec2f(v1.x / v2.x, v1.y / v2.y);
}

inline SFVec2f operator/ (const SFVec2f& v1, SFFloat f)
{
  return SFVec2f(v1.x / f, v1.y / f);
}

inline SFBool operator== (const SFVec2f& v1, const SFVec2f& v2)
{
  return 
    (fabs(v1.x-v2.x) < 0.00001) && 
		  (fabs(v1.y-v2.y) < 0.00001);
}

inline SFBool operator!= (const SFVec2f& v1, const SFVec2f& v2)
{
  return !(operator==(v1, v2));
}

#define xy1     SFVec2f(1,1)
#define origin2 SFVec2f(0,0)

#endif

