cmake_minimum_required(VERSION 3.10)

project(AVX512_Benchmarks LANGUAGES C CXX ASM_NASM)

set(CMAKE_VERBOSE_MAKEFILE True)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SRC_FILES
    src/sample.c)

source_group("\\" FILES ${SRC_FILES})

add_executable(${PROJECT_NAME}
    ${SRC_FILES})

target_compile_options(${PROJECT_NAME} PRIVATE -g -march=skylake-avx512 -mavx)

add_subdirectory(src/x86)

target_link_libraries(${PROJECT_NAME}
    x86)
