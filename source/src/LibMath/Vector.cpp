#include "LibMath/Arithmetic.h"
#include "LibMath/Trigonometry.h"
#include "LibMath/Matrix.h"
#include "LibMath/Angle/Radian.h"

#include "LibMath/Vector.h"

#include <sstream>

namespace LibMath
{
	Vector2::Vector2(const float value) : Vector2(value, value)
	{
	}

	Vector2::Vector2(const float x, const float y) : m_x(x), m_y(y)
	{
	}

	Vector2 Vector2::zero()
	{
		return Vector2(0.f);
	}

	Vector2 Vector2::one()
	{
		return Vector2(1.f);
	}

	Vector2 Vector2::up()
	{
		return { 0.f, 1.f };
	}

	Vector2 Vector2::down()
	{
		return { 0.f, -1.f };
	}

	Vector2 Vector2::left()
	{
		return { -1.f, 0.f };
	}

	Vector2 Vector2::right()
	{
		return { 1.f, 0.f };
	}

	Vector2::operator Vector3() const
	{
		return { m_x, m_y, 0 };
	}

	float& Vector2::operator[](const int index)
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		default:
			throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
		}
	}

	float Vector2::operator[](const int index) const
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		default:
			throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
		}
	}

	Vector2& Vector2::operator+=(Vector2 const& other)
	{
		this->m_x += other.m_x;
		this->m_y += other.m_y;

		return *this;
	}

	Vector2& Vector2::operator-=(Vector2 const& other)
	{
		this->m_x -= other.m_x;
		this->m_y -= other.m_y;

		return *this;
	}

	Vector2& Vector2::operator*=(Vector2 const& other)
	{
		this->m_x *= other.m_x;
		this->m_y *= other.m_y;

		return *this;
	}

	Vector2& Vector2::operator/=(Vector2 const& other)
	{
		this->m_x /= other.m_x;
		this->m_y /= other.m_y;

		return *this;
	}

	Vector2& Vector2::operator+=(float const& value)
	{
		this->m_x += value;
		this->m_y += value;

		return *this;
	}

	Vector2& Vector2::operator-=(float const& value)
	{
		this->m_x -= value;
		this->m_y -= value;

		return *this;
	}

	Vector2& Vector2::operator*=(float const& value)
	{
		this->m_x *= value;
		this->m_y *= value;

		return *this;
	}

	Vector2& Vector2::operator/=(float const& value)
	{
		this->m_x /= value;
		this->m_y /= value;

		return *this;
	}

	Radian Vector2::angleFrom(Vector2 const& other) const
	{
		return acos(this->dot(other) / squareRoot(this->magnitudeSquared() * other.magnitudeSquared()));
	}

	Radian Vector2::signedAngleFrom(Vector2 const& other) const
	{
		const Radian angle = angleFrom(other);
		const float sign = other.cross(*this) >= 0 ? 1.f : -1.f;
		return angle * sign;
	}

	float Vector2::cross(Vector2 const& other) const
	{
		return this->m_x * other.m_y - this->m_y * other.m_x;
	}

	float Vector2::distanceFrom(Vector2 const& other) const
	{
		return squareRoot(this->distanceSquaredFrom(other));
	}

	float Vector2::distanceSquaredFrom(Vector2 const& other) const
	{
		const float xDist = other.m_x - this->m_x;
		const float yDist = other.m_y - this->m_y;

		return xDist * xDist + yDist * yDist;
	}

	float Vector2::dot(Vector2 const& other) const
	{
		return this->m_x * other.m_x + this->m_y * other.m_y;
	}

	bool Vector2::isLongerThan(Vector2 const& other) const
	{
		return this->magnitudeSquared() > other.magnitudeSquared();
	}

	bool Vector2::isShorterThan(Vector2 const& other) const
	{
		return this->magnitudeSquared() < other.magnitudeSquared();
	}

	bool Vector2::isUnitVector() const
	{
		return 1.f == this->magnitudeSquared();
	}

	float Vector2::magnitude() const
	{
		return squareRoot(this->magnitudeSquared());
	}

	float Vector2::magnitudeSquared() const
	{
		return this->m_x * this->m_x + this->m_y * this->m_y;
	}

	void Vector2::normalize()
	{
		*this /= this->magnitude();
	}

	Vector2 Vector2::normalized() const
	{
		Vector2 vec = *this;
		vec.normalize();
		return vec;
	}

	void Vector2::projectOnto(Vector2 const& normal)
	{
		*this = this->dot(normal) / normal.magnitudeSquared() * normal;
	}

	// Adapted from https://math.stackexchange.com/a/4325839
	void Vector2::reflectOnto(Vector2 const& other)
	{
		*this -= 2 * this->dot(other) / other.magnitudeSquared() * other;
	}

	void Vector2::rotate(const Radian& angle)
	{
		m_x = m_x * cos(angle) - m_y * sin(angle);
		m_y = m_x * sin(angle) + m_y * cos(angle);
	}

	void Vector2::scale(Vector2 const& other)
	{
		*this *= other;
	}

	std::string Vector2::string() const
	{
		std::ostringstream oss;

		oss << "{" << this->m_x << "," << this->m_y << "}";

		return oss.str();
	}

	std::string Vector2::stringLong() const
	{
		std::ostringstream oss;

		oss << "Vector2{ x:" << this->m_x << ", y:" << this->m_y << " }";

		return oss.str();
	}

	void Vector2::translate(Vector2 const& vect)
	{
		*this += vect;
	}

	bool Vector2::inBounds(Vector2 const& p_min, Vector2 const& p_max)const
	{
		return	this->m_x >= p_min.m_x && this->m_x <= p_max.m_x &&
				this->m_y >= p_min.m_y && this->m_y <= p_max.m_y;
	}

	bool operator==(Vector2 const& lhs, Vector2 const& rhs)
	{
		return floatEquals(lhs.m_x, rhs.m_x)
			&& floatEquals(lhs.m_y, rhs.m_y);
	}

	bool operator!=(Vector2 const& p_vector2, Vector2 const& p_vector3)
	{
		return !(p_vector2 == p_vector3);
	}

	Vector2 operator-(const Vector2& vect)
	{
		return vect * -1;
	}

	Vector2 operator+(Vector2 left, Vector2 const& right)
	{
		return left += right;
	}

	Vector2 operator-(Vector2 left, Vector2 const& right)
	{
		return left -= right;
	}

	Vector2 operator*(Vector2 left, Vector2 const& right)
	{
		return left *= right;
	}

	Vector2 operator/(Vector2 left, Vector2 const& right)
	{
		return left /= right;
	}

	Vector2 operator+(Vector2 vect, float const& val)
	{
		return vect += val;
	}

	Vector2 operator-(Vector2 vect, float const& val)
	{
		return vect -= val;
	}

	Vector2 operator*(Vector2 vect, float const& val)
	{
		return vect *= val;
	}

	Vector2 operator*(float const& val, Vector2 vect)
	{
		return vect *= val;
	}

	Vector2 operator/(Vector2 vect, float const& val)
	{
		return vect /= val;
	}

	std::ostream& operator<<(std::ostream& stream, Vector2 const& vect)
	{
		stream << vect.string();

		return stream;
	}

	std::istream& operator>>(std::istream& stream, Vector2& vect)
	{
		std::string line;

		std::getline(stream, line, '}');

		int component = 0;
		size_t valStart = 0;

		do
		{
			if (valStart == std::string::npos)
				break;

			if (line[valStart] == '{' || std::isspace(line[valStart]))
			{
				valStart++;
				continue;
			}

			if (line[valStart] != '-' && !std::isdigit(line[valStart]))
				break;

			vect[component] = std::stof(line.substr(valStart));

			valStart = line.find(',', valStart) + 1;
			component++;
		} while (component < 2 && valStart != 0);

		if (component != 2)
			vect = Vector2::zero();

		return stream;
	}

	Vector3::Vector3(const float value) : Vector3(value, value, value)
	{
	}

	Vector3::Vector3(const float x, const float y, const float z) : m_x(x), m_y(y), m_z(z)
	{
	}

	//Vector3::Vector3(Vector2 const& other) : Vector3(other.m_x, other.m_y, 0)
	//{
	//}

	Vector3 Vector3::zero()
	{
		return Vector3(0.f);
	}

	Vector3 Vector3::one()
	{
		return Vector3(1.f);
	}

	Vector3 Vector3::up()
	{
		return {0.f, 1.f, 0.f};
	}

	Vector3 Vector3::down()
	{
		return {0.f, -1.f, 0.f};
	}

	Vector3 Vector3::left()
	{
		return {-1.f, 0.f, 0.f};
	}

	Vector3 Vector3::right()
	{
		return {1.f, 0.f, 0.f};
	}

	Vector3 Vector3::front()
	{
		return {0.f, 0.f, 1.f};
	}

	Vector3 Vector3::back()
	{
		return {0.f, 0.f, -1.f};
	}

	float& Vector3::operator[](const int index)
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		case 2:
			return this->m_z;
		default:
			throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
		}
	}

	float Vector3::operator[](const int index) const
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		case 2:
			return this->m_z;
		default:
			throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
		}
	}

	Vector3& Vector3::operator+=(Vector3 const& other)
	{
		this->m_x += other.m_x;
		this->m_y += other.m_y;
		this->m_z += other.m_z;

		return *this;
	}

	Vector3& Vector3::operator-=(Vector3 const& other)
	{
		this->m_x -= other.m_x;
		this->m_y -= other.m_y;
		this->m_z -= other.m_z;

		return *this;
	}

	Vector3& Vector3::operator*=(Vector3 const& other)
	{
		this->m_x *= other.m_x;
		this->m_y *= other.m_y;
		this->m_z *= other.m_z;

		return *this;
	}

	Vector3& Vector3::operator/=(Vector3 const& other)
	{
		this->m_x /= other.m_x;
		this->m_y /= other.m_y;
		this->m_z /= other.m_z;

		return *this;
	}

	Vector3& Vector3::operator+=(float const& value)
	{
		this->m_x += value;
		this->m_y += value;
		this->m_z += value;

		return *this;
	}

	Vector3& Vector3::operator-=(float const& value)
	{
		this->m_x -= value;
		this->m_y -= value;
		this->m_z -= value;

		return *this;
	}

	Vector3& Vector3::operator*=(float const& value)
	{
		this->m_x *= value;
		this->m_y *= value;
		this->m_z *= value;

		return *this;
	}

	Vector3& Vector3::operator/=(float const& value)
	{
		this->m_x /= value;
		this->m_y /= value;
		this->m_z /= value;

		return *this;
	}

	Radian Vector3::angleFrom(Vector3 const& other) const
	{
		return acos(this->dot(other) / squareRoot(this->magnitudeSquared() * other.magnitudeSquared()));
	}

	Radian Vector3::signedAngleFrom(Vector3 const& other, Vector3 const& axis) const
	{
		const Radian angle = angleFrom(other);
		const Vector3 cross = other.cross(*this);
		const float sign = axis.m_x * cross.m_x + axis.m_y * cross.m_y + axis.m_z * cross.m_z >= 0 ? 1.f : -1.f;
		return angle * sign;
	}

	Vector3 Vector3::cross(Vector3 const& other) const
	{
		return {
			this->m_y * other.m_z - this->m_z * other.m_y,
			this->m_z * other.m_x - this->m_x * other.m_z,
			this->m_x * other.m_y - this->m_y * other.m_x
		};
	}

	float Vector3::distanceFrom(Vector3 const& other) const
	{
		return squareRoot(this->distanceSquaredFrom(other));
	}

	float Vector3::distanceSquaredFrom(Vector3 const& other) const
	{
		const float xDist = other.m_x - this->m_x;
		const float yDist = other.m_y - this->m_y;
		const float zDist = other.m_z - this->m_z;

		return xDist * xDist + yDist * yDist + zDist * zDist;
	}

	float Vector3::distance2DFrom(Vector3 const& other) const
	{
		return squareRoot(this->distance2DSquaredFrom(other));
	}

	float Vector3::distance2DSquaredFrom(Vector3 const& other) const
	{
		const float xDist = other.m_x - this->m_x;
		const float yDist = other.m_y - this->m_y;

		return xDist * xDist + yDist * yDist;
	}

	float Vector3::dot(Vector3 const& other) const
	{
		return this->m_x * other.m_x + this->m_y * other.m_y + this->m_z * other.m_z;
	}

	bool Vector3::isLongerThan(Vector3 const& other) const
	{
		return this->magnitudeSquared() > other.magnitudeSquared();
	}

	bool Vector3::isShorterThan(Vector3 const& other) const
	{
		return this->magnitudeSquared() < other.magnitudeSquared();
	}

	bool Vector3::isUnitVector() const
	{
		return floatEquals(1.f, this->magnitudeSquared());
	}

	float Vector3::magnitude() const
	{
		return squareRoot(this->magnitudeSquared());
	}

	float Vector3::magnitudeSquared() const
	{
		return this->m_x * this->m_x + this->m_y * this->m_y + this->m_z * this->m_z;
	}

	void Vector3::normalize()
	{
		*this /= this->magnitude();
	}

	Vector3 Vector3::normalized() const
	{
		Vector3 vec = *this;
		vec.normalize();
		return vec;
	}

	void Vector3::projectOnto(Vector3 const& normal)
	{
		*this = this->dot(normal) / normal.magnitudeSquared() * normal;
	}

	// Adapted from https://math.stackexchange.com/a/4325839
	void Vector3::reflectOnto(Vector3 const& other)
	{
		*this -= 2 * this->dot(other) / other.magnitudeSquared() * other;
	}

	void Vector3::rotate(const Radian& xAngle, const Radian& yAngle, const Radian& zAngle)
	{
		const Matrix4 rotationMat = Matrix4::rotationEuler(xAngle, yAngle, zAngle);
		const Vector4 vec4 = rotationMat * Vector4( m_x, m_y, m_z, 1 );

		m_x = vec4.m_x;
		m_y = vec4.m_y;
		m_z = vec4.m_z;
	}

	void Vector3::rotate(const Radian& angle, Vector3 const& axis)
	{
		const Matrix4 rotationMat = Matrix4::rotation(angle, axis);
		const Vector4 vec4 = rotationMat * Vector4(m_x, m_y, m_z, 1);

		m_x = vec4.m_x;
		m_y = vec4.m_y;
		m_z = vec4.m_z;
	}

	void Vector3::scale(Vector3 const& other)
	{
		*this *= other;
	}

	std::string Vector3::string() const
	{
		std::ostringstream oss;

		oss << "{" << this->m_x << "," << this->m_y << "," << this->m_z << "}";

		return oss.str();
	}

	std::string Vector3::stringLong() const
	{
		std::ostringstream oss;

		oss << "Vector3{ x:" << this->m_x << ", y:" << this->m_y << ", z:"
			<< this->m_z << " }";

		return oss.str();
	}

	void Vector3::translate(Vector3 const& vect)
	{
		*this += vect;
	}

	bool operator==(Vector3 const& lhs, Vector3 const& rhs)
	{
		return floatEquals(lhs.m_x, rhs.m_x)
			&& floatEquals(lhs.m_y, rhs.m_y)
			&& floatEquals(lhs.m_z, rhs.m_z);
	}

	bool operator!=(Vector3 const& p_vector3, Vector3 const& p_vector4)
	{
		return !(p_vector3 == p_vector4);
	}

	Vector3 operator-(const Vector3& vect)
	{
		return { -vect.m_x, -vect.m_y, -vect.m_z };
	}

	Vector3 operator+(Vector3 left, Vector3 const& right)
	{
		return left += right;
	}

	Vector3 operator-(Vector3 left, Vector3 const& right)
	{
		return left -= right;
	}

	Vector3 operator*(Vector3 left, Vector3 const& right)
	{
		return left *= right;
	}

	Vector3 operator/(Vector3 left, Vector3 const& right)
	{
		return left /= right;
	}

	Vector3 operator+(Vector3 vect, float const& val)
	{
		return vect += val;
	}

	Vector3 operator-(Vector3 vect, float const& val)
	{
		return vect -= val;
	}

	Vector3 operator*(Vector3 vect, float const& val)
	{
		return vect *= val;
	}

	Vector3 operator*(float const& val, Vector3 vect)
	{
		return vect *= val;
	}

	Vector3 operator/(Vector3 vect, float const& val)
	{
		return vect /= val;
	}

	std::ostream& operator<<(std::ostream& stream, Vector3 const& vect)
	{
		return stream << vect.string();
	}

	std::istream& operator>>(std::istream& stream, Vector3& vect)
	{
		std::string line;

		std::getline(stream, line, '}');

		int component = 0;
		size_t valStart = 0;

		do
		{
			if (valStart == std::string::npos)
				break;

			if (line[valStart] == '{' || std::isspace(line[valStart]))
			{
				valStart++;
				continue;
			}

			if (line[valStart] != '-' && !std::isdigit(line[valStart]))
				break;

			vect[component] = std::stof(line.substr(valStart));

			valStart = line.find(',', valStart) + 1;
			component++;
		} while (component < 3 && valStart != 0);

		if (component != 3)
			vect = Vector3::zero();

		return stream;
	}

	Vector4::Vector4(const float value) :
		Vector4(value, value, value, value)
	{
	}

	Vector4::Vector4(const float x, const float y, const float z, const float w) :
		Vector3(x, y, z), m_w(w)
	{
	}

	Vector4::Vector4(Vector3 const& v, float w) :
		Vector3(v), m_w(w)
	{
	}

	Vector4 Vector4::zero()
	{
		return { 0.f, 0.f, 0.f, 0.f };
	}

	Vector4 Vector4::one()
	{
		return { 1.f, 1.f, 1.f, 1.f };
	}

	Vector4 Vector4::up()
	{
		return { 0.f, 1.f, 0.f, 0.f };
	}

	Vector4 Vector4::down()
	{
		return { 0.f, -1.f, 0.f, 0.f };
	}

	Vector4 Vector4::left()
	{
		return { -1.f, 0.f, 0.f, 0.f };
	}

	Vector4 Vector4::right()
	{
		return { 1.f, 0.f, 0.f, 0.f };
	}

	Vector4 Vector4::front()
	{
		return { 0.f, 0.f, 1.f, 0.f };
	}

	Vector4 Vector4::back()
	{
		return { 0.f, 0.f, -1.f, 0.f };
	}

	float& Vector4::operator[](const int index)
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		case 2:
			return this->m_z;
		case 3:
			return this->m_w;
		default:
			throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
		}
	}

	float Vector4::operator[](const int index) const
	{
		switch (index)
		{
		case 0:
			return this->m_x;
		case 1:
			return this->m_y;
		case 2:
			return this->m_z;
		case 3:
			return this->m_w;
		default:
			throw std::out_of_range("Invalid index \"" + std::to_string(index) + "\" received");
		}
	}

	Vector4& Vector4::operator+=(Vector4 const& other)
	{
		m_x += other.m_x;
		m_y += other.m_y;
		m_z += other.m_z;
		m_w += other.m_w;

		return *this;
	}

	Vector4& Vector4::operator-=(Vector4 const& other)
	{
		m_x -= other.m_x;
		m_y -= other.m_y;
		m_z -= other.m_z;
		m_w -= other.m_w;

		return *this;
	}

	Vector4& Vector4::operator*=(Vector4 const& other)
	{
		m_x *= other.m_x;
		m_y *= other.m_y;
		m_z *= other.m_z;
		m_w *= other.m_w;

		return *this;
	}

	Vector4& Vector4::operator/=(Vector4 const& other)
	{
		m_x /= other.m_x;
		m_y /= other.m_y;
		m_z /= other.m_z;
		m_w /= other.m_w;

		return *this;
	}

	Vector4& Vector4::operator+=(float const& value)
	{
		m_x += value;
		m_y += value;
		m_z += value;
		m_w += value;

		return *this;
	}

	Vector4& Vector4::operator-=(float const& value)
	{
		m_x -= value;
		m_y -= value;
		m_z -= value;
		m_w -= value;

		return *this;
	}

	Vector4& Vector4::operator*=(float const& value)
	{
		m_x *= value;
		m_y *= value;
		m_z *= value;
		m_w *= value;

		return *this;
	}

	Vector4& Vector4::operator/=(float const& value)
	{
		m_x /= value;
		m_y /= value;
		m_z /= value;
		m_w /= value;

		return *this;
	}

	float Vector4::dot(Vector4 const& other) const
	{
		return this->m_x * other.m_x +
			this->m_y * other.m_y +
			this->m_z * other.m_z +
			this->m_w * other.m_w;
	}

	float Vector4::magnitudeSquared() const
	{
		return this->m_x * this->m_x +
			this->m_y * this->m_y +
			this->m_z * this->m_z +
			this->m_w * this->m_w;
	}

	Vector4 Vector4::normalized() const
	{
		return *this / magnitude();
	}

	std::string Vector4::string() const
	{
		std::ostringstream oss;

		oss << "{" << this->m_x << "," << this->m_y
			<< "," << this->m_z << "," << this->m_w << "}";

		return oss.str();
	}

	std::string Vector4::stringLong() const
	{
		std::ostringstream oss;

		oss << "Vector4{ x:" << this->m_x << ", y:" << this->m_y
			<< ", z:" << this->m_z << ", w:" << this->m_w << " }";

		return oss.str();
	}

	bool operator==(Vector4 const& left, Vector4 const& right)
	{
		return floatEquals(left.m_x, right.m_x) &&
			floatEquals(left.m_y, right.m_y) &&
			floatEquals(left.m_z, right.m_z) &&
			floatEquals(left.m_w, right.m_w);
	}

	bool operator!=(Vector4 const& left, Vector4 const& right)
	{
		return !(left == right);
	}

	Vector4 operator-(const Vector4& vector)
	{
		return { -vector.m_x, -vector.m_y, -vector.m_z, -vector.m_w };
	}

	Vector4 operator+(Vector4 left, Vector4 const& right)
	{
		return left += right;
	}

	Vector4 operator-(Vector4 left, Vector4 const& right)
	{
		return left -= right;
	}

	Vector4 operator*(Vector4 left, Vector4 const& right)
	{
		return left *= right;
	}

	Vector4 operator/(Vector4 vector, Vector4 const& value)
	{
		return vector /= value;
	}

	Vector4 operator+(Vector4 vector, float const& value)
	{
		return vector += value;
	}

	Vector4 operator-(Vector4 vector, float const& value)
	{
		return vector -= value;
	}

	Vector4 operator*(Vector4 vector, float const& scalar)
	{
		return vector *= scalar;
	}

	Vector4 operator*(float const& scalar, Vector4 vector)
	{
		return vector *= scalar;
	}

	Vector4 operator/(Vector4 vector, float const& scalar)
	{
		return vector /= scalar;
	}

	std::ostream& operator<<(std::ostream& stream, Vector4 const& vector)
	{
		return stream << vector.string();
	}

	std::istream& operator>>(std::istream& stream, Vector4& vector)
	{
		std::string line;

		std::getline(stream, line, '}');

		int component = 0;
		size_t valStart = 0;

		do
		{
			if (valStart == std::string::npos)
				break;

			if (line[valStart] == '{' || std::isspace(line[valStart]))
			{
				valStart++;
				continue;
			}

			if (line[valStart] != '-' && !std::isdigit(line[valStart]))
				break;

			vector[component] = std::stof(line.substr(valStart));

			valStart = line.find(',', valStart) + 1;
			component++;
		} while (component < 4 && valStart != 0);

		if (component != 4)
			vector = Vector4::zero();

		return stream;
	}
}
