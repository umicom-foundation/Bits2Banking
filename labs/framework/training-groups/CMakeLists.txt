#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/training-groups/CMakeLists.txt
#
# PURPOSE:
#   Compile a narrow teaching harness from actual Framework training sources.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(TrainingGroupsLesson LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching Framework source checkout")
foreach(required include/umicom/ai/training/dataset_split.h src/ai/training/dataset_group_split.c src/ai/training/initialisation.c)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${required}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the matching checkout; missing ${required}")
    endif()
endforeach()
# A focused source exercise, not an installed SDK or a second algorithm.
add_library(group_source STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/dataset_group_split.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/initialisation.c")
target_include_directories(group_source PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
if(NOT WIN32)
    target_link_libraries(group_source PUBLIC m)
endif()
add_executable(training_groups main.c)
target_link_libraries(training_groups PRIVATE group_source)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(group_source PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(training_groups PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
add_test(NAME lessons.training_groups.contract COMMAND training_groups)
