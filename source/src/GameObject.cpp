#include "GameObject.h"
#include "EmptyGM.h"


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

//const std::string& GameObject::GetName()
//{
//	return m_name;
//}

Transform& GameObject::GetLocalTransform()
{
	return m_localTransform;
}

const LibMath::Matrix4& GameObject::GetGlobalMat()
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
	this->UpdateGlobalMat();

	if (m_texture)
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

GameObject::Layer GameObject::GetLayer(const std::string& p_name)
{
	for (size_t i = 0; i < LayerNames.size(); i++)
	{
		if (LayerNames[i] == p_name)
			return i;
	}

	LayerNames.push_back(p_name);
	return LayerNames.size() - 1;
}

