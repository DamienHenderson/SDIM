cmake_minimum_required(VERSION 3.8)

project(SDIM VERSION 0.0.1 LANGUAGES CXX)
# Global compile options to enforce quality in my code
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wpedantic -Wall -Wextra -Werror)
endif()

add_subdirectory(src/SDIMCommon)
add_subdirectory(src/SDIMCompiler)
add_subdirectory(src/SDIMVirtualMachine)
add_subdirectory(src/SDIMC)
add_subdirectory(src/SDIMVM)
