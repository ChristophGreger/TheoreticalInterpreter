cmake_minimum_required(VERSION 3.28)
project(TheoreticalInterpreter C)

set(CMAKE_C_STANDARD 23)

include_directories(.)

add_executable(TheoreticalInterpreter
        main.c
        main.h)
