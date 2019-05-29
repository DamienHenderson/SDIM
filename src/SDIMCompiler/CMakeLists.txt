cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_library(SDIMCompiler STATIC Compiler.cpp Scanner.cpp Parser.cpp Token.cpp LangUtils.cpp BytecodeGenerator.cpp OperatorPrecedence.cpp Generator.cpp Expression.cpp ScopingBlock.cpp ILCompiler.cpp
	../../include/SDIMCompiler/ILCompiler.hpp ../../include/SDIMCompiler/Scanner.hpp ../../include/SDIMCompiler/Parser.hpp ../../include/SDIMCompiler/Token.hpp ../../include/SDIMCompiler/LangUtils.hpp ../../include/SDIMCompiler/BytecodeGenerator.hpp ../../include/SDIMCompiler/OperatorPrecedence.hpp ../../include/SDIMCompiler/Generator.hpp ../../include/SDIMCompiler/Expression.hpp ../../include/SDIMCompiler/ScopingBlock.hpp)

target_include_directories(
    SDIMCompiler 
    PUBLIC ../../include/SDIMCompiler
    PRIVATE .
)
target_compile_features(
    SDIMCompiler
    PUBLIC cxx_std_17
)





target_link_libraries(SDIMCompiler PUBLIC SDIMCommon)