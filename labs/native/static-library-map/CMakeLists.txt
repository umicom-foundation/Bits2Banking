#-----------------------------------------------------------------------------
# Bits to Banking | Umicom Foundation
# File: labs/native/static-library-map/CMakeLists.txt
# PURPOSE: Teach private/public symbols, static archives, link maps and install.
# LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingStaticLibrary LANGUAGES C)
include(CTest)
include(GNUInstallDirs)

add_library(btb_ledger STATIC src/ledger.c)
add_library(Bits2Banking::ledger ALIAS btb_ledger)
set_target_properties(btb_ledger PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
target_include_directories(btb_ledger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

add_executable(btb-ledger-demo src/main.c)
target_link_libraries(btb-ledger-demo PRIVATE Bits2Banking::ledger)
set_target_properties(btb-ledger-demo PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
    foreach(target IN ITEMS btb_ledger btb-ledger-demo)
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endforeach()
    # GNU-style linkers can explain why an object file was included. The map
    # is generated in the build directory, not added to the repository.
    if(NOT APPLE)
        target_link_options(btb-ledger-demo PRIVATE
            "LINKER:-Map,${CMAKE_CURRENT_BINARY_DIR}/btb-ledger-demo.map")
    endif()
endif()

if(BUILD_TESTING)
    add_executable(btb-ledger-contract-test tests/test_ledger.c)
    target_link_libraries(btb-ledger-contract-test PRIVATE Bits2Banking::ledger)
    set_target_properties(btb-ledger-contract-test PROPERTIES
        C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
    if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
        target_compile_options(btb-ledger-contract-test PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
    add_test(NAME bits2banking.library.contract COMMAND btb-ledger-contract-test)
    add_test(NAME bits2banking.library.demo COMMAND btb-ledger-demo)
    set_tests_properties(bits2banking.library.demo PROPERTIES
        PASS_REGULAR_EXPRESSION "Learning fund total \\(fictional\\): GBP 504[.]00")
endif()

install(TARGETS btb_ledger ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS btb-ledger-demo RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES include/btb/ledger.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/btb)
