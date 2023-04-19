#pragma once
#include <LibMath/header/Vector/Vector3.h>
#include "Shader.h"

class Light
{
public:
	Light();
	Light(LibMath::Vector3 color, float	ambientIntensity, LibMath::Vector3 direction, float diffuseIntensity);
	~Light();

	/*Light(LibMath::Vector3 p_pos);
	Light(LibMath::Vector3 p_pos, LibMath::Vector3 p_com);*/

	//void SetUniformLight(Shader& p_shader);

	void UseLight(float ambientIntesityLocation, float ambientColorLocation, float diffuseIntensityLocation, float directionLocation);


private:
	/*LibMath::Vector3 m_pos;
	LibMath::Vector3 m_com;*/

	LibMath::Vector3 color;
	float	ambientIntensity;

	LibMath::Vector3 direction;
	float diffuseIntensity;

	/*const char* UniformLightPos = "lightPos";
	const char* UniformLightCom = "lightCom";*/
};

