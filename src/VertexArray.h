//
// Created by luizh on 28/11/2023.
//

#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

class VertexArray {
private:
    GLuint m_RendererID;

public:
    VertexArray();

    ~VertexArray();

    void Bind() const;

    void UnBind() const;

    void AddBuffer(const VertexBuffer&vertexBuffer, const VertexBufferLayout&layout) const;
};

#endif //VERTEXARRAY_H
