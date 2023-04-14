#pragma once
#include "IResource.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Texture : public IResource
{
public:
	Texture(const std::string& p_fileName);

	bool SetTexture(const std::string& p_fileName);
	void Bind();
	void Unbind();
	void Delete()override;

	GLuint m_id;
private:
	const std::string TexturePath = "assets/textures/";
};

