cmake_minimum_required(VERSION 3.10)
project(mario)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)

# Add source files
set(SOURCE_FILES 
    src/main.cpp
    src/Game.cpp
    src/Mario.cpp
    src/Level.cpp
    src/Entity.cpp
    src/Block.cpp
    src/Coin.cpp
    src/Mushroom.cpp
    src/Animation.cpp
)

# Add header files
set(HEADER_FILES
    include/Game.hpp
    include/Mario.hpp
    include/Level.hpp
    include/Entity.hpp
    include/Block.hpp
    include/Coin.hpp
    include/Mushroom.hpp
    include/Animation.hpp
)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add executable
add_executable(mario ${SOURCE_FILES} ${HEADER_FILES})

# Link SFML libraries
target_link_libraries(mario sfml-graphics sfml-audio sfml-window sfml-system)

# Copy resources to build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/resources/)

# Installation rules
install(TARGETS mario DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/ DESTINATION bin/resources/)

set_property(TARGET mario PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
