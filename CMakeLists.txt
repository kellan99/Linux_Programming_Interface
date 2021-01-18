cmake_minimum_required(VERSION 3.0)

project(linux_interface)

add_compile_options( -g -std=c++11)

file(GLOB scr_file
./chapter5/*.cpp
./chapter5/*.c
./chapter4/*.c
./common_interface/*.cpp)


message("scr_file files: ${scr_file}")

include_directories(./chapter4)
include_directories(./chapter5)
include_directories(./common_interface)

add_executable(mainsample ./main.cpp ${scr_file})

target_link_libraries(mainsample pthread)