#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/physical-frame-runs/CMakeLists.txt
#
# PURPOSE:
#   Build aligned frame examples against Kernel source and attach canonical Framework brand resources.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(UmicomPhysicalFrameLab LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_KERNEL_SOURCE "" CACHE PATH "Path to the Umicom Kernel source checkout")
if(NOT EXISTS "${UMICOM_KERNEL_SOURCE}/kernel/physical_memory.c")
    message(FATAL_ERROR "Set UMICOM_KERNEL_SOURCE to the Kernel checkout containing kernel/physical_memory.c")
endif()
add_executable(physical-frame-runs main.c
    "${UMICOM_KERNEL_SOURCE}/kernel/physical_memory.c"
    "${UMICOM_KERNEL_SOURCE}/kernel/address.c")
target_include_directories(physical-frame-runs PRIVATE "${UMICOM_KERNEL_SOURCE}/include")
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(physical-frame-runs PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()

# Only this hosted executable receives Windows resources and staged artwork.
# The production freestanding allocator acquires no Framework or GTK dependency.
get_filename_component(_framework_default
    "${CMAKE_CURRENT_LIST_DIR}/../../../../Umicom-Applications/framework" ABSOLUTE)
set(UMICOM_FRAMEWORK_SOURCE "${_framework_default}" CACHE PATH "Framework source supplying canonical branding")
if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a Framework checkout with UmicomApplicationBranding.cmake")
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET physical-frame-runs
    PRODUCT_NAME "Umicom Kernel Physical Frames Learning Lab"
    INTERNAL_NAME "physical-frame-runs" NO_RUNTIME_DEPLOYMENT)
include(CTest)
if(BUILD_TESTING)
    foreach(_case IN ITEMS alignment fragmentation release coexist)
        add_test(NAME learning.kernel.frame-runs.${_case}
            COMMAND physical-frame-runs "${_case}")
        set_tests_properties(learning.kernel.frame-runs.${_case} PROPERTIES
            TIMEOUT 10 LABELS "education;kernel;host;no-devices")
    endforeach()
endif()
