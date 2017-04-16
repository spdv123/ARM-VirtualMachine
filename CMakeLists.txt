cmake_minimum_required(VERSION 3.6)
project(virtualARM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Instruction.cpp Instruction.h MyInput.cpp MyInput.h VirtualMachine.cpp VirtualMachine.h Scanner.cpp Scanner.h Loop.cpp Loop.h)
add_executable(virtualARM ${SOURCE_FILES})