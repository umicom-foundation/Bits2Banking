#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-retrieval-ownership/CMakeLists.txt
#
# PURPOSE:
#   Build an installed-SDK client for retrieval storage and finite score publication.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingRetrievalOwnership LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS ai)
include(CTest)
add_executable(btb-framework-retrieval-ownership main.c)
target_link_libraries(btb-framework-retrieval-ownership PRIVATE Umicom::ai)
set_target_properties(btb-framework-retrieval-ownership PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-framework-retrieval-ownership PRIVATE /W4)
else()
    target_compile_options(btb-framework-retrieval-ownership PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-framework-retrieval-ownership
    PRODUCT_NAME "Umicom Retrieval Ownership Learning Lab"
    INTERNAL_NAME btb-framework-retrieval-ownership NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(scenario chunk geometry lexical store top hybrid rerank)
        add_test(NAME bits2banking.retrieval-ownership.${scenario}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-framework-retrieval-ownership>"
                "-DSCENARIO=${scenario}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.retrieval-ownership.${scenario} PROPERTIES
            TIMEOUT 10 LABELS "education;framework;ai;retrieval")
    endforeach()
endif()
