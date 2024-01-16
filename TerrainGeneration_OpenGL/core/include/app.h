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

};

