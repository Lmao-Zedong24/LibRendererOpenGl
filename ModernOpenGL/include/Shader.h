#pragma once
#include "IResource.h"
#include <glad/glad.h>
#include <string>

class Shader : public IResource
{
public:
	Shader() = default;
	Shader(const std::string& p_fileBuffer);
	~Shader() = default;

	bool SetVertexShader(const std::string& p_filename);
	bool SetFragmentShader(const std::string& p_filename);

	bool Link();
	void Activate();
	void Delete()override;

	GLint GetUniformLocation(const std::string& p_uniformName)const;

	GLint m_id = 0;
private:
	GLuint m_vertexId = 0;
	GLuint m_fragId = 0;

	const std::string ShaderPath = "source/shaders/";

	static bool checkValidShader(GLint p_id);
};

