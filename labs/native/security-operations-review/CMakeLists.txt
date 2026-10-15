# Bits2Banking | Umicom Foundation | ISO C23 security operations review
# Training only; no SSH, accounts, services, firewall or filesystem changes.
# Retain all earlier teaching targets by importing their existing CMake modules.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingSecurityOperations LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/../remote-access-review/CMakeLists.txt")
  message(FATAL_ERROR "Merge Updates 39-43 before Update 44: remote-access-review is required.")
endif()
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../remote-access-review"
                 "${CMAKE_CURRENT_BINARY_DIR}/previous-remote-review")
add_library(btb-security-operations-lib STATIC security_operations_review.c)
target_include_directories(btb-security-operations-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-security-operations-lib PUBLIC btb-remote-access-review-lib)
add_library(btb-security-fixture STATIC training_fixture.c)
target_include_directories(btb-security-fixture PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-security-fixture PUBLIC btb-security-operations-lib)
add_executable(btb-security-operations-demo main.c)
add_executable(btb-security-operations-test test_security.c)
target_link_libraries(btb-security-operations-demo PRIVATE btb-security-fixture)
target_link_libraries(btb-security-operations-test PRIVATE btb-security-fixture)
foreach(target IN ITEMS btb-security-operations-lib btb-security-fixture
        btb-security-operations-demo btb-security-operations-test)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /WX)
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
  endif()
endforeach()
if(BUILD_TESTING)
  foreach(case_name IN ITEMS pending reviewable accounts groups privilege config drift
      patch restore audit credentials rotation certificate reviewer response
      stale outside-window revision config-mismatch policy-mismatch
      same-person bad-label bad-flag repeat upstream-rollback upstream-restored
      tampered-window fail-atomic mutations)
    add_test(NAME "bits2banking.security-operations.${case_name}"
             COMMAND btb-security-operations-test "${case_name}")
  endforeach()
  add_test(NAME bits2banking.security-operations.demo
           COMMAND btb-security-operations-demo)
endif()
install(TARGETS btb-security-operations-demo RUNTIME DESTINATION bin)
