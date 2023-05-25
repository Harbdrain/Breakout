cmake_minimum_required(VERSION 3.2)
project(breakout C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(WARNING_FLAGS -pedantic -Wall -Wextra -Werror -Wshadow -Wconversion -Wpointer-arith -Wswitch-enum)

add_executable(breakout src/platform.c)
target_compile_options(breakout PUBLIC ${WARNING_FLAGS})
