#-----------------------------------------------------------------------------
# Bits2Banking — C23 VFS Descriptors Laboratory
# Author: Sammy Hegab | Umicom Foundation | MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project(Bits2BankingVfsDescriptors LANGUAGES C)
  include(CTest)
endif()

add_library(btb_vfs STATIC vfs.c ram_provider.c)
target_include_directories(btb_vfs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(btb_vfs PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
  target_compile_options(btb_vfs PRIVATE /W4)
else()
  target_compile_options(btb_vfs PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()

# When another laboratory consumes this one, only build the shared C library.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  add_executable(btb-vfs-demo main.c)
  target_link_libraries(btb-vfs-demo PRIVATE btb_vfs)
  add_executable(btb-vfs-test test_vfs.c)
  target_link_libraries(btb-vfs-test PRIVATE btb_vfs)
  if(BUILD_TESTING)
    add_test(NAME bits2banking.vfs.ownership COMMAND btb-vfs-test ownership)
    add_test(NAME bits2banking.vfs.validation COMMAND btb-vfs-test validation)
    add_test(NAME bits2banking.vfs.demo COMMAND btb-vfs-demo)
    set_tests_properties(bits2banking.vfs.demo PROPERTIES
      PASS_REGULAR_EXPRESSION "Mounted /notes: Umicom Studio")
  endif()
endif()
