#pragma once

#include <LibMath/header/Matrix/Matrix4.h>
#include <LibMath/header/Vector/Vector3.h>
#include <LibMath/header/Angle/Radian.h>
#include <LibMath/header/Vector/Vector4.h>


namespace Exceptions
{
	class DivideByZero : public std::exception
	{
	public:
		/**
			* \brief Creates a divide by zero exception with a default message
			*/
		DivideByZero() :
			std::exception("Divide By Zero") {}

		/**
			* \brief Creates a divide by zero exception with a given message
			* \param message The message of the exception
			*/
		DivideByZero(char const* message) :
			std::exception(message) {}

		/**
			* \brief Creates a divide by zero exception with a given message
			* \param message The message of the exception
			*/
		DivideByZero(const std::string& message) :
			std::exception(message.c_str()) {}
	};

	class GimbalLock : public std::exception
	{
	public:
		/**
			* \brief Creates an invalid index buffer exception with a default message
			*/
		GimbalLock() :
			std::exception("Gimbal Lock") {}


		/**
			* \brief Creates a Gimbal Lock exception with a given message
			* \param message The message of the exception
			*/
		GimbalLock(char const* message) :
			std::exception(message) {}

		/**
			* \brief Creates a Gimbal Lock exception with a given message
			* \param message The message of the exception
			*/
		GimbalLock(const std::string& message) :
			std::exception(message.c_str()) {}
	};
}

class Transform
{
	// Syntactic sugar for shorter lines
	using Mat4 = LibMath::Matrix4;
	using Vec3 = LibMath::Vector3;
	using Vec4 = LibMath::Vector4;
	using Rad = LibMath::Radian;

public:
	Transform();
	Transform(Mat4 p_transform);
	~Transform() = default;
#pragma region Getters
	/// <summary>
	/// Get the Mat4 that Scales, Rotates and Translates the Mesh
	/// </summary>
	/// <returns></returns>
	Mat4 getTransform() const;

	/// <summary>
	/// Get the EntityTree's global position
	/// </summary>
	/// <returns></returns>
	Vec3 getPosition() const;

	/// <summary>
	/// Get the xyz's scaling factors as a Vector3
	/// </summary>
	/// <returns></returns>
	Vec3 getScale() const;

	/// <summary>
	/// Get the x axis' scaling factor
	/// </summary>
	/// <returns></returns>
	float getScaleX() const;

	/// <summary>
	/// Get the y axis' scaling factor
	/// </summary>
	/// <returns></returns>
	float getScaleY() const;

	/// <summary>
	/// Get the z axis' scaling factor
	/// </summary>
	/// <returns></returns>
	float getScaleZ() const;

	/// <summary>
	/// Get the EntityTree's rotation around each axis in radians in a Vector3
	/// </summary>
	/// <returns></returns>
	Vec3 getRotationEulerAngles() const;

	/// <summary>
	/// Get the Rightwards, Upwards and Forwards Vectors in a Mat4
	/// </summary>
	/// <returns></returns>
	Mat4 getRotation() const;
#pragma endregion

#pragma region LocalDirections
	/// <summary>
	/// Get local rightward Vector3
	/// </summary>
	/// <returns></returns>
	Vec3 getRightward() const;

	/// <summary>
	/// Get the inverse of the rightward Vector3
	/// </summary>
	/// <returns></returns>
	Vec3 getLeftward() const;

	/// <summary>
	/// Get local upward Vector3
	/// </summary>
	/// <returns></returns>
	Vec3 getUpward() const;

	/// <summary>
	/// Get the inverse of the upwards Vector3
	/// </summary>
	/// <returns></returns>
	Vec3 getDownward() const;

	/// <summary>
	/// Get local forward Vector3
	/// </summary>
	/// <returns></returns>
	Vec3 getForward() const;

	/// <summary>
	/// Get the inverse of the upwards Vector3
	/// </summary>
	/// <returns></returns>
	Vec3 getBackward() const;
#pragma endregion

#pragma region Transformations
	/// <summary>
	/// Replaces transform Mat4
	/// </summary>
	/// <param name="p_transform">: Copy Mat4</param>
	/// <returns></returns>
	void	setTransform(const Mat4& p_transform);

	/// <summary>
	/// Translate position by parameters
	/// </summary>
	/// <param name="p_x">: global x axis</param>
	/// <param name="p_y">: global y axis</param>
	/// <param name="p_z">: global z axis</param>
	/// <returns></returns>
	Transform& translate(float p_x, float p_y, float p_z);

	/// <summary>
	/// Translate position by parameters in global axis
	/// </summary>
	/// <param name="p_x">: global x axis</param>
	/// <param name="p_y">: global y axis</param>
	/// <param name="p_z">: global z axis</param>
	/// <returns></returns>
	Transform& globalTranslate(float p_x, float p_y, float p_z);

	/// <summary>
	/// Translate position by parameters
	/// </summary>
	/// <param name="p_translation">: translation vector</param>
	/// <returns></returns>
	Transform& translate(const Vec3& p_translation);

	//EntityTree& translateLocally(float p_x, float p_y, float p_z); // ???

	/// <summary>
	/// Multiply scaling factor by parameters
	/// </summary>
	/// <param name="p_x">: local x axis</param>
	/// <param name="p_y">: local y axis</param>
	/// <param name="p_z">: local z axis</param>
	/// <returns></returns>
	Transform& scale(float p_x, float p_y, float p_z);

	/// <summary>
	/// Multiply all 3 scaling factors by parameter
	/// </summary>
	/// <param name="p_x">: local x axis</param>
	/// <param name="p_y">: local y axis</param>
	/// <param name="p_z">: local z axis</param>
	/// <returns></returns>
	Transform& scale(float p_f);

	/// <summary>
	/// Rotate around axes by angles in radians
	/// </summary>
	/// <param name="p_x">: local x axis</param>
	/// <param name="p_y">: local y axis</param>
	/// <param name="p_z">: local z axis</param>
	/// <returns></returns>
	Transform& rotateEulerAngles(const Rad& p_x, const Rad& p_y, const Rad& p_z);

	/// <summary>
	/// Overrides position
	/// </summary>
	/// <param name="p_x">: global x axis</param>
	/// <param name="p_y">: global y axis</param>
	/// <param name="p_z">: global z axis</param>
	/// <returns></returns>
	Transform& setPosition(float p_x, float p_y, float p_z);

	/// <summary>
	/// Overrides scaling factor
	/// </summary>
	/// <param name="p_x">: local x axis</param>
	/// <param name="p_y">: local y axis</param>
	/// <param name="p_z">: local z axis</param>
	/// <returns></returns>
	Transform& setScale(float p_x, float p_y, float p_z);

	/// <summary>
	/// Overrides rotation with angles in radians
	/// </summary>
	/// <param name="p_x">: local x axis</param>
	/// <param name="p_y">: local y axis</param>
	/// <param name="p_z">: local z axis</param>
	/// <returns></returns>
	Transform& setRotationEulerAngles(const Rad& p_x, const Rad& p_y, const Rad& p_z);
#pragma endregion

private:
	Mat4		m_transform;

	/*
	* d = M * s
	*
	* SourceColumnVector :			s = (x, y, z)
	* DestinationColumnVector :		d = (x, y, z)
	*
	*
	*
	* M = T * R * S
	*
	*		|		sx * rx		sy * ux		sz * fx		  tx 	 |
	* M =	|		sx * ry		sy * uy		sz * fy		  ty 	 |
	*		|		sx * rz		sy * uz		sz * fz		  tz 	 |
	*		|		   0		   0		   0		   1 	 |
	*
	* 		|		   1		   0		   0		  tx 	 |
	* T =	|		   0		   1 		   0		  ty 	 |
	*		|		   0		   0		   1		  tz 	 |
	*		|		   0		   0		   0		   1 	 |
	*
	* 		|		  sx		   0		   0		   0 	 |
	* S =	|		   0		  sy 		   0		   0 	 |
	*		|		   0		   0		  sz		   0 	 |
	*		|		   0		   0		   0		   1 	 |
	*
	*		|		  rx		  ux		  fx		   0 	 |
	* R =	|		  ry		  uy		  fy		   0 	 |
	*		|		  rz		  uz		  fz		   0 	 |
	*		|		   0		   0		   0		   1 	 |
	*
	* rotates to new Rightwards :	r = (x, y, z)
	* rotates to new Upwards :		u = (x, y, z)
	* rotates to new Forwards :		f = (x, y, z)
	*
	*
	* SOURCE :
	* http://eecs.qmul.ac.uk/~gslabaugh/publications/euler.pdf
	* https://gamedev.stackexchange.com/questions/124667/how-does-a-4x4-matrix-represent-an-object-in-space-and-matrix-lore/124669#124669?newreg=23fefeecfcd746dfa5c747a8b4d5c072
	* https://www.euclideanspace.com/maths/geometry/affine/matrix4x4/index.htm
	* https://stackoverflow.com/questions/27655885/get-position-rotation-and-scale-from-matrix-in-opengl
	*
	*/
};
