cmake_minimum_required(VERSION 3.10)

project(diabloui VERSION 1.00 LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(diabloui SHARED diabloui.cpp)
target_include_directories(diabloui PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
    $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source
)
