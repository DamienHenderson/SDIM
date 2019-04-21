cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_executable(SDIMVM src/main.cpp)

target_include_directories(
    SDIMVM 
    PUBLIC include 
    PRIVATE src
)
target_compile_features(
    SDIMVM
    PUBLIC cxx_std_17
)
#IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
#    target_compile_definitions(SDIMVM PRIVATE SDIMVM_DEBUG=1)
#ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

target_link_libraries(SDIMVM PRIVATE SDIMVirtualMachine)