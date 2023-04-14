#ifndef __LIBMATH__ARITHMETIC_H__
#define __LIBMATH__ARITHMETIC_H__
#include <limits>

namespace LibMath
{
	/**
	 * \brief Returns the highest integer lower than or equal to the received value
	 * \param value The value to floor
	 * \return The highest integer value lower than or equal to the received value
	 */
	float	floor(float value);

	/**
	 * \brief Returns the lowest integer greater than or equal to the received value
	 * \param value The value to ceil
	 * \return The highest integer value lower than or equal to the received value
	 */
	float	ceil(float value);

	/**
	 * \brief Returns the rounded value
	 * \param value The value to round
	 * \return The received value rounded
	*/
	float round(const float value);

	/**
	 * \brief Returns the received value limited to the given range
	 * \param value The value to clamp
	 * \param a The first value of the range
	 * \param b The second value of the range
	 * \return The received value limited to the given range
	 */
	float	clamp(float value, float a, float b);	// Return parameter limited by the given range

	/**
	 * \brief Wraps the given value inside a given range
	 * \param value The value to wrap
	 * \param a The first value of the range
	 * \param b The second value of the range
	 * \return value wrapped between min and max
	 */
	float	wrap(float value, float a, float b);

	/**
	 * \brief Approximates the square root of a value up to the given precision.
	 * \param value The value to compute the square root of
	 * \param precision The target precision of the computed square root
	 * \param maxSteps The maximum number of babylonian steps to perform
	 * \return An approximation of the square root of the given value
	 */
	float	squareRoot(float value, float precision = std::numeric_limits<float>::epsilon(), size_t maxSteps = 16);

	/**
	 * \brief Raises the received value to the given exponent
	 * \param value The value to raise to the given exponent
	 * \param exponent The exponent to which the value must be raised
	 * \return The received value raised to the given exponent
	 */
	float	pow(float value, int exponent);

	/**
	 * \brief Returns the smallest of two given values
	 * \param a The first value
	 * \param b The second value
	 * \return a if a < b. b otherwise
	 */
	float	min(float a, float b);

	template<typename T>
	T		min(T a, T b)
	{
		return a < b ? a : b;
	}

	/**
	 * \brief Returns the largest of two given values
	 * \param a The first value
	 * \param b The second value
	 * \return a if a > b. b otherwise
	 */
	float	max(float a, float b);

	template<typename T>
	T		max(T a, T b)
	{
		return a > b ? a : b;
	}

	/**
	 * \brief Returns the absolute value of the given number
	 * \paran value The number whose absolute value must be returned
	 * \return The absolute value of the received number
	 */
	float	abs(float value);

	/**
	 * \brief Checks whether two floats can be considered equal
	 * \param a The first value to check
	 * \param b The second value to check
	 * \return True if a can be considered equal to b. False otherwise.
	 */
	bool	floatEquals(float a, float b);
	bool	floatLessThan(float a, float b);
	bool	floatGreaterThan(float a, float b);
}

#endif // !__LIBMATH__ARITHMETIC_H__
