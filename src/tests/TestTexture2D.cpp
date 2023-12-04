//
// Created by luizh on 03/12/2023.
//

#include "TestTexture2D.h"

#include "../Renderer.h"

#include <imgui.h>

namespace test {
    TestTexture2D::TestTexture2D() : m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
                                     m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
                                     m_TranslationA(200, 200, 0),
                                     m_TranslationB(400, 200, 0) {
        GLfloat vertices[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f
        };

        GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_VertexArray = std::make_unique<VertexArray>();
        const VertexBuffer vertexBuffer(vertices, 4 * 4 * sizeof(GLfloat));

        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);

        m_VertexArray->AddBuffer(vertexBuffer, layout);
        m_VertexArray->Bind();

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        m_Shader = std::make_unique<Shader>("../resources/shaders/basic.glsl");
        m_Shader->Bind();

        m_Texture = std::make_unique<Texture>("../resources/textures/pop_cat.png");
        m_Texture->Bind();

        m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        m_Shader->SetUniform1i("u_Texture", 0);

        m_Shader->UnBind();
        vertexBuffer.UnBind();
        m_IndexBuffer->UnBind();
        m_VertexArray->UnBind();
        m_Texture->UnBind();
    }

    TestTexture2D::~TestTexture2D() {
    }

    void TestTexture2D::OnUpdate(float deltaTime) {
        Test::OnUpdate(deltaTime);
    }

    void TestTexture2D::OnRender() {
        Test::OnRender();
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture2D::OnImGuiRender() {
        Test::OnImGuiRender();

        {
            ImGui::Text("Translation A: ");
            ImGui::SliderFloat2("##TranslationA", &m_TranslationA.x, 0.0f, 960.0f);

            ImGui::Text("Translation B: ");
            ImGui::SliderFloat2("##TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
        }
    }
} // test
