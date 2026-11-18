#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/image-resize/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow C23 consumer of bounded Framework pixel resampling and approved branding.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomImageResize LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_file IN ITEMS include/umicom/ai/training/image_resize.h
        src/ai/training/image_resize.c
        include/umicom/ai/training/image_histogram.h
        src/ai/training/image_histogram.c
        include/umicom/ai/training/image_view.h
        src/ai/training/image_view.c
        include/umicom/ai/training/image_tensor.h
        src/ai/training/image_tensor.c
        cmake/UmicomApplicationBranding.cmake)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_file}")
    endif()
endforeach()
add_library(lesson_image_resize STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_resize.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_histogram.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_view.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_tensor.c")
target_include_directories(lesson_image_resize PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_image_resize PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_image_resize PUBLIC m)
endif()
add_executable(umicom-image-resize main.c)
target_link_libraries(umicom-image-resize PRIVATE lesson_image_resize)
foreach(_target IN ITEMS lesson_image_resize umicom-image-resize)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
umicom_apply_application_branding(TARGET umicom-image-resize
    PRODUCT_NAME "Umicom Image Resize Laboratory"
    INTERNAL_NAME "umicom-image-resize" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.image-resize COMMAND umicom-image-resize)
set_tests_properties(lesson.training.image-resize PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;image;view")

# A second consumer compares policies without implementing interpolation locally.
add_executable(umicom-image-bilinear bilinear.c)
target_link_libraries(umicom-image-bilinear PRIVATE lesson_image_resize)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-image-bilinear PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-image-bilinear
    PRODUCT_NAME "Umicom Bilinear Resize Laboratory"
    INTERNAL_NAME "umicom-image-bilinear" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.image-bilinear COMMAND umicom-image-bilinear)
set_tests_properties(lesson.training.image-bilinear PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;image;view")
