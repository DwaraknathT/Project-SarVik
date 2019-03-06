#pragma once
#include<vector>
#define PI 3.141592653
#include "Shaders.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Texture.h"
#include "IndexBuffer.h"

class Sphere {
	// clear memory of prev arrays
private:
	float radius = 0.20f;
	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord
	int sectorCount = 100;
	int stackCount = 100;
	int slice = 10;
	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;
	glm::vec4 colour = glm::vec4(0,0,0,0);
public:
	VAO vao;
	VertexBuffer vbo;
	Texture tex;
	IndexBuffer indexbuff;
	Shader shader;
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	glm::vec3 pos;
	glm::mat4 model=glm::mat4(1.0f);
	bool isColoured = false;
	Sphere() = default;
	Sphere(float radius, int sectors, int stacks)
	{
		this->radius = radius;
		sectorCount = sectors;
		stackCount = stacks;
		GenerateSphere();
		
	}
	Sphere(glm::vec3 p_Pos) {
		GenerateSphere();
		vbo = VertexBuffer(vertices.data(), vertices.size()*sizeof(Vertex));
		indexbuff = IndexBuffer(indices.size()*sizeof(unsigned int), indices.data());
		pos = p_Pos;
		model = glm::translate(model, pos);
	
	}
	Sphere(glm::vec3 p_Pos,glm::vec4 p_Color) {
		
		pos = p_Pos;
		model = glm::translate(model, pos);
		colour = p_Color;
		isColoured = true;

		GenerateSphere();

		vbo = VertexBuffer(vertices.data(), vertices.size() * sizeof(Vertex));
		indexbuff = IndexBuffer(indices.size() * sizeof(unsigned int), indices.data());

	}
	void SetColor(glm::vec4 p_Color)
	{
		colour = p_Color;
		isColoured = true;
		shader.setBool("isTextured", false);
		
	}
	void GenerateSphere()
	{
		float sliceLen = radius / slice;
		for(int i = 1; i <= slice;i++ ){
		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
			xy = radius * cosf(stackAngle);             // r * cos(u)
			z = radius * sinf(stackAngle);              // r * sin(u)
			Vertex vertex;
			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position (x, y, z)
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
				vertex.x = x;
				vertex.y = y;
				vertex.z = z;


				//// normalized vertex normal (nx, ny, nz)
				//vertex.nx = x * lengthInv;
				//vertex.ny = y * lengthInv;
				//vertex.nz = z * lengthInv;
				vertex.r = colour.x;
				vertex.g = colour.y;
				vertex.b = colour.z;
				vertex.a = colour.w;
				// vertex tex coord (s, t) range between [0, 1]
				vertex.u = (float)j / sectorCount;
				vertex.v = (float)i / stackCount;
				vertices.push_back(vertex);
			}
		}
		}
		int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);     // beginning of current stack
			k2 = k1 + sectorCount + 1;      // beginning of next stack

			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding first and last stacks
				// k1 => k2 => k1+1
				if (i != 0)
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}

				// k1+1 => k2 => k2+1
				if (i != (stackCount - 1))
				{
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}
			}
		}
	/*	indices.resize(sectorCount * stackCount  * 4);
		std::vector<unsigned int>::iterator i = indices.begin();
		for (auto r = 0; r < stackCount; r++) {
			for (auto s = 0; s < sectorCount; s++) {
				*i++ = r * sectorCount + s;
				*i++ = r * sectorCount + (s + 1);
				*i++ = (r + 1) * sectorCount + (s + 1);
				*i++ = (r + 1) * sectorCount + s;
			}
		}*/
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
		glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(sizeof(float)*3));
		shader.setMat4("model", model);
		glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0); //GL_TRAINGLES for solid spheres 
		Unbind();
	}
};