#include "Light.h"

Light::Light(LibMath::Vector3 p_pos) : Light(p_pos, LibMath::Vector3(0.4f, 0.35f, 0.25f))
{
}

Light::Light(LibMath::Vector3 p_pos, LibMath::Vector3 p_com) : m_pos(p_pos), m_com(p_com)
{
}

void Light::SetUniformLight(Shader& p_shader)
{
	glUniformMatrix4fv(p_shader.GetUniformLocation(this->UniformLightPos), 1, GL_FALSE, (GLfloat*)&m_pos);
	glUniformMatrix4fv(p_shader.GetUniformLocation(this->UniformLightPos), 1, GL_FALSE, (GLfloat*)&m_pos);
}

