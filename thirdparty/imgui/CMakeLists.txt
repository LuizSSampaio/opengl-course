cmake_minimum_required(VERSION 3.27)
project(imgui)

add_library(imgui STATIC
        imgui.h
        imgui.cpp
        imconfig.h
        imgui_internal.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_widgets.cpp
        imgui_tables.cpp
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h
        backends/imgui_impl_glfw.h
        backends/imgui_impl_opengl3.h
        backends/imgui_impl_glfw.cpp
        backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/backends)
target_include_directories(imgui PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../glfw-3.3.8/include)
