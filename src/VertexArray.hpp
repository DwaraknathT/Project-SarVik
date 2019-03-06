#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
class VAO
{
private:
	GLuint m_ID;
	bool bound = false;
public:
	VAO()
	{
		
	}
	void Bind()
	{
		if (!bound)
		{
			bound = true;
			glGenVertexArrays(1, &m_ID);
		}
		glBindVertexArray(m_ID);
	}
	void Unbind() {
		glBindVertexArray(0);
	}
	GLuint GetID() const
	{
		return m_ID;
	}
};