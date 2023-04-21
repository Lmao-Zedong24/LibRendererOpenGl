#pragma once
#include "IResource.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Texture : public IResource
{
public:
	Texture(const std::string& p_fileName, float specularIntensity, float shininess);

	bool SetTexture(const std::string& p_fileName);
	void Bind();
	void Unbind();
	void Delete()override;

	void UseText(int specularIntensityLocation, int shininessLocation);

	GLuint m_id;
private:
	const std::string TexturePath = "../../assets/textures/";

	float specularIntensity;
	float shininess;
};

