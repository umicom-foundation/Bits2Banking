# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-ai-contracts/CMakeLists.txt
#
# PURPOSE:
#   Build a small consumer against the canonical Framework AI source files.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BtbFrameworkAiContracts LANGUAGES C)
include(CTest)
set(UMICOM_FRAMEWORK_SOURCE "" CACHE PATH "Path to the Umicom Framework source checkout")
if(NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/byte_tokenizer.c" OR
   NOT EXISTS "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/gradient_clipping.c")
    message(FATAL_ERROR "Set UMICOM_FRAMEWORK_SOURCE to a complete Umicom Framework checkout")
endif()
# This focused teaching target compiles the original Framework implementation.
# Keeping the source paths external avoids a copied or divergent tokenizer.
add_library(btb-framework-ai-contracts STATIC
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/byte_tokenizer.c"
    "${UMICOM_FRAMEWORK_SOURCE}/src/ai/training/gradient_clipping.c")
target_include_directories(btb-framework-ai-contracts PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
if(NOT WIN32)
    target_link_libraries(btb-framework-ai-contracts PUBLIC m)
endif()
add_executable(btb-ai-contracts main.c)
target_link_libraries(btb-ai-contracts PRIVATE btb-framework-ai-contracts)
set(_targets btb-framework-ai-contracts btb-ai-contracts)
if(BUILD_TESTING)
    add_executable(btb-ai-contract-tests test_contracts.c)
    target_link_libraries(btb-ai-contract-tests PRIVATE btb-framework-ai-contracts)
    list(APPEND _targets btb-ai-contract-tests)
    foreach(_case IN ITEMS bytes empty encode-capacity decode-capacity reserved invalid-id norm zero split nonfinite)
        add_test(NAME bits2banking.framework_ai_contracts.${_case}
            COMMAND btb-ai-contract-tests ${_case})
        set_tests_properties(bits2banking.framework_ai_contracts.${_case} PROPERTIES TIMEOUT 10)
    endforeach()
endif()
foreach(_target IN LISTS _targets)
    set_target_properties(${_target} PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    elseif(MSVC)
        target_compile_options(${_target} PRIVATE /W4)
    endif()
endforeach()
