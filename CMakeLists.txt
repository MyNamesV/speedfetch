cmake_minimum_required(VERSION 3.10)
project(speedfetch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(speedfetch
    src/main.cpp
    src/system_info.cpp
    src/ascii_art.cpp
    src/config.cpp
)

target_include_directories(speedfetch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
