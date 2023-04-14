#ifndef __LIBMATH__VECTOR__VECTOR2_H__
#define __LIBMATH__VECTOR__VECTOR2_H__

#include <iostream>
#include <string>

namespace LibMath
{
	class Radian;
	class Vector3;

	class Vector2
	{
	public:
						Vector2() = default;
		explicit		Vector2(float);									// set all the component to the same value
						Vector2(float, float);							// set all component individually
						Vector2(Vector2 const&) = default;
						Vector2(Vector2&&) noexcept = default;
						~Vector2() = default;

		static Vector2	zero();											// return a vector with all its component set to 0
		static Vector2	one();											// return a vector with all its component set to 1
		static Vector2	up();											// return a unit vector pointing upward
		static Vector2	down();											// return a unit vector pointing downward
		static Vector2	left();											// return a unit vector pointing left
		static Vector2	right();										// return a unit vector pointing right

						operator Vector3() const;						// Vector3 vect = Vector2{ 0.5, 3 };		// implicit conversion from Vector2 to Vector3

		Vector2&		operator=(Vector2 const&) = default;
		Vector2&		operator=(Vector2&&) noexcept = default;

		float&			operator[](int);								// return this vector component value
		float			operator[](int) const;							// return this vector component value

		Vector2&		operator+=(Vector2 const&);						// addition component wise
		Vector2&		operator-=(Vector2 const&);						// subtraction component wise
		Vector2&		operator*=(Vector2 const&);						// multiplication component wise
		Vector2&		operator/=(Vector2 const&);						// division component wise

		Vector2&		operator+=(float const&);						// add a value to all components
		Vector2&		operator-=(float const&);						// subtract a value from all components
		Vector2&		operator*=(float const&);						// multiply all components by a value
		Vector2&		operator/=(float const&);						// divide all components by a value

		Radian			angleFrom(Vector2 const&) const;				// return smallest angle between 2 vectors
		Radian			signedAngleFrom(Vector2 const& other) const;	// return signed angle between 2 vectors

		float			cross(Vector2 const&) const;					// return a copy of the cross product result

		float			distanceFrom(Vector2 const&) const;				// return distance between 2 points
		float			distanceSquaredFrom(Vector2 const&) const;		// return square value of the distance between 2 points

		float			dot(Vector2 const&) const;						// return dot product result

		bool			isLongerThan(Vector2 const&) const;				// return true if this vector magnitude is greater than the other
		bool			isShorterThan(Vector2 const&) const;			// return true if this vector magnitude is less than the other

		bool			isUnitVector() const;							// return true if this vector magnitude is 1

		float			magnitude() const;								// return vector magnitude
		float			magnitudeSquared() const;						// return square value of the vector magnitude

		void			normalize();									// scale this vector to have a magnitude of 1
		Vector2			normalized() const;								// returns this vector scaled to have a magnitude of 1

		void			projectOnto(Vector2 const&);					// project this vector onto an other

		void			reflectOnto(Vector2 const&);					// reflect this vector by an other

		void			rotate(const Radian&);							// rotate this vector using an angle in Radian

		void			scale(Vector2 const&);							// scale this vector by a given factor

		std::string		string() const;									// return a string representation of this vector
		std::string		stringLong() const;								// return a verbose string representation of this vector

		void			translate(Vector2 const&);						// offset this vector by a given distance
		bool			inBounds(Vector2 const&, Vector2 const&) const;

		float m_x = 0;
		float m_y = 0;
	};

	bool			operator==(Vector2 const&, Vector2 const&);			// Vector2{ 1 } == Vector2::one()				// true				// return whether 2 vectors have the same component
	bool			operator!=(Vector2 const&, Vector2 const&);			// Vector2{ 1 } != Vector2::zero()				// true				// return whether 2 vectors have different components

	Vector2			operator-(const Vector2&);							// -Vector2{ .5, 1.5 }							// { -.5, -1.5 }	// return a copy of a vector with all its component inverted

	Vector2			operator+(Vector2, Vector2 const&);					// Vector2{ .5, 1.5 } + Vector2::one()			// { 1.5, 2.5 }		// add 2 vectors component wise
	Vector2			operator-(Vector2, Vector2 const&);					// Vector2{ .5, 1.5 } - Vector2{ 1 }			// { -.5, .5 }		// subtract 2 vectors component wise
	Vector2			operator*(Vector2, Vector2 const&);					// Vector2{ .5, 1.5 } * Vector2::zero()			// { 0, 0 }			// multiply 2 vectors component wise
	Vector2			operator/(Vector2, Vector2 const&);					// Vector2{ .5, 1.5 } / Vector2{ 2 }			// { .25, .75 }		// divide 2 vectors component wise

	Vector2			operator+(Vector2, float const&);					// Vector2{ .5, 1.5 } + 1						// { 1.5, 2.5 }		// add a value to all components of a vector
	Vector2			operator-(Vector2, float const&);					// Vector2{ .5, 1.5 } - 1						// { -.5, .5 }		// subtract a value from all components of a vector

	Vector2			operator*(Vector2, float const&);					// Vector2{ .5, 1.5 } * 0						// { 0, 0 }			// multiply all components of a vector by a value
	Vector2			operator*(float const&, Vector2);					// 0 * Vector2{ .5, 1.5 }						// { 0, 0 }			// multiply all components of a vector by a value

	Vector2			operator/(Vector2, float const&);					// Vector2{ .5, 1.5 } / 2						// { .25, .75 }		// divide all components of a vector by a value

	std::ostream&	operator<<(std::ostream&, Vector2 const&);			// cout << Vector2{ .5, 1.5 }					// add a vector string representation to an output stream
	std::istream&	operator>>(std::istream&, Vector2&);				// ifstream file{ save.txt }; file >> vector;	// parse a string representation from an input stream into a vector
}

#endif // !__LIBMATH__VECTOR__VECTOR2_H__