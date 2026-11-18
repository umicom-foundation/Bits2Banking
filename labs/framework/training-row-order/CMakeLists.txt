#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/training-row-order/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow C23 consumer of Framework row ordering and approved branding.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomTrainingRowOrder LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_file IN ITEMS include/umicom/ai/training/sample_order.h
        src/ai/training/sample_order.c src/ai/training/initialisation.c
        cmake/UmicomApplicationBranding.cmake)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_file}")
    endif()
endforeach()
add_library(lesson_row_order STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/sample_order.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/initialisation.c")
target_include_directories(lesson_row_order PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_row_order PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_row_order PUBLIC m)
endif()
add_executable(umicom-training-row-order main.c)
target_link_libraries(umicom-training-row-order PRIVATE lesson_row_order)
foreach(_target IN ITEMS lesson_row_order umicom-training-row-order)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
umicom_apply_application_branding(TARGET umicom-training-row-order
    PRODUCT_NAME "Umicom Training Row Order Laboratory"
    INTERNAL_NAME "umicom-training-row-order" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.row-order COMMAND umicom-training-row-order)
set_tests_properties(lesson.training.row-order PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;dataset;order")
