#include "Shader.h"
#include <sstream>
#include <string>
#include <fstream>

Shader::Shader(const std::string& p_fileName)
{
	std::ifstream file;
	std::string line;
	file.open(ShaderPath + p_fileName);

	if (file.is_open())
	{
		std::getline(file, line);
		SetVertexShader(line);

		std::getline(file, line);
		SetFragmentShader(line);
	}
}

bool Shader::SetVertexShader(const std::string& p_filename)
{
	std::string tmp = ReadFile(p_filename, ShaderPath);

	if (tmp.empty())
		return false;

	this->m_vertexId = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSource = tmp.c_str();

	glShaderSource(m_vertexId, 1, &vertexSource, NULL);
	glCompileShader(m_vertexId);

	return checkValidShader(m_vertexId);
}

bool Shader::SetFragmentShader(const std::string& p_filename)
{
	std::string str = ReadFile(p_filename, ShaderPath);

	if (str.empty())
		return false;

	this->m_fragId = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSource = str.c_str();

	glShaderSource(m_fragId, 1, &fragmentSource, NULL);
	glCompileShader(m_fragId);

	return checkValidShader(m_fragId);
}

bool Shader::Link()
{
	m_id = glCreateProgram();
	glAttachShader(m_id, m_vertexId);
	glAttachShader(m_id, m_fragId);

	glLinkProgram(m_id);

	glDeleteShader(m_vertexId);
	glDeleteShader(m_fragId);

	return checkValidShader(m_id);
}

void Shader::Activate()
{
	glUseProgram(m_id);
}

void Shader::Delete()
{
	glDeleteProgram(m_id);
}

GLint Shader::GetUniformLocation(const std::string& p_uniformName) const
{
	return glGetUniformLocation(m_id, p_uniformName.c_str());
}

bool Shader::checkValidShader(GLint p_id)
{
	GLint res;
	GLchar log[1024];

	glGetProgramiv(p_id, GL_LINK_STATUS, &res);
	if (!res)
	{
		glGetProgramInfoLog(p_id, sizeof(log), NULL, log);//TODO : remove comment
		std::cout << "Shader Error : " << log << std::endl; //ligma 
		return false;
	}
	return true;
}
