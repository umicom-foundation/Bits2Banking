#-----------------------------------------------------------------------------
# Bits to Banking | Umicom Foundation
# File: labs/native/binary-payment-records/CMakeLists.txt
# PURPOSE: Build a portable C23 record encoder and deterministic tests.
# AUTHOR: Sammy Hegab | LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BitsToBankingBinaryPaymentRecords LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
add_library(btb_payment_record STATIC record.c)
target_include_directories(btb_payment_record PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(bits2banking-record-demo main.c)
target_link_libraries(bits2banking-record-demo PRIVATE btb_payment_record)
if(BUILD_TESTING)
    add_executable(bits2banking-record-test test_record.c)
    target_link_libraries(bits2banking-record-test PRIVATE btb_payment_record)
    add_test(NAME bits2banking.binary-records COMMAND bits2banking-record-test)
endif()
foreach(target IN ITEMS btb_payment_record bits2banking-record-demo bits2banking-record-test)
    if(TARGET ${target} AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()
