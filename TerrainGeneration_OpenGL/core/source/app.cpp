#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <iostream>

#include "app.h"
#include "camera.h"
#include "renderer.h"



App::App()
{
    defaultWindowWidth = 1920.0f;
    defaultWindowHeight = 1080.0f;
}

App* App::GetInstance()
{
    static App* instance = new App();
    return instance;
}

float App::GetWindowWidth()
{
    return defaultWindowWidth;
}

float App::GetWindowHeight()
{
    return defaultWindowHeight;
}
