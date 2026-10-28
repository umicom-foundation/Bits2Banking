#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/distributed-learning/federated-audit/CMakeLists.txt
#
# PURPOSE:
#   Build the public C23 learning application against the original Framework
#   record-chain and the opt-in federated audit adapter, without another hash.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingFederatedAudit LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT DEFINED UMICOM_FRAMEWORK_SOURCE OR
   NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/learning/native-ai-federated-audit/CMakeLists.txt")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the existing Framework root")
endif()
add_subdirectory("${UMICOM_FRAMEWORK_SOURCE}/learning/native-ai-federated-audit"
                 "${CMAKE_BINARY_DIR}/framework-audit")
add_executable(bits2banking-federated-audit main.c)
target_link_libraries(bits2banking-federated-audit PRIVATE Umicom::AiFederatedAuditChain)
if(NOT MSVC)
    target_compile_options(bits2banking-federated-audit PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(BUILD_TESTING)
    add_test(NAME bits2banking.native.federated_audit
             COMMAND bits2banking-federated-audit)
endif()
