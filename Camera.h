#pragma once
#include<glm/gtx/transform.hpp>
#include<GLFW/glfw3.h>
#include "Shaders.hpp"
class Camera
{
	glm::vec3 cameraPos = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::vec3(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	glm::mat4 view;
	glm::mat4 projection;
	int width = 800;
	int height = 600;
	GLFWwindow * window;
	float radius = 1.0f;
	Shader shader;
	float currPhi = glm::radians(45.0f);
	float currTheta = glm::radians(45.0f);
public:
	Camera(GLFWwindow * p_Window)
	{
		window = p_Window;
		cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		cameraUp = glm::cross(cameraDirection, cameraRight);
		view = glm::lookAt(cameraPos, cameraTarget, up);
		projection = glm::perspective(glm::radians(55.0f), (float)width / height, 0.1f, 100.0f);

	}
	void setShader(Shader p_shader)
	{
		shader = p_shader;
	
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
	}
	void ZoomIn()
	{
		radius -= 0.05f;
		updateCamera(currPhi,currTheta);
	}
	void ZoomOut()
	{
		radius += 0.05f;
		updateCamera(currPhi, currTheta);
	}
	void updateCamera(float phi, float theta)
	{
		currTheta = theta;
		currPhi = phi;
		float camX = radius * sin(currTheta) * sin(currPhi);
		float camY = radius * cos(currPhi);
		float camZ = radius * cos(currTheta) * sin(currPhi);
		cameraPos = glm::vec3(camX, camY, camZ);
		view = glm::lookAt(cameraPos,cameraTarget,up);
		shader.setMat4("view", view);
	}
	
};