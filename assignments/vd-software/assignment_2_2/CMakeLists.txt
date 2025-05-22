cmake_minimum_required(VERSION 3.10)
project(assignment_2_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# had tarball URL instead of Git. rapidjson has too many warnings and errors
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz
  URL_HASH SHA256=8c4b26bf4b422252e13f332bc5e388ec0ab5c3443d24399acb675e68278d341f
)
FetchContent_MakeAvailable(json)


set(SOURCES
    main.cpp
    Student.cpp
)

add_executable(assignment_2_2 ${SOURCES})

#  find the nlohmann/json headers
target_include_directories(assignment_2_2 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${json_SOURCE_DIR}/include
)

target_link_libraries(assignment_2_2 PRIVATE nlohmann_json::nlohmann_json)

#  test data file for the JSON reader
file(WRITE ${CMAKE_BINARY_DIR}/students.json "[\n  {\n    \"id\": 1,\n    \"name\": \"Lisa Larsen\",\n    \"age\": 22,\n    \"attendance\": 70\n  },\n  {\n    \"id\": 2,\n    \"name\": \"Knut Knutsen\",\n    \"age\": 29,\n    \"attendance\": 50\n  }\n]")

