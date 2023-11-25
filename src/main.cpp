#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

float vertices[] = {
    -0.5f, -0.5f,
    0.0f, 0.5f,
    0.5f, -0.5f
};

static GLuint compileShader(GLuint type, const std::string&source) {
    const GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = static_cast<char *>(alloca(length * sizeof(char)));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static GLuint createShader(const std::string&vertexShaderSource, const std::string&fragmentShaderSource) {
    const GLuint shaderProgram = glCreateProgram();
    const GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    const GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();

    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

    const std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec4 position;\n"
        "\n"
        "void main() {\n"
        "    gl_Position = position;\n"
        "}\n";
    const std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) out vec4 color;\n"
        "\n"
        "void main() {\n"
        "    color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    const GLuint shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
