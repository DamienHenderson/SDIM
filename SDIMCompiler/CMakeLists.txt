cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_library(SDIMCompiler STATIC src/Compiler.cpp src/Scanner.cpp src/Parser.cpp src/Token.cpp src/LangUtils.cpp src/BytecodeGenerator.cpp src/OperatorPrecedence.cpp src/Generator.cpp
	include/Compiler.hpp include/Scanner.hpp include/Parser.hpp include/Token.hpp include/LangUtils.hpp include/BytecodeGenerator.hpp include/OperatorPrecedence.hpp include/Generator.hpp)

target_include_directories(
    SDIMCompiler 
    PUBLIC include 
    PRIVATE src
)
target_compile_features(
    SDIMCompiler
    PUBLIC cxx_std_17
)


#target_compile_definitions(SDIMVirtualMachine PUBLIC $<$<CONFIG:DEBUG>:SDIMVM_DEBUG>)


target_link_libraries(SDIMCompiler PUBLIC SDIMCommon)