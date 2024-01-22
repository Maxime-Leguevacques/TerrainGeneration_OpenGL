#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "app.h"
#include "camera.h"
#include "terrain.h"
#include "skybox.h"
#include "shader.h"

class Renderer
{
private:
	GLFWwindow* window;
	unsigned int mapVAO, mapVBO, mapEBO;
	Terrain* map = new Terrain("assets/heightmap.png");

public:
	Skybox* skybox;
	App* app;
	Camera* camera;

	float deltaTime;
	float lastFrame;

	float depth = 0.0f;
	float upPos = 0.0f;
	float horizontalPos = 0.0f;

	int rockNums;
	std::vector<int>rockPositions;

public:

	Renderer();
	~Renderer();

	static Renderer* GetInstance();
	void InitWindow();
	void RenderWindow();
	void CloseWindow();

	void InitImGui(GLFWwindow* _window);
	void RenderImGui(Shader* _shader);
	void CleanImGui();
	void RenderMap();

	void processInput(GLFWwindow* window);
};