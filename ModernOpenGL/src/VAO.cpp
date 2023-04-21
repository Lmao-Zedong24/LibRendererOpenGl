#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &m_id);
	glBindVertexArray(m_id);
}

VAO::~VAO()
{
}

void VAO::LinkVBO(VBO& VBO2, GLuint layout, GLuint numComponents, GLsizei stride, void* offset)
{
	VBO2.Bind();
	glVertexAttribPointer(layout, numComponents, GL_FLOAT, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO2.Unbind();
}

void VAO::Bind()const
{
	glBindVertexArray(m_id);
}

void VAO::Unbind()const
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &m_id);
}
