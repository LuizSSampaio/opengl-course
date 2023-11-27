//
// Created by luizh on 27/11/2023.
//

#include "Renderer.h"

void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, const int line) {
    if (const GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << file << " : " << line << std::endl;
        return false;
    }
    return true;
}
