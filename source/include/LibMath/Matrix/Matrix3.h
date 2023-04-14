#ifndef __LIBMATH__MATRIX__MATRIX3_H__
#define __LIBMATH__MATRIX__MATRIX3_H__

#include "MatrixInternal.h"

namespace LibMath
{
	class Matrix3x2 : public Matrix
	{
	public:
					Matrix3x2(length_t, length_t) = delete;
					Matrix3x2(length_t, length_t, float) = delete;
					Matrix3x2();
		explicit	Matrix3x2(float scalar);
					Matrix3x2(const Matrix& other);
					Matrix3x2(Matrix&& other);
	};

	class Matrix3x3 : public Matrix
	{
	public:
					Matrix3x3(length_t, length_t) = delete;
					Matrix3x3(length_t, length_t, float) = delete;
					Matrix3x3();
		explicit	Matrix3x3(float scalar);
					Matrix3x3(const Matrix& other);
					Matrix3x3(Matrix&& other);
	};

	class Matrix3x4 : public Matrix
	{
	public:
					Matrix3x4(length_t, length_t) = delete;
					Matrix3x4(length_t, length_t, float) = delete;
					Matrix3x4();
		explicit	Matrix3x4(float scalar);
					Matrix3x4(const Matrix& other);
					Matrix3x4(Matrix&& other);
	};

	typedef Matrix3x3 Matrix3;
}

#endif // !__LIBMATH__MATRIX__MATRIX3_H__
