cmake_minimum_required(VERSION 3.18)
project(assignment_4_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLiteCpp QUIET)

if(NOT SQLiteCpp_FOUND)
    # If not found via find_package, check if we have it as a submodule
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SQLiteCpp/CMakeLists.txt")
        # Add SQLiteCpp as a submodule
        add_subdirectory(SQLiteCpp)
        set(SQLITECPP_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/SQLiteCpp/include")
    else()
        # Try to find it in the system paths or vcpkg (i tthink its for windows)
        find_path(SQLITECPP_INCLUDE_DIRS NAMES SQLiteCpp/SQLiteCpp.h)
        find_library(SQLITECPP_LIBRARIES NAMES SQLiteCpp)
        
        if(NOT SQLITECPP_INCLUDE_DIRS OR NOT SQLITECPP_LIBRARIES)
            message(FATAL_ERROR "SQLiteCpp not found. Please install it or clone the submodule.")
        endif()
    endif()
endif()

find_package(Threads REQUIRED)
find_package(SQLite3 QUIET)

if(NOT SQLite3_FOUND)
    # Look for it in standard locations
    find_library(SQLITE3_LIBRARY NAMES sqlite3)
    find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h)
    
    if(NOT SQLITE3_LIBRARY OR NOT SQLITE3_INCLUDE_DIR)
        message(FATAL_ERROR "SQLite3 not found. Please install it.")
    endif()
endif()

add_executable(assignment_4_1 main.cpp)

# Include directories
if(TARGET SQLiteCpp)
    # If we're using the submodule or found via find_package
    target_link_libraries(assignment_4_1 
        SQLiteCpp
        ${CMAKE_DL_LIBS}
        Threads::Threads
    )
else()
    # If we found it manually
    target_include_directories(assignment_4_1 PRIVATE ${SQLITECPP_INCLUDE_DIRS})
    target_link_libraries(assignment_4_1 
        ${SQLITECPP_LIBRARIES}
        ${SQLITE3_LIBRARY}
        ${CMAKE_DL_LIBS}
        Threads::Threads
    )
endif()

# Set installation targets
install(TARGETS assignment_4_1 DESTINATION bin)
