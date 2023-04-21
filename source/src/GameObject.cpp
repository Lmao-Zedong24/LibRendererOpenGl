#include "GameObject.h"
#include "EmptyGO.h"
#include "AllGO.h"
#include "PFA/PFAGM.h"


std::vector<std::string> GameObject::LayerNames = { "default" };

GameObject::GameObject(GameObject* p_parent)
{
	m_model = nullptr;
	m_texture = nullptr;
	m_parent = p_parent;

	m_localTransform.setTransform(LibMath::Matrix4(1));
	m_globalMat = LibMath::Matrix4(1);
	this->m_children;
}

GameObject::GameObject(GameObject* p_parent, Model* p_model, Texture* p_texture) :
	m_model(p_model), m_texture(p_texture)
{
	m_parent = p_parent;
	m_localTransform.setTransform(LibMath::Matrix4(1));
	m_globalMat = LibMath::Matrix4(1);
}

void GameObject::SetupEntity(Model* p_model, Texture* p_texture)
{
	m_model = p_model;
	m_texture = p_texture;
}

void GameObject::SetModel(Model* p_model)
{
	m_model = p_model;
}

void GameObject::SetTexture(Texture* p_texture)
{
	m_texture = p_texture;
}

void GameObject::SetLayer(Layer p_layer)
{
	m_layer = p_layer;
}

//const std::string& GameObject::GetName()
//{
//	return m_name;
//}

GameObject::Layer GameObject::GetLayer() const
{
	return m_layer;
}

Transform& GameObject::GetLocalTransform()
{
	return m_localTransform;
}

const Transform& GameObject::GetLocalTransform() const
{
	return m_localTransform;
}

const LibMath::Matrix4& GameObject::GetGlobalMat()const
{
	return m_globalMat;
}

GameObject* GameObject::GetParent()
{
	return m_parent;
}

GameObject::Childreen& GameObject::GetChildreen()
{
	return m_children;
}

void GameObject::DrawNodes(Shader& p_shader, Camera& p_camera)
{
	//if (m_model == nullptr || m_texture == nullptr)
	//	return;

	//this->UpdateGlobalMat();
	//this->UpdateGlobalMat();

	if (m_model && m_texture)
	{
		this->SetUniform(p_shader, p_camera);
		m_model->Draw(*m_texture, p_shader, p_camera);
	}

	for (auto& child : m_children)
		child.second->DrawNodes(p_shader, p_camera); //recursive with all childreen ? 
}

void GameObject::SetUniform(Shader& p_shader, Camera& p_camera)
{
	m_projViewModelMat = p_camera.getViewProjMatrix() * m_globalMat * m_model->getTransform();

	//m_projViewModelMat = p_camera.getViewProjMatrix() * m_globalTransform.getTransform() * m_localTransform.getTransform() * m_model->getTransform();
	glUniformMatrix4fv(p_shader.GetUniformLocation("vertMat"), 1, GL_FALSE, (GLfloat*)&m_projViewModelMat[0]);
}

void GameObject::UpdateGlobalMat()
{
	m_globalMat = this->m_parent != nullptr ?	this->m_parent->GetGlobalMat() * m_localTransform.getTransform() :
												m_localTransform.getTransform();
}

EmptyGO* GameObject::AddCapsuleChild(float p_height, float p_radius, Model* p_sphereModel, Model* p_cylindreModel, Texture* p_texture)
{
	std::vector<std::string>	names = { "sphere1", "cylindre1", "sphere2"};
	std::vector<Model*>			models = { p_sphereModel, p_cylindreModel, p_sphereModel };
	std::vector<Texture*>		textures = { p_texture };

	EmptyGO* capasule = this->AddChild<EmptyGO>("capsule");
	capasule->AddChildreen<GameObject>(names, models, textures);

	Transform& s1 = capasule->GetChild<GameObject>(names[0])->GetLocalTransform();
	Transform& c1 = capasule->GetChild<GameObject>(names[1])->GetLocalTransform();
	Transform& s2 = capasule->GetChild<GameObject>(names[2])->GetLocalTransform();

	s1.translate(0, p_height / 4.0f, 0); //move s1 upwards
	s2.translate(0, -p_height / 4.0f, 0); //move s2 downwards

	s1.scale(p_radius); //scale s1 to radius
	s2.scale(p_radius); //scale s2 to radius

	c1.scale(p_radius, p_height, p_radius); //scale y axis by height, scale x anx z axis by radius

	return capasule;
}

bool GameObject::HasColor() const
{
	return m_color != Color::DEFAULT;
}

GameObject::Color GameObject::GetColor() const
{
	return m_color;
}

bool GameObject::IsSameColor(const Color& p_color)const
{
	return m_color == p_color;
}

void GameObject::SwitchColorTexture(const Color& p_color)
{
	if (m_color == Color::DEFAULT)
		return;

	m_color = p_color;
	this->SetTexture(GameObject::GetTextureColor(p_color));
}


void GameObject::SetColor(e_colors p_color)
{
	m_color = p_color;
}

Texture* GameObject::GetTextureColor(e_colors p_color)
{
	auto& rm = PFA::PFAGM::GetInstance()->GetRM();
	std::string texName;

	switch (p_color)
	{
	case GameObject::e_colors::RED:
		texName = "red.png";
		break;

	case GameObject::e_colors::GREEN:
		texName = "green.png";
		break;

	case GameObject::e_colors::BLUE:
		texName = "blue.png";
		break;

	case GameObject::e_colors::DEFAULT:
	default:
		return nullptr;
		break;
	}

	return rm.Get<Texture>(texName);
}

void GameObject::Update()
{
	this->UpdateGlobalMat();

	for (auto& child : m_children)
		child.second->Update(); 
}

GameObject::Layer GameObject::FetchLayer(const std::string& p_name)
{
	for (size_t i = 0; i < LayerNames.size(); i++)
	{
		if (LayerNames[i] == p_name)
			return i;
	}

	LayerNames.push_back(p_name);
	return LayerNames.size() - 1;
}

