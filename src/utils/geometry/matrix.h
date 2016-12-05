#ifndef __MATRIX3D_H3D
#define __MATRIX3D_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "vec3f.h"
#include "vec2f.h"
#include "rotation.h"

/*----------------------------------------------------------------------
 CLASS
	vrMatrix

	Represents a 4x4 transformation matrix.

 DESCRIPTION
	<ul>
	Utility class for representing an arbitrary 4x4 transformation.
	This class can be used stand-alone to perform various matrix
	related operations.
	</ul>

 NOTES
	<ul>
	<li>None.</li>
	</ul>

 EXAMPLE CODE
	<pre>
	// Use the vrMatrix class to perform various matrix related operations:
	vrMatrix rot = RotationZMatrix(vrDeg2Rad(180.0));
	SFVec3f rotated = rot * xAxis;
	ASSERT(rotated == -xAxis);

	vrMatrix scale = ScaleMatrix(2.0);
	SFVec3f scaled = scale * xAxis;
	ASSERT(scaled == xAxis*2.0);
	</pre>

 MEMBERS
 ----------------------------------------------------------------------*/
class vrMatrix
{
public:
	//<doc>------------------------------------------------------------
	// <dd>16 floating point numbers representing the matrix.
	// [default:] IdentityMatrix
	//
	SFFloat vals [4][4];

	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrMatrix   (void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrMatrix   (const vrMatrix& mat);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] c0: Column 0 of the matrix.
	// [in] c1: Column 1 of the matrix.
	// [in] c2: Column 2 of the matrix.
	// [in] c3: Column 3 of the matrix.
	//
	vrMatrix   (const SFVec4& c0, const SFVec4& c1, const SFVec4& c2, const SFVec4& c3);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	~vrMatrix   (void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	// [in] A: The matrix to assign from.
	//
	vrMatrix& operator=  (const vrMatrix& A);

	//<doc>------------------------------------------------------------
	// <dd>Additive equals operator.
	//
	// [in] A: The matrix to add from.
	//
	vrMatrix& operator+= (const vrMatrix& A);

	//<doc>------------------------------------------------------------
	// <dd>Subtractive equals operator.
	//
	// [in] A: The matrix to subtract.
	//
	vrMatrix& operator-= (const vrMatrix& A);

	//<doc>------------------------------------------------------------
	// <dd>Multiplicitive equals operator.
	//
	// [in] A: The matrix to multiply by.
	//
	vrMatrix& operator*= (const vrMatrix& A);

	//<doc>------------------------------------------------------------
	// <dd>Multiplicitive by scalar equals operator.
	//
	// [in] A: The scalar to multiply by.
	//
	vrMatrix& operator*= (SFFloat A);

	//<doc>------------------------------------------------------------
	// <dd>Invert the matrix.
	//
	void      Invert     (void);

	//<doc>------------------------------------------------------------
	// <dd>Transpose the matrix.
	//
	void      Transpose  (void);

	//<doc>------------------------------------------------------------
	// <dd>Invert the given matrix.
	//
	// [in] M: The matrix to invert.
	//
	friend vrMatrix Invert            (const vrMatrix& M);

	//<doc>------------------------------------------------------------
	// <dd>Transpose the given matrix.
	//
	// [in] M: The matrix to transpose.
	//
	friend vrMatrix Transpose         (const vrMatrix& M);

	//<doc>------------------------------------------------------------
	// <dd>Return an identity matrix.
	//
	friend vrMatrix IdentityMatrix    (void);

	//<doc>------------------------------------------------------------
	// <dd>Return a zero matrix.
	//
	friend vrMatrix ZeroMatrix        (void);

	//<doc>------------------------------------------------------------
	// <dd>Return a translation matrix by the given vector.
	//
	// [in] trans: The translation amount.
	//
	friend vrMatrix TranslationMatrix (const SFVec3f& trans);

	//<doc>------------------------------------------------------------
	// <dd>Return a rotation matrix by the given angle about the X axis.
	//
	// [in] angle: The rotation amount.
	//
	friend vrMatrix RotationXMatrix   (SFFloat angle);

	//<doc>------------------------------------------------------------
	// <dd>Return a rotation matrix by the given angle about the Y axis.
	//
	// [in] angle: The rotation amount.
	//
	friend vrMatrix RotationYMatrix   (SFFloat angle);

	//<doc>------------------------------------------------------------
	// <dd>Return a rotation matrix by the given angle about the Z axis.
	//
	// [in] angle: The rotation amount.
	//
	friend vrMatrix RotationZMatrix   (SFFloat angle);

	//<doc>------------------------------------------------------------
	// <dd>Return the matrix that will align the vector from pt1 to pt2 with the X axis.
	//
	// [in] pt1: The start of the alignment vector.
	// [in] pt2: The end of the alignment vector.
	//
	friend vrMatrix AlignXMatrix      (const SFVec3f& pt1, const SFVec3f& pt2);

	//<doc>------------------------------------------------------------
	// <dd>Return the matrix that will align the vector from pt1 to pt2 with the Y axis.
	//
	// [in] pt1: The start of the alignment vector.
	// [in] pt2: The end of the alignment vector.
	//
	friend vrMatrix AlignYMatrix      (const SFVec3f& pt1, const SFVec3f& pt2);

	//<doc>------------------------------------------------------------
	// <dd>Return the matrix that will align the vector from pt1 to pt2 with the Z axis.
	//
	// [in] pt1: The start of the alignment vector.
	// [in] pt2: The end of the alignment vector.
	//
	friend vrMatrix AlignZMatrix      (const SFVec3f& pt1, const SFVec3f& pt2);

	//<doc>------------------------------------------------------------
	// <dd>Return a matrix given yaw, pitch and roll.
	//
	// [in] yaw:   The yaw value for the matrix.
	// [in] pitch: The pitch value for the matrix.
	// [in] roll:  The roll value for the matrix.
	//
	friend vrMatrix RotationYPRMatrix (SFFloat yaw, SFFloat pitch, SFFloat roll);

	//<doc>------------------------------------------------------------
	// <dd>Return the matrix represented by the axis and angle.
	//
	// [in] axis:  The axis about which to rotate.
	// [in] radians: The angle (in radians) to rotate about the axis.
	//
	friend vrMatrix RotationAxisMatrix(const SFVec3f& axis, SFFloat radians);

	//<doc>------------------------------------------------------------
	// <dd>Return the matrix represented by the SFRotation.
	//
	// [in] rot: The SFRotation representing the angle and axis for the matrix.
	//
	friend vrMatrix RotationMatrix    (const SFRotation& rot);

	//<doc>------------------------------------------------------------
	// <dd>Return a view matrix given lookat, viewer location and up vectors.
	//
	// [in] lookAt: A point at which the viewer is looking.
	// [in] viewer: The position of the viewer.
	// [in] up:     The direction of 'up'.
	//
	friend vrMatrix ViewMatrix        (const SFVec3f& lookAt, const SFVec3f& viewer, const SFVec3f& up);

	//<doc>------------------------------------------------------------
	// <dd>Return a scale matrix.
	//
	// [in] scale: The amount to scale in each dimension.
	//
	friend vrMatrix ScaleMatrix       (const SFVec3f& scale);

	//<doc>------------------------------------------------------------
	// <dd>Return a scale matrix.
	//
	// [in] X: The amount to scale in the X dimension.
	// [in] Y: The amount to scale in the Y dimension.
	// [in] Z: The amount to scale in the Z dimension.
	//
	friend vrMatrix ScaleMatrix       (SFFloat X, SFFloat Y, SFFloat Z);

	friend vrMatrix GenRotation       (const SFVec3f& x,const SFVec3f& y,const SFVec3f& z);
	friend vrMatrix QuadricMatrix     (SFFloat a, SFFloat b, SFFloat c, SFFloat d, SFFloat e, SFFloat f, SFFloat g, SFFloat h, SFFloat j, SFFloat k);

	//<doc>------------------------------------------------------------
	// <dd>Return a matrix that will mirror a vector about the X axis.
	//
	friend vrMatrix MirrorX           (void);

	//<doc>------------------------------------------------------------
	// <dd>Return a matrix that will mirror a vector about the Y axis.
	//
	friend vrMatrix MirrorY           (void);

	//<doc>------------------------------------------------------------
	// <dd>Return a matrix that will mirror a vector about the Z axis.
	//
	friend vrMatrix MirrorZ           (void);

	//<doc>------------------------------------------------------------
	// <dd>Return the rotation only portion of a matrix.
	//
	// [in] M: The matrix to extract the rotation from.
	//
	friend vrMatrix RotationOnly      (const vrMatrix& M);

	//<doc>------------------------------------------------------------
	// <dd>Return the componentwise addition of two matricies.
	//
	// [in] A: The first matrix.
	// [in] B: The second matrix.
	//
	friend vrMatrix operator+         (const vrMatrix& A, const vrMatrix& B);

	//<doc>------------------------------------------------------------
	// <dd>Return the componentwise subtraction of two matricies.
	//
	// [in] A: The first matrix.
	// [in] B: The second matrix.
	//
	friend vrMatrix operator-         (const vrMatrix& A, const vrMatrix& B);

	//<doc>------------------------------------------------------------
	// <dd>Return the scalar mulitplication of the matrix by a scalar.
	//
	// [in] A: The first matrix.
	// [in] B: A scalar.
	//
	friend vrMatrix operator*         (const vrMatrix& A, SFFloat B);

	//<doc>------------------------------------------------------------
	// <dd>Return the mulitplication of two matricies.
	//
	// [in] A: The first matrix.
	// [in] B: The second matrix.
	//
	friend vrMatrix operator*         (const vrMatrix& A, const vrMatrix& B);

	friend SFVec3f RotateOnly         (const vrMatrix& M, const SFVec3f& v);
};

extern vrMatrix IdentityMatrix(void);
extern vrMatrix RotationAxisMatrix(const SFVec3f& axis, SFFloat radians);
extern vrMatrix ScaleMatrix(SFFloat X, SFFloat Y, SFFloat Z);
extern SFVec3f  RotateOnly(const vrMatrix& M, const SFVec3f& v);

inline vrMatrix::vrMatrix(const SFVec4& c1, const SFVec4& c2, const SFVec4& c3, const SFVec4& c4)
{
	vals[0][0] = c1.x; vals[0][1] = c1.y; vals[0][2] = c1.z; vals[0][3] = c1.w;
	vals[1][0] = c2.x; vals[1][1] = c2.y; vals[1][2] = c2.z; vals[1][3] = c2.w;
	vals[2][0] = c3.x; vals[2][1] = c3.y; vals[2][2] = c3.z; vals[2][3] = c3.w;
	vals[3][0] = c4.x; vals[3][1] = c4.y; vals[3][2] = c4.z; vals[3][3] = c4.w;
}

inline vrMatrix::vrMatrix()
{
	for (SFInt32 i = 0; i<4; i++)
	{
		for (SFInt32 j=0; j<4; j++)
		{
			vals[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}
}

inline vrMatrix::vrMatrix(const vrMatrix& mat)
{
	*this = mat;
}

inline vrMatrix::~vrMatrix()
{
}

#endif
