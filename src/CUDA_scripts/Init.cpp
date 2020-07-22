#include "Init.hpp"
using namespace Init;
void Init::LogError(std::string p_ErrMsg)
{
	std::cerr << "Error: " << p_ErrMsg;
	std::system("pause");
	std::cout << "\nContinue?(Y/N)..";

}
void Init::InitGLFW()
{
	if (!glfwInit())
	{
		Init::LogError("Fatal Error: glfw failed to initialize. ");
	}

}
void Init::SetGLFWWindow(GLFWwindow & window, short samples, short major, short minor, int profile, bool forwardCompatibility)
{
	glfwWindowHint(GLFW_SAMPLES, samples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	if (forwardCompatibility == true)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	else
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);

	glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
	glfwMakeContextCurrent(&window);

}
GLFWwindow * Init::CreateWindow(int p_Width, int p_Height, std::string title)
{
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	if (p_Width == 0)
		p_Width = mode->width;
	if (p_Height == 0)
		p_Height = mode->height;
	p_Height = p_Height;
	p_Width = p_Width;
	GLFWwindow* window = glfwCreateWindow(p_Width, p_Height, title.c_str(), NULL, NULL);
	return window;
}