#pragma once
#include <LibMath/header/Vector/Vector3.h>

#include <glad/glad.h>

class Light
{
public:
	Light();
	Light(LibMath::Vector3 color, float aIntensity, float dIntensity);

protected:
	LibMath::Vector3 color;
	float aIntensity;
	float dIntensity;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(LibMath::Vector3 color, float aIntensity,
		LibMath::Vector3 direction, float dIntensity);

	void UseLight(GLuint aIntensityLocation, GLuint colorLocation, GLuint dIntensityLocation, GLuint directionLocation);

private:
	LibMath::Vector3 direction;
};

class PointLight : public Light
{
public:
	PointLight();
	PointLight(LibMath::Vector3 color, float aIntensity,
			LibMath::Vector3 position, float dIntensity,
			float constant, float linear, float exponent);

	void UseLight(GLuint aIntensityLocation, GLuint colorLocation, GLuint dIntensityLocation, GLuint positionLocation,
				GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

private:
	LibMath::Vector3 position;
	float constant, linear, exponent;
};