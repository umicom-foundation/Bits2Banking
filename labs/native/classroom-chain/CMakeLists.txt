#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/classroom-chain/CMakeLists.txt
#
# PURPOSE:
#   Build a strict C23 classroom chain and optional x86-64 parity fixture.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingClassroomChain LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Use the reviewed Framework implementation shared by the other digest labs.
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Reviewed Umicom Framework checkout")
if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/src/base/sha256.c" OR
   NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/include/umicom/base/sha256.h")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the reviewed Umicom Framework checkout.")
endif()
add_library(bits2banking-classroom-chain STATIC chain.c "${UMICOM_FRAMEWORK_SOURCE}/src/base/sha256.c")
target_include_directories(bits2banking-classroom-chain PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}" "${UMICOM_FRAMEWORK_SOURCE}/include")

function(classroom_strict_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE $<$<COMPILE_LANGUAGE:C>:/W4>)
    else()
        target_compile_options(${target} PRIVATE
            $<$<COMPILE_LANGUAGE:C>:-Wall;-Wextra;-Wpedantic;-Wconversion;-Wshadow;-Werror>)
    endif()
endfunction()
classroom_strict_warnings(bits2banking-classroom-chain)

add_executable(bits2banking-classroom-chain-demo main.c)
target_link_libraries(bits2banking-classroom-chain-demo PRIVATE bits2banking-classroom-chain)
classroom_strict_warnings(bits2banking-classroom-chain-demo)

option(CLASSROOM_ENABLE_X86_64_ASM "Enable optional GNU-style x86-64 ABI parity check" OFF)
if(BUILD_TESTING)
    add_executable(bits2banking-classroom-chain-test test_chain.c)
    target_link_libraries(bits2banking-classroom-chain-test PRIVATE bits2banking-classroom-chain)
    classroom_strict_warnings(bits2banking-classroom-chain-test)
    foreach(case IN ITEMS ledger refusal tamper forks)
        add_test(NAME bits2banking.classroom_chain.${case} COMMAND bits2banking-classroom-chain-test ${case})
    endforeach()
    add_test(NAME bits2banking.classroom_chain.example COMMAND bits2banking-classroom-chain-demo)
    set_tests_properties(bits2banking.classroom_chain.example PROPERTIES
        PASS_REGULAR_EXPRESSION "accepted branch: 3 blocks, 18 classroom units")
    if(CLASSROOM_ENABLE_X86_64_ASM)
        if(NOT CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64)$" OR MSVC OR
           NOT CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$" OR
           NOT CMAKE_SYSTEM_NAME MATCHES "^(Linux|Windows)$")
            message(FATAL_ERROR "This Assembly lesson requires GNU-style x86-64 Linux or Windows tools.")
        endif()
        enable_language(ASM)
        target_sources(bits2banking-classroom-chain-test PRIVATE target_x86_64.S)
        target_compile_definitions(bits2banking-classroom-chain-test PRIVATE CLASSROOM_TEST_ASM=1)
        add_test(NAME bits2banking.classroom_chain.assembly_abi COMMAND bits2banking-classroom-chain-test assembly)
    endif()
endif()
