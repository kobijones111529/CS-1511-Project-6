cmake_minimum_required(VERSION 3.0.0)
project(Project6 VERSION 0.1.0)

add_subdirectory(lib/fmt-8.1.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} fmt::fmt)

target_include_directories(${PROJECT_NAME} PRIVATE include)
