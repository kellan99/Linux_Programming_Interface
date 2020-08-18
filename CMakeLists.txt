cmake_minimum_required(VERSION 3.0)

project(linux_interface)

add_definitions( -g -std=c++11)

file(GLOB scr_file
./chapter5/*.cpp
./chapter5/*.c
./chapter4/*.c)

include_directories(./chapter4)
include_directories(./chapter5)

add_executable(mainsample ./main.cpp ${scr_file})

target_link_libraries(mainsample pthread)