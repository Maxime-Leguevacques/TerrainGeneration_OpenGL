#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>



class App
{
private:
	float defaultWindowWidth;
	float defaultWindowHeight;

public:
	bool fpsView = false;

public:
	App();

	static App* GetInstance();

	float GetWindowWidth();
	float GetWindowHeight();

};

