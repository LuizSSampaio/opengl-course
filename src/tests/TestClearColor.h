//
// Created by luizh on 03/12/2023.
//

#ifndef TESTCLEARCOLOR_H
#define TESTCLEARCOLOR_H
#include "Test.h"

namespace test {
    class TestClearColor : public Test {
    public:
        TestClearColor();
        ~TestClearColor();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        float m_ClearColor[4];
    };
} // test

#endif //TESTCLEARCOLOR_H
