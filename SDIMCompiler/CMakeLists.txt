cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_library(SDIMCompiler STATIC src/Compiler.cpp src/Scanner.cpp src/Token.cpp src/LangUtils.cpp include/Compiler.hpp include/Scanner.hpp include/Token.hpp include/LangUtils.hpp)

target_include_directories(
    SDIMCompiler 
    PUBLIC include 
    PRIVATE src
)
target_compile_features(
    SDIMCompiler
    PUBLIC cxx_std_17
)

IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    target_compile_definitions(SDIMVirtualMachine PUBLIC SDIMC_DEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

target_link_libraries(SDIMCompiler PUBLIC SDIMCommon)