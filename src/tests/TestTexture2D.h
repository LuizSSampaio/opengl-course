//
// Created by luizh on 03/12/2023.
//

#ifndef TESTTEXTURE2D_H
#define TESTTEXTURE2D_H

#include <memory>

#include "Test.h"
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace test {
    class TestTexture2D : public Test {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::mat4 m_Proj{}, m_View{};
        glm::vec3 m_TranslationA, m_TranslationB;
    };
} // test

#endif //TESTTEXTURE2D_H
