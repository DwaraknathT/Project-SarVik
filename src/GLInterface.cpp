#pragma once

#include "GLIntferace.h"
using namespace GLI;
GLSetup::GLSetup(int * err)
{
	if (!glfwInit())
	{
		LogError("Fatal Error: glfw failed to initialize. ");
		*err = -1;
	}
	*err = 0;
}
void GLSetup::SetGLFWWindow(short samples, short major, short minor, int profile, bool forwardCompatibility) const
{
	glfwWindowHint(GLFW_SAMPLES, samples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	if (forwardCompatibility == true)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	else
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

	glfwWindowHint(GLFW_OPENGL_PROFILE, profile);

}
GLFWwindow * GLSetup::CreateWindow(int _width, int _height, std::string title) 
{
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	if(_width == 0)
		_width = mode->width;
	if (_height == 0)
		_height = mode->height;
	
    height = _height;
	width = _width;
	GLFWwindow* window = glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL);
	return window;
}
