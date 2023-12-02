#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "../thirdparty/glfw-3.3.8/deps/glad/gl.h"

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 1.0f
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

    GLCall(glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    const VertexArray vertexArray;
    const VertexBuffer vertexBuffer(vertices, 4 * 4 * sizeof(GLfloat));

    VertexBufferLayout layout;
    layout.Push(GL_FLOAT, 2);
    layout.Push(GL_FLOAT, 2);
    vertexArray.AddBuffer(vertexBuffer, layout);
    vertexArray.Bind();

    const IndexBuffer indexBuffer(indices, 6);

    Shader shader("../resources/shaders/basic.glsl");
    shader.Bind();

    shader.SetUniform4f("uColor",0.2f, 0.3f, 0.8f, 1.0f);

    const Texture texture("../resources/textures/pop_cat.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    shader.UnBind();
    vertexBuffer.UnBind();
    indexBuffer.UnBind();
    vertexArray.UnBind();
    texture.UnBind();

    constexpr Renderer renderer;

    GLfloat red = 0.0f;
    GLfloat increment = 0.00005f;
    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("uColor", red, 0.3f, 0.8f, 1.0f);

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
