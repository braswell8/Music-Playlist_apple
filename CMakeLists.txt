cmake_minimum_required(VERSION 4.2)
project(untitled)

set(CMAKE_CXX_STANDARD 20)


add_executable(untitled main.cpp
        playlist_linked_list.cpp
        playlist_linked_list.h
        Song.cpp
        Song.h
)
add_custom_command(
        TARGET untitled POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Library-simple.csv
        ${CMAKE_BINARY_DIR}/Library-simple.csv
)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(untitled PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)

