//
// Created by luizh on 27/11/2023.
//

#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <glad/glad.h>
#include "Renderer.h"

class IndexBuffer {
private:
    GLuint m_RendererID;
    GLuint m_Count;

public:
    IndexBuffer(const GLuint* data, GLuint count);

    ~IndexBuffer();

    void Bind() const;

    void UnBind() const;

    inline GLuint getCount() const { return m_Count; };
};

#endif //INDEXBUFFER_H
