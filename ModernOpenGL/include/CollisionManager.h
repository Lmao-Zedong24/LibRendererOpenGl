#pragma once
#include "RigidBody.h"
#include <vector>
#include <list>

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

private:
	std::vector<RigidBody*> m_rigidBodies;
	std::list<RigidBody[2]>	m_onCollision;


};

