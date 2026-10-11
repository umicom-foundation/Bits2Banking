#-----------------------------------------------------------------------------
# Bits to Banking | Umicom Foundation
# File: labs/native/checked-money/CMakeLists.txt
# PURPOSE: Compile and test exact fictional account arithmetic in C23.
# AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
# LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingCheckedMoney LANGUAGES C)
include(CTest)
option(BTB_ENABLE_SANITIZERS "Use AddressSanitizer and UBSan where supported" OFF)
add_library(btb_checked_account STATIC account.c)
add_executable(bits2banking-checked-money main.c)
add_executable(bits2banking-checked-money-test test_account.c)
target_link_libraries(bits2banking-checked-money PRIVATE btb_checked_account)
target_link_libraries(bits2banking-checked-money-test PRIVATE btb_checked_account)
foreach(target IN ITEMS btb_checked_account bits2banking-checked-money bits2banking-checked-money-test)
    set_target_properties(${target} PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
    if(BTB_ENABLE_SANITIZERS AND NOT MSVC)
        target_compile_options(${target} PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(${target} PRIVATE -fsanitize=address,undefined)
    endif()
endforeach()
if(BUILD_TESTING)
    add_test(NAME bits2banking.checked_money COMMAND bits2banking-checked-money-test)
    set_tests_properties(bits2banking.checked_money PROPERTIES LABELS "education;c23;money;overflow")
endif()
