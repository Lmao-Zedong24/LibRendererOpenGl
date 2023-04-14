#include "LibMath/Trigonometry.h"
#include "LibMath/Angle.h"

#include "LibMath/Arithmetic.h"

namespace LibMath
{
	Radian::Radian() : Radian(0)
	{
	}

	Radian::Radian(const float angle) : m_value(angle)
	{
	}

	Radian::Radian(Radian const& other) : Radian(other.m_value)
	{
	}

	Radian::~Radian() = default;

	Radian::operator Degree() const
	{
		return Degree(m_value * 180 / g_pi);
	}

	Radian& Radian::operator=(Radian const& other)
	{
		if (this == &other)
			return *this;

		this->m_value = other.m_value;

		return *this;
	}

	Radian& Radian::operator+=(const Radian& angle)
	{
		this->m_value += angle.m_value;

		return *this;
	}

	Radian& Radian::operator-=(const Radian& angle)
	{
		this->m_value -= angle.m_value;

		return *this;
	}

	Radian& Radian::operator*=(const float val)
	{
		this->m_value *= val;

		return *this;
	}

	Radian& Radian::operator/=(const float val)
	{
		this->m_value /= val;

		return *this;
	}

	void Radian::wrap(const bool useNegative)
	{
		if (useNegative)
			this->m_value = LibMath::wrap(this->m_value, -g_pi, g_pi);
		else
			this->m_value = LibMath::wrap(this->m_value, 0, 2 * g_pi);
	}

	float Radian::degree(const bool useNegative) const
	{
		Degree deg = Degree(*this);
		deg.wrap(useNegative);

		return deg.raw();
	}

	float Radian::radian(const bool useNegative) const
	{
		Radian tmp = Radian(*this);
		tmp.wrap(useNegative);

		return tmp.raw();
	}

	float Radian::raw() const
	{
		return this->m_value;
	}

	bool operator==(const Radian& lhs, const Radian& rhs)
	{
		return floatEquals(lhs.radian(), rhs.radian());
	}

	bool operator==(const Radian& rad, Degree const& deg)
	{
		return floatEquals(rad.radian(), deg.radian());
	}

	Radian operator-(const Radian& angle)
	{
		return Radian(-angle.raw());
	}

	Radian operator+(Radian lhs, const Radian& rhs)
	{
		return lhs += rhs;
	}

	Radian operator-(Radian lhs, const Radian& rhs)
	{
		return lhs -= rhs;
	}

	Radian operator*(Radian radian, const float x)
	{
		return radian *= x;
	}

	Radian operator/(Radian radian, const float x)
	{
		return radian /= x;
	}

	Radian Literal::operator ""_rad(const long double angle)
	{
		return Radian(static_cast<float>(angle));
	}

	Radian Literal::operator ""_rad(const unsigned long long int angle)
	{
		return Radian(static_cast<float>(angle));
	}

	Degree::Degree() : m_value(0)
	{
	}

	Degree::Degree(const float angle) : m_value(angle)
	{
	}

	Degree::Degree(Degree const& other) : Degree(other.m_value)
	{
	}

	Degree::~Degree() = default;

	Degree::operator Radian() const
	{
		return Radian(m_value * g_pi / 180);
	}

	Degree& Degree::operator=(Degree const& other)
	{
		if (this == &other)
			return *this;

		this->m_value = other.m_value;

		return *this;
	}

	Degree& Degree::operator+=(const Degree& angle)
	{
		this->m_value += angle.m_value;

		return *this;
	}

	Degree& Degree::operator-=(const Degree& angle)
	{
		this->m_value -= angle.m_value;

		return *this;
	}

	Degree& Degree::operator*=(const float val)
	{
		this->m_value *= val;

		return *this;
	}

	Degree& Degree::operator/=(const float val)
	{
		this->m_value /= val;

		return *this;
	}

	void Degree::wrap(const bool useNegative)
	{
		if (useNegative)
			this->m_value = LibMath::wrap(this->m_value, -180, 180);
		else
			this->m_value = LibMath::wrap(this->m_value, 0, 360);
	}

	float Degree::degree(const bool useNegative) const
	{
		Degree tmp = Degree(*this);
		tmp.wrap(useNegative);

		return tmp.raw();
	}

	float Degree::radian(const bool useNegative) const
	{
		Radian rad = Radian(*this);
		rad.wrap(useNegative);
		return rad.raw();
	}

	float Degree::raw() const
	{
		return this->m_value;
	}

	bool operator==(const Degree& lhs, const Degree& rhs)
	{
		return floatEquals(lhs.degree(), rhs.degree());
	}

	bool operator==(const Degree& deg, Radian const& rad)
	{
		return rad == deg;
	}

	Degree operator-(const Degree& angle)
	{
		return Degree(-angle.raw());
	}

	Degree operator+(Degree lhs, const Degree& rhs)
	{
		return lhs += rhs;
	}

	Degree operator-(Degree lhs, const Degree& rhs)
	{
		return lhs -= rhs;
	}

	Degree operator*(Degree degree, const float x)
	{
		return degree *= x;
	}

	Degree operator/(Degree degree, const float x)
	{
		return degree /= x;
	}

	Degree Literal::operator ""_deg(const long double angle)
	{
		return Degree(static_cast<float>(angle));
	}

	Degree Literal::operator ""_deg(const unsigned long long int angle)
	{
		return Degree(static_cast<float>(angle));
	}
}
