# Bits2Banking | Umicom Foundation | C23 work-dispatch composition laboratory.
# The two preceding libraries are reused as source dependencies, unmodified.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingWorkDispatch LANGUAGES C)
include(CTest)

add_library(btb-dispatch-foundations STATIC
    ../work-handoff/handoff.c
    ../completion-queue/queue.c)
target_include_directories(btb-dispatch-foundations PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../work-handoff"
    "${CMAKE_CURRENT_SOURCE_DIR}/../completion-queue")

add_library(btb-work-dispatch STATIC dispatch.c)
target_link_libraries(btb-work-dispatch PUBLIC btb-dispatch-foundations)
target_include_directories(btb-work-dispatch PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(btb-work-dispatch-test test_dispatch.c)
add_executable(btb-work-dispatch-demo dispatch_demo.c)
target_link_libraries(btb-work-dispatch-test PRIVATE btb-work-dispatch)
target_link_libraries(btb-work-dispatch-demo PRIVATE btb-work-dispatch)

option(BTB_ENABLE_SANITIZERS "Enable ASan and UBSan with Clang/GCC" OFF)
foreach(target IN ITEMS btb-dispatch-foundations btb-work-dispatch
                       btb-work-dispatch-test btb-work-dispatch-demo)
    set_target_properties(${target} PROPERTIES
        C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
        if(BTB_ENABLE_SANITIZERS)
            target_compile_options(${target} PRIVATE
                -fsanitize=address,undefined -fno-omit-frame-pointer -g -O1)
            target_link_options(${target} PRIVATE -fsanitize=address,undefined)
        endif()
    endif()
endforeach()

if(BUILD_TESTING)
    foreach(case_name IN ITEMS fifo capacity cancel stale quiesce
                               invalid ownership stress)
        add_test(NAME "bits2banking.dispatch.${case_name}"
                 COMMAND btb-work-dispatch-test "${case_name}")
    endforeach()
    add_test(NAME bits2banking.dispatch.demo COMMAND btb-work-dispatch-demo)
endif()
