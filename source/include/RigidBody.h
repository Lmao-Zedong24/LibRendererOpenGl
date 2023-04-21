#pragma once
#include "LibMath/Vector.h"
#include "LibMath/Matrix.h"
#include "LibMath/Arithmetic.h"
#include "ITransformable.h"
#include <functional>
#include <vector>

class ICollidable
{
public:
	virtual bool	Collision(const ICollidable& p_collidable)const { return false; };
	virtual void	Update(const Transform& p_tarnsform) {};
	virtual float	GetMin(int axis)const { return 0; };
	virtual float	GetMax(int axis)const { return 0; };

	virtual LibMath::Vector3	GetCenter()const { return LibMath::Vector3(0); };

protected:
	static LibMath::Vector4 ClosestPointOnSegment(const LibMath::Vector4& p_A, const LibMath::Vector4& p_B, const LibMath::Vector4& p_pt);
	static bool ShpereCollision(const LibMath::Vector3& p_pt1, float p_r1, const LibMath::Vector3& p_pt2, float p_r2);
	static bool CircleCollision(const LibMath::Vector2& p_pt1, float p_r1, const LibMath::Vector2& p_pt2, float p_r2);
	static bool test();
};

class BoxCollider;

class SphereCollider : public ICollidable
{
public:
	SphereCollider();
	SphereCollider(LibMath::Vector3	p_pos, float p_rad);
	~SphereCollider() = default;

	bool	Collision(const ICollidable& p_collidable)const override;
	void	Update(const Transform& p_tarnsform) override;
	float	GetMin(int axis)const override;
	float	GetMax(int axis)const override;

	LibMath::Vector3	GetCenter()const override;
	float				GetRadius()const;

	bool	CollisionSph(const SphereCollider& p_sphere) const;
	bool	CollisionBox(const BoxCollider& p_box) const;


	LibMath::Vector3	m_pos;
	float				m_rad;
};

class CapsuleCollider : public ICollidable
{
public:
	CapsuleCollider();
	CapsuleCollider(const LibMath::Vector3& p_p1, const LibMath::Vector3& p_p2, float p_rad, const LibMath::Matrix4& p_mat);
	~CapsuleCollider() = default;

	bool Collision(const ICollidable& p_collidable)const override;
	bool CollisionCap(const CapsuleCollider& p_cap)const;
	bool CollisionBox(const BoxCollider& p_box)const;
	bool CollisionSph(const SphereCollider& p_sph)const;

	void	Update(const Transform& p_tarnsform) override;
	float	GetMin(int axis)const override;
	float	GetMax(int axis)const override;

	LibMath::Vector3	GetCenter()const override;


	LibMath::Vector4	m_p1;
	LibMath::Vector4	m_p2;
	float				m_rad;
	Transform			m_mat;
};

class VertCapsuleCollider : public ICollidable
{
public:
	VertCapsuleCollider();
	VertCapsuleCollider(float p_height, float p_rad, const LibMath::Vector3& p_pos);
	~VertCapsuleCollider() = default;

	bool Collision(const ICollidable& p_collidable)const override;
	bool Collision(const VertCapsuleCollider& p_vertCapsule)const;

	float				m_height;
	float				m_rad;
	LibMath::Vector3	m_pos;
};

class BoxCollider : public ICollidable
{
public:
	BoxCollider();
	BoxCollider(const LibMath::Vector3& p_dim, const LibMath::Vector3& p_pos);
	~BoxCollider() = default;

	bool	Collision(const ICollidable& p_collidable)const override;
	void	Update(const Transform& p_tarnsform) override;
	float	GetMin(int axis)const override;
	float	GetMax(int axis)const override;
	LibMath::Vector3 GetCenter()const override;

	bool	CollisionBox(const BoxCollider& p_box)const;
	bool	CollisionSph(const SphereCollider& p_sphere)const;
	bool	CollisionCap(const CapsuleCollider& p_cap)const;

	LibMath::Vector3 m_dim; //dimentions
	LibMath::Vector3 m_pos; //position
};

class GameObject;

class Collider
{
public:
	typedef int ColRes;	//collision return type = void
	typedef const Collider& ColArg;	//collision argument type = const Collider&
	typedef std::function<ColRes(ColArg)> CollsionFunc;
	//enum class e_collider;

	Collider(	GameObject* p_GO);

	/// <summary>
	/// Initialize rigidbody
	/// </summary>
	/// <param name="p_GO"> ptr to linked GO</param>
	/// <param name="p_collidables"> move vector of collidables </param>
	/// <param name="p_collisionFuncs"> ptr to collisionFuncs (Enter, Stay, Exit) </param>
	Collider(	GameObject* p_GO, std::vector<std::unique_ptr<ICollidable>>& p_collidables,
				CollsionFunc p_collisionFuncs[3] = nullptr);
	~Collider() = default;

	//GameObject& GetGameObject();

	bool				HasACollisionFunc() const;
	bool				IsActive() const;
	GameObject*			GetGameObj() const;
	void				UpdateCollidables(const Transform&);


	const std::vector<std::unique_ptr<ICollidable>>&	GetCollidables() const;

	/// <summary>
	/// Cant set true if no collidables
	/// </summary>
	/// <param name="p_active"> active value</param>
	void SetActive(bool p_active = true);
	//void SetApplyGravity(bool p_gravity = true);

	/// <summary>
	/// If a func is null, doesn't ovveride it
	/// </summary>
	/// <param name="p_collisionFuncs"></param>
	void SetCollisionFuncs(CollsionFunc p_collisionFuncs[3]);

	/// <summary>
	/// If a func is null, set it to null
	/// </summary>
	/// <param name="p_collisionFuncs"></param>
	void OverrideCollisionFuncs(CollsionFunc p_collisionFuncs[3]);

	bool CheckCollision(const Collider& p_other); // TODO : Do better Rigidbody Collision

	void OnCollsionEnter(const Collider& p_other);
	void OnCollsionStay(const Collider& p_other);
	void OnCollsionExit(const Collider& p_other);

	template <class T>
	static inline Collider::CollsionFunc CreateBoundedCollisionFunc(T* p_objPtr, ColRes (T::* p_funcToBind) (ColArg)) //int (*func)(int, int)
	{
		return Collider::CollsionFunc(std::bind(p_funcToBind, p_objPtr, std::placeholders::_1));

		//return Collider::CollsionFunc([p_objPtr, p_funcToBind] (Collider::ColArg p_other) -> Collider::ColRes
		//		{ return p_objPtr->p_funcToBind(p_other); });


		// Cant make it wotk with llambda expresion
			//int i = 0;
			//return Collider::CollsionFunc();
			//return Collider::CollsionFunc([p_objPtr, p_funcToBind] (Collider::ColArg p_other) -> Collider::ColRes
			//	{ return p_objPtr->p_funcToBind(p_other); });
	};

	//enum class e_collider
	//{
	//	E_SPHERE,
	//	E_CAPSULE,
	//	E_VERTCAPSULE,
	//	E_BOX
	//};

private:
	GameObject*			m_GO;
	CollsionFunc		m_onCollsionEnterFunc;
	CollsionFunc		m_onCollsionStayFunc;
	CollsionFunc		m_onCollsionExitFunc;

	bool				m_isActive;
	//bool				m_applyGravity;

	std::vector<std::unique_ptr<ICollidable>>	m_collidables;

	//static void DefaultDoNothingCollision(const Collider&);
};

