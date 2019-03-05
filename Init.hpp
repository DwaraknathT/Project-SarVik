#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>

#include<stdio.h>
#include<stdlib.h>
#include<glm/glm.hpp>
#include<iostream>
#include<string>
namespace Init {
	void LogError(std::string p_ErrMsg);
	void InitGLFW();
	void SetGLFWWindow(GLFWwindow & window, short samples, short major, short minor, int profile, bool forwardCompatibility);
	GLFWwindow * CreateWindow(int p_Width, int p_Height, std::string title);
	void InitGLEW();

}

