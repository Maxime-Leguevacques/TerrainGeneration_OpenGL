#include <iostream>

#include "renderer.h"
#include "app.h"
#include "shader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"



float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
};

unsigned int indices[] = {

    0, 1, 3,
    1, 2, 3
};

Renderer::Renderer()
{
}

Renderer* Renderer::GetInstance()
{
    static Renderer* instance = new Renderer();
    return instance;
}

void Renderer::InitWindow()
{
    App* app = App::GetInstance();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(app->GetWindowWidth(), app->GetWindowHeight(), "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void Renderer::RenderWindow()
{
    // Create VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Create Pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // Enable the pointer     

    //// VS
    //const char* vertexShaderSource = "assets/shaders/v_shader.vs";
    //// FS
    //const char* fragmentShaderSource = "assets/shaders/f_shader.fs";

    Shader shader("assets/shaders/v_shader.vs", "assets/shaders/f_shader.fs");

    // //VS
    //const char* vertexShaderSource = "#version 460 core\n"
    //    "layout (location = 0) in vec3 aPos;\n"
    //    "void main()\n"
    //    "{\n"
    //    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //    "}\0";
    ////FS
    //const char* fragmentShaderSource = "#version 460 core\n"
    //    "out vec4 FragColor;\n"
    //    "void main()\n"
    //    "{\n"
    //    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //    "}\0";

    //unsigned int vertexShader;
    //vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexShader);
    //unsigned int fragmentShader;
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //glCompileShader(fragmentShader);



    //// Link VS and FS
    //unsigned int shaderProgram;
    //shaderProgram = glCreateProgram(); // Create a program object
    //glAttachShader(shaderProgram, vertexShader); // Attach the shader objects
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram); // Link the program object
    shader.Use();

    //// Clean shader
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);

    InitImGui(window);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw triangle
        //glUseProgram(shaderProgram); // Use the program object we created earlier
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        RenderImGui();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Renderer::CloseWindow()
{
    CleanImGui();
    glfwTerminate();
}


#pragma region Renderer ImGui

void Renderer::InitImGui(GLFWwindow* _window)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

void Renderer::RenderImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Hello, world!");
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::CleanImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

#pragma endregion Renderer ImGui