# 生成Makefile文件到build目录:
# cmake -G "MinGW Makefiles" -B build .
# 利用Makefile文件生成exe:
# cmake --build ./build

cmake_minimum_required(VERSION 3.5)

project(Yesane LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(. DIR_SRCS)

add_executable(Yesane ${DIR_SRCS})

install(TARGETS Yesane
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
