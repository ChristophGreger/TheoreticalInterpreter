cmake_minimum_required(VERSION 3.28)
project(TheoreticalInterpreter C)

set(CMAKE_C_STANDARD 23)

include_directories(.)

add_executable(TheoreticalInterpreter
        main.c
        main.h
        lexical/lexicalanalyzer.c
        lexical/lexicalanalyzer.h
        Parser/parser.c
        Parser/parser.h)
