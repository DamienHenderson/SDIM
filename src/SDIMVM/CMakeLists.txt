cmake_minimum_required(VERSION 3.8)


add_executable(SDIMVM main.cpp)

target_include_directories(
    SDIMVM 
    PUBLIC ../../include/SDIMVM
    PRIVATE .
)
target_compile_features(
    SDIMVM
    PUBLIC cxx_std_17
)

target_link_libraries(SDIMVM PRIVATE SDIMVirtualMachine)