#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/distributed-learning/federated-job/CMakeLists.txt
#
# PURPOSE:
#   Build a native educational consumer of the Framework-owned federated
#   admission and numeric aggregation services, without copying their maths.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(UmicomBits2BankingFederatedJob LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT DEFINED UMICOM_FRAMEWORK_SOURCE OR
   NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomAiFederatedJob.cmake")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to an Umicom Framework checkout containing the native federated job module")
endif()
include("${UMICOM_FRAMEWORK_SOURCE}/cmake/UmicomAiFederatedJob.cmake")
add_executable(umicom-bits2banking-learning-job main.c)
target_link_libraries(umicom-bits2banking-learning-job PRIVATE
    Umicom::AiFederatedJob)
target_compile_features(umicom-bits2banking-learning-job PRIVATE c_std_23)
if(MSVC)
    target_compile_options(umicom-bits2banking-learning-job PRIVATE /W4)
else()
    target_compile_options(umicom-bits2banking-learning-job PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(BUILD_TESTING)
    add_test(NAME education.distributed_learning.federated_job
        COMMAND umicom-bits2banking-learning-job)
    set_tests_properties(education.distributed_learning.federated_job
        PROPERTIES PASS_REGULAR_EXPRESSION "FedAvg candidate delta: 0.029000")
endif()
