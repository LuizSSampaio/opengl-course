//
// Created by luizh on 03/12/2023.
//

#ifndef TEST_H
#define TEST_H

namespace test {
    class Test {
    public:
        Test();
        virtual ~Test();

        virtual void OnUpdate(float deltaTime) {
        }

        virtual void OnRender() {
        }

        virtual void OnImGuiRender() {
        }
    };
}

#endif //TEST_H
