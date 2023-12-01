//
// Created by luizh on 28/11/2023.
//

#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const {
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer&vertexBuffer, const VertexBufferLayout&layout) const {
    vertexBuffer.Bind();
    this->Bind();
    const auto&elements = layout.GetElements();
    GLuint offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const auto& [type, count, normalized] = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(
            glVertexAttribPointer(i, count, type, normalized, layout.GetStride(),
                reinterpret_cast<const void *>(offset)));
        offset += count * VertexBufferElement::GetSizeOfType(type);
    }
}
