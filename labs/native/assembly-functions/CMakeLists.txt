#-----------------------------------------------------------------------------
# Bits to Banking | Umicom Foundation
# File: labs/native/assembly-functions/CMakeLists.txt
# PURPOSE: Teach platform calling conventions with real C23 and Assembly.
# AUTHOR: Sammy Hegab | LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BitsToBankingAssemblyFunctions LANGUAGES C ASM)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# The source chooses the matching calling convention. Students must not run
# x86-64 machine instructions inside a RISC-V emulator or vice versa.
include(CheckCSourceCompiles)
check_c_source_compiles("#ifndef __x86_64__\n#error wrong target\n#endif\nint main(void){return 0;}"
    UMICOM_ASSEMBLY_LAB_X86_64)
check_c_source_compiles("#if !defined(__riscv) || __riscv_xlen != 64\n#error wrong target\n#endif\nint main(void){return 0;}"
    UMICOM_ASSEMBLY_LAB_RISCV64)
if(UMICOM_ASSEMBLY_LAB_X86_64 AND NOT APPLE)
    set(ASSEMBLY_SOURCE "add_x86_64.S")
elseif(UMICOM_ASSEMBLY_LAB_RISCV64)
    set(ASSEMBLY_SOURCE "add_riscv64.S")
else()
    message(FATAL_ERROR "This Assembly lab supports x86-64 Windows/Linux and RISC-V64 ELF. Read README.md for other targets.")
endif()

add_executable(bits2banking-assembly-functions main.c "${ASSEMBLY_SOURCE}")
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(bits2banking-assembly-functions PRIVATE
        $<$<COMPILE_LANGUAGE:C>:-Wall;-Wextra;-Wpedantic;-Wconversion;-Wshadow>)
endif()
if(BUILD_TESTING)
    add_test(NAME bits2banking.assembly.functions COMMAND bits2banking-assembly-functions)
    set_tests_properties(bits2banking.assembly.functions PROPERTIES
        PASS_REGULAR_EXPRESSION "C and Assembly agree")
endif()
