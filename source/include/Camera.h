#pragma once
#include "Shader.h"
#include "LibMath/Matrix.h"
#include "ITransformable.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera //: public Transform
{
	using Mat4 = LibMath::Matrix4x4;

public:
	Camera();
	Camera(const Mat4& p_transform, Mat4 p_projection);
	Camera(Mat4* p_globalMat, Mat4 p_projection);
	~Camera() = default;

	void Inputs(GLFWwindow* window);

	Mat4 getViewMatrix() const;
	Mat4 getProjectionMatrix() const;
	const Mat4& getViewProjMatrix();

	void setProjectionMatrix(const Mat4& p_projection);
	void SetUniformCam(Shader& p_shader);
	void SetTransform(Mat4* p_transform);

	void UpdateViewMat();
	void UpdatemViewProjMat();

private:
	Mat4*		m_globalMat;
	Mat4		m_projectionMatrix;
	Mat4		m_viewMatrix;
	Mat4		m_viewProjMatrix;

	LibMath::Vector3	m_camPos;
	const float Speed = 0.1f;
};

