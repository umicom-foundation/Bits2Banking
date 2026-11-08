# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-http-contracts/CMakeLists.txt
#
# PURPOSE:
#   Build small clients of the existing Framework HTTP contracts.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BtbHttpContracts LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS web)
# The incremental example uses the same installed web component. Preserve
# the earlier four-program list for review as the lab gains an owned stream.
# foreach(name IN ITEMS framing response routes exchange)
foreach(name IN ITEMS framing response routes exchange stream)
    add_executable(btb-http-${name} ${name}.c)
    target_link_libraries(btb-http-${name} PRIVATE Umicom::web)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(btb-http-${name} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
    if(BUILD_TESTING)
        add_test(NAME bits2banking.http.${name} COMMAND btb-http-${name})
        set_tests_properties(bits2banking.http.${name} PROPERTIES TIMEOUT 10)
    endif()
endforeach()
