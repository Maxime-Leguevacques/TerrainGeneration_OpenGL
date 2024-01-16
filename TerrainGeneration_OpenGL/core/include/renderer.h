#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "app.h"
#include "camera.h"

class Renderer
{
private:
	Renderer();
	GLFWwindow* window;
public:
	App* app;
	Camera* camera;
	static Renderer* GetInstance();

	void InitWindow();
	void RenderWindow();
	void CloseWindow();

	void InitImGui(GLFWwindow* _window);
	void RenderImGui();
	void CleanImGui();

	float deltaTime;
	float lastFrame;

	float depth = 0.0f;
	float upPos = 0.0f;
	float horizontalPos = 0.0f;

	void processInput(GLFWwindow* window);
};