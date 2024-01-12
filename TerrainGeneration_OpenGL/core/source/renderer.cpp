#include <iostream>

#include "renderer.h"
#include "app.h"
#include "terrain.h"
#include "shader.h"
#include "camera.h"
#include "texture.h"
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    // Init timer
    DeltaTime = 0.0f;
    LastFrame = 0.0f;

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

    glEnable(GL_DEPTH_TEST);
}

void Renderer::RenderWindow()
{
    int row_num = 200, col_num = 200;
    std::vector<float> p;
    float x = -0, z = -50;

    for (int i = 0; i < row_num; i++) {
        x = 5;
        for (int j = 0; j < col_num; j++) {
            p.push_back(x);
            p.push_back(0);
            p.push_back(z);
            p.push_back(1.0f / col_num * j);
            p.push_back(1 - i * 1.0f / row_num);
            x += 0.1;
        }
        z += 0.1;
    }

    std::vector<unsigned int> indicess;
    for (int i = 1; i < row_num; i++) {
        for (int j = 1; j < col_num; j++) {
            indicess.push_back((i - 1) * col_num + j - 1);
            indicess.push_back((i - 1) * col_num + j);
            indicess.push_back(i * col_num + j - 1);

            indicess.push_back(i * col_num + j - 1);
            indicess.push_back((i - 1) * col_num + j);
            indicess.push_back(i * col_num + j);
        }
    }

    Camera* camera = Camera::GetInstance();

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, p.size() * sizeof(float), p.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicess.size() * sizeof(unsigned int), indicess.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int dep = 0, texture1 = 0, texture2 = 0;

    Texture* map = new Texture(dep);

    Texture* T1 = new Texture(texture1);
    Texture* T2 = new Texture(texture2);

    map->LoadTexture("assets/heightmap.png");
    T1->LoadTexture("assets/rock.jpg");
    T2->LoadTexture("assets/water.jpg");

    Shader shader("assets/shaders/v_shader.vs", "assets/shaders/f_shader.fs");

    shader.Use();

    shader.SetInt("dep", 0);
    shader.SetInt("tex1", 1);
    shader.SetInt("tex2", 2);

    InitImGui(window);
    float deltaTime, lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shader.Use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, map->GetTextureName());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, T1->GetTextureName());
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, T2->GetTextureName());

        glm::mat4 view = glm::lookAt(camera->GetCameraPos(), camera->GetCameraPos() + camera->GetCameraFront(), camera->GetCameraUp());

        glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::perspective(glm::radians(45.0f), (float)app->GetWindowWidth() / (float)app->GetWindowHeight(), 0.1f, 100.0f);

        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

        // pass transformation matrices to the shader
        shader.SetMat4("projection", projection);
        shader.SetMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        glm::mat4 Model = glm::mat4(1.0f);
        Model = glm::translate(Model, glm::vec3(0.0f, upPos, depth));
        
        shader.SetMat4("model", Model);
        glDrawElements(GL_TRIANGLES, (row_num - 1) * (col_num - 1) * 6, GL_UNSIGNED_INT, 0);

        RenderImGui();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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

    ImGui::SliderFloat("Depth", &depth, -30.0f, 30.0f, "%.f", 0);
    ImGui::SliderFloat("Vertical", &upPos, -30.0f, 30.0f, "%.f", 0);

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