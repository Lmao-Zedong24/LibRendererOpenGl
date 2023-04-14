#ifndef __LIBMATH__ANGLE__DEGREE_H__
#define __LIBMATH__ANGLE__DEGREE_H__

namespace LibMath
{
	class Radian;

	class Degree
	{
	public:
		Degree();
		explicit Degree(float);						// explicit so no ambiguous / implicit conversion from float to angle can happen
		Degree(Degree const&);
		~Degree();

		operator Radian() const;					// Radian angle = Degree{0.5};		// implicit conversion from Degree to Radian

		Degree& operator=(Degree const&);
		Degree& operator+=(const Degree&);					// Degree angle += Degree{45};
		Degree& operator-=(const Degree&);					// Degree angle -= Degree{45};
		Degree& operator*=(float);					// Degree angle *= 3;
		Degree& operator/=(float);					// Degree angle /= 3;

		void	wrap(bool = false);					// true -> limit m_value to range [-180, 180[	// false -> limit m_value to range [0, 360[

		float	degree(bool = false) const;			// return angle in degree	// true -> limit value to range [-180, 180[	// false -> limit value to range [0, 360[
		float	radian(bool = true) const;			// return angle in radian	// true -> limit value to range [-pi, pi[		// false -> limit value to range [0, 2 pi[
		float	raw() const;						// return m_angle

	private:
		float m_value;
	};

	bool	operator==(const Degree&, const Degree&);		// bool isEqual = Degree{45} == Degree{45};		// true
	bool	operator==(const Degree&, Radian const&);		// bool isEqual = Degree{60} == Radian{0.5};	// false

	Degree	operator-(const Degree&);						// Degree angle = - Degree{45};					// Degree{-45}

	Degree	operator+(Degree, const Degree&);				// Degree angle = Degree{45} + Degree{45};		// Degree{90}
	Degree	operator-(Degree, const Degree&);				// Degree angle = Degree{45} - Degree{45};		// Degree{0}
	Degree	operator*(Degree, float);				// Degree angle = Degree{45} * 3;				// Degree{135}
	Degree	operator/(Degree, float);				// Degree angle = Degree{45} / 3;				// Degree{15}

	inline namespace Literal
	{
		Degree operator""_deg(long double);			// Degree angle = 7.5_deg;
		Degree operator""_deg(unsigned long long int);	// Degree angle = 45_deg;
	}
}

#endif // !__LIBMATH__ANGLE__DEGREE_H__
