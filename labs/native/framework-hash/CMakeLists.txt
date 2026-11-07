#-----------------------------------------------------------------------------
# Bits to Banking
# File: labs/native/framework-hash/CMakeLists.txt
#
# PURPOSE:
#   Teach an installed Framework consumer with independently selectable contracts.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(BtbFrameworkHash LANGUAGES C)
include(CTest)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS base)
add_executable(btb-framework-hash main.c)
target_link_libraries(btb-framework-hash PRIVATE Umicom::base)
set_target_properties(btb-framework-hash PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-framework-hash PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
elseif(MSVC)
    target_compile_options(btb-framework-hash PRIVATE /W4)
endif()
if(BUILD_TESTING)
    foreach(scenario IN ITEMS known chunks changed rejected chain)
        add_test(NAME bits2banking.framework_hash.${scenario}
            COMMAND btb-framework-hash ${scenario})
        set_tests_properties(bits2banking.framework_hash.${scenario} PROPERTIES TIMEOUT 10)
    endforeach()
endif()
