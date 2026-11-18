#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/image-tensor/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow C23 consumer of Framework RGB tensor packing and approved branding.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomImageTensor LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_file IN ITEMS include/umicom/ai/training/image_tensor.h
        src/ai/training/image_tensor.c
        cmake/UmicomApplicationBranding.cmake)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_file}")
    endif()
endforeach()
add_library(lesson_image_tensor STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_tensor.c")
target_include_directories(lesson_image_tensor PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_image_tensor PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_image_tensor PUBLIC m)
endif()
add_executable(umicom-image-tensor main.c)
target_link_libraries(umicom-image-tensor PRIVATE lesson_image_tensor)
foreach(_target IN ITEMS lesson_image_tensor umicom-image-tensor)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
umicom_apply_application_branding(TARGET umicom-image-tensor
    PRODUCT_NAME "Umicom Image Tensor Laboratory"
    INTERNAL_NAME "umicom-image-tensor" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.image-tensor COMMAND umicom-image-tensor)
set_tests_properties(lesson.training.image-tensor PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;image;tensor")

# The second consumer shares the canonical packer and has an independent
# executable so the original layout exercise remains available unchanged.
add_executable(umicom-image-standardize standardize.c)
target_link_libraries(umicom-image-standardize PRIVATE lesson_image_tensor)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-image-standardize PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-image-standardize
    PRODUCT_NAME "Umicom Image Standardization Laboratory"
    INTERNAL_NAME "umicom-image-standardize" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.image-standardization COMMAND umicom-image-standardize)
set_tests_properties(lesson.training.image-standardization PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;image;preprocessing")

# Output pixels use the same shared image library and an explicit policy exercise.
add_executable(umicom-image-quantize quantize.c)
target_link_libraries(umicom-image-quantize PRIVATE lesson_image_tensor)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-image-quantize PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-image-quantize
    PRODUCT_NAME "Umicom Image Quantization Laboratory"
    INTERNAL_NAME "umicom-image-quantize" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.image-quantization COMMAND umicom-image-quantize)
set_tests_properties(lesson.training.image-quantization PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;image;quantization")
