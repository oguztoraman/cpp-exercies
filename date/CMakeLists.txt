cmake_minimum_required(VERSION 3.13)

project(date LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_link_options(-g)

add_executable(date main.cpp date.cpp)
