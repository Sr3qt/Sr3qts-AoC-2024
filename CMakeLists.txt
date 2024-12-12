cmake_minimum_required(VERSION 3.5.0)
project(AoC-2024 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(AoC-2024 main.cpp)

# include_directories(dec01)
# link_directories(dec01)
# add_subdirectory(dec01)

# target_link_libraries(AoC-2024 dec01 )

# add_subdirectory(${CMAKE_SOURCE_DIR}/dec1)
# add_subdirectory(${CMAKE_SOURCE_DIR}/dec1)
# add_subdirectory(${CMAKE_SOURCE_DIR}/dec1)

target_include_directories(AoC-2024 PUBLIC
    .
    ${CMAKE_SOURCE_DIR}/utils
)