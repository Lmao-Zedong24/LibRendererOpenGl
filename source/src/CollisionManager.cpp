#include "CollisionManager.h"

//void My::CollisionManager::Init()
//{
//}

Collider* My::CollisionManager::AddCollider(	GameObject* p_GO, 
												std::vector<std::unique_ptr<ICollidable>>& p_collidables, 
												Collider::CollsionFunc p_collisionFuncs[3])
{
	m_colliders.push_back(std::make_unique<Collider>(p_GO, p_collidables, p_collisionFuncs));
	//return nullptr;
	return m_colliders.back().get();
}

void My::CollisionManager::SortAndSweep()
{
}

void My::CollisionManager::Update()
{
	if (m_colliders.empty())
		return;

	// Disabled RigidBodies at end of list
	std::sort(m_colliders.begin(), m_colliders.end(), m_compareAABB);

	LibMath::Vector3	centerSum,	centerSumSq;
	Collider*			aCol,		*bCol; //Collider a and b
	std::map<Collider*, std::list<Collider*>> collisionMap;

	for (size_t i = 0; i < m_colliders.size(); i++) //for all colliders
	{
		aCol = m_colliders[i].get();

		if (!aCol->IsActive())
			break;

		LibMath::Vector3 center = aCol->GetCollidables()[0].get()->GetCenter();
		centerSum += center;
		centerSum += center * center;

		for (size_t j = i + 1; j < m_colliders.size(); j++)
		{
			bCol = m_colliders[j].get();

			float aMax = aCol->GetCollidables()[0].get()->GetMax(m_compareAABB.m_axis);
			float bMin = bCol->GetCollidables()[0].get()->GetMin(m_compareAABB.m_axis);

			if (!bCol->IsActive() || //if not active or not in axis min/max, stop comparing
				aMax < bMin)
				break;

			//check collision
			if (aCol->CheckCollision(*bCol)) // TODO : compare all collidables
			{
				//add to collision map
				collisionMap[aCol].push_back(bCol);
				collisionMap[bCol].push_back(aCol);
			}
		}
	}

	//Do collsions
	{
		for (auto& pair : collisionMap) //new collision 
		{
			aCol = pair.first;
			auto& collisionWithA =	pair.second;
			bool hasOldCollisions = static_cast<bool>(m_oldInCollision.count(aCol));

			for (auto& collider : collisionWithA) //new colliders with aCol
			{
				bCol = collider;
				bool isNewCol = true;

				if (hasOldCollisions)
				{
					for (auto itt = m_oldInCollision[aCol].begin(); itt != m_oldInCollision[aCol].end(); itt++) //old collision of aCol
					{
						auto wasColliding = *itt;
						if (bCol == wasColliding)				//already colliding
						{
							aCol->OnCollsionStay(*bCol);		//Proc OnCollisionStay
							isNewCol = false;
							m_oldInCollision[aCol].erase(itt);	//Remove from old collisions
							break;
						}
					}
				}

				if (isNewCol)								// bCol is new collision of aCol
					aCol->OnCollsionEnter(*bCol);			//Proc OnCollsionEnter
			}
		}


		for (auto& oldPair : m_oldInCollision)				//all old collision that didn't Stayed
		{
			auto oldA = oldPair.first;

			for (auto& oldB : oldPair.second)				//old collision of oldA and oldB
				oldA->OnCollsionExit(*oldB);				//Proc  OnCollsionExit
		}
			
		m_oldInCollision = collisionMap;					//After collisions => update old collision map
	}


	// Set Max Var axis
	{
		centerSum	/= static_cast<float>(m_colliders.size());
		centerSumSq /= static_cast<float>(m_colliders.size());

		LibMath::Vector3 variance = centerSumSq - (centerSum * centerSum);

		float maxVar =		variance[0];
		int	maxVarAxis =	0;

		if (maxVar < variance[1])
		{
			maxVar = variance[1];
			maxVarAxis = 1;
		}

		if (maxVar < variance[2])
		{
			maxVar = variance[2];
			maxVarAxis = 2;
		}

		m_compareAABB.m_axis = maxVarAxis;
	}
}

My::CollisionManager* My::CollisionManager::GetInstance()
{
	if (!m_CollisionManager)
		m_CollisionManager = std::make_unique<CollisionManager>();

	return m_CollisionManager.get();
}