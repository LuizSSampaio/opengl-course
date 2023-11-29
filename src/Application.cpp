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

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderProgramSource parseShader(const std::string&filePath) {
    std::ifstream stream(filePath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream stringStream[2];
    auto type = ShaderType::NONE;
    while (std::getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else if (type != ShaderType::NONE) {
            stringStream[static_cast<int>(type)] << line << "\n";
        }
    }

    return {stringStream[0].str(), stringStream[1].str()};
}

static GLuint compileShader(const GLuint type, const std::string&source) {
    GLCall(const GLuint id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    GLint result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        const auto message = static_cast<char *>(alloca(length * sizeof(char)));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static GLuint createShader(const std::string&vertexShaderSource, const std::string&fragmentShaderSource) {
    GLCall(const GLuint shaderProgram = glCreateProgram());
    const GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    const GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLCall(glAttachShader(shaderProgram, vertexShader));
    GLCall(glAttachShader(shaderProgram, fragmentShader));
    GLCall(glLinkProgram(shaderProgram));
    GLCall(glValidateProgram(shaderProgram));

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));

    return shaderProgram;
}

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

    const auto [vertexSource, fragmentSource] = parseShader("../resources/shaders/basic.glsl");

    const GLuint shader = createShader(vertexSource, fragmentSource);
    GLCall(glUseProgram(shader));

    GLCall(const GLint uniformLocation = glGetUniformLocation(shader, "uColor"));
    ASSERT(uniformLocation != -1);
    GLCall(glUniform4f(uniformLocation, 0.2f, 0.3f, 0.8f, 1.0f));

    GLCall(glUseProgram(0));
    GLCall(glBindVertexArray(0));
    vertexBuffer.UnBind();
    indexBuffer.UnBind();
    vertexArray.UnBind();

    GLfloat red = 0.0f;
    GLfloat increment = 0.00005f;
    while (!glfwWindowShouldClose(window)) {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(uniformLocation, red, 0.3f, 0.8f, 1.0f));

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
    GLCall(glDeleteProgram(shader));

    GLCall(glfwTerminate());
    return 0;
}
