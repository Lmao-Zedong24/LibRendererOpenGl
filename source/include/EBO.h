#pragma once
#include <glad/glad.h>

class EBO
{
public:
	EBO(GLuint* p_indices, GLsizeiptr size);
	~EBO() = default;

	void Bind();
	void Unbind();
	void Delete();

	GLuint m_id;
private:
};

