#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/image-orientation/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow C23 consumer of Framework crop and orientation composition and approved branding.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomImageOrientation LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_file IN ITEMS include/umicom/ai/training/image_flip.h
        src/ai/training/image_flip.c
        include/umicom/ai/training/image_view.h
        src/ai/training/image_view.c
        include/umicom/ai/training/image_tensor.h
        src/ai/training/image_tensor.c
        cmake/UmicomApplicationBranding.cmake)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_file}")
    endif()
endforeach()
add_library(lesson_image_orientation STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_flip.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_view.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_tensor.c")
target_include_directories(lesson_image_orientation PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_image_orientation PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_image_orientation PUBLIC m)
endif()
add_executable(umicom-image-orientation main.c)
target_link_libraries(umicom-image-orientation PRIVATE lesson_image_orientation)
foreach(_target IN ITEMS lesson_image_orientation umicom-image-orientation)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
umicom_apply_application_branding(TARGET umicom-image-orientation
    PRODUCT_NAME "Umicom Image Orientation Laboratory"
    INTERNAL_NAME "umicom-image-orientation" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.image-orientation COMMAND umicom-image-orientation)
set_tests_properties(lesson.training.image-orientation PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;image;view")
