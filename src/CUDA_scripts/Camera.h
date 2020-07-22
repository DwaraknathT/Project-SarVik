#pragma once
#include<glm/gtx/transform.hpp>
#include<GLFW/glfw3.h>
#include "Shaders.hpp"
class IsoCamera
{
	glm::vec3 cameraPos = glm::vec3(3.0f, 3.0f, 3.0f);
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
	Shader shader;
	float currPhi = glm::radians(45.0f);
	float currTheta = glm::radians(45.0f);
public:
	bool isIsometric = true;
	float radius = 3.0f;
	IsoCamera(GLFWwindow * p_Window, int p_Width, int p_Height)
	{
		window = p_Window;
		cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		cameraUp = glm::cross(cameraDirection, cameraRight);
		view = glm::lookAt(cameraPos, cameraTarget, up);
		projection = glm::perspective(glm::radians(55.0f), (float)width / height, 0.1f, 100.0f);
		width = p_Width;
		height = p_Height;
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
		updateCamera(currPhi, currTheta);
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
		view = glm::lookAt(cameraPos, cameraTarget, up);
		shader.setMat4("view", view);
	}
	void updateCamera()
	{
		float camX = radius * sin(currTheta) * sin(currPhi);
		float camY = radius * cos(currPhi);
		float camZ = radius * cos(currTheta) * sin(currPhi);
		cameraPos = glm::vec3(camX, camY, camZ);
		view = glm::lookAt(cameraPos, cameraTarget, up);
		shader.setMat4("view", view);
	}

};
class FreeCamera
{
	// camera
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;
	float lastX = 800.0f / 2.0;
	float lastY = 600.0 / 2.0;
	float fov = 45.0f;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;
	int width = 0;
	int height = 0;
	Shader m_Shader;
public:
	bool firstMouse = true;

	FreeCamera() = default;
	FreeCamera(int p_Width, int p_Height)
	{
		width = p_Width;
		height = p_Height;
	}
	void ProcessInputs(GLFWwindow * window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		float cameraSpeed = 0.05;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		updateCamera();
	}
	void SetShader(Shader p_Shader)
	{
		m_Shader = p_Shader;
	}
	void updateCamera()
	{
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
		m_Shader.setMat4("projection", projection);
		// camera/view transformation
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		m_Shader.setMat4("view", view);

	}
	void mouse_callback(GLFWwindow * window, double xpos, double ypos)
	{
		if (this->firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.1f; // change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		// make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
		updateCamera();
	}
};