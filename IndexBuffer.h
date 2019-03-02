#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
class IndexBuffer
{
private:
	unsigned int id;
public:
	IndexBuffer()
	{

	}
	IndexBuffer(unsigned int size, unsigned int * data,unsigned int draw = GL_DYNAMIC_DRAW)
	{
		glGenBuffers(1,&id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,draw);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
	void Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
};