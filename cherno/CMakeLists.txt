cmake_minimum_required(VERSION 3.10)

# Project name
project(MyCppProject)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add your executable
add_executable(main main.cpp Log.cpp)
