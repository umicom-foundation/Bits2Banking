#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/image-histogram/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow C23 consumer of bounded Framework image frequencies and approved branding.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomImageHistogram LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_file IN ITEMS include/umicom/ai/training/image_histogram.h
        src/ai/training/image_histogram.c
        include/umicom/ai/training/image_moments.h
        src/ai/training/image_moments.c
        include/umicom/ai/training/image_view.h
        src/ai/training/image_view.c
        include/umicom/ai/training/image_tensor.h
        src/ai/training/image_tensor.c
        cmake/UmicomApplicationBranding.cmake)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_file}")
    endif()
endforeach()
add_library(lesson_image_histogram STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_histogram.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_moments.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_view.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_tensor.c")
target_include_directories(lesson_image_histogram PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_image_histogram PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_image_histogram PUBLIC m)
endif()
add_executable(umicom-image-histogram main.c)
target_link_libraries(umicom-image-histogram PRIVATE lesson_image_histogram)
foreach(_target IN ITEMS lesson_image_histogram umicom-image-histogram)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
umicom_apply_application_branding(TARGET umicom-image-histogram
    PRODUCT_NAME "Umicom Image Histogram Laboratory"
    INTERNAL_NAME "umicom-image-histogram" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.image-histogram COMMAND umicom-image-histogram)
set_tests_properties(lesson.training.image-histogram PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;image;view")


add_executable(umicom-image-moments moments.c)
target_link_libraries(umicom-image-moments PRIVATE lesson_image_histogram)
target_compile_features(umicom-image-moments PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-image-moments PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-image-moments
    PRODUCT_NAME "Umicom Image Statistics Laboratory"
    INTERNAL_NAME "umicom-image-moments" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.image-moments COMMAND umicom-image-moments)
set_tests_properties(lesson.training.image-moments PROPERTIES TIMEOUT 30 LABELS "lesson;training;image;statistics")
