cmake_minimum_required(VERSION 3.10)
project(assignment_2_1)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

# Fetch RapidCSV library (header only)
FetchContent_Declare(
    rapidcsv
    GIT_REPOSITORY https://github.com/d99kris/rapidcsv.git
    GIT_TAG master
)
FetchContent_MakeAvailable(rapidcsv)

# Include RapidCSV header path
include_directories(${rapidcsv_SOURCE_DIR}/src)

add_executable(assignment_2_1 main.cpp)

# Create test data files. found out i could use file(WRITE) to create the files
file(WRITE ${CMAKE_BINARY_DIR}/customers.csv "id,name,address\n1,\"Knut\",\"Knutveien 3\"\n2,\"Lise\",\"Liseveien 7\"")
file(WRITE ${CMAKE_BINARY_DIR}/products.csv "id,name,price\n1,\"banana\",5\n2,\"apple\",10")
file(WRITE ${CMAKE_BINARY_DIR}/orders.csv "id,customerid,productid,amount\n1,1,1,2\n2,2,1,3\n3,1,2,4")
