#-----------------------------------------------------------------------------
# Bits to Banking
# File: labs/native/distributed-learning/anchored-evidence/CMakeLists.txt
#
# PURPOSE:
#   Build the genuine Umicom Framework C23 evidence implementation as a
#   consumer of its canonical record-chain, Merkle and SHA-256 source files.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingAnchoredEvidence LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Existing Umicom Framework source checkout")
if(NOT UMICOM_FRAMEWORK_SOURCE OR NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/include/umicom/record_chain/merkle.h")
    message(FATAL_ERROR "Supply -DUMICOM_FRAMEWORK_SOURCE=<existing-framework-source-root>")
endif()
add_library(bits2banking-existing-framework-evidence STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/base/sha256.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/record_chain/chain.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/record_chain/merkle.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/federated_evidence_anchor.c")
target_include_directories(bits2banking-existing-framework-evidence PUBLIC
    "${UMICOM_FRAMEWORK_SOURCE}/include")
if(MSVC)
    target_compile_options(bits2banking-existing-framework-evidence PRIVATE /W4)
else()
    target_compile_options(bits2banking-existing-framework-evidence PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_executable(bits2banking-anchored-evidence main.c)
target_link_libraries(bits2banking-anchored-evidence PRIVATE
    bits2banking-existing-framework-evidence)
if(BUILD_TESTING)
    add_test(NAME education.distributed_learning.anchored_evidence
        COMMAND bits2banking-anchored-evidence)
endif()
