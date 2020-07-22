#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include<stdio.h>
#include<stdlib.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>
#include "ErrorLog.h"
using namespace glm;
namespace GLI {
	class GLSetup
	{
	public:
		GLSetup(int * err);
		void  SetGLFWWindow(short samples, short major, short minor, int profile, bool forwardCompatibility = true) const;
		GLFWwindow * CreateWindow(int width, int height, std::string name);
		int width = 0;
		int height = 0;

	};
	
}