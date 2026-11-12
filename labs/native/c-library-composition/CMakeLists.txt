#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/c-library-composition/CMakeLists.txt
#
# PURPOSE:
#   Build independent educational archives and exact-byte regression exercises.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#---------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(Bits2BankingLibraryComposition LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
option(BTB_TEACH_UNQUALIFIED_HELPERS "Deliberately restore a linker collision for a separate teaching build" OFF)
add_library(btb-source-pages STATIC scanner.c)
add_library(btb-catalogue-bytes STATIC catalogue.c)
if(BTB_TEACH_UNQUALIFIED_HELPERS)
    target_compile_definitions(btb-source-pages PRIVATE BTB_TEACH_UNQUALIFIED_HELPERS)
    target_compile_definitions(btb-catalogue-bytes PRIVATE BTB_TEACH_UNQUALIFIED_HELPERS)
endif()
add_executable(btb-source-first composition_test.c)
add_executable(btb-catalogue-first composition_test.c)
target_link_libraries(btb-source-first PRIVATE btb-source-pages btb-catalogue-bytes)
target_link_libraries(btb-catalogue-first PRIVATE btb-catalogue-bytes btb-source-pages)
add_executable(btb-fixture-representation fixture_test.c)
if(UNIX)
    target_link_libraries(btb-fixture-representation PRIVATE m)
endif()
foreach(_target btb-source-pages btb-catalogue-bytes btb-source-first btb-catalogue-first btb-fixture-representation)
    if(MSVC)
        target_compile_options(${_target} PRIVATE /W4 /WX)
    else()
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(BUILD_TESTING)
    add_test(NAME bits2banking.composition.source-first COMMAND btb-source-first)
    add_test(NAME bits2banking.composition.catalogue-first COMMAND btb-catalogue-first)
    foreach(_case hex-boundary utf8-octets signed-zero)
        add_test(NAME bits2banking.fixture.${_case} COMMAND btb-fixture-representation ${_case})
    endforeach()
endif()
