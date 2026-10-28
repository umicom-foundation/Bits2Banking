#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/distributed-learning/federated-auth/CMakeLists.txt
#
# PURPOSE:
#   Compile a C23 learner that consumes the existing Umicom Framework public
#   authenticated-federated wire target, without a local crypto implementation.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingFederatedAuth LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
include(CTest)
if(NOT DEFINED UMICOM_FRAMEWORK_SOURCE OR NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomAiFederatedAuthenticatedFrame.cmake")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the existing Umicom Framework root")
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomAiFederatedAuthenticatedFrame.cmake")
add_executable(bits2banking-federated-auth main.c)
target_link_libraries(bits2banking-federated-auth PRIVATE Umicom::AiFederatedAuthenticatedFrame)
if(NOT MSVC)
    target_compile_options(bits2banking-federated-auth PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(BUILD_TESTING)
    add_test(NAME bits2banking.native.federated_auth COMMAND bits2banking-federated-auth)
endif()
