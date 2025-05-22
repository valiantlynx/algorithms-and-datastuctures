cmake_minimum_required(VERSION 3.10)
project(assignment_1_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(assignment_1_1
        main.cpp
        Student.cpp
        Student.h
        Test.cpp
        Test.h
        TestResult.cpp
        TestResult.h
        DataManager.cpp
        DataManager.h
        UserInterface.cpp
        UserInterface.h)
