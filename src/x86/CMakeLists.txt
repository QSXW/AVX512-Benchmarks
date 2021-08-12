cmake_minimum_required(VERSION 3.10)

project(x86 ASM_NASM)

set(ASM_FILES
    sample.asm)

source_group("\\" FILES ${SRC_FILES})
source_group("\\x86\\" FILES ${ASM_FILES})

add_library(${PROJECT_NAME} STATIC ${ASM_FILES})
