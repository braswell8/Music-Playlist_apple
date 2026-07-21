cmake_minimum_required(VERSION 4.2)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/qt")

include_directories()

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(untitled main.cpp
        playlist_linked_list.cpp
        playlist_linked_list.h
        Song.cpp
        Song.h
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_custom_command(
        TARGET untitled POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/Library-Genre.csv
        ${CMAKE_BINARY_DIR}/Library-Genre.csv
)



target_link_libraries(untitled PRIVATE CURL::libcurl nlohmann_json::nlohmann_json Qt6::Widgets)

