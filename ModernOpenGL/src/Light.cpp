#include "Light.h"

//Light::Light(LibMath::Vector3 p_pos) : Light(p_pos, LibMath::Vector3(0.4f, 0.35f, 0.25f))
//{
//}
//
//Light::Light(LibMath::Vector3 p_pos, LibMath::Vector3 p_com) : m_pos(p_pos), m_com(p_com)
//{
//}
//
//void Light::SetUniformLight(Shader& p_shader)
//{
//	glUniformMatrix4fv(p_shader.GetUniformLocation(this->UniformLightPos), 1, GL_FALSE, (GLfloat*)&m_pos);
//	glUniformMatrix4fv(p_shader.GetUniformLocation(this->UniformLightPos), 1, GL_FALSE, (GLfloat*)&m_pos);
//}

Light::Light()
{
	color = LibMath::Vector3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;

	direction = LibMath::Vector3(0.0f, -1.0f, 0.0f);
	//diffuseIntensity
}

Light::Light(LibMath::Vector3 color, float	ambientIntensity, LibMath::Vector3 direction, float diffuseIntensity)
{
	color = LibMath::Vector3(color);
	ambientIntensity = ambientIntensity;
}

Light::~Light()
{

}

void Light::UseLight(float ambientIntesityLocation, float ambientColorLocation, float diffuseIntensityLocation, float directionLocation)
{
	glUniform3f(ambientColorLocation, color.m_x, color.m_y, color.m_z);
	glUniform1f(ambientIntesityLocation, ambientIntensity);
}

