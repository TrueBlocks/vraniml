#ifndef __ROTATION_H3D
#define __ROTATION_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "vec3f.h"

/*----------------------------------------------------------------------
CLASS
	SFRotation

	Represents a rotation as an axis and angle.

DESCRIPTION
	<ul>
	Represents the SFRotation field as defined in VRML.
	</ul>

NOTES
	<ul>
	<li>SFRotations are stored as an axis and a rotation (in radians)
	about the given axis. This is as per the VRML spec.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class SFRotation : public SFVec3f
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The angle (in radians) of the rotation (axis is represented by x, y, z).
	// [default:] 0.0
	//
	SFFloat     w;

  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	SFRotation (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	SFRotation (const SFRotation& v);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] axis: The axis about which to rotate.
	// [in] radians: The angle of the rotation.
	//
	SFRotation (const SFVec3f& axis, SFFloat radians);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] x: The x component of the axis about which to rotate.
	// [in] y: The y component of the axis about which to rotate.
	// [in] z: The z component of the axis about which to rotate.
	// [in] radians: The angle of the rotation.
	//
	SFRotation (SFFloat x, SFFloat y, SFFloat z, SFFloat radians);

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	SFRotation& operator=  (const SFRotation& v);

  //<doc>------------------------------------------------------------
  // <dd>Multiplies the angle component of the rotation by -1 inverting the rotation.
	//
  void        Invert     (void);

  //<doc>------------------------------------------------------------
  // <dd>Adds two rotations.
	//
	// [in] r1: The first rotation.
	// [in] r2: The second rotation.
	// [known bug] This calculation should happen after conversion to Quarternions.
	//
	friend SFRotation   operator+  (const SFRotation& r1, const SFRotation& r2);

  //<doc>------------------------------------------------------------
  // <dd>Subtract two rotations.
	//
	// [in] r1: The first rotation.
	// [in] r2: The second rotation.
	// [known bug] This calculation should happen after conversion to Quarternions.
	//
  friend SFRotation   operator-  (const SFRotation& r1, const SFRotation& r2);

  //<doc>------------------------------------------------------------
  // <dd>Multiply a rotation by a scalar.
	//
	// [in] r1: The first rotation.
	// [in] f: A scalar
	//
  friend SFRotation   operator*  (const SFRotation& r,  SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the two rotations are identical
	//
	// [in] r1: The first rotation.
	// [in] r2: The second rotation.
	//
  friend SFBool       operator== (const SFRotation& r1, const SFRotation& r2);

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the two rotations are different
	//
	// [in] r1: The first rotation.
	// [in] r2: The second rotation.
	//
  friend SFBool      operator!= (const SFRotation& r1, const SFRotation& r2);
};

inline SFRotation& SFRotation::operator=(const SFRotation& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}

inline void SFRotation::Invert(void)
{
	w = -w;
}

inline SFRotation operator+ (const SFRotation& v1, const SFRotation& v2)
{
  return SFRotation(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

inline SFRotation operator- (const SFRotation& v1, const SFRotation& v2)
{
  return SFRotation(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

inline SFRotation operator* (const SFRotation& v1, SFFloat f)
{
  return SFRotation(v1.x * f, v1.y * f, v1.z * f, v1.w * f);
}

inline SFBool operator== (const SFRotation& v1, const SFRotation& v2)
{
  return 
    ((fabs(v1.x-v2.x) < 0.00001) && 
		  (fabs(v1.y-v2.y) < 0.00001) && 
		  (fabs(v1.z-v2.z) < 0.00001) &&
		  (fabs(v1.w-v2.w) < 0.00001));
}

inline SFBool operator!= (const SFRotation& v1, const SFRotation& v2)
{
  return !(operator==(v1, v2));
}

#define SFVec4 SFRotation

#endif
