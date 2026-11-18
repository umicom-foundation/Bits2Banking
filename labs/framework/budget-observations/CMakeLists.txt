#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/budget-observations/CMakeLists.txt
#
# PURPOSE:
#   Build a small source-linked observation lesson against canonical Framework code.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomBudgetObservationLesson LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Existing primary Framework source checkout")
if(NOT UMICOM_FRAMEWORK_SOURCE)
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the matching Framework checkout.")
endif()
# Source-linked numerical/value exercise; no installed SDK or application build.
add_library(lesson_budget_owner STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/observability/performance/memory_budget.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/observability/performance/types.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/base/value_archive.c")
target_include_directories(lesson_budget_owner PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_budget_owner PUBLIC c_std_23)
add_executable(umicom-budget-observations main.c)
target_link_libraries(umicom-budget-observations PRIVATE lesson_budget_owner)
target_compile_features(umicom-budget-observations PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lesson_budget_owner PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(umicom-budget-observations PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
if(NOT WIN32)
    target_link_libraries(lesson_budget_owner PUBLIC m)
endif()
add_test(NAME lesson.memory.budget-observations COMMAND umicom-budget-observations)
set_tests_properties(lesson.memory.budget-observations PROPERTIES TIMEOUT 20 LABELS "lesson;memory;observability")
