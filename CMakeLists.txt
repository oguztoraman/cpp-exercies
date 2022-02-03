cmake_minimum_required(VERSION 3.14)

project(date LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

add_compile_options(-Wall -Werror)

include_directories("${PROJECT_SOURCE_DIR}/inc")

file(GLOB SRCS "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(date tests.cpp ${SRCS})
