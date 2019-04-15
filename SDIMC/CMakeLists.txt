cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_executable(SDIMC src/main.cpp)

target_include_directories(
    SDIMC 
    PUBLIC include 
    PRIVATE src
)
target_compile_features(
    SDIMC
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates
)
target_link_libraries(SDIMC PRIVATE SDIMCompiler)