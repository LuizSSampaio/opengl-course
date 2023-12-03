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

GLfloat vertices[] = {
    100.0f, 100.0f, 0.0f, 0.0f,
    200.0f, 100.0f, 1.0f, 0.0f,
    200.0f, 200.0f, 1.0f, 1.0f,
    100.0f, 200.0f, 0.0f, 1.0f
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
    const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    const glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

    const glm::mat4 mvp = proj * view * model;

    const IndexBuffer indexBuffer(indices, 6);

    Shader shader("../resources/shaders/basic.glsl");
    shader.Bind();

    shader.SetUniform4f("u_Color",0.2f, 0.3f, 0.8f, 1.0f);
    shader.SetUniformMat4f("u_MVP", mvp);

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

    GLfloat red = 0.0f;
    GLfloat increment = 0.00005f;
    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", red, 0.3f, 0.8f, 1.0f);

        texture.Bind();

        renderer.Draw(vertexArray, indexBuffer, shader);

        if (red > 1.0f) {
            increment = -0.00005f;
        }
        else if (red < 0.0f) {
            increment = 0.00005f;
        }

        red += increment;

        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());
    }
    delete &texture;
    delete &vertexBuffer;
    delete &indexBuffer;
    delete &vertexArray;
    delete &shader;

    GLCall(glfwTerminate());
    return 0;
}
