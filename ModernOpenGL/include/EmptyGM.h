#pragma once
#include "Model.h"
#include "Texture.h"
#include "GameObject.h"

class EmptyGO : public GameObject
{
public:
	EmptyGO(GameObject* p_parent) : GameObject(p_parent)
	{};

	EmptyGO(GameObject*, Model*, Texture*) = delete;
	void SetupEntity(Model* p_model, Texture* p_texture) = delete;
};

