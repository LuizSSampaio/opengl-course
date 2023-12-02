cmake_minimum_required(VERSION 3.27)
project(stb VERSION 1.0.0)

add_library(stb stb_image.cpp)

target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})