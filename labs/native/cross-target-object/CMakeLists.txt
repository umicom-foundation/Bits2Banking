#-----------------------------------------------------------------------------
# Bits to Banking | Umicom Foundation
# File: labs/native/cross-target-object/CMakeLists.txt
# PURPOSE: Build relocatable, freestanding C23 objects for host or RISC-V64.
# LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingCrossTarget LANGUAGES C)

# An OBJECT library compiles .c/.S to .o/.obj but does not link or run a
# program. This prevents accidental execution of RISC-V64 code on Windows.
add_library(btb-target-probe OBJECT probe.c)
set_target_properties(btb-target-probe PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
    target_compile_options(btb-target-probe PRIVATE
        -ffreestanding -fno-builtin -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(CMAKE_SYSTEM_PROCESSOR STREQUAL "riscv64")
    enable_language(ASM)
    target_sources(btb-target-probe PRIVATE riscv64_hart.S)
endif()
