#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/framework/venue-shift-report/CMakeLists.txt
#
# PURPOSE:
#   Link the report and its regression tests to an installed Framework SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingVenueReport LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS base platform output_file)
include(CTest)

add_library(btb-venue-model STATIC venue_report.c publish.c)
target_link_libraries(btb-venue-model PRIVATE Umicom::base Umicom::output_file)

add_executable(btb-venue-report main.c)
target_link_libraries(btb-venue-report PRIVATE btb-venue-model Umicom::base Umicom::platform Umicom::output_file)
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(btb-venue-model PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(btb-venue-report PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

if(BUILD_TESTING)
    add_executable(btb-venue-contracts test_venue_report.c)
    target_link_libraries(btb-venue-contracts PRIVATE btb-venue-model Umicom::base)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(btb-venue-contracts PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
    foreach(case IN ITEMS good header number range malformed empty limit render)
        add_test(NAME learning.venue.${case} COMMAND btb-venue-contracts ${case})
    endforeach()
    foreach(case IN ITEMS read save refuse_bad refuse_existing refuse_large)
        add_test(NAME learning.venue.cli.${case} COMMAND "${CMAKE_COMMAND}"
            "-DAPP=$<TARGET_FILE:btb-venue-report>"
            "-DCASE=${case}"
            "-DEXAMPLES=${CMAKE_CURRENT_SOURCE_DIR}/examples"
            "-DWORK=${CMAKE_CURRENT_BINARY_DIR}/checks"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/test_cli.cmake")
    endforeach()
endif()
