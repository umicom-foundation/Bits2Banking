# Bits2Banking C23 process-file services | Sammy Hegab, Umicom Foundation | MIT
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingProcessFileServices LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

# Share the previously taught authoritative VFS/Notes provider implementation.
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../vfs-descriptors"
                 "${CMAKE_CURRENT_BINARY_DIR}/vfs-core")
add_library(btb_process_files STATIC process_files.c)
target_include_directories(btb_process_files PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb_process_files PUBLIC btb_vfs)
if(MSVC)
  target_compile_options(btb_process_files PRIVATE /W4)
else()
  target_compile_options(btb_process_files PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
add_executable(btb-process-files-demo main.c)
target_link_libraries(btb-process-files-demo PRIVATE btb_process_files)
add_executable(btb-process-files-test test_process_files.c)
target_link_libraries(btb-process-files-test PRIVATE btb_process_files)
if(BUILD_TESTING)
  add_test(NAME bits2banking.process_file_services.copy_and_access
           COMMAND btb-process-files-test access)
  add_test(NAME bits2banking.process_file_services.lifetime
           COMMAND btb-process-files-test lifetime)
  add_test(NAME bits2banking.process_file_services.demo
           COMMAND btb-process-files-demo)
  set_tests_properties(bits2banking.process_file_services.demo PROPERTIES
    PASS_REGULAR_EXPRESSION "Process 11 read: Umicom Notes")
endif()
