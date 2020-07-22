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
Vertex CreateVertex(glm::vec3 p_Pos, glm::vec4 p_Color, glm::vec2 p_UV = glm::vec2(0.0f, 0.0f))
{
	Vertex vertex;
	vertex.x = p_Pos.x;
	vertex.y = p_Pos.y;
	vertex.z = p_Pos.z;
	vertex.r = p_Color.r;
	vertex.g = p_Color.g;
	vertex.b = p_Color.b;
	vertex.a = p_Color.a;
	vertex.u = p_UV.x;
	vertex.v = p_UV.y;
	return vertex;
}
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