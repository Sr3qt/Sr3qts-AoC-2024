cmake_minimum_required(VERSION 3.5.0)
project(AoC-2024 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(AoC-2024 main.cpp)

target_include_directories(AoC-2024 PUBLIC
    .
    ${CMAKE_SOURCE_DIR}/utils
)