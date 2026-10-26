# Bits2Banking | Sammy Hegab, Umicom Foundation | MIT
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingKernelBootMetadata LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
set(UMICOM_KERNEL_SOURCE "" CACHE PATH "Umicom Kernel source checkout")
foreach(_source IN ITEMS device_tree_layout.c device_tree_reader.c boot_reservations.c address.c)
    if(NOT EXISTS "${UMICOM_KERNEL_SOURCE}/kernel/${_source}")
        message(FATAL_ERROR "Set UMICOM_KERNEL_SOURCE to a checkout containing the native boot reservation feature")
    endif()
endforeach()
add_executable(btb-kernel-boot-metadata main.c
    "${UMICOM_KERNEL_SOURCE}/kernel/device_tree_layout.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/device_tree_reader.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/boot_reservations.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/address.c")
target_include_directories(btb-kernel-boot-metadata PRIVATE "${UMICOM_KERNEL_SOURCE}/include")
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-kernel-boot-metadata PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    foreach(_case IN ITEMS plan overflow missing-end)
        add_test(NAME "bits2banking.kernel_boot_metadata.${_case}" COMMAND btb-kernel-boot-metadata "${_case}")
        set_tests_properties("bits2banking.kernel_boot_metadata.${_case}" PROPERTIES TIMEOUT 10)
    endforeach()
endif()
