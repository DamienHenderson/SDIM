cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_library(SDIMCompiler STATIC src/Compiler.cpp src/Scanner.cpp src/Token.cpp src/LangUtils.cpp)

target_include_directories(
    SDIMCompiler 
    PUBLIC include 
    PRIVATE src
)
target_compile_features(
    SDIMCompiler
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates
)
target_link_libraries(SDIMCompiler PRIVATE SDIMCommon)