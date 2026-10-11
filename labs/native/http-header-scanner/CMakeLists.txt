#-----------------------------------------------------------------------------
# Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
# File: labs/native/http-header-scanner/CMakeLists.txt
# PURPOSE: Compare C and Assembly without duplicating Umicom Framework.
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BitsHttpScanner LANGUAGES C)
include(CTest)
option(BITS_HTTP_ENABLE_ASSEMBLY "Build architecture-specific Assembly when supported" ON)
add_library(bits_http_scanner STATIC scanner.c)
target_include_directories(bits_http_scanner PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(bits_http_scanner PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)

if(BITS_HTTP_ENABLE_ASSEMBLY)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(x86_64|AMD64|amd64)$")
        set(_bits_assembly_file scan_x86_64.S)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "^(riscv64|riscv64gc)$" AND NOT WIN32)
        set(_bits_assembly_file scan_riscv64.S)
    endif()
    if(DEFINED _bits_assembly_file AND CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
        enable_language(ASM)
        target_sources(bits_http_scanner PRIVATE "${_bits_assembly_file}")
        target_compile_definitions(bits_http_scanner PUBLIC BITS_HTTP_HAVE_ASSEMBLY=1)
    else()
        message(STATUS "No supported native Assembly target; using portable C only.")
    endif()
endif()

add_executable(bits-http-scan main.c)
target_link_libraries(bits-http-scan PRIVATE bits_http_scanner)
if(BUILD_TESTING)
    add_executable(bits-http-scan-test test_scanner.c)
    target_link_libraries(bits-http-scan-test PRIVATE bits_http_scanner)
    add_test(NAME bits.http.scanner.boundaries COMMAND bits-http-scan-test)
    add_test(NAME bits.http.scanner.demo COMMAND bits-http-scan)
endif()
foreach(target IN ITEMS bits_http_scanner bits-http-scan)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()
