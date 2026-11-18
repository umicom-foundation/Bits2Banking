#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/denoising-objective/CMakeLists.txt
# 
# PURPOSE:
#   Build the small CPU denoising lesson from existing Framework source without an application build.
# 
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
# 
# LICENCE:
# MIT
#-----------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.25)
project(UmicomDenoisingObjective LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Existing primary Framework source checkout for this teaching lab")
if(NOT UMICOM_FRAMEWORK_SOURCE)
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to your existing Umicom-Applications/framework checkout.")
endif()
# Reuse the Framework algorithms. This small source exercise does not validate
# installation or exported SDK dependencies and downloads no third-party code.
add_library(lesson_framework_training STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/tape.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/matrix_kernel.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/denoising.c")
target_include_directories(lesson_framework_training PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(lesson_framework_training PUBLIC c_std_23)
if(NOT WIN32)
    target_link_libraries(lesson_framework_training PUBLIC m)
endif()
add_executable(umicom-denoising-objective main.c)
target_link_libraries(umicom-denoising-objective PRIVATE lesson_framework_training)
target_compile_features(umicom-denoising-objective PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-denoising-objective PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_test(NAME lesson.denoising.objective COMMAND umicom-denoising-objective)
set_tests_properties(lesson.denoising.objective PROPERTIES TIMEOUT 30 LABELS "lesson;ai;training")

# Sampling remains Framework-owned. This second executable measures its output
# without changing the original fixed-noise overfitting experiment.
target_sources(lesson_framework_training PRIVATE
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/initialisation.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/normal_noise.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/security/secrets.c")
add_executable(umicom-noise-statistics noise_statistics.c)
target_link_libraries(umicom-noise-statistics PRIVATE lesson_framework_training)
target_compile_features(umicom-noise-statistics PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-noise-statistics PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_test(NAME lesson.denoising.noise-statistics COMMAND umicom-noise-statistics)
set_tests_properties(lesson.denoising.noise-statistics PROPERTIES TIMEOUT 30 LABELS "lesson;ai;training;random")

# The coefficient example calls the shared numerical owner; it adds no trainer.
target_sources(lesson_framework_training PRIVATE "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/noise_schedule.c")
add_executable(umicom-noise-schedule noise_schedule.c)
target_link_libraries(umicom-noise-schedule PRIVATE lesson_framework_training)
target_compile_features(umicom-noise-schedule PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-noise-schedule PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_test(NAME lesson.denoising.noise-schedule COMMAND umicom-noise-schedule)
set_tests_properties(lesson.denoising.noise-schedule PROPERTIES TIMEOUT 30 LABELS "lesson;ai;training;denoising")

# Epsilon guidance reuses the numerical owner already linked above.
add_executable(umicom-noise-guidance guidance.c)
target_link_libraries(umicom-noise-guidance PRIVATE lesson_framework_training)
target_compile_features(umicom-noise-guidance PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-noise-guidance PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_test(NAME lesson.denoising.guidance COMMAND umicom-noise-guidance)
set_tests_properties(lesson.denoising.guidance PROPERTIES TIMEOUT 30 LABELS "lesson;ai;denoising;guidance")

# Keep model-free trajectory arithmetic in the existing shared source library.
add_executable(umicom-denoising-trajectory trajectory.c)
target_link_libraries(umicom-denoising-trajectory PRIVATE lesson_framework_training)
target_compile_features(umicom-denoising-trajectory PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-denoising-trajectory PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_test(NAME lesson.denoising.trajectory COMMAND umicom-denoising-trajectory)
set_tests_properties(lesson.denoising.trajectory PROPERTIES TIMEOUT 30 LABELS "lesson;ai;denoising;sampler")

# Prediction convention conversion requires no model runtime.
add_executable(umicom-denoising-velocity velocity.c)
target_link_libraries(umicom-denoising-velocity PRIVATE lesson_framework_training)
target_compile_features(umicom-denoising-velocity PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-denoising-velocity PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_test(NAME lesson.denoising.velocity COMMAND umicom-denoising-velocity)
set_tests_properties(lesson.denoising.velocity PROPERTIES TIMEOUT 30 LABELS "lesson;ai;denoising;prediction")

add_executable(umicom-padded-frame-loss padded_frames.c)
target_link_libraries(umicom-padded-frame-loss PRIVATE lesson_framework_training)
target_compile_features(umicom-padded-frame-loss PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-padded-frame-loss PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
# Native identity is supplied by Framework masters, with no runtime deployment.
if(WIN32)
    enable_language(RC)
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomApplicationBranding.cmake")
set(UMICOM_FRAMEWORK_RESOURCE_ROOT "${UMICOM_FRAMEWORK_SOURCE}/resources")
umicom_apply_application_branding(TARGET umicom-padded-frame-loss
    PRODUCT_NAME "Umicom Padded Frame Loss Laboratory"
    INTERNAL_NAME "umicom-padded-frame-loss" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.denoising.padded-frame-loss COMMAND umicom-padded-frame-loss)
set_tests_properties(lesson.denoising.padded-frame-loss PROPERTIES TIMEOUT 30 LABELS "lesson;ai;training;loss")

# Continuous objective weights are owned by the canonical tape, not the app.
add_executable(umicom-weighted-pixel-loss weighted_pixels.c)
target_link_libraries(umicom-weighted-pixel-loss PRIVATE lesson_framework_training)
target_compile_features(umicom-weighted-pixel-loss PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-weighted-pixel-loss PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-weighted-pixel-loss
    PRODUCT_NAME "Umicom Weighted Objective Laboratory"
    INTERNAL_NAME "umicom-weighted-pixel-loss" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.denoising.weighted-pixel-loss COMMAND umicom-weighted-pixel-loss)
set_tests_properties(lesson.denoising.weighted-pixel-loss PROPERTIES TIMEOUT 30 LABELS "lesson;ai;training;weights")

# Replay and step noise remain application-owned; arithmetic remains Framework-owned.
add_executable(umicom-stochastic-step stochastic_step.c)
target_link_libraries(umicom-stochastic-step PRIVATE lesson_framework_training)
target_compile_features(umicom-stochastic-step PRIVATE c_std_23)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(umicom-stochastic-step PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
umicom_apply_application_branding(TARGET umicom-stochastic-step
    PRODUCT_NAME "Umicom Stochastic Denoising Laboratory"
    INTERNAL_NAME "umicom-stochastic-step" NO_RUNTIME_DEPLOYMENT)
add_test(NAME lesson.denoising.stochastic-step COMMAND umicom-stochastic-step)
set_tests_properties(lesson.denoising.stochastic-step PROPERTIES TIMEOUT 30 LABELS "lesson;ai;denoising;sampler")
