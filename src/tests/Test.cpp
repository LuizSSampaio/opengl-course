//
// Created by luizh on 03/12/2023.
//

#include "Test.h"

#include "imgui.h"

namespace test {
    TestMenu::TestMenu(Test*& currentTestPointer) : m_CurrentTest(currentTestPointer) {
    }

    void TestMenu::OnImGuiRender() {
        Test::OnImGuiRender();
        for (auto& test : m_Tests) {
            if (ImGui::Button(test.first.c_str())) {
                m_CurrentTest = test.second();
            }
        }
    }
}
