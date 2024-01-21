#include <iostream>

#include "renderer.h"

int main()
{
    Renderer* renderer = Renderer::GetInstance();

    // Initialization
    renderer->InitWindow();

    // Main loop
    renderer->RenderWindow();

    // Clean
    renderer->CloseWindow();

    std::cout << "Closed Window" << std::endl;

    return 0;
}