# Bits to Banking | Umicom Foundation | MIT | Compose existing C23 teaching APIs
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingBlockingIpc LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
# The queue and ready-list algorithms already belong to previous learning labs.
# Reuse their exact sources rather than create a second competing implementation.
add_library(btb_blocking_dependencies STATIC
    ../bounded-channel/channel.c
    ../round-robin-scheduler/round_robin.c)
target_include_directories(btb_blocking_dependencies PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../bounded-channel"
    "${CMAKE_CURRENT_SOURCE_DIR}/../round-robin-scheduler")
add_library(btb_blocking_session STATIC session.c)
target_include_directories(btb_blocking_session PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb_blocking_session PUBLIC btb_blocking_dependencies)
add_executable(btb-blocking-ipc main.c)
target_link_libraries(btb-blocking-ipc PRIVATE btb_blocking_session)
if(BUILD_TESTING)
    add_executable(btb-blocking-ipc-test test_session.c)
    target_link_libraries(btb-blocking-ipc-test PRIVATE btb_blocking_session)
    add_test(NAME bits2banking.blocking_ipc.delivery COMMAND btb-blocking-ipc-test delivery)
    add_test(NAME bits2banking.blocking_ipc.cancellation COMMAND btb-blocking-ipc-test cancellation)
    set_tests_properties(bits2banking.blocking_ipc.delivery bits2banking.blocking_ipc.cancellation
        PROPERTIES LABELS "education;c23;ipc;kernel-learning")
endif()
foreach(target IN ITEMS btb_blocking_dependencies btb_blocking_session btb-blocking-ipc btb-blocking-ipc-test)
    if(TARGET ${target})
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endif()
endforeach()
