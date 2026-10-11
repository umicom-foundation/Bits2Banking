# Bits to Banking | Umicom Foundation | MIT
# Composition: use the earlier scheduler and timer source once; this project
# supplies only the coordinating service. No duplicate scheduler/clock.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingTimedService LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_library(btb_timed_dependencies STATIC
    ../round-robin-scheduler/round_robin.c
    ../monotonic-deadlines/deadline.c)
target_include_directories(btb_timed_dependencies PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../round-robin-scheduler"
    "${CMAKE_CURRENT_SOURCE_DIR}/../monotonic-deadlines")
add_library(btb_timed_service STATIC service.c)
target_include_directories(btb_timed_service PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb_timed_service PUBLIC btb_timed_dependencies)
add_executable(btb-timed-service main.c)
target_link_libraries(btb-timed-service PRIVATE btb_timed_service)
if(BUILD_TESTING)
    add_executable(btb-timed-service-test test_service.c)
    target_link_libraries(btb-timed-service-test PRIVATE btb_timed_service)
    add_test(NAME bits2banking.timed_service.event COMMAND btb-timed-service-test delivery)
    add_test(NAME bits2banking.timed_service.timeout COMMAND btb-timed-service-test timeout)
    add_test(NAME bits2banking.timed_service.cancel COMMAND btb-timed-service-test cancel)
    set_tests_properties(bits2banking.timed_service.event bits2banking.timed_service.timeout
        bits2banking.timed_service.cancel PROPERTIES LABELS "education;c23;scheduling;timer")
endif()
foreach(target IN ITEMS btb_timed_dependencies btb_timed_service btb-timed-service btb-timed-service-test)
    if(TARGET "${target}")
        if(MSVC)
            target_compile_options("${target}" PRIVATE /W4)
        else()
            target_compile_options("${target}" PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endif()
endforeach()
