cmake_minimum_required(VERSION 3.27)
project(opengl_course)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw-3.3.8)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/imgui)
add_subdirectory(thirdparty/stb)

add_executable(opengl_course src/Application.cpp
        src/Renderer.cpp
        src/Renderer.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h
        src/VertexArray.cpp
        src/VertexArray.h
        src/VertexBufferLayout.h
        src/Shader.cpp
        src/Shader.h
        src/Texture.cpp
        src/Texture.h
        src/tests/Test.h
        src/tests/TestClearColor.cpp
        src/tests/TestClearColor.h
        src/tests/Test.cpp
        src/tests/TestTexture2D.cpp
        src/tests/TestTexture2D.h
)

target_link_libraries(opengl_course PRIVATE glfw glad stb glm imgui)
