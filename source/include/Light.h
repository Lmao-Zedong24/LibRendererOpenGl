#pragma once
#include "LibMath/Vector/Vector3.h"
#include "Shader.h"

class Light
{
public:
	Light() = default;
	Light(LibMath::Vector3 p_pos);
	Light(LibMath::Vector3 p_pos, LibMath::Vector3 p_com);

	void SetUniformLight(Shader& p_shader);

private:
	LibMath::Vector3 m_pos;
	LibMath::Vector3 m_com;
	const char* UniformLightPos = "lightPos";
	const char* UniformLightCom = "lightCom";
};

