#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Renderer
{
private:
	Renderer();
	GLFWwindow* window;

public:
	static Renderer* GetInstance();

	void InitWindow();
	void RenderWindow();
	void CloseWindow();

	void InitImGui(GLFWwindow* _window);
	void RenderImGui();
	void CleanImGui();
};