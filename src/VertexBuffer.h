//
// Created by luizh on 27/11/2023.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <glad/glad.h>
#include "Renderer.h"

class VertexBuffer {
private:
    GLuint m_RendererID;
public:
    VertexBuffer(const void* data, GLuint size);
    ~VertexBuffer();

    void Bind() const;

    void UnBind() const;
};

#endif //VERTEXBUFFER_H
