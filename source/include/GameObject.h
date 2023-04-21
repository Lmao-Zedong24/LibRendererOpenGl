#pragma once
#include "Model.h"
#include "ITransformable.h"
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

class EmptyGO;

class GameObject
{
public:
	struct Layer
	{
		size_t val;

		Layer() : Layer(0) {};
		Layer(size_t i) : 
			val(i) {};

		bool operator==(Layer p_l) { return val == p_l.val; };

		bool IsName(const std::string& p_name)
		{
			return val == FetchLayer(p_name).val;
		};
	};
	static enum class e_colors
	{
		DEFAULT,
		RED,
		GREEN,
		BLUE
	};

	using Childreen = std::unordered_map<std::string, std::unique_ptr<GameObject>>;
	using Color		= e_colors; // TODO : use colors


	GameObject(GameObject* p_parent);
	GameObject(GameObject* p_parent, Model* p_model, Texture* p_texture);
	~GameObject() = default;

	static Layer				FetchLayer(const std::string& p_name);

	void						SetupEntity(Model* p_model, Texture* p_texture);
	void						SetModel(Model* p_model);
	void						SetTexture(Texture* p_texture);
	void						SetLayer(Layer);

	Layer						GetLayer()const;
	Transform&					GetLocalTransform();
	const Transform&			GetLocalTransform()const;
	const LibMath::Matrix4&		GetGlobalMat()const;
	GameObject*					GetParent();
	Childreen&					GetChildreen();

	virtual void				Update();
	void						DrawNodes(Shader& p_shader, Camera& p_camera);
	void						SetUniform(Shader& p_shader, Camera& p_camera);
	void						UpdateGlobalMat();
	EmptyGO*					AddCapsuleChild(float p_height, float p_radius, Model* p_sphereModel, 
												Model* p_cylindreModel, Texture* p_texture);

	bool						HasColor()const;
	void						SetColor(e_colors p_color);
	Color						GetColor()const;
	bool						IsSameColor(const Color& p_color)const;
	void						SwitchColorTexture(const Color& p_color);

	template <typename T>
	T* GetChild(const std::string& p_name)
	{
		if (!(std::is_same_v<GameObject, T> || std::is_base_of_v<GameObject, T>))
			return nullptr;

		if (m_children.count(p_name) != 0)
			return static_cast<T*>(m_children.at(p_name).get());
		//return m_children.at(p_name).get();

		return nullptr;
	};

	template <typename T>
	T* AddChild(const std::string& p_name)
	{
		if (!(std::is_same_v<GameObject, T> || std::is_base_of_v<GameObject, T>))
			return nullptr;

		this->m_children.insert({ p_name, std::make_unique<T>(this) });
		T* childPtr = static_cast<T*>(this->m_children.at(p_name).get());
		//childPtr->m_parent = this;

		return childPtr;
	}

	template <typename T>
	T* AddChild(const std::string& p_name, Model* p_model, Texture* p_texture)
	{
		if (std::is_same_v<EmptyGO, T> || !(std::is_same_v<GameObject, T> || std::is_base_of_v<GameObject, T>))
			return nullptr;

		this->m_children.insert({ p_name, std::make_unique<T>(this, p_model, p_texture) });
		T* childPtr = static_cast<T*>(this->m_children.at(p_name).get());
		//childPtr->m_parent = this;

		//childPtr->SetupEntity(p_model, p_texture);

		return childPtr;
	};

	template <typename T>
	void AddChildreen(	std::vector<std::string>& p_names,
						std::vector<Model*>& p_models, std::vector<Texture*>& p_textures)
	{
		if (!(std::is_same_v<GameObject, T> || std::is_base_of_v<GameObject, T>))
			return;

		if (p_models.empty())
			p_models.emplace_back(nullptr);

		if (p_textures.empty())
			p_models.emplace_back(nullptr);

		size_t mIndex = 0, tIndex = 0; //model index, texture index
		for (size_t nIndex = 0; nIndex < p_names.size(); nIndex++) // name index
		{
			this->m_children.insert({ p_names[nIndex], std::make_unique<T>(this) });
			T* childPtr = static_cast<T*>(this->m_children.at(p_names[nIndex]).get());
			//childPtr->m_parent = this;

			if (!(p_models[mIndex] == nullptr || p_textures[tIndex] == nullptr))
				childPtr->SetupEntity(p_models[mIndex], p_textures[tIndex]);

			mIndex += mIndex < p_models.size() - 1 ? 1 : 0; //increment if not at end of array
			tIndex += tIndex < p_textures.size() - 1 ? 1 : 0;
		}
	};

protected:
	static std::vector<std::string>		LayerNames;

	Model* 						m_model;
	Texture* 					m_texture;

	GameObject*					m_parent;
	Childreen					m_children;
	Layer						m_layer;
	Color						m_color;

	Transform					m_localTransform;
	LibMath::Matrix4			m_globalMat;
	LibMath::Matrix4			m_projViewModelMat; 

	static Texture* GetTextureColor(e_colors p_color);
};



