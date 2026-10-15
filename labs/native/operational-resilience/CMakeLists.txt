# Bits2Banking | Umicom Foundation | C23 operational resilience teaching lab.
# Uses previous C23 source as-is: no copied security, monitoring or Git engines.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingOperationalResilience LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/../security-operations-review/CMakeLists.txt")
  message(FATAL_ERROR "Merge the original Update 39–44 C23 labs before Update 45.")
endif()
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../security-operations-review"
                 "${CMAKE_CURRENT_BINARY_DIR}/previous-security-operations")
add_library(btb-operations-lib STATIC operations_review.c)
target_include_directories(btb-operations-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-operations-lib PUBLIC btb-security-operations-lib)
add_library(btb-operations-fixture STATIC operations_fixture.c)
target_include_directories(btb-operations-fixture PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-operations-fixture PUBLIC btb-operations-lib btb-security-fixture)
add_executable(btb-operations-demo main.c)
add_executable(btb-operations-test test_operations.c)
target_link_libraries(btb-operations-demo PRIVATE btb-operations-fixture)
target_link_libraries(btb-operations-test PRIVATE btb-operations-fixture)
foreach(target IN ITEMS btb-operations-lib btb-operations-fixture
        btb-operations-demo btb-operations-test)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /WX)
  else()
    target_compile_options(${target} PRIVATE
      -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
  endif()
endforeach()
if(BUILD_TESTING)
  foreach(case_name IN ITEMS ready pending missing-heartbeat stale-heartbeat
      missing-backup stale-backup missing-restore stale-restore rpo rto queue
      alert-owner alert-route privacy independent-restore outside-window
      upstream-blocked upstream-restored source-mismatch repeat-attach
      invalid-flag future-timestamp policy-invalid atomic-init atomic-attach
      atomic-evaluate cadence cadence-overflow mutations)
    add_test(NAME "bits2banking.operations.${case_name}"
             COMMAND btb-operations-test "${case_name}")
  endforeach()
  add_test(NAME bits2banking.operations.demo COMMAND btb-operations-demo)
endif()
install(TARGETS btb-operations-demo RUNTIME DESTINATION bin)
