#include "Light.h"

Light::Light()
{
	color = { 1.0f,1.0f,1.0f };
	aIntensity = 1;

	dIntensity = 0.0f;
}

Light::Light(LibMath::Vector3 color, float aIntensity, float dIntensity)
{
	this->color = color;
	this->aIntensity = aIntensity;

	this->dIntensity = dIntensity;
}

DirectionalLight::DirectionalLight() : Light()
{
	direction = { 0,1.0f,0 };
}

DirectionalLight::DirectionalLight(LibMath::Vector3 color, float aIntensity,
									LibMath::Vector3 direction, float dIntensity)
									: Light(color, aIntensity, dIntensity)
{
	this->direction = direction;
}

void DirectionalLight::UseLight(float aIntensityLocation, float colorLocation, float dIntensityLocation, float directionLocation)
{
	glUniform3f(colorLocation, color.m_x, color.m_y, color.m_x);
	glUniform1f(aIntensityLocation, aIntensity);

	glUniform3f(directionLocation, direction.m_x, direction.m_y, direction.m_x);
	glUniform1f(dIntensityLocation, dIntensity);

}

PointLight::PointLight() : Light()
{
	position = { 0,0,0 };
	constant = 1;
	linear = 0;
	exponent = 0;
}

PointLight::PointLight(LibMath::Vector3 color, float aIntensity,
						LibMath::Vector3 position, float dIntensity,
						float constant, float linear, float exponent)
						: Light(color, aIntensity, dIntensity)
{
	this->position = position;
	this->constant = constant;
	this->linear = linear;
	this->exponent = exponent;
}

void PointLight::UseLight(float aIntensityLocation, float colorLocation,
						float dIntensityLocation, float positionLocation,
						float constantLocation, float linearLocation, float exponentLocation)
{
	glUniform3f(colorLocation, color.m_x, color.m_y, color.m_x);
	glUniform1f(aIntensityLocation, aIntensity);

	glUniform3f(positionLocation, position.m_x, position.m_y, position.m_x);
	glUniform1f(dIntensityLocation, dIntensity);

	glUniform1f(constantLocation, constant);
	glUniform1f(linearLocation, linear);
	glUniform1f(exponentLocation, exponent);
}
