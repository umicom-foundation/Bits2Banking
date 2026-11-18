#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/host-cache-budget/CMakeLists.txt
#
# PURPOSE:
#   Build a source-linked host/cache arithmetic exercise without loading a model.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomHostCacheBudgetLesson LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Existing primary Framework source checkout")
if(NOT UMICOM_FRAMEWORK_SOURCE)
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the matching Framework checkout.")
endif()
# Source-linked numerical/value exercise; no installed SDK or application build.
add_library(lesson_cache_owner STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/local_models/memory_plan.c")
target_include_directories(lesson_cache_owner PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_cache_owner PUBLIC c_std_23)
add_executable(umicom-host-cache-budget main.c)
target_link_libraries(umicom-host-cache-budget PRIVATE lesson_cache_owner)
target_compile_features(umicom-host-cache-budget PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lesson_cache_owner PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(umicom-host-cache-budget PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
if(NOT WIN32)
    target_link_libraries(lesson_cache_owner PUBLIC m)
endif()
add_test(NAME lesson.memory.host-cache-budget COMMAND umicom-host-cache-budget)
set_tests_properties(lesson.memory.host-cache-budget PROPERTIES TIMEOUT 20 LABELS "lesson;memory;observability")
