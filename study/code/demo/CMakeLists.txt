cmake_minimum_required(VERSION 3.13)
project(demo C)

set(CMAKE_C_STANDARD 99)

add_executable(demo main.c basic_type.h nginx_pool.h nginx_pool.c basic_constant.h nginx_alloc.c nginx_alloc.h basic_constants.c)