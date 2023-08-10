cmake_minimum_required(VERSION 3.26)
project(cflag_parser C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(cflag_parser
        flag_parser.c
        flag_parser.h
        main.c)
