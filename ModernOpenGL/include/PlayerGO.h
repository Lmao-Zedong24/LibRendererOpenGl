#pragma once
#include "GameObject.h"
#include <LibMath/header/Matrix/Matrix4.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <LibMath/header/Angle/Degree.h>
#include "Rigidbody.h"


class PlayerGO : public GameObject
{
public:
	PlayerGO(GameObject* p_parent);
	void Inputs(GLFWwindow* p_window);

	void SetProjectionCamera(const LibMath::Matrix4& p_projMat);
	void Update() override;

	static const std::string	CameraName;
private:
	static const float			PLAYER_SPEED;
	static const float			PLAYER_JUMP_RATE;
	static const float			PLAYER_GRAVITY;
	static const float			CAM_MAX_ANGLE;
	static const float			CAM_MIN_ANGLE;

	float	m_yCamAngle;

	bool	m_isJump;
	float 	m_counterJump;
	float	m_yVelocity;

};


