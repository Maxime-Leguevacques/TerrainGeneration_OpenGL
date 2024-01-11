#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "app.h"

class Renderer
{
private:
	Renderer();
	GLFWwindow* window;
public:
	App* app = App::GetInstance();
	static Renderer* GetInstance();

	void InitWindow();
	void RenderWindow();
	void CloseWindow();

	void InitImGui(GLFWwindow* _window);
	void RenderImGui();
	void CleanImGui();

	float DeltaTime;
	float LastFrame;

	float depth = 0.0f;
};