#include "Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <LibMath/header/Angle/Degree.h>

using namespace LibMath::Literal;


Camera::Camera() :
	m_globalMat(new LibMath::Matrix4(1)),
	m_projectionMatrix(Mat4::perspectiveProjection(
		120_deg, 16.f / 9.f, .01f, 200.f))
{
	m_viewMatrix = this->getViewMatrix();
	UpdatemViewProjMat();
}

Camera::Camera(const Mat4& p_transform, Mat4 p_projection)
	: //Transform(p_transform), 
	m_globalMat(new LibMath::Matrix4(p_transform)),
	m_projectionMatrix(std::move(p_projection))
{
}

Camera::Camera(Mat4* p_globalMat, Mat4 p_projection) :
	m_globalMat(p_globalMat),
	m_projectionMatrix(std::move(p_projection))
{
}

Camera::Mat4 Camera::getProjectionMatrix() const
{
	return m_projectionMatrix;
}

void Camera::SetUniformCam(Shader& p_shader)
{
	glUniformMatrix4fv(p_shader.GetUniformLocation("camPos"), 1, GL_FALSE, (GLfloat*)&m_camPos[0]);
}

void Camera::SetTransform(Mat4* p_transform)
{
	this->m_globalMat = p_transform;
}

void Camera::UpdateViewMat()
{
	m_viewMatrix = this->getViewMatrix();
}

void Camera::setProjectionMatrix(const Mat4& p_projection)
{
	m_projectionMatrix = p_projection;
}

Camera::Mat4 Camera::getViewMatrix() const
{
	return m_globalMat->inverse();
}

void Camera::UpdatemViewProjMat()
{
	this->m_viewProjMatrix = m_projectionMatrix * m_viewMatrix;
	//this->m_camPos = LibMath::Vector3(	m_globalMat[3],
	//									m_globalMat[7],
	//									m_globalMat[11]);
}

const Camera::Mat4& Camera::getViewProjMatrix()
{
	//UpdatemViewProjMat();
	return m_viewProjMatrix;
}

void Camera::Inputs(GLFWwindow* p_window)
{
	//if (glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
	//{
	//	m_transform.translate(0, 0, -Speed);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
	//{
	//	m_transform->translate(-Speed, 0, 0);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
	//{
	//	m_transform->translate(0, 0, Speed);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	m_transform->translate(Speed, 0, 0);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	//{
	//	m_transform->translate(0, Speed, 0);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	//{
	//	m_transform->translate(0, -Speed, 0);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	LibMath::Degree angle(Speed * 10);
	//	m_transform->rotateEulerAngles(angle, 0_deg, 0_deg);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	LibMath::Degree angle(-Speed * 10);
	//	m_transform->rotateEulerAngles(angle, 0_deg, 0_deg);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	//{
	//	LibMath::Degree angle(-Speed * 10);
	//	m_transform->rotateEulerAngles(0_deg, angle, 0_deg);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_LEFT) == GLFW_PRESS)
	//{
	//	LibMath::Degree angle(Speed * 10);
	//	m_transform->rotateEulerAngles(0_deg, angle, 0_deg);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
	//if (glfwGetKey(p_window, GLFW_KEY_R) == GLFW_PRESS)
	//{
	//	m_transform->setRotationEulerAngles(0_deg, 0_deg, 0_deg);
	//	m_transform->setPosition(0, 0, 0);
	//	m_viewMatrix = this->getViewMatrix();
	//	UpdatemViewProjMat();
	//}
}