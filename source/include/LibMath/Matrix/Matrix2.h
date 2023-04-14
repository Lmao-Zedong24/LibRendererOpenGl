#ifndef __LIBMATH__MATRIX__MATRIX2_H__
#define __LIBMATH__MATRIX__MATRIX2_H__

#include "MatrixInternal.h"

namespace LibMath
{
	class Matrix2x2 : public Matrix
	{
	public:
					Matrix2x2(length_t, length_t) = delete;
					Matrix2x2(length_t, length_t, float) = delete;
					Matrix2x2();
		explicit	Matrix2x2(float scalar);
					Matrix2x2(const Matrix& other);
					Matrix2x2(Matrix&& other);
	};

	class Matrix2x3 : public Matrix
	{
	public:
					Matrix2x3(length_t, length_t) = delete;
					Matrix2x3(length_t, length_t, float) = delete;
					Matrix2x3();
		explicit	Matrix2x3(float scalar);
					Matrix2x3(const Matrix& other);
					Matrix2x3(Matrix&& other);
	};

	class Matrix2x4 : public Matrix
	{
	public:
					Matrix2x4(length_t, length_t) = delete;
					Matrix2x4(length_t, length_t, float) = delete;
					Matrix2x4();
		explicit	Matrix2x4(float scalar);
					Matrix2x4(const Matrix& other);
					Matrix2x4(Matrix&& other);
	};

	typedef Matrix2x2 Matrix2;
}

#endif // !__LIBMATH__MATRIX__MATRIX2_H__