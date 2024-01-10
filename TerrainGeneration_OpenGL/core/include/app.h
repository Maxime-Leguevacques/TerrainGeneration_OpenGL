#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class App
{
private:
	App();
	float defaultWindowWidth;
	float defaultWindowHeight;

public:
	static App* GetInstance();

	float GetWindowWidth();
	float GetWindowHeight();

	float GetWindowWidth(float _width);
	float GetWindowHeight(float _Height);
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path);