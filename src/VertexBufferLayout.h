//
// Created by luizh on 28/11/2023.
//

#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <vector>
#include <glad/glad.h>

#include "Renderer.h"

struct VertexBufferElement {
    GLuint type;
    GLuint count;
    GLubyte normalized;

    static GLuint GetSizeOfType(const GLuint type) {
        switch (type) {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    GLuint m_Stride;

public:
    VertexBufferLayout()
        : m_Stride(0) {
    }

    void Push(GLuint type, GLuint count) {
        m_Elements.push_back({type, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(type);
    }

    inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
};

#endif //VERTEXBUFFERLAYOUT_H
