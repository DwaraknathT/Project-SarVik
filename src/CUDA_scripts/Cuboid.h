#pragma once
#include<glm/gtx/transform.hpp>
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.h"
class Cuboid
{
	VAO vao;
	VertexBuffer vbo;
	IndexBuffer ibuff;
	int count = 0;
	Shader shader;
	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::mat4 model = glm::mat4(1.0f);
public:
	Cuboid() = default;
	
	Cuboid(glm::vec3 p_Pos, float xlength, float ylength, float zlength,glm::vec4 p_Color)
	{
		Vertex vertA;
		Vertex vertB;
		Vertex vertC;
		Vertex vertD;
		Vertex vertE;
		Vertex vertF;
		Vertex vertG;
		Vertex vertH;
		unsigned int indices[] = { 0,1,2,3,0,2,1,3,1,5,0,4,5,4,4,6,5,7,6,7,2,6,3,7 };
		count = sizeof(indices) / sizeof(unsigned int);
		//(0,0,0)
		vertA = CreateVertex(glm::vec3(-xlength/2, -ylength/2, -zlength/2), p_Color);

		//(1,0,0)
		vertB = CreateVertex(glm::vec3(xlength / 2, -ylength / 2, -zlength / 2), p_Color);
		
		//(0,1,0)
		vertC = CreateVertex(glm::vec3(-xlength / 2, ylength / 2, -zlength / 2), p_Color);

		//(1,1,0)
		vertD = CreateVertex(glm::vec3(xlength / 2, ylength / 2, -zlength / 2), p_Color);

		//(0,0,1)
		vertE = CreateVertex(glm::vec3(-xlength / 2, -ylength / 2, zlength / 2), p_Color);

		//(1,0,1)
		vertF = CreateVertex(glm::vec3(xlength / 2, -ylength / 2, zlength / 2), p_Color);

		//(0,1,1)
		vertG = CreateVertex(glm::vec3(-xlength / 2, ylength / 2, zlength / 2), p_Color);

		//(1,1,1)
		vertH = CreateVertex(glm::vec3(xlength / 2, ylength / 2, zlength / 2), p_Color);

		Vertex  GuideVertex[] = { vertA,vertB,vertC,vertD,vertE,vertF,vertG,vertH };
		pos = p_Pos;
		vbo = VertexBuffer(GuideVertex, sizeof(GuideVertex));
		ibuff = IndexBuffer(sizeof(indices), indices);
		model = glm::translate(model, pos);
	}
	void SetShader(Shader p_Shader)
	{
		shader = p_Shader;
		shader.setBool("isTextured", false);
	}
	void Bind()
	{
		shader.Bind();
		vao.Bind();
		vbo.Bind();
		ibuff.Bind();
		glEnableVertexArrayAttrib(vao.GetID(), 0);
		glEnableVertexArrayAttrib(vao.GetID(), 1);
	}
	void Unbind()
	{
		glDisableVertexArrayAttrib(vao.GetID(), 0);
		glDisableVertexArrayAttrib(vao.GetID(), 1);
		ibuff.Bind();
		vbo.Unbind();
		vao.Unbind();

	}
	void Draw()
	{
		Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
		shader.setMat4("model", model);
		glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)0);
		Unbind();
	}
};