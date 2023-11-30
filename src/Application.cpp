#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

GLfloat vertices[] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f, 0.5f,
    -0.5f, 0.5f
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

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    const VertexArray vertexArray;
    const VertexBuffer vertexBuffer(vertices, 4 * 2 * sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    vertexArray.AddBuffer(vertexBuffer, layout);
    vertexArray.Bind();

    const IndexBuffer indexBuffer(indices, 6);

    Shader shader("../resources/shaders/basic.glsl");
    shader.Bind();

    shader.SetUniform4f("uColor",0.2f, 0.3f, 0.8f, 1.0f);

    shader.UnBind();
    vertexBuffer.UnBind();
    indexBuffer.UnBind();
    vertexArray.UnBind();

    GLfloat red = 0.0f;
    GLfloat increment = 0.00005f;
    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        shader.Bind();
        shader.SetUniform4f("uColor", red, 0.3f, 0.8f, 1.0f);

        vertexArray.Bind();
        indexBuffer.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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
    delete &vertexBuffer;
    delete &indexBuffer;
    delete &vertexArray;
    delete &shader;

    GLCall(glfwTerminate());
    return 0;
}
