#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/video-tensor/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow C23 consumer of Framework video tensor packing and approved branding.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomVideoTensor LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_file IN ITEMS include/umicom/ai/training/video_tensor.h
        src/ai/training/video_tensor.c
        include/umicom/ai/training/image_tensor.h
        src/ai/training/image_tensor.c
        cmake/UmicomApplicationBranding.cmake)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_file}")
    endif()
endforeach()
add_library(lesson_video_tensor STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/video_tensor.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/image_tensor.c")
target_include_directories(lesson_video_tensor PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_video_tensor PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_video_tensor PUBLIC m)
endif()
add_executable(umicom-video-tensor main.c)
target_link_libraries(umicom-video-tensor PRIVATE lesson_video_tensor)
foreach(_target IN ITEMS lesson_video_tensor umicom-video-tensor)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
umicom_apply_application_branding(TARGET umicom-video-tensor
    PRODUCT_NAME "Umicom Video Tensor Laboratory"
    INTERNAL_NAME "umicom-video-tensor" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.video-tensor COMMAND umicom-video-tensor)
set_tests_properties(lesson.training.video-tensor PROPERTIES
    TIMEOUT 30 LABELS "lesson;training;video;tensor")

# Timing is a separate policy from the existing positive index-step example.
foreach(_file IN ITEMS include/umicom/ai/training/video_timing.h src/ai/training/video_timing.c)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_file}")
        message(FATAL_ERROR "The timing example needs a matching Framework input: ${_file}")
    endif()
endforeach()
target_sources(lesson_video_tensor PRIVATE "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/video_timing.c")
add_executable(umicom-video-timing timing.c)
target_link_libraries(umicom-video-timing PRIVATE lesson_video_tensor)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-video-timing PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-video-timing
    PRODUCT_NAME "Umicom Video Timing Laboratory"
    INTERNAL_NAME "umicom-video-timing" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.video-timing COMMAND umicom-video-timing)
set_tests_properties(lesson.training.video-timing PROPERTIES TIMEOUT 30 LABELS "lesson;training;video;timing")

# Pixel output is a separate stage from frame selection and input packing.
add_executable(umicom-video-output output.c)
target_link_libraries(umicom-video-output PRIVATE lesson_video_tensor)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-video-output PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-video-output
    PRODUCT_NAME "Umicom Video Output Laboratory"
    INTERNAL_NAME "umicom-video-output" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.video-output COMMAND umicom-video-output)
set_tests_properties(lesson.training.video-output PROPERTIES TIMEOUT 30 LABELS "lesson;training;video;ownership")
