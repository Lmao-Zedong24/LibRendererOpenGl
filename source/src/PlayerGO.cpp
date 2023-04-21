#include "PlayerGO.h"
#include "CameraG0.h"
#include "WallGO.h"
#include "PFA/PFAGM.h"

using namespace LibMath::Literal;

const float PlayerGO::PLAYER_SPEED		= 0.1f;
const float PlayerGO::PLAYER_JUMP_RATE	= 2.0f;
const float PlayerGO::PLAYER_GRAVITY	= 0.05f;
const float PlayerGO::CAM_MAX_ANGLE		= 90.0f;
const float PlayerGO::CAM_MIN_ANGLE		= -90.0f;
const std::string PlayerGO::CameraName	= "PlayerCamera";

PlayerGO::PlayerGO(GameObject* p_parent) : 
	GameObject(p_parent), m_yCamAngle(0), m_counterJump(0), 
	m_isJump(false), m_yVelocity(0), m_translationVector(1),
	m_rigidBody(nullptr), m_rayCast(nullptr)
{
	auto camGo = this->AddChild<CameraGO>(CameraName);
}

void PlayerGO::Inputs(GLFWwindow* p_window)
{
	Transform&	playerT	= this->m_localTransform;
	CameraGO&	camOB	= *this->GetChild<CameraGO>(CameraName);
	Camera&		cam		= camOB.GetCamera();
	
	m_translationVector = LibMath::Vector3(0); // TODO : reset movementMat cant be in inputs (is getss undone in collissions)

	if (glfwGetKey(p_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_translationVector += LibMath::Vector3(0, 0, -PLAYER_SPEED);
	}
	if (glfwGetKey(p_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_translationVector += LibMath::Vector3(-PLAYER_SPEED, 0, 0);
	}
	if (glfwGetKey(p_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_translationVector += LibMath::Vector3(0, 0, PLAYER_SPEED);
	}
	if (glfwGetKey(p_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_translationVector += LibMath::Vector3(PLAYER_SPEED, 0, 0);
	}
	if (glfwGetKey(p_window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (m_counterJump >= PLAYER_JUMP_RATE)
			m_isJump = true;
	}
	//if (glfwGetKey(p_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	//{
	//	playerT.translate(0, -PLAYER_SPEED, 0);
	//}
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
	if (glfwGetKey(p_window, GLFW_KEY_E) == GLFW_PRESS)
	{
		this->Interact();
	}
}

void PlayerGO::SetProjectionCamera(const LibMath::Matrix4& p_viewMat)
{
	CameraGO* camGO = this->GetChild<CameraGO>(CameraName);
	camGO->GetCamera().setProjectionMatrix(p_viewMat);
}

void PlayerGO::SetRigidBodyCollider(Collider* p_rigidBody)
{
	m_rigidBody = p_rigidBody;
}

void PlayerGO::SetRayCastCollider(Collider* p_rayCast)
{
	if (!p_rayCast ||
		p_rayCast->GetCollidables().empty())
		return;

	m_rayCast = p_rayCast;
}

void PlayerGO::SetRigidBodyFuncs()
{	
	Collider::CollsionFunc p_collisionFuncs[3]
	{
		//std::bind(PlayerGO::PlayerRigidWithWall, this, std::placeholders::_1),	//		same as llamda
		//captures [this] ptr so func knows where to call collision func
		[this](Collider::ColArg p_other) -> Collider::ColRes { return this->PlayerRigidWithWall(p_other); },	//onCollisonEnter and Stay
		Collider::CreateBoundedCollisionFunc<PlayerGO>(this, &PlayerGO::PlayerRigidWithWall),					//it do work ;,,,,, )
		// (Both ways do the same thing)
		Collider::CreateBoundedCollisionFunc<PlayerGO>(this, &PlayerGO::PlayerExitFloor)		//no onCollisonExit
	};

	//does copy set 
	this->m_rigidBody->SetCollisionFuncs(p_collisionFuncs);
}

void PlayerGO::SetRayCastFuncs()
{
	Collider::CollsionFunc p_collisionFuncs[3]
	{
		Collider::CreateBoundedCollisionFunc<PlayerGO>(this, &PlayerGO::RayCastNewTarget),		//yes onCollisionEnter
		nullptr,																				//no  onCollisonStay
		Collider::CreateBoundedCollisionFunc<PlayerGO>(this, &PlayerGO::RayCastRemoveTarget),	//yes onCollisionExit
	};

	//does copy set 
	this->m_rayCast->SetCollisionFuncs(p_collisionFuncs);
}

void PlayerGO::Update()
{
	//Update Input Movement

	//if movement with no Collision
	//m_localTransform.multiplyTransform(m_translationVector);

	//Gravity
	if (!(m_floorCollision || m_localTransform.getPosition().m_y < -50))
		m_yVelocity -= PLAYER_GRAVITY;

	else if (m_localTransform.getPosition().m_y < 0)
		m_yVelocity = 0;

	//Jump
	m_counterJump += 0.0163f;
	if (m_isJump && m_counterJump >= PLAYER_JUMP_RATE)
	{
		m_isJump = false;
		m_counterJump = 0;

		m_yVelocity += 2;
	}

	//if gravity
	if (m_yVelocity)
		m_translationVector += LibMath::Vector3(0, m_yVelocity, 0);

	// CURSOR CHANGE ON HOVER
	{
		auto& rm = PFA::PFAGM::GetInstance()->GetRM();
		auto cam = this->GetChild<CameraGO>(CameraName);
		auto cursor1 = cam->GetChild<CameraGO>("crosshair1");
		auto cursor2 = cam->GetChild<CameraGO>("crosshair2");

		if (m_rayCastSelected)
		{
			auto green = rm.Get<Texture>("green.png");
			cursor1->SetTexture(green);
			cursor2->SetTexture(green);
		}
		else
		{
			auto red = rm.Get<Texture>("black.png");
			cursor1->SetTexture(red);
			cursor2->SetTexture(red);
		}
	}

	UpdatePos();

	//camOB.UpdateGlobalMat();
	//camOB.Update();

	for (auto& child : m_children)
		child.second->Update(); //recursive with all childreen ? 
}

const Collider& PlayerGO::GetRigidBody()
{
	return *m_rigidBody;
}

void PlayerGO::UpdatePos()
{
	//update transform
	m_localTransform.translate(m_translationVector);
	//update rigidbody
	m_rigidBody->UpdateCollidables(m_localTransform);

	this->UpdateGlobalMat();

	auto cam = this->GetChild<CameraGO>(CameraName);
	cam->UpdateMats();
	m_rayCast->UpdateCollidables(cam->GetGlobalMat());
}

void PlayerGO::UndoMovement()
{
	m_translationVector *= -1;
	this->UpdatePos();
}

void PlayerGO::Interact()
{
	if (!m_rayCastSelected)
		return;

	auto tempColor = m_rayCastSelected->GetGameObj()->GetColor();
	m_rayCastSelected->GetGameObj()->SwitchColorTexture(m_color);

	m_color = tempColor;
	this->GetChild<CameraGO>(CameraName)->GetChild<GameObject>("phoneColor")->SwitchColorTexture(tempColor);

	m_rayCastSelected = nullptr;
}

Collider::ColRes PlayerGO::PlayerRigidWithWall(Collider::ColArg p_other)
{
	auto* go = p_other.GetGameObj();
	if ((go->GetLayer().IsName("wall")) &&										//is wall
		(!go->HasColor() ||	(go->HasColor() && !go->IsSameColor(m_color))) ||	//and not same color or no color
		go->GetLayer().IsName("cubeColor"))										//or cube	
		UndoMovement();

	if (!go->GetLayer().IsName("player"))
		this->m_floorCollision = true;

	return Collider::ColRes(); //void (can be changed latter if needed)
}

Collider::ColRes PlayerGO::PlayerExitFloor(Collider::ColArg p_other)
{
	//if (p_other.GetGameObj()->GetLayer().IsName("floor") || 
	//	p_other.GetGameObj()->GetLayer().IsName("cubeColor"))
	this->m_floorCollision = false;

	return Collider::ColRes();
}

Collider::ColRes PlayerGO::RayCastNewTarget(Collider::ColArg p_other)
{
	auto pos = this->m_localTransform.getPosition();

	if (!(&p_other == m_rigidBody) && 
		p_other.GetGameObj()->GetLayer().IsName("cubeColor") &&
		(!m_rayCastSelected ||																	//no selection or
		pos.distanceSquaredFrom(m_rayCastSelected->GetCollidables()[0].get()->GetCenter()) >	//selected futher away
		pos.distanceSquaredFrom(p_other.GetCollidables()[0].get()->GetCenter())))
		m_rayCastSelected = &p_other;

	return Collider::ColRes();
}

Collider::ColRes PlayerGO::RayCastRemoveTarget(Collider::ColArg p_other)
{
	if (m_rayCastSelected == &p_other)
		m_rayCastSelected = nullptr;

	return Collider::ColRes();
}

//Collider::ColRes PlayerGO::PlayerCollisionStay(Collider::ColArg)
//{
//	return Collider::ColRes();
//}
//
//Collider::ColRes PlayerGO::PlayerCollisionExit(Collider::ColArg)
//{
//	return Collider::ColRes();
//}

