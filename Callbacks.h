#pragma once
#include<GLFW/glfw3.h>
#include"Camera.h"
namespace Callbacks {
	bool leftMousePressed = false;
	bool rightMousePressed = false;
	double lastX;
	double lastY;
	float theta = glm::radians(45.0f);
	float phi = glm::radians(45.0f);
	float zoom = 1.0f;
	int width = 800;
	int height = 600;
	Camera * camera;
	void updateCamera() {
		camera->updateCamera(theta, phi);
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		{
			camera->ZoomIn();
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		{
			camera->ZoomOut();
		}
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		leftMousePressed = (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
		rightMousePressed = (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS);
	}

	void mousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
		if (leftMousePressed) {
			// compute new camera parameters
			phi += (lastX - xpos)*1.2 / width;
			theta -= (ypos - lastY)*1.2 / height;
			theta = std::fmax(0.01f, std::fmin(theta, 3.14f));
			updateCamera();
		}
		else if (rightMousePressed) {
			zoom += (ypos - lastY) / height;
			zoom = std::fmax(0.1f, std::fmin(zoom, 5.0f));
			updateCamera();
		}

		lastX = xpos;
		lastY = ypos;
	}
}