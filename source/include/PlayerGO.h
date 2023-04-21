#pragma once
#include "GameObject.h"
#include "LibMath/Matrix/Matrix4.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "LibMath/Angle/Degree.h"
#include "Rigidbody.h"


class PlayerGO : public GameObject
{
public:
	PlayerGO(GameObject* p_parent);

	void Inputs(GLFWwindow* p_window);

	void SetProjectionCamera(const LibMath::Matrix4& p_projMat);

	void SetRigidBodyCollider(Collider* p_rigidBody);
	void SetRayCastCollider(Collider* p_rayCast);

	void SetRigidBodyFuncs();
	void SetRayCastFuncs();

	void Update() override;

	const Collider&	GetRigidBody();


	static const std::string	CameraName;

private:
	static const float			PLAYER_SPEED;
	static const float			PLAYER_JUMP_RATE;
	static const float			PLAYER_GRAVITY;
	static const float			CAM_MAX_ANGLE;
	static const float			CAM_MIN_ANGLE;

	LibMath::Vector3	m_translationVector;
	Collider*			m_rigidBody;
	Collider*			m_rayCast;
	const Collider*		m_rayCastSelected;

	bool	m_floorCollision;
	float	m_yCamAngle;
	bool	m_isJump;
	float 	m_counterJump;
	float	m_yVelocity;

	void UpdatePos();
	void UndoMovement();
	void Interact();

	Collider::ColRes PlayerRigidWithWall(Collider::ColArg p_other);
	Collider::ColRes PlayerExitFloor(Collider::ColArg p_other);

	Collider::ColRes RayCastNewTarget(Collider::ColArg p_other);
	Collider::ColRes RayCastRemoveTarget(Collider::ColArg p_other);
	//Collider::ColRes PlayerCollisionStay(Collider::ColArg);
	//Collider::ColRes PlayerCollisionExit(Collider::ColArg);

};


