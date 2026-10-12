#-----------------------------------------------------------------------------
# Bits2Banking — Umicom Foundation
# File: labs/native/writeback-sector-store/CMakeLists.txt
# PURPOSE: Build the standalone C23 block-storage laboratory.
# AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
# LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingWritebackSectorStore LANGUAGES C)
include(CTest)

add_library(btb_writeback_sector_store STATIC block_store.c)
target_include_directories(btb_writeback_sector_store PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(btb_writeback_sector_store PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)

add_executable(btb-sector-store-demo main.c)
target_link_libraries(btb-sector-store-demo PRIVATE btb_writeback_sector_store)
add_executable(btb-sector-store-test test_block_store.c)
target_link_libraries(btb-sector-store-test PRIVATE btb_writeback_sector_store)

foreach(target IN ITEMS btb_writeback_sector_store btb-sector-store-demo btb-sector-store-test)
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
  endif()
endforeach()
if(BUILD_TESTING)
  add_test(NAME bits2banking.writeback.sector_store COMMAND btb-sector-store-test)
  add_test(NAME bits2banking.writeback.demo COMMAND btb-sector-store-demo)
endif()
