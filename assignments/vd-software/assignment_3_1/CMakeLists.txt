cmake_minimum_required(VERSION 3.10)
project(assignment_3_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

add_executable(assignment_3_1 main.cpp)

# Link SFML libraries
target_link_libraries(assignment_3_1 sfml-graphics sfml-audio sfml-window sfml-system)

file(COPY ${CMAKE_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/resources/)

# some installation rules
install(TARGETS assignment_3_1 DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/ DESTINATION bin/resources/)

set_property(TARGET assignment_3_1 PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
