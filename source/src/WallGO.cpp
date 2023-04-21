#include "WallGO.h"

void RigidGO::SetRigidBodyCollider(Collider* p_rigidBody)
{
    m_rigidBody = p_rigidBody;
}

const Collider& RigidGO::GetRigidBody()
{
	return *m_rigidBody;
}
