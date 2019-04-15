cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_executable(SDIMVM src/main.cpp)

target_include_directories(
    SDIMVM 
    PUBLIC include 
    PRIVATE src
)
target_compile_features(
    SDIMVM
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates
)
target_link_libraries(SDIMVM PRIVATE SDIMVirtualMachine)