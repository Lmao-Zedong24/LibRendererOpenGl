#ifndef __LIBMATH__MATRIX4VECTOR4OPERATION_H_
#define __LIBMATH__MATRIX4VECTOR4OPERATION_H_

#include "Vector/Vector4.h"
#include "Matrix/Matrix4.h"

namespace LibMath
{
	inline Vector4 operator*(Matrix4 const& operation, Vector4 const& operand)
	{
		Matrix vec4Mat(4, 1);
		vec4Mat[0] = operand.m_x;
		vec4Mat[1] = operand.m_y;
		vec4Mat[2] = operand.m_z;
		vec4Mat[3] = operand.m_w;

		vec4Mat = operation * vec4Mat;
		return { vec4Mat[0], vec4Mat[1], vec4Mat[2], vec4Mat[3] };
	}
}

#endif // !__LIBMATH__MATRIX4VECTOR4OPERATION_H_
