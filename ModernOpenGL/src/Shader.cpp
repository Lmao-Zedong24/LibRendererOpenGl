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

	pointLightCount = 0;
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

	uniformDirectionalLight.uniformColor = glGetUniformLocation(m_id, "directionalLight.base.color");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(m_id, "directionalLight.base.aIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(m_id, "directionalLight.direction");
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(m_id, "directionalLight.base.dIntensity");
	uniformShininess = glGetUniformLocation(m_id, "material.shininess");
	uniformSpecularIntensity = glGetUniformLocation(m_id, "material.sIntensity");
	uniformCamPos = glGetUniformLocation(m_id, "camPosition");

	uniformPointLightCount = glGetUniformLocation(m_id, "pointLightCount");

	for (int i = 0; i < 10; i++)
	{
		char locBuff[100] = {'\0'};

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
		uniformPointLight[i].uniformColor = glGetUniformLocation(m_id, locBuff);
		
		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.aIntensity", i);
		uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(m_id, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.dIntensity", i);
		uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(m_id, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLight[i].uniformPosition = glGetUniformLocation(m_id, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
		uniformPointLight[i].uniformConstant = glGetUniformLocation(m_id, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
		uniformPointLight[i].uniformLinear = glGetUniformLocation(m_id, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
		uniformPointLight[i].uniformExponent = glGetUniformLocation(m_id, locBuff);
	}

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

GLuint Shader::GetAmbientIntensityLocation()
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}

GLuint Shader::GetColorLocation()
{
	return uniformDirectionalLight.uniformColor;
}

GLuint Shader::GetDiffuseIntensityLocation()
{
	return uniformDirectionalLight.uniformDiffuseIntensity;
}

GLuint Shader::GetDirectionLocation()
{
	return uniformDirectionalLight.uniformDirection;
}

GLuint Shader::GetSpecularIntensityLocation()
{
	return uniformSpecularIntensity;
}

GLuint Shader::GetShininessLocation()
{
	return uniformShininess;
}

GLuint Shader::GetCamPositionLocation()
{
	return uniformCamPos;
}

void Shader::SetDirectionalLight(DirectionalLight* dLight)
{
	dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColor,
						uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}

void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount)
{
	if (lightCount > 10)
		lightCount = 10;

	glUniform1i(uniformPointLightCount, lightCount);

	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColor,
							uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
							uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
	}
}

GLuint Shader::GetVertexID()
{
	return m_vertexId;
}

GLuint Shader::GetFragID()
{
	return m_fragId;
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
