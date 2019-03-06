#pragma once
#include<glm/glm.hpp>
#include "Shaders.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
class GuideLines
{
	VAO vao;
	VertexBuffer vbo;
	Shader shader;
	glm::vec3 pos = glm::vec3(0,0,0);
	glm::mat4 model = glm::mat4(1.0f);
public:
	GuideLines() = default;
	GuideLines(glm::vec3 p_Pos)
	{
		Vertex posX;
		Vertex negX;
		Vertex posY;
		Vertex negY;
		Vertex posZ;
		Vertex negZ;
	
		posX.x = 100.0f;
		posX.r = 1.0f;
		posX.a = 1.0f;
		posY.y = 100.0f;
		posY.r = 1.0f;
		posY.a = 1.0f;
		posZ.z = 100.0f;
		posZ.r = 1.0f;
		posZ.a = 1.0f;
		
		negX.x = -100.0f;
		negX.r = 1.0f;
		negX.a = 1.0f;
		negY.y = -100.0f;
		negY.r = 1.0f;
		negY.a = 1.0f;
		negZ.z = -100.0f;
		negZ.r = 1.0f;
		negZ.a = 1.0f;


		Vertex  GuideVertex[] = { posX,negX,posY,negY,posZ,negZ };
		pos = p_Pos;
		vbo = VertexBuffer(GuideVertex, sizeof(GuideVertex));
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
		glEnableVertexArrayAttrib(vao.GetID(), 0);
		glEnableVertexArrayAttrib(vao.GetID(), 1);
	}
	void Unbind()
	{
		glDisableVertexArrayAttrib(vao.GetID(), 0);
		glDisableVertexArrayAttrib(vao.GetID(), 1);
		vbo.Unbind();
		vao.Unbind();
		
	}
	void Draw()
	{
		Bind();
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*3));
		shader.setMat4("model", model);
		glDrawArrays(GL_LINES, 0, 6);
		Unbind();
	}
};