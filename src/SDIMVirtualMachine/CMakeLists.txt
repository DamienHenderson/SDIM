cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_library(SDIMVirtualMachine STATIC VirtualMachine.cpp VMState.cpp Instructions.cpp ../../include/SDIMVirtualMachine/VirtualMachine.hpp ../../include/SDIMVirtualMachine/VMState.hpp ../../include/SDIMVirtualMachine/Instructions.hpp)

target_include_directories(
    SDIMVirtualMachine 
    PUBLIC ../../include/SDIMVirtualMachine 
    PRIVATE .
)
target_compile_features(
    SDIMVirtualMachine
    PUBLIC cxx_std_17
)

target_link_libraries(SDIMVirtualMachine PUBLIC SDIMCommon)

