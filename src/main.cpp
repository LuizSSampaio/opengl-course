#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    const GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        const auto message = static_cast<char *>(alloca(length * sizeof(char)));
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
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);

    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);

    const auto [vertexSource, fragmentSource] = parseShader("../resources/shaders/basic.glsl");

    const GLuint shader = createShader(vertexSource, fragmentSource);
    glUseProgram(shader);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        //glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1,  &indexBufferObject);
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}
