# CMakeList.txt : CMake project for TodoList, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("TodoList")

# Add source to this project's executable.
add_executable (TodoList  "LinkedList.cpp" "LinkedList.h" "Node.cpp" "Node.h" "Source.cpp" "fort.c" "fort.h" "fort.hpp")

# TODO: Add tests and install targets if needed.
