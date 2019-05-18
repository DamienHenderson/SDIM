cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_library(SDIMCommon STATIC Utils.cpp Allocator.cpp Stack.cpp Types.cpp VariableStorage.cpp HashTable.cpp
 ../../include/SDIMCommon/Utils.hpp ../../include/SDIMCommon/Allocator.hpp ../../include/SDIMCommon/Stack.hpp ../../include/SDIMCommon/Types.hpp ../../include/SDIMCommon/VariableStorage.hpp ../../include/SDIMCommon/HashTable.hpp)

target_include_directories(
    SDIMCommon 
    PUBLIC ../../include/SDIMCommon 
    PRIVATE .
)
target_compile_features(
    SDIMCommon
    PUBLIC cxx_std_17
)

target_compile_definitions(SDIMCommon PUBLIC SDIM_VERBOSE=1)