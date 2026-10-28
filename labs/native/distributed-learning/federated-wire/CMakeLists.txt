#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/native/distributed-learning/federated-wire/CMakeLists.txt
#
# PURPOSE:
#   Compile an educational native C23 consumer of the canonical Umicom
#   Framework federated wire and job services, without duplicating maths.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingFederatedWireLab LANGUAGES C)
include(CTest)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
if(NOT DEFINED UMICOM_FRAMEWORK_SOURCE OR
   NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomAiFederatedWire.cmake")
    message(FATAL_ERROR
        "Provide -DUMICOM_FRAMEWORK_SOURCE=<checkout of Umicom Framework>")
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomAiFederatedWire.cmake")
add_executable(bits2banking-federated-wire-lab main.c)
target_link_libraries(bits2banking-federated-wire-lab PRIVATE
    Umicom::AiFederatedWire)
target_compile_features(bits2banking-federated-wire-lab PRIVATE c_std_23)
if(MSVC)
    target_compile_options(bits2banking-federated-wire-lab PRIVATE /W4)
else()
    target_compile_options(bits2banking-federated-wire-lab PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(BUILD_TESTING)
    add_test(NAME bits2banking.native.federated_wire
        COMMAND bits2banking-federated-wire-lab)
endif()
