#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-preview-revisions/CMakeLists.txt
#
# PURPOSE:
#   Teach revision-aware preview bookkeeping through a small Framework consumer.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingPreviewRevisions LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Optional Framework source for focused service study")
add_executable(btb-preview-revisions main.c)
if(UMICOM_FRAMEWORK_SOURCE)
    # Deliberate source-study mode compiles only the same production service.
    # It does not claim to exercise an installed SDK package or its deployment.
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/include/umicom/frontend/hot_reload.h")
        message(FATAL_ERROR "UMICOM_FRAMEWORK_SOURCE must name the Framework checkout")
    endif()
    target_sources(btb-preview-revisions PRIVATE
        "${UMICOM_FRAMEWORK_SOURCE}/src/frontend/hot_reload.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/frontend/dev_types.c")
    target_include_directories(btb-preview-revisions PRIVATE "${UMICOM_FRAMEWORK_SOURCE}/include")
else()
    find_package(UmicomFramework CONFIG REQUIRED COMPONENTS frontend)
    target_link_libraries(btb-preview-revisions PRIVATE Umicom::frontend)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-preview-revisions PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
enable_testing()
add_test(NAME btb.preview_revisions.walkthrough COMMAND btb-preview-revisions)
set_tests_properties(btb.preview_revisions.walkthrough PROPERTIES
    PASS_REGULAR_EXPRESSION "Applied generation 3: acknowledged=2 pending=0"
    TIMEOUT 15)
