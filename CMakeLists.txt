cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "aoc")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${PROJECT_NAME})
include_directories(include)

set(SOURCE_FILES
	src/main.cpp
	src/day1.cpp
	src/day2.cpp
	src/day3.cpp
	src/day4.cpp
	src/day5.cpp
	src/day6.cpp
	src/day7.cpp
	src/day8.cpp
)

add_compile_options(-Wall -Wextra -pedantic -g)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
