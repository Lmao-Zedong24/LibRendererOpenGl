#ifndef __LIBMATH__MATRIX__MATRIX4_H__
#define __LIBMATH__MATRIX__MATRIX4_H__

#include "MatrixInternal.h"

namespace LibMath
{
	class Radian;
	class Vector3;

	class Matrix4x2 : public Matrix
	{
	public:
							Matrix4x2(length_t, length_t) = delete;
							Matrix4x2(length_t, length_t, float) = delete;
							Matrix4x2();
		explicit			Matrix4x2(float scalar);
							Matrix4x2(const Matrix& other);
							Matrix4x2(Matrix&& other);
	};

	class Matrix4x3 : public Matrix
	{
	public:
							Matrix4x3(length_t, length_t) = delete;
							Matrix4x3(length_t, length_t, float) = delete;
							Matrix4x3();
		explicit			Matrix4x3(float scalar);
							Matrix4x3(const Matrix& other);
							Matrix4x3(Matrix&& other);
	};

	class Matrix4x4 : public Matrix
	{
	public:
							Matrix4x4(length_t, length_t) = delete;
							Matrix4x4(length_t, length_t, float) = delete;
							Matrix4x4();
		explicit			Matrix4x4(float scalar);
							Matrix4x4(const Matrix& other);
							Matrix4x4(Matrix&& other);

		static Matrix4x4	translation(float x, float y, float z);
		static Matrix4x4	scaling(float x, float y, float z);
		static Matrix4x4	rotation(const Radian& angle, const Vector3& axis);
		static Matrix4x4	rotation(const Radian& yaw, const Radian& pitch, const Radian& roll);
		static Matrix4x4	rotationEuler(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle);
		static Matrix4x4	orthographicProjection(float left, float right, float bottom, float top, float near, float far);
		static Matrix4x4	perspectiveProjection(const Radian& fovY, float aspect, float near, float far);
	};

	typedef Matrix4x4 Matrix4;
}

#ifdef __LIBMATH__VECTOR__VECTOR4_H__
#include "Matrix4Vector4Operation.h"
#endif // __LIBMATH__MATRIX_H__

#endif // !__LIBMATH__MATRIX__MATRIX4_H__
