#pragma once
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

namespace Init {
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.00f, 1.00f);

	void InitImgui(GLFWwindow & window)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();
		const char* glsl_version = "#version 330";
		// Setup Platform/Rendeer bindings
		ImGui_ImplGlfw_InitForOpenGL(&window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}
	void StartImguiFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	void PrepareImguiFrame()
	{

		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Project Sarvik");


		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

		/*if (ImGui::Button("Button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);*/

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}
	void Render()
	{
		ImGui::End();
		ImGui::Render();
	}
	void EndImguiFrame()
	{

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}
}
