#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/prediction-metrics/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow C23 consumer of Framework prediction scoring and approved branding.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomPredictionMetrics LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_file IN ITEMS include/umicom/ai/training/prediction_metrics.h
        src/ai/training/prediction_metrics.c
        src/ai/training/categorical_loss.h
        src/ai/training/prediction_summary.inc
        cmake/UmicomApplicationBranding.cmake)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_file}")
    endif()
endforeach()
add_library(lesson_prediction_metrics STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/prediction_metrics.c")
target_include_directories(lesson_prediction_metrics PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_prediction_metrics PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_prediction_metrics PUBLIC m)
endif()
add_executable(umicom-prediction-metrics main.c)
target_link_libraries(umicom-prediction-metrics PRIVATE lesson_prediction_metrics)
foreach(_target IN ITEMS lesson_prediction_metrics umicom-prediction-metrics)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
umicom_apply_application_branding(TARGET umicom-prediction-metrics
    PRODUCT_NAME "Umicom Training Prediction Metrics Laboratory"
    INTERNAL_NAME "umicom-prediction-metrics" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.prediction-metrics COMMAND umicom-prediction-metrics)
set_tests_properties(lesson.training.prediction-metrics PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;evaluation;metrics")

# Evaluation sums retain the denominator; no gradient tape is allocated here.
add_executable(umicom-prediction-loss loss.c)
target_link_libraries(umicom-prediction-loss PRIVATE lesson_prediction_metrics)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-prediction-loss PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-prediction-loss
    PRODUCT_NAME "Umicom Token Loss Laboratory"
    INTERNAL_NAME "umicom-prediction-loss" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.prediction-loss COMMAND umicom-prediction-loss)
set_tests_properties(lesson.training.prediction-loss PROPERTIES TIMEOUT 30 LABELS "lesson;training;evaluation;loss")

# Keep batch statistics in shared native reporting, with approved resources.
add_executable(umicom-prediction-aggregate aggregate.c)
target_link_libraries(umicom-prediction-aggregate PRIVATE lesson_prediction_metrics)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-prediction-aggregate PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-prediction-aggregate
    PRODUCT_NAME "Umicom Checked Evaluation Laboratory"
    INTERNAL_NAME "umicom-prediction-aggregate" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.prediction-aggregate COMMAND umicom-prediction-aggregate)
set_tests_properties(lesson.training.prediction-aggregate PROPERTIES TIMEOUT 30 LABELS "lesson;training;evaluation;aggregation")
