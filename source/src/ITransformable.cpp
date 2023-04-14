#include "ITransformable.h"
#include "LibMath/Arithmetic.h"
#include "LibMath/Trigonometry.h"

Transform::Transform() : m_transform(1)
{
}

Transform::Transform(Mat4 p_transform)
		: m_transform(std::move(p_transform))
{
}

	LibMath::Matrix4 Transform::getTransform() const
	{
		return m_transform;
	}

	void Transform::setTransform(const Mat4& p_transform)
	{
		m_transform = p_transform;
	}

	Transform& Transform::translate(const float p_x, const float p_y, const float p_z)
	{
		this->m_transform *= Mat4::translation(p_x, p_y, p_z);
		return *this;
	}

	Transform& Transform::globalTranslate(float p_x, float p_y, float p_z)
	{
		if (p_x)
			translate(p_x * getRightward());
		if (p_y)
			translate(p_y * getUpward());
		if (p_z)
			translate(p_z * getForward());
		return *this;
	}

	Transform& Transform::translate(const Vec3& p_translation)
	{
		translate(p_translation.m_x, p_translation.m_y, p_translation.m_z);
		return *this;
	}

	Transform& Transform::scale(const float p_x, const float p_y, const float p_z)
	{
		this->m_transform *= Mat4::scaling(p_x, p_y, p_z);
		return *this;
	}

	Transform& Transform::scale(float p_f)
	{
		return this->scale(p_f, p_f, p_f);
	}

	Transform& Transform::rotateEulerAngles(const Rad& p_x, const Rad& p_y, const Rad& p_z)
	{
		this->m_transform *= Mat4::rotation(p_x, Vec3::right());	//rotate x axis
		this->m_transform *= Mat4::rotation(p_y, Vec3::up());		//rotate y axis
		this->m_transform *= Mat4::rotation(p_z, Vec3::back());		//rotate z axis
		return *this;
	}

	Transform& Transform::setPosition(const float p_x, const float p_y, const float p_z)
	{
		const LibMath::Vector3 pos = this->getPosition();
		this->translate(p_x - pos.m_x,
			p_y - pos.m_y,
			p_z - pos.m_z);
		return *this;
	}

	Transform& Transform::setScale(const float p_x, const float p_y, const float p_z)
	{
		const LibMath::Vector3 scale = this->getScale();

		if (LibMath::floatEquals(scale.m_x, 0.f)
			|| LibMath::floatEquals(scale.m_y, 0.f)
			|| LibMath::floatEquals(scale.m_z, 0.f))
			throw Exceptions::DivideByZero("Divide by zero, scale = " + scale.string());

		this->scale(p_x / scale.m_x,
			p_y / scale.m_y,
			p_z / scale.m_z);

		return *this;
	}

	Transform& Transform::setRotationEulerAngles(const Rad& p_x, const Rad& p_y, const Rad& p_z)
	{
		const LibMath::Vector3 rotateAngles = this->getRotationEulerAngles();
		this->rotateEulerAngles(p_x - static_cast<Rad>(rotateAngles.m_x),
			p_y - static_cast<Rad>(rotateAngles.m_y),
			p_z - static_cast<Rad>(rotateAngles.m_z));

		return *this;
	}

	Transform::Vec3 Transform::getPosition() const
	{
		/**
		* 		|		   1		   0		   0		  tx 	 |
		* T =	|		   0		   1 		   0		  ty 	 |
		*		|		   0		   0		   1		  tz 	 |
		*		|		   0		   0		   0		   1 	 |
		*                     [ m03 ]
		* translationVector = [ m13 ]
		*	                  [ m23 ]
		*/
		return {
			m_transform[3],
			m_transform[7],
			m_transform[11]
		};
	}

	Transform::Vec3 Transform::getScale() const
	{
		/**
		* 		|		  sx		   0		   0		   0 	 |
		* S =	|		   0		  sy 		   0		   0 	 |
		*		|		   0		   0		  sz		   0 	 |
		*		|		   0		   0		   0		   1 	 |
		*
		* scalingFactor = sqrt(m00 * m00 + m01 * m01 + m02 * m02);
		*/

		return {
			this->getScaleX(),
			this->getScaleY(),
			this->getScaleZ()
		};
	}

	float Transform::getScaleX() const
	{
		//see GetScale()
		//
		return LibMath::squareRoot(m_transform[0] * m_transform[0] +
			m_transform[4] * m_transform[4] +
			m_transform[8] * m_transform[8]);
	}

	float Transform::getScaleY() const
	{
		//see GetScale()
		//
		return LibMath::squareRoot(m_transform[1] * m_transform[1] +
			m_transform[5] * m_transform[5] +
			m_transform[9] * m_transform[9]);
	}

	float Transform::getScaleZ() const
	{
		//see GetScale()
		//
		return LibMath::squareRoot(m_transform[2] * m_transform[2] +
			m_transform[6] * m_transform[6] +
			m_transform[10] * m_transform[10]);
	}

	Transform::Vec3 Transform::getRotationEulerAngles() const
	{
		/**
		*                                          [ m00 m01 m02 ]
		* rotationMatrix = (1.0 / scalingFactor) * [ m10 m11 m12 ]
		*										   [ m20 m21 m22 ]
		*		|		  rx		  ux		  fx		   0 	 |
		* R =	|		  ry		  uy		  fy		   0 	 |
		*		|		  rz		  uz		  fz		   0 	 |
		*		|		   0		   0		   0		   1 	 |
		* http://eecs.qmul.ac.uk/~gslabaugh/publications/euler.pdf
		*/

		const Vec3 scale(this->getScale());
		Mat4 rotation(this->m_transform);

		if (LibMath::floatEquals(scale.m_x, 0.f)
			|| LibMath::floatEquals(scale.m_y, 0.f)
			|| LibMath::floatEquals(scale.m_z, 0.f))
			throw Exceptions::DivideByZero("Divide by zero, scale = " + scale.string());

		rotation *= Mat4::scaling(1.0f / scale.m_x, 1.0f / scale.m_y, 1.0f / scale.m_z); //un-scale mat
		//don't have to un-translate mat bcs trans doesn't affect rotation

		if (LibMath::abs(rotation[8]) == 1.f)
			throw Exceptions::GimbalLock();

		//infinity solutions / gimbal lock
		/**
			*		|		   0		   1		   2		   3 	 |
			* R =	|		   4		   5		   6		   7 	 |
			*		|		   8		   9		  10		   0 	 |
			*		|		   0		   0		   0		   1 	 |
			*/

		const LibMath::Radian theta1 = -LibMath::asin(rotation[8]);
		//theta2 = static_cast<Rad>(LibMath::g_pi) - theta1;

		const float cosTheta1 = LibMath::cos(theta1);
		//cosTheta2 = LibMath::cos(theta2);

		const LibMath::Radian psi1 = LibMath::atan(rotation[9] / cosTheta1, rotation[10] / cosTheta1);
		//psi2 = LibMath::atan(rotation[9] / cosTheta2, rotation[10] / cosTheta2);

		LibMath::Radian phi1 = LibMath::atan(rotation[4] / cosTheta1, rotation[0] / cosTheta1);
		//phi2 = LibMath::atan(rotation[4] / cosTheta2, rotation[0] / cosTheta2);

		//reverse phi bcs of global orientation
		phi1 *= -1;
		//phi2 *= -1;

		return { psi1.radian(), theta1.radian(), phi1.radian() };
	}

	Transform::Mat4 Transform::getRotation() const
	{
		Mat4 mat;

		Vec3 v = this->getRightward();
		mat[0] = v.m_x;
		mat[4] = v.m_y;
		mat[8] = v.m_z;

		v = this->getUpward();
		mat[1] = v.m_x;
		mat[5] = v.m_y;
		mat[9] = v.m_z;

		v = this->getForward();
		mat[2] = v.m_x;
		mat[6] = v.m_y;
		mat[10] = v.m_z;

		mat[15] = 1.0f;

		return mat;
	}

	Transform::Vec3 Transform::getRightward() const
	{
		const float xScale = this->getScaleX();
		if (LibMath::floatEquals(xScale, 0.f))
			throw Exceptions::DivideByZero("Divide by zero, xScale = " + std::to_string(xScale));

		return { m_transform[0] / xScale, m_transform[4] / xScale, m_transform[8] / xScale };
	}

	Transform::Vec3 Transform::getLeftward() const
	{
		return -this->getRightward();
	}

	Transform::Vec3 Transform::getUpward() const
	{
		const float yScale = this->getScaleY();
		if (LibMath::floatEquals(yScale, 0.f))
			throw Exceptions::DivideByZero("Divide by zero, yScale = " + std::to_string(yScale));

		return { m_transform[1] / yScale, m_transform[5] / yScale,  m_transform[9] / yScale };
	}

	Transform::Vec3 Transform::getDownward() const
	{
		return -this->getUpward();
	}

	Transform::Vec3 Transform::getForward() const
	{
		const float zScale = this->getScaleZ();
		if (LibMath::floatEquals(zScale, 0.f))
			throw Exceptions::DivideByZero("Divide by zero, zScale = " + std::to_string(zScale));

		return { m_transform[2] / zScale, m_transform[6] / zScale, m_transform[10] / zScale };
	}

	Transform::Vec3 Transform::getBackward() const
	{
		return -this->getForward();
	}

