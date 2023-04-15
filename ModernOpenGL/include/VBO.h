#pragma once
#include <glad/glad.h>

class VBO
{
public:
	VBO(GLfloat* vertices, GLsizeiptr size);
	~VBO() = default;

	void Bind();
	void Unbind();
	void Delete();

	GLuint m_id;
private:
};

