//
// Created by luizh on 01/12/2023.
//

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Renderer.h"
#include <glad/glad.h>
#include <stb_image.h>

class Texture {
private:
    GLuint m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture(const std::string& path);
    ~Texture();

    void Bind(GLuint slot = 0) const;
    void UnBind() const;

    inline int GetWidth() const { return  m_Width; }
    inline int GetHeight() const { return  m_Height; }
    inline int GetBPP() const { return  m_BPP; }
};

#endif //TEXTURE_H
