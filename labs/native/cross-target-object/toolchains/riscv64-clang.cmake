#-----------------------------------------------------------------------------
# Bits to Banking | Umicom Foundation
# File: labs/native/cross-target-object/toolchains/riscv64-clang.cmake
# PURPOSE: Select Clang's RISC-V64 backend for relocatable freestanding objects.
# LICENCE: MIT
#-----------------------------------------------------------------------------
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR riscv64)
set(CMAKE_C_COMPILER clang)
set(CMAKE_ASM_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET riscv64-unknown-elf)
set(CMAKE_ASM_COMPILER_TARGET riscv64-unknown-elf)
# Build compile-only probes rather than trying to link a target executable
# using a host system library or missing startup object.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
