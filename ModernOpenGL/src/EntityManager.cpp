#include "EntityManager.h"

//EntityTree* EntityManager::AddEntityTree(const std::string& p_name, EntityTree& p_entityPtr)
//{
//	this->Remove(p_name);
//
//	this->m_resources.insert({ p_name, std::make_unique<EntityTree>(std::move(p_entityPtr)) });
//
//	return m_resources.at(p_name).get();
//}
//
//EntityTree* EntityManager::Get(const std::string& p_name)
//{
//	if (this->m_resources.count(p_name) != 0)
//		return m_resources.at(p_name).get();
//}
//
//void EntityManager::Remove(const std::string& p_name)
//{
//	if (this->m_resources.count(p_name) != 0)
//		m_resources.erase(p_name);
//}

void EntityManager::DrawAllEntities(Shader& p_shader, Camera& p_camera)
{
	for (auto& pair : m_entities)
		pair.second->DrawNodes(p_shader, p_camera);

	//this->m_entities.insert({ "tmpStr", std::make_unique<GameObject>(new GameObject(""))});

}
