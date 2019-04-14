cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_library(SDIMVirtualMachine STATIC src/VirtualMachine.cpp src/VMState.cpp src/Instructions.cpp)

target_include_directories(
    SDIMVirtualMachine 
    PUBLIC include 
    PRIVATE src
)
target_compile_features(
    SDIMVirtualMachine
    PUBLIC cxx_auto_type
    PRIVATE cxx_variadic_templates
)
target_link_libraries(SDIMVirtualMachine PRIVATE SDIMCommon)

