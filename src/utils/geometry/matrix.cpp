//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "matrix.h"

// operators
vrMatrix& vrMatrix::operator=(const vrMatrix& A)
{
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
			vals[i][j] = A.vals[i][j];
	return *this;
}

vrMatrix& vrMatrix::operator+=(const vrMatrix& A)
{
	for (SFInt32 i = 0; i < 4; i++)
		for (SFInt32 j = 0; j < 4; j++)
			vals[i][j] += A.vals[i][j];

	return *this;
}

vrMatrix& vrMatrix::operator-= (const vrMatrix& A)
{
	for (SFInt32 i = 0; i < 4; i++)
		for (SFInt32 j = 0; j < 4; j++)
			vals[i][j] -= A.vals[i][j];

	return *this;
}

vrMatrix& vrMatrix::operator*= (SFFloat A)
{
	for (SFInt32 i = 0; i < 4; i++)
		for (SFInt32 j = 0; j < 4; j++)
			vals[i][j] *= A;

	return *this;
}

vrMatrix& vrMatrix::operator*= (const vrMatrix& A)
{
	vrMatrix ret = *this;

	for (SFInt32 i = 0; i < 4; i++)
	{
		for (SFInt32 j = 0; j < 4; j++)
		{
			SFFloat subt = 0.0f;
			for (SFInt32 k = 0; k < 4; k++)
			{
				subt += ret.vals[i][k] * A.vals[k][j];
			}
			vals[i][j] = subt;
		}
	}

	return *this;
}

vrMatrix operator+(const vrMatrix& A, const vrMatrix& B)
{
	vrMatrix ret;

	for (SFInt32 i = 0; i < 4; i++)
		for (SFInt32 j = 0; j < 4; j++)
			ret.vals[i][j] = A.vals[i][j] + B.vals[i][j];

	return ret;
}

vrMatrix operator- (const vrMatrix& A, const vrMatrix& B)
{
	vrMatrix ret;

	for (SFInt32 i = 0; i < 4; i++)
		for (SFInt32 j = 0; j < 4; j++)
			ret.vals[i][j] = A.vals[i][j] - B.vals[i][j];

	return ret;
}

vrMatrix operator* (const vrMatrix& A, const vrMatrix& B)
{
	vrMatrix ret;

	for (SFInt32 i = 0; i < 4; i++)
	{
		for (SFInt32 j = 0; j < 4; j++)
		{
			SFFloat subt = 0.0f;
			for (SFInt32 k = 0; k < 4; k++)
				subt += A.vals[i][k] * B.vals[k][j];
			ret.vals[i][j] = subt;
		}
	}

	return ret;
}

SFVec3f operator* (const vrMatrix& M, const SFVec3f& v)
{
	SFVec3f ret;
	SFFloat denom;

	ret.x = v.x * M.vals[0][0] + v.y * M.vals[1][0] + v.z * M.vals[2][0] + M.vals[3][0];
	ret.y = v.x * M.vals[0][1] + v.y * M.vals[1][1] + v.z * M.vals[2][1] + M.vals[3][1];
	ret.z = v.x * M.vals[0][2] + v.y * M.vals[1][2] + v.z * M.vals[2][2] + M.vals[3][2];
	denom = M.vals[0][3] + M.vals[1][3] + M.vals[2][3] + M.vals[3][3];

	if (denom != 1.0)
	{
		//    VRTRACE(("demon != 1.0 in operator*(vrMatrix, SFVec3f)"));
		ret /= denom;
	}

	return ret;
}

vrMatrix operator* (const vrMatrix& A, SFFloat B)
{
	vrMatrix ret;

	for (SFInt32 i = 0; i < 4; i++)
		for (SFInt32 j = 0; j < 4; j++)
			ret.vals[i][j] = A.vals[i][j] * B;

	return ret;
}

// Operations
void vrMatrix::Invert()
{
	// Uses Gaussian elimination.  Could use optimization
	SFInt32 i, j, k;
	vrMatrix Out = IdentityMatrix();

	for (i = 0; i < 4; i++)
	{
		if (vals[i][i] != 1.0)
		{
			SFFloat divby = vals[i][i];
			for (j = 0; j < 4; j++)
			{
				Out.vals[i][j] /= divby;
				vals[i][j] /= divby;
			}
		}

		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				if (vals[j][i] != 0.0)
				{
					SFFloat mulby = vals[j][i];
					for (k = 0; k < 4; k++)
					{
						vals[j][k] -= mulby * vals[i][k];
						Out.vals[j][k] -= mulby * Out.vals[i][k];
					}
				}
			}
		}
	}

	*this = Out;
}

vrMatrix Invert(const vrMatrix& M)
{
	vrMatrix inverted = M;
	inverted.Invert();
	return inverted;
}

void vrMatrix::Transpose()
{
	for (SFInt32 i = 0; i < 4; i++)
	{
		for (SFInt32 j = i; j < 4; j++)
		{
			if (i != j)
			{
				SFFloat temp = vals[i][j];
				vals[i][j] = vals[j][i];
				vals[j][i] = temp;
			}
		}
	}
}

vrMatrix Transpose(const vrMatrix& M)
{
	vrMatrix transpose = M;
	transpose.Transpose();
	return transpose;
}

// Matrix creators
vrMatrix IdentityMatrix(void)
{
	vrMatrix M;

	for (SFInt32 i = 0; i < 4; i++)
		for (SFInt32 j = 0; j < 4; j++)
			M.vals[i][j] = (i == j) ? 1.0f : 0.0f;

	return M;
}

vrMatrix ZeroMatrix()
{
	vrMatrix M;

	for (SFInt32 i = 0; i < 4; i++)
		for (SFInt32 j = 0; j < 4; j++)
			M.vals[i][j] = 0.0f;

	return M;
}

vrMatrix TranslationMatrix(const SFVec3f& loc)
{
	vrMatrix M = IdentityMatrix();

	M.vals[3][0] = loc.x;
	M.vals[3][1] = loc.y;
	M.vals[3][2] = loc.z;

	return M;
}

vrMatrix RotationMatrix(const SFRotation& rotation)
{
	return RotationAxisMatrix(SFVec3f(rotation.x, rotation.y, rotation.z), rotation.w);
}

vrMatrix RotationXMatrix(SFFloat angle)
{
	vrMatrix M = IdentityMatrix();
	SFFloat cosine = (SFFloat)cos(angle);
	SFFloat sine   = (SFFloat)sin(angle);

	M.vals[1][1] = cosine;
	M.vals[2][1] = -sine;
	M.vals[1][2] = sine;
	M.vals[2][2] = cosine;

	return M;
}

vrMatrix RotationYMatrix(SFFloat angle)
{
	vrMatrix M = IdentityMatrix();
	SFFloat cosine = (SFFloat)cos(angle);
	SFFloat sine   = (SFFloat)sin(angle);

	M.vals[0][0] = cosine;
	M.vals[2][0] = -sine;
	M.vals[0][2] = sine;
	M.vals[2][2] = cosine;

	return M;
}

vrMatrix RotationZMatrix(SFFloat angle)
{
	vrMatrix M = IdentityMatrix();
	SFFloat cosine = (SFFloat)cos(angle);
	SFFloat sine   = (SFFloat)sin(angle);

	M.vals[0][0] = cosine;
	M.vals[1][0] = -sine;
	M.vals[0][1] = sine;
	M.vals[1][1] = cosine;

	return M;
}

vrMatrix ScaleMatrix(const SFVec3f& vec)
{
	return ScaleMatrix(vec.x, vec.y, vec.z);
}

vrMatrix ScaleMatrix(SFFloat X, SFFloat Y, SFFloat Z)
{
	vrMatrix M = IdentityMatrix();

	M.vals[0][0] = X;
	M.vals[1][1] = Y;
	M.vals[2][2] = Z;

	return M;
}

vrMatrix MirrorX()
{
	vrMatrix M = IdentityMatrix();

	M.vals[0][0] = -1.0f;

	return M;
}

vrMatrix MirrorY()
{
	vrMatrix M = IdentityMatrix();

	M.vals[1][1] = -1.0f;

	return M;
}

vrMatrix MirrorZ()
{
	vrMatrix M = IdentityMatrix();

	M.vals[2][2] = -1.0f;

	return M;
}

vrMatrix AlignXMatrix(const SFVec3f& pt, const SFVec3f& v)
{
	vrMatrix T = TranslationMatrix(pt);
	SFVec3f dirCos = GetDirectionCosines(v);

	vrMatrix withY = RotationYMatrix(-dirCos.y);
	vrMatrix withZ = RotationZMatrix(-dirCos.z);

	return (withZ * (withY * T));
}

vrMatrix AlignYMatrix(const SFVec3f& pt, const SFVec3f& v)
{
	vrMatrix T = TranslationMatrix(pt);
	SFVec3f dirCos = GetDirectionCosines(v);

	vrMatrix withX = RotationXMatrix(-dirCos.x);
	vrMatrix withZ = RotationZMatrix(-dirCos.z);

	return (withZ * (withX * T));
}

vrMatrix AlignZMatrix(const SFVec3f& pt, const SFVec3f& v)
{
	vrMatrix T = TranslationMatrix(pt);
	SFVec3f dirCos = GetDirectionCosines(v);

	vrMatrix withX = RotationXMatrix(-dirCos.x);
	vrMatrix withY = RotationYMatrix(-dirCos.y);

	return (withY * (withX * T));
}

vrMatrix RotationYPRMatrix(SFFloat yaw, SFFloat pitch, SFFloat roll)
{
	vrMatrix M;
	SFFloat ch = (SFFloat)cos(yaw);
	SFFloat sh = (SFFloat)sin(yaw);
	SFFloat cp = (SFFloat)cos(pitch);
	SFFloat sp = (SFFloat)sin(pitch);
	SFFloat cr = (SFFloat)cos(roll);
	SFFloat sr = (SFFloat)sin(roll);

	M.vals[0][0] = ch*cr + sh*sp*sr;
	M.vals[1][0] = -ch*sr + sh*sp*cr;
	M.vals[2][0] = sh*cp;
	M.vals[0][1] = sr*cp;
	M.vals[1][1] = cr*cp;
	M.vals[2][1] = -sp;
	M.vals[0][2] = -sh*cr - ch*sp*sr;
	M.vals[1][2] = sr*sh + ch*sp*cr;
	M.vals[2][2] = ch*cp;

	for (SFInt32 i = 0; i < 4; i++)
		M.vals[3][i] = M.vals[i][3] = 0.0f;

	M.vals[3][3] = 1.0f;

	return M;
}

vrMatrix RotationAxisMatrix(const SFVec3f& axis, SFFloat radians)
{
	vrMatrix M;
	SFFloat cosine = (SFFloat)cos(radians);
	SFFloat sine   = (SFFloat)sin(radians);
	SFFloat one_minus_cosine = 1.0f - cosine;

	M.vals[0][0] = axis.x * axis.x + (1.0f - axis.x * axis.x) * cosine;
	M.vals[0][1] = axis.x * axis.y * one_minus_cosine + axis.z * sine;
	M.vals[0][2] = axis.x * axis.z * one_minus_cosine - axis.y * sine;
	M.vals[0][3] = 0.0f;

	M.vals[1][0] = axis.x * axis.y * one_minus_cosine - axis.z * sine;
	M.vals[1][1] = axis.y * axis.y + (1.0f - axis.y * axis.y) * cosine;
	M.vals[1][2] = axis.y * axis.z * one_minus_cosine + axis.x * sine;
	M.vals[1][3] = 0.0f;

	M.vals[2][0] = axis.x * axis.z * one_minus_cosine + axis.y * sine;
	M.vals[2][1] = axis.y * axis.z * one_minus_cosine - axis.x * sine;
	M.vals[2][2] = axis.z * axis.z + (1.0f - axis.z * axis.z) * cosine;
	M.vals[2][3] = 0.0f;

	M.vals[3][0] = 0.0f;
	M.vals[3][1] = 0.0f;
	M.vals[3][2] = 0.0f;
	M.vals[3][3] = 1.0f;

	return M;
}

vrMatrix ViewMatrix(const SFVec3f& lookAt, const SFVec3f& viewer, const SFVec3f& upL)
{
	SFVec3f U, V, N;
	SFVec3f Up = Normalize(upL);
	vrMatrix M = IdentityMatrix();

	N = Normalize(viewer - lookAt);

	V = Up - lookAt;
	V -= N * DotProduct(V, N);
	V = Normalize(V);

	U = CrossProduct(V, N);

	M.vals[0][0] = U.x;
	M.vals[1][0] = U.y;
	M.vals[2][0] = U.z;
	M.vals[0][1] = V.x;
	M.vals[1][1] = V.y;
	M.vals[2][1] = V.z;
	M.vals[0][2] = N.x;
	M.vals[1][2] = N.y;
	M.vals[2][2] = N.z;

	M.vals[3][0] = -DotProduct(U, viewer);
	M.vals[3][1] = -DotProduct(V, viewer);
	M.vals[3][2] = -DotProduct(N, viewer);

	return M;
}

vrMatrix GenRotation(const SFVec3f& x, const SFVec3f& y, const SFVec3f& z)
{
	// The vectors should form a basis for the space.
	ASSERT(!vrCompare(DotProduct(x, y), 0.0f));
	ASSERT(!vrCompare(DotProduct(y, z), 0.0f));
	ASSERT(!vrCompare(DotProduct(z, x), 0.0f));

	vrMatrix M = IdentityMatrix();

	M.vals[0][0] = x.x;
	M.vals[1][0] = x.y;
	M.vals[2][0] = x.z;
	M.vals[0][1] = y.x;
	M.vals[1][1] = y.y;
	M.vals[2][1] = y.z;
	M.vals[0][2] = z.x;
	M.vals[1][2] = z.y;
	M.vals[2][2] = z.z;

	return M;
}

// Construct a quadric matrix.	After Foley et al. pp. 528-529.
vrMatrix QuadricMatrix(SFFloat a, SFFloat b, SFFloat c, SFFloat d, SFFloat e,
					   SFFloat f, SFFloat g, SFFloat h, SFFloat j, SFFloat k)
{
	vrMatrix M;

	M.vals[0][0] = a;  M.vals[0][1] = d;  M.vals[0][2] = f;  M.vals[0][3] = g;
	M.vals[1][0] = d;  M.vals[1][1] = b;  M.vals[1][2] = e;  M.vals[1][3] = h;
	M.vals[2][0] = f;  M.vals[2][1] = e;  M.vals[2][2] = c;  M.vals[2][3] = j;
	M.vals[3][0] = g;  M.vals[3][1] = h;  M.vals[3][2] = j;  M.vals[3][3] = k;

	return M;
}

vrMatrix RotationOnly(const vrMatrix& x)
{
	vrMatrix M = x;

	M.vals[3][0] = M.vals[3][1] = M.vals[3][2] = 0.0f;

	return M;
}

// Apply the rotation portion of a matrix to a vector.
SFVec3f RotateOnly(const vrMatrix& M, const SFVec3f& v)
{
	SFVec3f ret;
	SFFloat denom;

	ret.x = v.x * M.vals[0][0] + v.y * M.vals[1][0] + v.z * M.vals[2][0];
	ret.y = v.x * M.vals[0][1] + v.y * M.vals[1][1] + v.z * M.vals[2][1];
	ret.z = v.x * M.vals[0][2] + v.y * M.vals[1][2] + v.z * M.vals[2][2];
	denom = M.vals[0][3] + M.vals[1][3] + M.vals[2][3] + M.vals[3][3];

	if (denom != 1.0) {
		ret /= denom;
	}

	return ret;
}

// Rotate a direction vector (ie. the normal of a plane)
SFVec3f PlaneRotate(const vrMatrix& tform, const SFVec3f& p)
{
	// Hope matrix is invertible...
	vrMatrix use = Transpose(Invert(tform));
	return RotateOnly(use, p);
}
