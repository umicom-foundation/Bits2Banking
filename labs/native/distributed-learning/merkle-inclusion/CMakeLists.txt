#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/distributed-learning/merkle-inclusion/CMakeLists.txt
#
# PURPOSE:
#   Build a native C23 Merkle lesson using shared Framework implementations.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(UmicomBits2BankingMerkle LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Location of shared Umicom Framework sources")
if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/src/record_chain/merkle.c")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the reviewed Framework checkout")
endif()
add_library(umicom-merkle-lesson STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/record_chain/merkle.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/base/sha256.c")
target_include_directories(umicom-merkle-lesson PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
target_compile_features(umicom-merkle-lesson PUBLIC c_std_23)
if(MSVC)
  target_compile_options(umicom-merkle-lesson PRIVATE /W4)
else()
  target_compile_options(umicom-merkle-lesson PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
add_executable(umicom-bits2banking-merkle main.c)
target_link_libraries(umicom-bits2banking-merkle PRIVATE umicom-merkle-lesson)
if(BUILD_TESTING)
    add_test(NAME bits2banking.blockchain.merkle_membership
             COMMAND umicom-bits2banking-merkle)
endif()
