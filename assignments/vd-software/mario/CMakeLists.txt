cmake_minimum_required(VERSION 3.10)
project(SuperMarioBros)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML packages
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# src files
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "src/Headers/*.hpp")

# Add executable
add_executable(mario ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(mario sfml-graphics sfml-window sfml-system sfml-audio)

# Include directories
target_include_directories(mario PRIVATE "src")

# Create resources/Sounds directory in build directory if it doesn't exist
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources/Sounds)

# Copy sound resources
set(SOUND_FILES
    resources/Sounds/jump.wav
    resources/Sounds/coin.wav
    resources/Sounds/powerup.wav
    resources/Sounds/break.wav
    resources/Sounds/stomp.wav
    resources/Sounds/theme.ogg
)

foreach(SOUND_FILE ${SOUND_FILES})
    configure_file(${SOUND_FILE} ${CMAKE_BINARY_DIR}/${SOUND_FILE} COPYONLY)
endforeach()
