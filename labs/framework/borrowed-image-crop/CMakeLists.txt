#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/borrowed-image-crop/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow C23 consumer of Framework borrowed image crop composition and approved branding.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomBorrowedImageCrop LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_file IN ITEMS include/umicom/ai/training/image_view.h
        src/ai/training/image_view.c
        include/umicom/ai/training/image_tensor.h
        src/ai/training/image_tensor.c
        cmake/UmicomApplicationBranding.cmake)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_file}")
    endif()
endforeach()
add_library(lesson_image_view STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_view.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_tensor.c")
target_include_directories(lesson_image_view PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_image_view PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_image_view PUBLIC m)
endif()
add_executable(umicom-borrowed-image-crop main.c)
target_link_libraries(umicom-borrowed-image-crop PRIVATE lesson_image_view)
foreach(_target IN ITEMS lesson_image_view umicom-borrowed-image-crop)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
umicom_apply_application_branding(TARGET umicom-borrowed-image-crop
    PRODUCT_NAME "Umicom Borrowed Image Crop Laboratory"
    INTERNAL_NAME "umicom-borrowed-image-crop" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.borrowed-image-crop COMMAND umicom-borrowed-image-crop)
set_tests_properties(lesson.training.borrowed-image-crop PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;image;view")
