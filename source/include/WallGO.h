#pragma once
#include "GameObject.h"
#include "RigidBody.h"

class RigidGO : public GameObject
{
public:
	RigidGO(GameObject* p_parent) : 
		GameObject(p_parent), m_rigidBody(nullptr){};
	RigidGO(GameObject* p_parent, Model* p_model, Texture* p_texture) : 
		GameObject(p_parent, p_model, p_texture), m_rigidBody(nullptr) {};
	~RigidGO() = default;

	void				SetRigidBodyCollider(Collider* p_rigidBody);
	const Collider&		GetRigidBody();

private:
	Collider*	m_rigidBody;	//dont need to update bcs static wall

};


