# CMakeList.txt : CMake project for Lumina, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Lumina")

message(${PROJECT_NAME})

# Add source to this project's executable.
add_executable (Lumina "Lumina.cpp" "Lumina.h")

# TODO: Add tests and install targets if needed.
