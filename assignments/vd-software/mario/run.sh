#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define the build directory name
BUILD_DIR="build"

# Define the executable name
EXECUTABLE_NAME="mario"

# Get the current directory (project root)
PROJECT_ROOT_DIR=$(pwd)

# 1. Check if the build directory exists and remove it if it does
if [ -d "$BUILD_DIR" ]; then
  echo "Removing existing build directory: $BUILD_DIR"
  rm -rf "$BUILD_DIR"
fi

# 2. Create the build directory
echo "Creating build directory: $BUILD_DIR"
mkdir "$BUILD_DIR"

# 3. Change to the build directory
echo "Changing to build directory: $BUILD_DIR"
cd "$BUILD_DIR"

# 4. Run cmake
echo "Running cmake..."
cmake ..

# 5. Run make
echo "Running make..."
make

# 6. Change back to the project root directory
echo "Changing back to project root directory: $PROJECT_ROOT_DIR"
cd "$PROJECT_ROOT_DIR"

# 7. Run the executable
# Assuming the executable 'mario' is created in the build directory
EXECUTABLE_PATH="./$BUILD_DIR/$EXECUTABLE_NAME"

if [ -f "$EXECUTABLE_PATH" ]; then
  echo "Running executable: $EXECUTABLE_PATH"
  "$EXECUTABLE_PATH"
else
  echo "Error: Executable '$EXECUTABLE_NAME' not found in '$BUILD_DIR'."
  # Try to find it in the current directory as a fallback,
  # though typically build systems place it in the build dir.
  if [ -f "./$EXECUTABLE_NAME" ]; then
    echo "Found executable in current directory. Running: ./$EXECUTABLE_NAME"
    "./$EXECUTABLE_NAME"
  else
    echo "Error: Executable '$EXECUTABLE_NAME' also not found in current directory."
    exit 1
  fi
fi

echo "Script finished."