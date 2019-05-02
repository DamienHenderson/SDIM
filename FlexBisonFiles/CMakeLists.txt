cmake_minimum_required(VERSION 3.8)

# TODO: add actual files here
add_executable(Comp SDIM.tab.c FlexLexer.h)

target_compile_features(Comp PRIVATE cxx_std_17)