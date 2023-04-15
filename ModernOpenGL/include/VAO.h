#pragma once
#include <glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	VAO();
	~VAO();

	void LinkVBO(	VBO& VBO2, GLuint layout, GLuint numComponents, 
					GLsizei stride, void* offset);
	void Bind()const;
	void Unbind()const;
	void Delete();

	GLuint m_id;
private:

};

