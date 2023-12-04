//
// Created by luizh on 27/11/2023.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) glClearError();\
x;\
ASSERT(glLogCall(#x, __FILE__, __LINE__));

void glClearError();

bool glLogCall(const char* function, const char* file, int line);

class VertexArray;
class IndexBuffer;
class Shader;

class Renderer {
public:
    void Clear() const;
    void SetClearColor(float r, float g, float b, float a) const;
    void Draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader) const;
};

#endif //RENDERER_H
