#-----------------------------------------------------------------------------
# Bits2Banking — Umicom Foundation
# File: labs/native/journalled-notes/CMakeLists.txt
# PURPOSE: Compose the earlier C23 sector library with the WAL Notes lesson.
# AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
# LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingJournalledNotes LANGUAGES C)
include(CTest)

# Reuse the authoritative block_store.c rather than duplicating storage logic.
set(BTB_STORAGE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../writeback-sector-store")
add_library(btb_writeback_sector_store STATIC "${BTB_STORAGE_ROOT}/block_store.c")
target_include_directories(btb_writeback_sector_store PUBLIC "${BTB_STORAGE_ROOT}")
add_library(btb_notes_journal STATIC journal.c)
target_include_directories(btb_notes_journal PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb_notes_journal PUBLIC btb_writeback_sector_store)
add_executable(btb-journalled-notes-demo main.c)
target_link_libraries(btb-journalled-notes-demo PRIVATE btb_notes_journal)
add_executable(btb-journalled-notes-test test_journal.c)
target_link_libraries(btb-journalled-notes-test PRIVATE btb_notes_journal)
foreach(target IN ITEMS btb_writeback_sector_store btb_notes_journal btb-journalled-notes-demo btb-journalled-notes-test)
  set_target_properties(${target} PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
  if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
  endif()
endforeach()
if(BUILD_TESTING)
  add_test(NAME bits2banking.journalled_notes.recovery COMMAND btb-journalled-notes-test)
  add_test(NAME bits2banking.journalled_notes.demo COMMAND btb-journalled-notes-demo)
endif()
