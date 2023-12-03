#include <fstream>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "tests/TestClearColor.h"

GLfloat vertices[] = {
    -50.0f, -50.0f, 0.0f, 0.0f,
    50.0f, -50.0f, 1.0f, 0.0f,
    50.0f, 50.0f, 1.0f, 1.0f,
    -50.0f, 50.0f, 0.0f, 1.0f
};

GLuint indices[] = {
    0, 1, 2,
    2, 3, 0
};

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(960, 540, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    gladLoadGL();

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    const VertexArray vertexArray;
    const VertexBuffer vertexBuffer(vertices, 4 * 4 * sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    layout.Push(GL_FLOAT, 2);
    vertexArray.AddBuffer(vertexBuffer, layout);
    vertexArray.Bind();

    const glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    const IndexBuffer indexBuffer(indices, 6);

    Shader shader("../resources/shaders/basic.glsl");
    shader.Bind();

    shader.SetUniform4f("u_Color",1.0f, 1.0f, 1.0f, 1.0f);

    const Texture texture("../resources/textures/pop_cat.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    shader.UnBind();
    vertexBuffer.UnBind();
    indexBuffer.UnBind();
    vertexArray.UnBind();
    texture.UnBind();

    constexpr Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    test::TestClearColor test;

    glm::vec3 color(1.0f, 1.0f, 1.0f);
    glm::vec3 translation(200, 200, 0);
    glm::vec3 translation2(400, 400, 0);
    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        test.OnUpdate(0.0f);
        test.OnRender();


        glm::mat4 model;
        glm::mat4 mvp;

        texture.Bind();

        {
            model = glm::translate(glm::mat4(1.0f), translation);
            mvp = proj * view * model;
            shader.Bind();
            shader.SetUniform4f("u_Color", color.r, color.g, color.b, 1.0f);
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(vertexArray, indexBuffer, shader);
        }

        {
            model = glm::translate(glm::mat4(1.0f), translation2);
            mvp = proj * view * model;
            shader.Bind();
            shader.SetUniform4f("u_Color", color.r, color.g, color.b, 1.0f);
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(vertexArray, indexBuffer, shader);
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Engine Debug");

            ImGui::Text("Translation A: ");
            ImGui::SliderFloat2("##TranslationA", &translation.x, 0.0f, 960.0f);

            ImGui::Text("Translation B: ");
            ImGui::SliderFloat2("##TranslationB", &translation2.x, 0.0f, 960.0f);

            ImGui::Text("Color Filter: ");
            ImGui::ColorEdit3("##ColorFilter", &color.x);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        test.OnImGuiRender();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    GLCall(glfwTerminate());
    return 0;
}
