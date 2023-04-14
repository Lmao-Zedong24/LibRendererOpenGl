#pragma once
#include <unordered_map>
#include"IResource.h"
#include <memory>
#include <string>

class ResourceManager
{
public:
	ResourceManager() = default;
	~ResourceManager() = default;

	template <typename T>
	T* Add(const std::string& p_fileName)
	{
		if (!(std::is_same_v<IResource, T> || std::is_base_of_v<IResource, T>))
			return nullptr;

		if (this->m_resources.count(p_fileName) != 0)
			this->m_resources.erase(p_fileName);

		this->m_resources.insert({	p_fileName, 
									std::make_unique<T>(p_fileName) });

		return static_cast<T*>(m_resources.at(p_fileName).get());
	};

	template <typename T>
	T* Get(const std::string& p_fileName)
	{
		if (this->m_resources.count(p_fileName) != 0)
			return static_cast<T*>(this->m_resources.at(p_fileName).get());

		return nullptr;
	};

	void Delete(const std::string& p_fileName);
	void DeleteAll();

private:
	std::unordered_map<std::string, std::unique_ptr<IResource>> m_resources;
};

