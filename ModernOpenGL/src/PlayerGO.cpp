#include "PlayerGO.h"
#include "CameraG0.h"

using namespace LibMath::Literal;

const float PlayerGO::PLAYER_SPEED		= 0.1f;
const float PlayerGO::PLAYER_JUMP_RATE	= 2.0f;
const float PlayerGO::PLAYER_GRAVITY	= 0.05f;
const float PlayerGO::CAM_MAX_ANGLE		= 90.0f;
const float PlayerGO::CAM_MIN_ANGLE		= -90.0f;
const std::string PlayerGO::CameraName	= "PlayerCamera";

PlayerGO::PlayerGO(GameObject* p_parent) : GameObject(p_parent), m_yCamAngle(0)
{
	this->AddChild<CameraG0>(CameraName);
}

void PlayerGO::Inputs(GLFWwindow* p_window)
{
	Transform&	playerT	= this->m_localTransform;
	CameraG0&	camOB	= *this->GetChild<CameraG0>(CameraName);
	Camera&		cam		= camOB.GetCamera();

	if (glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		playerT.translate(0, 0, -PLAYER_SPEED);
	}
	if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		playerT.translate(-PLAYER_SPEED, 0, 0);
	}
	if (glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		playerT.translate(0, 0, PLAYER_SPEED);
	}
	if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		playerT.translate(PLAYER_SPEED, 0, 0);
	}
	if (glfwGetKey(p_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		//playerT.translate(0, PLAYER_SPEED, 0);
		if (m_counterJump >= PLAYER_JUMP_RATE)
			m_isJump = true;
	}
	if (glfwGetKey(p_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		//playerT.translate(0, -PLAYER_SPEED, 0);
	}
	if (glfwGetKey(p_window, GLFW_KEY_UP) == GLFW_PRESS && m_yCamAngle <= CAM_MAX_ANGLE)
	{
		LibMath::Degree angle(PLAYER_SPEED * 10);
		m_yCamAngle += PLAYER_SPEED * 10;

		camOB.GetLocalTransform().rotateEulerAngles(angle, 0_deg, 0_deg);
	}
	if (glfwGetKey(p_window, GLFW_KEY_DOWN) == GLFW_PRESS && m_yCamAngle >= CAM_MIN_ANGLE)
	{
		LibMath::Degree angle(-PLAYER_SPEED * 10);
		m_yCamAngle += -PLAYER_SPEED * 10;

		camOB.GetLocalTransform().rotateEulerAngles(angle, 0_deg, 0_deg);
	}
	if (glfwGetKey(p_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		LibMath::Degree angle(-PLAYER_SPEED * 10);	

		playerT.rotateEulerAngles(0_deg, angle, 0_deg);
	}
	if (glfwGetKey(p_window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		LibMath::Degree angle(PLAYER_SPEED * 10);

		playerT.rotateEulerAngles(0_deg, angle, 0_deg);
	}
	if (glfwGetKey(p_window, GLFW_KEY_R) == GLFW_PRESS)
	{
		//m_transform->setRotationEulerAngles(0_deg, 0_deg, 0_deg);
		//m_transform->setPosition(0, 0, 0);
		//m_viewMatrix = this->getViewMatrix();
		//UpdatemViewProjMat();
	}
}

void PlayerGO::SetProjectionCamera(const LibMath::Matrix4& p_viewMat)
{
	CameraG0* camGO = this->GetChild<CameraG0>(CameraName);
	camGO->GetCamera().setProjectionMatrix(p_viewMat);
}

void PlayerGO::Update()
{
	m_counterJump += 0.0163;

	if (m_localTransform.getPosition().m_y >= 2)
	{
		m_yVelocity -= PLAYER_GRAVITY;
	}
	else if (m_localTransform.getPosition().m_y < 0)
	{
		m_yVelocity = 0;
	}

	if (m_isJump)
	{
		m_yVelocity += 2;
		m_isJump = false;
		m_counterJump = 0;
	}

	m_localTransform.translate(0, m_yVelocity, 0);

	this->UpdateGlobalMat();
	CameraG0* camGO = this->GetChild<CameraG0>(CameraName);

	camGO->UpdateGlobalMat();
	camGO->Update();
}
