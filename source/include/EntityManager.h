#pragma once
#include "GameObject.h"
#include <unordered_map>
#include <vector>
#include <memory>


class EntityManager
{
public:
	EntityManager() = default;
	~EntityManager() = default;

	template <typename T>
	T* Add(const std::string& p_name, GameObject* p_parent)
	{
		if (!(std::is_same_v<GameObject, T> || std::is_base_of_v<GameObject, T>))
			return nullptr;

		if (this->m_entities.count(p_name) != 0)
			return nullptr;

		//auto tmpStr = p_entity->GetName();
		this->m_entities.insert({ p_name, std::make_unique<T>(p_parent)});

		return static_cast<T*>(m_entities.at(p_name).get());

	};

	template <typename T>
	T* Add(const std::string& p_name, GameObject* p_parent, Model* p_model, Texture* p_texture)
	{
		T* entityPtr = this->Add<T>(p_name, p_parent);

		if (entityPtr != nullptr)
			entityPtr->SetupEntity(p_model, p_texture);

		return entityPtr;
	};

	template <typename T>
	T* Get(const std::string& p_name)
	{
		if (this->m_entities.count(p_name) != 0)
			return static_cast<T*>(this->m_entities.at(p_name).get());

		return nullptr;
	};

	void DrawAllEntities(Shader& p_shader, Camera& p_camera);

	//void Delete(const std::string& p_fileName);
	//void DeleteAll();

private:
	std::unordered_map<std::string, std::unique_ptr<GameObject>> m_entities;
};

