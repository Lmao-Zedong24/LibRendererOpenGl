#ifndef __LIBMATH__VECTOR__VECTOR3_H__
#define __LIBMATH__VECTOR__VECTOR3_H__

#include <iostream>
#include <string>

namespace LibMath
{
	class Radian;
	//class Vector2;

	class Vector3
	{
	public:
						Vector3() = default;
		explicit		Vector3(float);									// set all the component to the same value
						Vector3(float, float, float);					// set all component individually
						//Vector3(Vector2 const& other);
						Vector3(Vector3 const& other) = default;
						Vector3(Vector3&& other) = default;
						~Vector3() = default;

		static Vector3	zero();											// return a vector with all its component set to 0
		static Vector3	one();											// return a vector with all its component set to 1
		static Vector3	up();											// return a unit vector pointing upward
		static Vector3	down();											// return a unit vector pointing downward
		static Vector3	left();											// return a unit vector pointing left
		static Vector3	right();										// return a unit vector pointing right
		static Vector3	front();										// return a unit vector pointing forward
		static Vector3	back();											// return a unit vector pointing backward

		Vector3&		operator=(Vector3 const& other) = default;
		Vector3&		operator=(Vector3&& other) = default;

		float&			operator[](int);								// return this vector component value
		float			operator[](int) const;							// return this vector component value

		Vector3&		operator+=(Vector3 const& other);				// addition component wise
		Vector3&		operator-=(Vector3 const& other);				// subtraction component wise
		Vector3&		operator*=(Vector3 const& other);				// multiplication component wise
		Vector3&		operator/=(Vector3 const& other);				// division component wise

		Vector3&		operator+=(float const&);						// add a value to all components
		Vector3&		operator-=(float const&);						// subtract a value from all components
		Vector3&		operator*=(float const&);						// multiply all components by a value
		Vector3&		operator/=(float const&);						// divide all components by a value

		Radian			angleFrom(Vector3 const& other) const;			// return smallest angle between 2 vectors
		Radian			signedAngleFrom(Vector3 const& other,
							Vector3 const& axis) const;					// return signed angle between 2 vectors around 

		Vector3			cross(Vector3 const&) const;					// return a copy of the cross product result

		float			distanceFrom(Vector3 const&) const;				// return distance between 2 points
		float			distanceSquaredFrom(Vector3 const&) const;		// return square value of the distance between 2 points
		float			distance2DFrom(Vector3 const&) const;			// return the distance between 2 points on the X-Y axis only
		float			distance2DSquaredFrom(Vector3 const&) const;	// return the square value of the distance between 2 points points on the X-Y axis only

		float			dot(Vector3 const&) const;						// return dot product result

		bool			isLongerThan(Vector3 const&) const;				// return true if this vector magnitude is greater than the other
		bool			isShorterThan(Vector3 const&) const;			// return true if this vector magnitude is less than the other

		bool			isUnitVector() const;							// return true if this vector magnitude is 1

		float			magnitude() const;								// return vector magnitude
		float			magnitudeSquared() const;						// return square value of the vector magnitude

		void			normalize();									// scale this vector to have a magnitude of 1
		Vector3			normalized() const;								// returns this vector scaled to have a magnitude of 1

		void			projectOnto(Vector3 const&);					// project this vector onto an other

		void			reflectOnto(Vector3 const&);					// reflect this vector by an other

		void			rotate(const Radian&, const Radian&,
							const Radian&);								// rotate this vector using euler angle apply in the z, x, y order
		void			rotate(const Radian&, Vector3 const&);			// rotate this vector around an arbitrary axis
		//void			rotate(Quaternion const&); todo quaternion		// rotate this vector using a quaternion rotor

		void			scale(Vector3 const&);							// scale this vector by a given factor

		std::string		string() const;									// return a string representation of this vector
		std::string		stringLong() const;								// return a verbose string representation of this vector

		void			translate(Vector3 const&);						// offset this vector by a given distance

		float m_x = 0;
		float m_y = 0;
		float m_z = 0;
	};

	bool			operator==(Vector3 const&, Vector3 const&);			// Vector3{ 1 } == Vector3::one()				// true					// return whether 2 vectors have the same components
	bool			operator!=(Vector3 const&, Vector3 const&);			// Vector3{ 1 } != Vector3::zero()				// true					// return whether 2 vectors have different components

	Vector3			operator-(const Vector3&);							// -Vector3{ .5, 1.5, -2.5 }					// { -.5, -1.5, 2.5 }	// return a copy of a vector with all its component inverted

	Vector3			operator+(Vector3, Vector3 const&);					// Vector3{ .5, 1.5, -2.5 } + Vector3::one()	// { 1.5, 2.5, -1.5 }	// add 2 vectors component wise
	Vector3			operator-(Vector3, Vector3 const&);					// Vector3{ .5, 1.5, -2.5 } - Vector3{ 1 }		// { -.5, .5, -3.5 }	// subtract 2 vectors component wise
	Vector3			operator*(Vector3, Vector3 const&);					// Vector3{ .5, 1.5, -2.5 } * Vector3::zero()	// { 0, 0, 0 }			// multiply 2 vectors component wise
	Vector3			operator/(Vector3, Vector3 const&);					// Vector3{ .5, 1.5, -2.5 } / Vector3{ 2 }		// { .25, .75, -1.25 }	// divide 2 vectors component wise

	Vector3			operator+(Vector3, float const&);					// Vector3{ .5, 1.5, -2.5 } + 1					// { 1.5, 2.5, -1.5 }	// add a value to all components of a vector
	Vector3			operator-(Vector3, float const&);					// Vector3{ .5, 1.5, -2.5 } - 1					// { -.5, .5, -3.5 }	// subtract a value from all components of a vector

	Vector3			operator*(Vector3, float const&);					// Vector3{ .5, 1.5, -2.5 } * 0					// { 0, 0, 0 }			// multiply all components of a vector by a value
	Vector3			operator*(float const&, Vector3);					// 0 * Vector3{ .5, 1.5, -2.5 }					// { 0, 0, 0 }			// multiply all components of a vector by a value

	Vector3			operator/(Vector3, float const&);					// Vector3{ .5, 1.5, -2.5 } / 2					// { .25, .75, -1.25 }	// divide all components of a vector by a value

	std::ostream&	operator<<(std::ostream&, Vector3 const&);			// cout << Vector3{ .5, 1.5, -2.5 }				// add a vector string representation to an output stream
	std::istream&	operator>>(std::istream&, Vector3&);				// ifstream file{ save.txt }; file >> vector;	// parse a string representation from an input stream into a vector
}

#endif // !__LIBMATH__VECTOR__VECTOR3_H__
