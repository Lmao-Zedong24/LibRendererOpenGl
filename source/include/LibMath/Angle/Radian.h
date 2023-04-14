#ifndef __LIBMATH__ANGLE__RADIAN_H__
#define __LIBMATH__ANGLE__RADIAN_H__

namespace LibMath
{
	class Degree;

	class Radian
	{
	public:
		Radian();
		explicit Radian(float);						// explicit so no ambiguous / implicit conversion from float to angle can happen
		Radian(Radian const&);
		~Radian();

		operator Degree() const;					// Degree angle = Radian{0.5};		// implicit conversion from Radian to Degree

		Radian& operator=(Radian const&);
		Radian& operator+=(const Radian&);					// Radian angle += Radian{0.5};
		Radian& operator-=(const Radian&);					// Radian angle -= Radian{0.5};
		Radian& operator*=(float);					// Radian angle *= 3;
		Radian& operator/=(float);					// Radian angle /= 3;

		void	wrap(bool = false);					// true -> limit m_value to range [-pi, pi[	// false -> limit m_value to range [0, 2 pi[

		float	degree(bool = false) const;			// return angle in degree	// true -> limit value to range [-180, 180[	// false -> limit value to range [0, 360[
		float	radian(bool = true) const;			// return angle in radian	// true -> limit value to range [-pi, pi[		// false -> limit value to range [0, 2 pi[
		float	raw() const;						// return m_angle

	private:
		float m_value;
	};

	bool	operator==(const Radian&, const Radian&);				// bool isEqual = Radian{0.5} == Radian{0.5};	// true
	bool	operator==(const Radian&, Degree const&);		// bool isEqual = Radian{0.5} == Degree{60};	// false

	Radian	operator-(const Radian&);						// Degree angle = - Radian{0.5};				// Radian{-0.5}

	Radian	operator+(Radian, const Radian&);				// Radian angle = Radian{0.5} + Radian{0.5};	// Radian{1}
	Radian	operator-(Radian, const Radian&);				// Radian angle = Radian{0.5} - Radian{0.5};	// Radian{0}
	Radian	operator*(Radian, float);				// Radian angle = Radian{0.5} * 3;				// Radian{1.5}
	Radian	operator/(Radian, float);				// Radian angle = Radian{0.5} / 3;				// Radian{0.166...}

	inline namespace Literal
	{
		Radian operator""_rad(long double);			// Radian angle = 0.5_rad;
		Radian operator""_rad(unsigned long long int);	// Radian angle = 1_rad;
	}
}

#endif // !__LIBMATH__ANGLE__RADIAN_H__
