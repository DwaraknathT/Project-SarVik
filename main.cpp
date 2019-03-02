#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Init.hpp"
#include "Shaders.hpp"
#include "Render.h"
#include <glm/glm.hpp>
#define GLM_ENALBLE_EXPERIMENTAL

static const GLfloat g_fragment_buffer_data[] =
{
	0.0f,0.0f,0.0f,
	1.0f,-1.0f,0.0f,
	0.0f,1.0f,0.0f,

};
GLuint VertexArrayID;


void CheckGLError();
void makeTriangle();

int main()
{
	
	
	Render render;
	Sphere* s2;
	s2 = new Sphere(glm::vec3(0.0f, 5.0f, -0.2f), glm::vec4(0.0f, 1.0f, 0.0f, 0.02f));
	render.Start();
	do {
		render.Loop();
	} while (render.KeepRendering);
	render.End();
	return 0;
}
void SetImguiInputs()
{

}



void CheckGLError()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::string error;

		switch (err) {
		case GL_INVALID_OPERATION:      error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}

		Init::LogError(error);
		err = glGetError();
	}
}



