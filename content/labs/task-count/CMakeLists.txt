cmake_minimum_required(VERSION 3.24)
project(UmicomTaskCount LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(task-count main.c)

enable_testing()
add_test(NAME task-count-output COMMAND task-count)
set_tests_properties(task-count-output PROPERTIES
    PASS_REGULAR_EXPRESSION "Remaining tasks: 7")
