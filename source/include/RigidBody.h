#pragma once
#include "LibMath/Vector.h"
#include "LibMath/Matrix.h"
#include "LibMath/Arithmetic.h"
#include <functional>
#include <vector>

class ICollidable
{
public:
	virtual bool collision(const ICollidable& p_collidable);

protected:
	static LibMath::Vector4 ClosestPointOnSegment(const LibMath::Vector4& p_A, const LibMath::Vector4& p_B, const LibMath::Vector4& p_pt);
	static bool ShpereCollision(const LibMath::Vector3& p_pt1, float p_r1, const LibMath::Vector3& p_pt2, float p_r2);
	static bool CircleCollision(const LibMath::Vector2& p_pt1, float p_r1, const LibMath::Vector2& p_pt2, float p_r2);
};

class SphereCollider : ICollidable
{
public:
	SphereCollider();
	SphereCollider(LibMath::Vector3	p_pos, float p_rad);
	~SphereCollider() = default;

	bool collision(const ICollidable& p_collidable) override;
	bool collision(const SphereCollider& p_sphere);

	LibMath::Vector3	m_pos;
	float				m_rad;
};

class CapsuleCollider : ICollidable
{
public:
	CapsuleCollider();
	CapsuleCollider(const LibMath::Vector3& p_p1, const LibMath::Vector3& p_p2, float p_rad, const LibMath::Matrix4& p_mat);
	~CapsuleCollider() = default;

	bool collision(const ICollidable& p_collidable)override;
	bool collision(const CapsuleCollider& p_sphere);

	LibMath::Vector4	m_p1;
	LibMath::Vector4	m_p2;
	float				m_rad;
	LibMath::Matrix4	m_mat;
};

class VertCapsuleCollider : ICollidable
{
public:
	VertCapsuleCollider();
	VertCapsuleCollider(float p_height, float p_rad, const LibMath::Vector3& p_pos);
	~VertCapsuleCollider() = default;

	bool collision(const ICollidable& p_collidable)override;
	bool collision(const VertCapsuleCollider& p_vertCapsule);

	float				m_height;
	float				m_rad;
	LibMath::Vector3	m_pos;
};

class BoxCollider : ICollidable
{
	BoxCollider();
	BoxCollider(const LibMath::Vector3& p_dim, const LibMath::Vector3& p_pos);
	~BoxCollider() = default;

	bool collision(const ICollidable& p_collidable)override;
	bool collision(const BoxCollider& p_sphere);

	LibMath::Vector3 m_dim; //dimentions
	LibMath::Vector3 m_pos; //position
};

class RigidBody
{
	using CollsionFunc = std::function<void(const RigidBody&)>;
	class GameObject;

public:
	//enum class e_collider;

	RigidBody();
	RigidBody(std::vector<std::unique_ptr<ICollidable>>& p_collidables, CollsionFunc p_collisionFuncs[3]);
	~RigidBody() = default;

	//enum class e_collider
	//{
	//	E_SPHERE,
	//	E_CAPSULE,
	//	E_VERTCAPSULE,
	//	E_BOX
	//};

private:
	GameObject*					m_GO;
	CollsionFunc				m_onCollsionEnterFunc;
	CollsionFunc				m_onCollsionStayFunc;
	CollsionFunc				m_onCollsionExitFunc;

	std::vector<std::unique_ptr<ICollidable>>	m_collidable;

	static void DefaultCollision(const RigidBody&);
};

