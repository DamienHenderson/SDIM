cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_library(SDIMCommon STATIC src/Utils.cpp src/Allocator.cpp src/Stack.cpp src/Types.cpp include/Utils.hpp include/Allocator.hpp include/Stack.hpp include/Types.hpp)

target_include_directories(
    SDIMCommon 
    PUBLIC include 
    PRIVATE src
)
target_compile_features(
    SDIMCommon
    PUBLIC cxx_std_17
)

target_compile_definitions(SDIMCommon PUBLIC SDIM_VERBOSE=1)