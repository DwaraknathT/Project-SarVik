#pragma once
#include<vector>
#define PI 3.141592653
#include "Shaders.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Texture.h"
#include "IndexBuffer.h"
#include <glm/gtx/transform.hpp>
class Cylinder {
	// clear memory of prev arrays
private:
	float radius = 0.20f;
	float height = 1.0f;
	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord
	int sectorCount = 100;
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle, stackAngle;
	glm::vec4 colour = glm::vec4(0, 0, 0, 0);
public:
	VAO vao;
	VertexBuffer vbo;
	Texture tex;
	IndexBuffer indexbuff;
	Shader shader;
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	glm::vec3 pos;
	glm::mat4 model;
	bool isColoured = false;
	Cylinder() = default;
	Cylinder(float p_Radius, float p_Height, glm::vec3 p_Pos, glm::vec4 p_Color)
	{
		model = glm::mat4(1.0f);
		radius = p_Radius;
		height = p_Height;
		pos = p_Pos;
		model = glm::translate(model, pos);
		colour = p_Color;
		isColoured = true;
		GenerateCylinder();
		vbo = VertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex));
		indexbuff = IndexBuffer(indices.size() * sizeof(unsigned int), indices.data());
		pos = p_Pos;
		model = glm::translate(model, pos);

	}
	void RotateX(float degX)
	{
		model = glm::rotate(model, glm::radians(degX), glm::vec3(1.0f, 0.0f, 0.0f));
	}
	void RotateY(float degY)
	{
		model = glm::rotate(model, glm::radians(degY), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	void RotateZ(float degZ)
	{
		model = glm::rotate(model, glm::radians(degZ), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	Cylinder(glm::vec3 p_Pos) {
		GenerateCylinder();
		vbo = VertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex));
		indexbuff = IndexBuffer(indices.size() * sizeof(unsigned int), indices.data());
		pos = p_Pos;
		model = glm::translate(model, pos);

	}
	Cylinder(glm::vec3 p_Pos, glm::vec4 p_Color) {

		pos = p_Pos;
		model = glm::translate(model, pos);
		colour = p_Color;
		isColoured = true;

		GenerateCylinder();

		vbo = VertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex));
		indexbuff = IndexBuffer(indices.size() * sizeof(unsigned int), indices.data());

	}
	void SetColor(glm::vec4 p_Color)
	{
		colour = p_Color;
		isColoured = true;
		shader.setBool("isTextured", false);

	}
	Vertex CreateVertex(glm::vec3 p_Pos, glm::vec4 p_Color, glm::vec2 p_TexUV)
	{
		Vertex vertex;
		vertex.x = p_Pos.x;
		vertex.y = p_Pos.y;
		vertex.z = p_Pos.z;
		vertex.a = p_Color.a;
		vertex.r = p_Color.r;
		vertex.g = p_Color.g;
		vertex.b = p_Color.b;
		vertex.u = p_TexUV.x;
		vertex.v = p_TexUV.y;
		return vertex;
	}
	void GenerateCylinder()
	{
		Vertex center;
		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		center = CreateVertex(glm::vec3(0, 0, -height / 2), colour, glm::vec2(0, 0));
		vertices.push_back(center);
		Vertex vertex;
		float u, v;
		for (int j = 0; j < sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi
			// vertex position (x, y, z)
			x = radius * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = radius * sinf(sectorAngle);             // r * cos(u) * sin(v)
			z = -height / 2;
			//// normalized vertex normal (nx, ny, nz)
			//vertex.nx = x * lengthInv;
			//vertex.ny = y * lengthInv;
			//vertex.nz = z * lengthInv;
			// vertex tex coord (s, t) range between [0, 1]

			u = (float)j / sectorCount;
			v = (float)j / sectorCount;

			vertex = CreateVertex(glm::vec3(x, y, z), colour, glm::vec2(u, v));
			vertices.push_back(vertex);


		}
		Vertex center2;
		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		center2 = CreateVertex(glm::vec3(0, 0, height / 2), colour, glm::vec2(0, 0));
		vertices.push_back(center2);

		for (int j = 0; j < sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi
			// vertex position (x, y, z)
			x = radius * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = radius * sinf(sectorAngle);             // r * cos(u) * sin(v)
			z = height / 2;
			//// normalized vertex normal (nx, ny, nz)
			//vertex.nx = x * lengthInv;
			//vertex.ny = y * lengthInv;
			//vertex.nz = z * lengthInv;
			// vertex tex coord (s, t) range between [0, 1]

			u = (float)j / sectorCount;
			v = (float)j / sectorCount;

			vertex = CreateVertex(glm::vec3(x, y, z), colour, glm::vec2(u, v));
			vertices.push_back(vertex);

		}

		unsigned int k1 = 0, k2 = 0;
		for (int i = 1; i <= sectorCount - 1; ++i)
		{

			k1 = i;     // beginning of current stack
			k2 = i + 1;      // beginning of next stack
			indices.push_back(k1);
			indices.push_back(k2);
		}

		indices.push_back(1);
		indices.push_back(sectorCount);
		for (int i = 1; i <= sectorCount - 1; ++i)
		{

			k1 = i;     // beginning of current stack
			k2 = i + 1;      // beginning of next stack
			indices.push_back(0);
			indices.push_back(k1);
			indices.push_back(k2);
		}
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(sectorCount);
		for (int i = 1; i <= sectorCount - 1; ++i)
		{

			k1 = i + sectorCount + 1;     // beginning of current stack
			k2 = i + sectorCount + 2;      // beginning of next stack
			indices.push_back(k1);
			indices.push_back(k2);
		}
		indices.push_back(2 + sectorCount);
		indices.push_back(sectorCount * 2 + 1);

		for (int i = 1; i <= sectorCount - 1; ++i)
		{

			k1 = i + sectorCount + 1;     // beginning of current stack
			k2 = i + sectorCount + 2;      // beginning of next stack
			indices.push_back(sectorCount + 1);
			indices.push_back(k1);
			indices.push_back(k2);
		}
		indices.push_back(sectorCount + 1);
		indices.push_back(2 + sectorCount);
		indices.push_back(sectorCount * 2 + 1);
		//indices.push_back(0);
		//indices.push_back(sectorCount+1);

		k1 = 0; k2 = 0;
		for (int i = 1; i <= sectorCount; i++)
		{
			indices.push_back(i);
			indices.push_back(i + 1 + sectorCount);
		}
	}
	void Bind()
	{
		vao.Bind();
		vbo.Bind();
		tex.Bind();
		indexbuff.Bind();
		glEnableVertexArrayAttrib(vao.GetID(), 0);
		glEnableVertexArrayAttrib(vao.GetID(), 2);
		glEnableVertexArrayAttrib(vao.GetID(), 1);

	}
	void Unbind()
	{
		indexbuff.Unbind();
		vao.Unbind();
		vbo.Unbind();
		tex.Unbind();

	}
	void SetTexture(Texture texbuff)
	{
		tex = texbuff;
	}
	void SetShader(Shader p_shader)
	{
		shader = p_shader;
		if (isColoured)
		{
			shader.setBool("isTextured", false);
		}
		else
		{
			shader.setBool("isTextured", true);
		}
	}
	void Draw()
	{
		Bind();
		int size = sizeof(Vertex);
		//Vertex Pos
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		//Texture Pos
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 7));
		//Color Pos
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
		shader.setMat4("model", model);
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);
		Unbind();
	}
};