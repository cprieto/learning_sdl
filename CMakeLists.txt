cmake_minimum_required(VERSION 3.16)

project(test_ui VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This is to support conan packages
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(app main.cpp Game.cpp)
target_link_libraries(app ${CONAN_LIBS})
