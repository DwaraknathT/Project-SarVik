#pragma once
#include "Init.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.h"
#include "Imgui.h"
#include "Callbacks.h"
#include "Camera.h"
#include "GuideLines.h"
#include "Sphere.h"
#include "Simulation.h"
void error()
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
		std::cout << "GL_" << error.c_str();
		err = glGetError();
	}
}

class Render
{
private:
	GLFWwindow * window;
	GLuint programID;
	IsoCamera * cam;
	FreeCamera * free;
	Simulation sim;
	int camID = 0;
public:

	bool KeepRendering = true;
	Render()
	{
		int err = 0;
		cudaDeviceProp deviceProp;
		int gpuDevice = 0;
		int device_count = 0;
		cudaGetDeviceCount(&device_count);
		Init::InitGLFW();
		window = Init::CreateWindow(1920, 1080, "VIS.");
		Init::SetGLFWWindow(*window, 4, 3, 3, GLFW_OPENGL_CORE_PROFILE, true);
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			std::cout << "Couldn't init glew.";
		}
		if (err != 0)
		{
		}
		cudaGLSetGLDevice(0);

		cam = new IsoCamera(window, 1920, 1080);
		free = new FreeCamera(1920, 1080);

		Callbacks::camID = camID;
		Callbacks::freecam = free;
		Callbacks::cam = cam;

		glfwSetKeyCallback(window, Callbacks::keyCallback);
		glfwSetCursorPosCallback(window, Callbacks::mousePositionCallback);
		glfwSetMouseButtonCallback(window, Callbacks::mouseButtonCallback);


		Init::InitImgui(*window);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CW);


	}
	void Start()
	{
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		Shader shader;
		shader.LoadShader("vertexShader.glsl", ShaderType::VERTEX);
		shader.LoadShader("fragmentShader.glsl", ShaderType::FRAGMENT);
		shader.LoadProgram();
		programID = shader.GetProgramID();
		error();
		glUseProgram(programID);
		sim = Simulation(shader);
		int display_w, display_h;
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glClearColor(Init::clear_color.x, Init::clear_color.y, Init::clear_color.z, Init::clear_color.w);

		glViewport(0, 0, display_w, display_h);
		cam->setShader(shader);
		free->SetShader(shader);
		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4("model", model);
		shader.setBool("isTextured", false);

	}
	void makeTriangle()
	{
	}
	void Update()
	{
		sim.Update();
		if (ImGui::InputFloat("View Radius: ", &cam->radius, 0.5, 0.5, 4))
		{
			cam->updateCamera();
		}
		if (ImGui::ColorEdit3("clear color", (float*)&Init::clear_color))
		{
			glClearColor(Init::clear_color.x, Init::clear_color.y, Init::clear_color.z, Init::clear_color.w);
		}
		if (camID == 0) {
			if (ImGui::Button("Switch Camera"))
			{
				if (camID == 0)
				{
					Callbacks::camID = 1;
					camID = 1;
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


				}
			}
		}
		else {
			ImGui::Text("Press K to switch back.");
			if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
			{

				Callbacks::camID = 0;
				camID = 0;
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			}
		}
	}
	void DrawCalls()
	{
		sim.Draw();
	}
	void RenderEverything()
	{
		DrawCalls();

		Init::Render();
		Init::EndImguiFrame();
		glfwSwapBuffers(window);
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			KeepRendering = false;
		}
	}
	void Loop()
	{
		glfwPollEvents();
		//Clear the screen. Can cause flickering if not done
		//Draw Nothing, not yet.
		Init::StartImguiFrame();
		Init::PrepareImguiFrame();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		Update();
		RenderEverything();
	}
	void End()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(window);
		glfwTerminate();

	}
};
//vao->Bind();
//buff = VertexBuffer(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
//buff.Bind();
//cudaGLRegisterBufferObject(buff.getID());
//glEnable(GL_DEPTH_TEST);
//glEnableVertexArrayAttrib(vao->GetID(), 0);
//glVertexAttribPointer(
//	0,
//	3,
//	GL_FLOAT,
//	GL_FALSE,
//	sizeof(float) * 3,
//	(void*)0
//);
//glUseProgram(programID);
//glPointSize(12);*/