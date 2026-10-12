#-----------------------------------------------------------------------------
# Bits2Banking — C23 VFS Provider Composition Laboratory
# Author: Sammy Hegab | Umicom Foundation | MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingVfsProviders LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

# The previous laboratory is the one owner of the VFS and Notes provider.
# add_subdirectory in nested mode builds its library but not its demos/tests.
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../vfs-descriptors"
                 "${CMAKE_CURRENT_BINARY_DIR}/vfs-core")
add_library(btb_reference_provider STATIC reference_provider.c)
target_link_libraries(btb_reference_provider PUBLIC btb_vfs)
target_include_directories(btb_reference_provider PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
if(MSVC)
  target_compile_options(btb_reference_provider PRIVATE /W4)
else()
  target_compile_options(btb_reference_provider PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
add_executable(btb-vfs-provider-demo main.c)
target_link_libraries(btb-vfs-provider-demo PRIVATE btb_reference_provider)
add_executable(btb-vfs-provider-test test_composition.c)
target_link_libraries(btb-vfs-provider-test PRIVATE btb_reference_provider)
if(BUILD_TESTING)
  add_test(NAME bits2banking.vfs.providers COMMAND btb-vfs-provider-test)
  add_test(NAME bits2banking.vfs.providers.demo COMMAND btb-vfs-provider-demo)
  set_tests_properties(bits2banking.vfs.providers.demo PROPERTIES
    PASS_REGULAR_EXPRESSION "Library: Computing, C23, Assembly, Umicom Kernel")
endif()
