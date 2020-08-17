cmake_minimum_required(VERSION 3.0)

project(linux_interface)

add_definitions( -g )

file(GLOB scr_file
./chapter4/*.c)

include_directories(./chapter4)

add_executable(mainsample ./main.c ${scr_file})