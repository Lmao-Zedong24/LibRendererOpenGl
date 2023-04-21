#pragma once
#include "RigidBody.h"
#include "GameObject.h"
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <map>

namespace My
{
	
	struct CollisionManagerRigiBodyCompare
	{
		int m_axis;

		CollisionManagerRigiBodyCompare(int p_axis = 0) :
			m_axis(p_axis) {};

		//smaller < bigger < (NotActive A < NotActive B)
		//p_A Bigger	=> false
		//p_B Bigger	=> true
		bool operator()(const std::unique_ptr<Collider>& p_A, const std::unique_ptr<Collider>& p_B) 
		{
			if (!p_B->IsActive())	//B Not active => B Bigger => true
				return true;

			if (!p_A->IsActive())	//B active, A not active => A Biger => false
				return false;

			return	p_A->GetCollidables()[0].get()->GetMin(m_axis) < //min a is smaller then min b in axis (most general collider is 0)
					p_B->GetCollidables()[0].get()->GetMin(m_axis);
		}
	};

	//struct CollisionManagerRigiBodyCompare
	//{
	//	int m_axis;

	//	CollisionManagerRigiBodyCompare(int p_axis = 0) :
	//		m_axis(p_axis) {};

	//	bool operator()(const std::unique_ptr<Collider>& p_A, const std::unique_ptr<Collider>& p_B)
	//	{
	//		if (!p_A->IsActive())
	//			return false;

	//		return	p_A->GetCollidables()[0].get()->GetMin(m_axis) < //min a is smaller then min b in axis (most general collider is 0)
	//			p_B->GetCollidables()[0].get()->GetMin(m_axis);
	//	}
	//};

	class CollisionManager
	{
	public:

		CollisionManager() = default;
		~CollisionManager() = default;

		Collider* AddCollider(	GameObject* p_GO, std::vector<std::unique_ptr<ICollidable>>& p_collidables,
									Collider::CollsionFunc p_collisionFuncs[3] = (nullptr, nullptr, nullptr));

		void SortAndSweep();
		void Update();

		static CollisionManager* GetInstance();

	private:
		static inline std::unique_ptr<CollisionManager> m_CollisionManager;

		std::vector<std::unique_ptr<Collider>>					m_colliders;
		std::map<Collider*, std::list<Collider*>>				m_oldInCollision;
		//std::map<Collider*, size_t>							m_checkCollision;

		CollisionManagerRigiBodyCompare							m_compareAABB;



	};
}


