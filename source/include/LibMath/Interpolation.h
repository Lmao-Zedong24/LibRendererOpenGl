#ifndef __LIBMATH__INTERPOLATION_H__
#define __LIBMATH__INTERPOLATION_H__

namespace LibMath
{
	constexpr float lerp(const float a, const float b, const float t)
	{
		return a + (b - a) * t;
	}

	inline Vector3 lerp(const Vector3 a, const Vector3 b, const float t)
	{
		return a + (b - a) * t;
	}
}

#endif // !__LIBMATH__INTERSECTION_H__
