#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include "Renderer.h"

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

class Shader {
private:
    GLuint m_RendererID;
    std::string m_FilePath;
    std::unordered_map<std::string, GLint> m_UniformLocationCache;

public:
    Shader(const std::string& filePath);

    ~Shader();

    void Bind() const;

    void UnBind() const;

    // Set uniforms
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
    ShaderProgramSource ParseShader() const;

    GLuint CompileShader(const GLuint type, const std::string&source);

    GLuint CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    GLint GetUniformLocation(const std::string& name);
};

#endif //SHADER_H
