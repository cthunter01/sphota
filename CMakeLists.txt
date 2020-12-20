cmake_minimum_required(VERSION 3.0)

project(sphota)

FILE(GLOB CPPSources *.cpp Lexer/*.cpp Parser/*.cpp)
include_directories(.)
add_executable(sphota ${CPPSources})

install(TARGETS sphota RUNTIME DESTINATION bin)
