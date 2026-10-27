#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/distributed-learning/fedavg-round/CMakeLists.txt
#
# PURPOSE:
#   Compile an educational C23 consumer of the canonical Framework
#   federated-round component.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(UmicomBits2BankingFederatedRound LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT DEFINED UMICOM_FRAMEWORK_SOURCE OR NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomAiFederatedRound.cmake")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to the checked-out Umicom Framework source root")
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomAiFederatedRound.cmake")
add_executable(umicom-bits2banking-fedavg main.c)
target_link_libraries(umicom-bits2banking-fedavg PRIVATE Umicom::AiFederatedRound)
if(BUILD_TESTING)
    add_test(NAME education.distributed_learning.fedavg
        COMMAND umicom-bits2banking-fedavg)
    set_tests_properties(education.distributed_learning.fedavg PROPERTIES
        PASS_REGULAR_EXPRESSION "Synthetic model weight:")
endif()
