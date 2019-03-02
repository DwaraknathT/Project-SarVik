#pragma once
#include <GL/GL.h>
#include <GL/glew.h>
#include <gl/GLU.h>
struct Vertex {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 0.0f;
	float u = 0.0f;
	float v = 0.0f;
};
class VertexBuffer
{
private:
	unsigned int m_ID;
	bool set;
	unsigned int size = 0;
public:
	VertexBuffer()
	{

	}
	VertexBuffer(const void * p_Data, unsigned int p_Size, unsigned int p_Draw = GL_DYNAMIC_DRAW)
	{
		size = p_Size;
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, p_Size, p_Data, p_Draw);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	VertexBuffer(unsigned int size);
	//To Add:
	/*
	VertexBuffer(const Model model);
	*/
	void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}
	void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	unsigned int getID() const
	{
		return m_ID;
	}
};