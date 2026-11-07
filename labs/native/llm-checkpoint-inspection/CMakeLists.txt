#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/llm-checkpoint-inspection/CMakeLists.txt
#
# PURPOSE:
#   Build an inspection laboratory from the canonical Framework training module.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(CheckpointInspection LANGUAGES C)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Framework source checkout")
if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomNativeLlmTraining.cmake")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to an Umicom Framework checkout.")
endif()
# Reuse Framework's composition module and sources; do not copy neural logic.
option(BUILD_TESTING "Build Framework regression tests" OFF)
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomNativeLlmTraining.cmake")
add_executable(checkpoint-inspection main.c)
target_compile_features(checkpoint-inspection PRIVATE c_std_23)
target_link_libraries(checkpoint-inspection PRIVATE Umicom::AiTraining)
