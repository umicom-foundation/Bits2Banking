#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/masked-language-loss/CMakeLists.txt
#
# PURPOSE:
#   Build a narrow learning consumer of the shared native training-tape source.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(UmicomMaskedLanguageLoss LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Matching existing Framework source checkout")
foreach(_required include/umicom/ai/training/tape.h src/ai/training/tape.c src/ai/training/matrix_kernel.c)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/${_required}")
        message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a matching checkout: missing ${_required}")
    endif()
endforeach()
add_library(lesson_training_tape STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/tape.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/matrix_kernel.c")
target_include_directories(lesson_training_tape PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_training_tape PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_training_tape PUBLIC m)
endif()
add_executable(umicom-masked-language-loss main.c)
target_link_libraries(umicom-masked-language-loss PRIVATE lesson_training_tape)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lesson_training_tape PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(umicom-masked-language-loss PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
add_test(NAME lesson.training.masked-loss COMMAND umicom-masked-language-loss)
set_tests_properties(lesson.training.masked-loss PROPERTIES TIMEOUT 30 LABELS "lesson;training;loss")

# The decoder remains Framework-owned. This teaching composition reuses its
# production sources and the tape library above; it is not an SDK installation.
add_library(lesson_training_decoder STATIC)
foreach(_source IN ITEMS initialisation transformer decoder optimizer gradient_clipping checkpoint optimizer_checkpoint capacity_plan)
    if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/${_source}.c")
        message(FATAL_ERROR "Matching decoder source is missing: ${_source}.c")
    endif()
    target_sources(lesson_training_decoder PRIVATE "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/${_source}.c")
endforeach()
target_link_libraries(lesson_training_decoder PUBLIC lesson_training_tape)
add_executable(umicom-masked-decoder decoder.c)
target_link_libraries(umicom-masked-decoder PRIVATE lesson_training_decoder)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(lesson_training_decoder PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(umicom-masked-decoder PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
add_test(NAME lesson.training.masked-decoder COMMAND umicom-masked-decoder)
set_tests_properties(lesson.training.masked-decoder PROPERTIES TIMEOUT 60 LABELS "lesson;training;decoder")

# Attention and objective selection share the same canonical tape implementation.
add_executable(umicom-padding-attention attention.c)
target_link_libraries(umicom-padding-attention PRIVATE lesson_training_tape)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-padding-attention PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(WIN32)
    enable_language(RC)
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
umicom_apply_application_branding(TARGET umicom-padding-attention
    PRODUCT_NAME "Umicom Attention Mask Laboratory"
    INTERNAL_NAME "umicom-padding-attention" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.padding-attention COMMAND umicom-padding-attention)
set_tests_properties(lesson.training.padding-attention PROPERTIES TIMEOUT 30 LABELS "lesson;training;attention")

add_executable(umicom-padded-decoder padded_decoder.c)
target_link_libraries(umicom-padded-decoder PRIVATE lesson_training_decoder)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-padded-decoder PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-padded-decoder
    PRODUCT_NAME "Umicom Padded Decoder Laboratory"
    INTERNAL_NAME "umicom-padded-decoder" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.padded-decoder COMMAND umicom-padded-decoder)
set_tests_properties(lesson.training.padded-decoder PROPERTIES TIMEOUT 60 LABELS "lesson;training;decoder;padding")

# This consumer exercises the real optimizer and portable state codec.
add_executable(umicom-selected-adamw adamw_decoder.c)
target_link_libraries(umicom-selected-adamw PRIVATE lesson_training_decoder)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-selected-adamw PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-selected-adamw
    PRODUCT_NAME "Umicom Selected AdamW Laboratory"
    INTERNAL_NAME "umicom-selected-adamw" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.selected-adamw COMMAND umicom-selected-adamw)
set_tests_properties(lesson.training.selected-adamw PROPERTIES
    TIMEOUT 60 LABELS "lesson;training;adamw;checkpoint")

# A small consumer measures graph peaks without duplicating the reducer.
add_executable(umicom-selected-microbatches microbatches.c)
target_link_libraries(umicom-selected-microbatches PRIVATE lesson_training_decoder)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-selected-microbatches PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-selected-microbatches
    PRODUCT_NAME "Umicom Selected Microbatch Laboratory"
    INTERNAL_NAME "umicom-selected-microbatches" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.selected-microbatches COMMAND umicom-selected-microbatches)
set_tests_properties(lesson.training.selected-microbatches PROPERTIES
    TIMEOUT 60 LABELS "lesson;training;adamw;accumulation")

# The learning consumer uses the same byte semantics and sequence preparation as the SDK.
target_sources(lesson_training_decoder PRIVATE
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/byte_tokenizer.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/byte_pair_sequence.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/byte_pair_shape.c")
add_executable(umicom-byte-pair-training byte_pair.c)
target_link_libraries(umicom-byte-pair-training PRIVATE lesson_training_decoder)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-byte-pair-training PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-byte-pair-training
    PRODUCT_NAME "Umicom Byte Pair Training Laboratory"
    INTERNAL_NAME "umicom-byte-pair-training" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.training.byte-pair COMMAND umicom-byte-pair-training)
set_tests_properties(lesson.training.byte-pair PROPERTIES
    TIMEOUT 60 LABELS "lesson;training;tokenizer;decoder;selection")
