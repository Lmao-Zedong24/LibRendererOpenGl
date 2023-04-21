#pragma once
#include "IResource.h"
#include <glad/glad.h>
#include <string>

#include "Light.h"

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

	//lighting
	GLuint GetAmbientIntensityLocation();
	GLuint GetColorLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetCamPositionLocation();

	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);

	GLuint GetVertexID();
	GLuint GetFragID();

	GLint m_id = 0;
private:
	GLuint m_vertexId = 0;
	GLuint m_fragId = 0;
	
	//lighting
	int pointLightCount;

	GLuint uniformSpecularIntensity, uniformShininess;

	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} uniformDirectionalLight;

	GLuint uniformPointLightCount;

	struct
	{
		GLuint uniformColor;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;

		GLuint uniformConstant;
		GLuint uniformLinear;
		GLuint uniformExponent;
	} uniformPointLight[10];

	GLuint uniformCamPos;

	const std::string ShaderPath = "../../ModernOpenGL/shaders/";

	static bool checkValidShader(GLint p_id);
};

