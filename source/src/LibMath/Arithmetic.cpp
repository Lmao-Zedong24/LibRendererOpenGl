#include "LibMath/Arithmetic.h"

#include <limits>

namespace LibMath
{
	float floor(const float value)
	{
		const float intPart = static_cast<float>(static_cast<int>(value));

		if (intPart > value)
			return intPart - 1;

		return intPart;
	}


	float ceil(const float value)
	{
		const auto intPart = static_cast<float>(static_cast<int>(value));

		if (intPart < value)
			return intPart + 1;

		return intPart;
	}

	float round(const float value)
	{
		const auto intPart = static_cast<float>(static_cast<int>(value));
		const float decimalPart = value - intPart;

		if (decimalPart < .5f)
			return intPart;

		return intPart + 1;
	}

	float clamp(const float value, const float a, const float b)
	{
		const float min = a < b ? a : b;
		const float max = a > b ? a : b;

		if (value < min)
			return min;

		if (value > max)
			return max;

		return value;
	}

	float wrap(const float value, const float a, const float b)
	{
		const float min = a < b ? a : b;
		const float max = a > b ? a : b;

		return value - (max - min) * floor((value - min) / (max - min));
	}

	float squareRoot(const float value, float precision, const size_t maxSteps)
	{
		if (value < 0)
			return NAN;

		if (value == 0.f)
			return 0.f;

		if (precision == 0.f)
			precision = std::numeric_limits<float>::epsilon();
		else
			precision = abs(precision);

		float sqrt = value >= 4.f ? value / 2.f :
			value < .5f ? 1.f / (1 - value) :
			value < 1.f ? 1.f / value : value;

		// Keep repeating until the approximation is close enough to the real value
		for (size_t i = 0; (maxSteps == 0 || i < maxSteps) && abs(sqrt * sqrt - value) > precision; i++)
			sqrt = .5f * (sqrt + value / sqrt); // Babylonian step - cf. https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Heron's_method

		return sqrt;
	}

	float pow(const float value, const int exponent)
	{
		if (floatEquals(value, 1.f) || exponent == 0)
			return 1.f;

		if (floatEquals(value, 0))
			return 0.f;

		float result;

		if (exponent > 0)
		{
			result = value;

			for (int i = 1; i < exponent; i++)
				result *= value;
		}
		else
		{
			result = 1.f;

			for (int i = 0; i > exponent; i--)
				result /= value;
		}

		return result;
	}

	float min(const float a, const float b)
	{
		return a < b ? a : b;
	}

	float max(const float a, const float b)
	{
		return a > b ? a : b;
	}

	float abs(const float value)
	{
		return value < 0 ? -value : value;
	}

	// adapted from https://stackoverflow.com/a/15012792
	bool floatEquals(const float a, const float b)
	{
		const float maxXYOne = max(max(1.0f, abs(a)),	abs(b));

		return abs(a - b) <= std::numeric_limits<float>::epsilon() * maxXYOne;
	}

	bool floatLessThan(float a, float b)
	{
		return (a - b) < std::numeric_limits<float>::epsilon();
	}

	bool floatGreaterThan(float a, float b)
	{
		return !floatEquals(a, b) && !floatLessThan(a, b);
	}
}