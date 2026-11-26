#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/labs/native/riscv-inactive-domain/CMakeLists.txt
#
# PURPOSE:
#   Link the hosted lesson to the real Kernel reservation and table owners.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(UmicomBitsInactiveDomain LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_KERNEL_SOURCE "" CACHE PATH "Reviewed sibling Umicom Kernel checkout with inactive domain protection")

# Reuse the production table and allocator implementation in this small
# hosted composition. This target does not contain firmware entry points.
if(NOT EXISTS "${UMICOM_KERNEL_SOURCE}/kernel/riscv_domain_address_space.c" OR
   NOT EXISTS "${UMICOM_KERNEL_SOURCE}/kernel/virtual_memory_protection.h")
    message(FATAL_ERROR "Set UMICOM_KERNEL_SOURCE to a checkout with the inactive domain protections")
endif()
add_executable(btb-inactive-domain private_pages.c
    "${UMICOM_KERNEL_SOURCE}/kernel/address.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/physical_memory.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/virtual_memory.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/riscv_domain_memory.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/riscv_domain_address_space.c")
target_include_directories(btb-inactive-domain PRIVATE "${UMICOM_KERNEL_SOURCE}/include")
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-inactive-domain PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()

# Each case owns its own process address space and emulated RAM.
if(BUILD_TESTING)
    foreach(example IN ITEMS change-private late-mismatch)
        add_test(NAME "btb.education.inactive_domain.${example}" COMMAND btb-inactive-domain "${example}")
    endforeach()
endif()
