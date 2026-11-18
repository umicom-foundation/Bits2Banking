#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/reflection-snapshot/CMakeLists.txt
#
# PURPOSE:
#   Build a native snapshot-ownership exercise with installed SDK or explicit source owner.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomReflectionSnapshotLesson LANGUAGES C)
include(CTest)
if(WIN32)
    enable_language(RC)
endif()
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Optional explicit Framework source for focused teaching checks")
if(UMICOM_FRAMEWORK_SOURCE)
    # This opt-in path checks the source owner only; it is not installed SDK qualification.
    find_package(Threads REQUIRED)
    add_library(lesson_reflection_owner STATIC
        "${UMICOM_FRAMEWORK_SOURCE}/src/reflection/types.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/reflection/registry.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/platform/threading.c")
    target_include_directories(lesson_reflection_owner PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
    target_compile_features(lesson_reflection_owner PUBLIC c_std_23)
    target_link_libraries(lesson_reflection_owner PUBLIC Threads::Threads)
    set(lesson_owner lesson_reflection_owner)
    include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
    set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
else()
    find_package(UmicomFramework CONFIG REQUIRED COMPONENTS reflection)
    set(lesson_owner Umicom::reflection)
endif()
add_executable(umicom-reflection-snapshot main.c)
target_compile_features(umicom-reflection-snapshot PRIVATE c_std_23)
target_link_libraries(umicom-reflection-snapshot PRIVATE ${lesson_owner})
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-reflection-snapshot PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-reflection-snapshot
    PRODUCT_NAME "Umicom Reflection Ownership Laboratory"
    INTERNAL_NAME "umicom-reflection-snapshot" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.reflection.snapshot-ownership COMMAND umicom-reflection-snapshot)
set_tests_properties(lesson.reflection.snapshot-ownership PROPERTIES TIMEOUT 20 LABELS "lesson;reflection;ownership")

# The metadata exercise shares the same SDK/source owner and canonical brand.
add_executable(umicom-reflection-media-labels media_labels.c)
target_compile_features(umicom-reflection-media-labels PRIVATE c_std_23)
target_link_libraries(umicom-reflection-media-labels PRIVATE ${lesson_owner})
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-reflection-media-labels PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-reflection-media-labels
    PRODUCT_NAME "Umicom Resource Metadata Laboratory"
    INTERNAL_NAME "umicom-reflection-media-labels" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.reflection.resource-labels COMMAND umicom-reflection-media-labels)
set_tests_properties(lesson.reflection.resource-labels PROPERTIES TIMEOUT 20 LABELS "lesson;reflection;metadata")
