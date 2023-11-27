cmake_minimum_required(VERSION 3.27)
project(opengl_course)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty/glfw-3.3.8)
add_subdirectory(thirdparty/glad)

add_executable(opengl_course src/Application.cpp
        src/Renderer.cpp
        src/Renderer.h
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h)

target_link_libraries(opengl_course PRIVATE glfw glad)
