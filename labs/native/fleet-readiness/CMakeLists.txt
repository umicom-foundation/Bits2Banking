# Bits2Banking | Umicom Foundation | C23 multi-host support teaching laboratory.
# Compose previously delivered evidence checks; do not copy existing sources.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingFleetReadiness LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/../operational-resilience/CMakeLists.txt")
  message(FATAL_ERROR "Merge and verify Updates 39-45 before configuring Update 46.")
endif()
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../operational-resilience"
                 "${CMAKE_CURRENT_BINARY_DIR}/previous-operational-resilience")
add_library(btb-fleet-readiness-lib STATIC fleet_readiness.c)
target_include_directories(btb-fleet-readiness-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-fleet-readiness-lib PUBLIC btb-operations-lib)
add_library(btb-fleet-training-fixture STATIC fleet_fixture.c)
target_include_directories(btb-fleet-training-fixture PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-fleet-training-fixture PUBLIC
  btb-fleet-readiness-lib btb-operations-fixture)
add_executable(btb-fleet-readiness-demo main.c)
add_executable(btb-fleet-readiness-test test_fleet.c)
target_link_libraries(btb-fleet-readiness-demo PRIVATE btb-fleet-training-fixture)
target_link_libraries(btb-fleet-readiness-test PRIVATE btb-fleet-training-fixture)
foreach(target IN ITEMS btb-fleet-readiness-lib btb-fleet-training-fixture
         btb-fleet-readiness-demo btb-fleet-readiness-test)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4 /WX)
  else()
    target_compile_options(${target} PRIVATE
      -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
  endif()
endforeach()
if(BUILD_TESTING)
  foreach(case_name IN ITEMS ready pending empty stale future revision package
    storage operation clock provenance reviewer privacy upstream-blocked
    restored-only independent-host missing-host unknown duplicate invalid-name
    invalid-policy invalid-hex atomic-init atomic-attach atomic-evaluate
    tampered-host pending-upstream out-of-order mutations)
    add_test(NAME "bits2banking.fleet.${case_name}"
             COMMAND btb-fleet-readiness-test "${case_name}")
  endforeach()
  add_test(NAME bits2banking.fleet.demo COMMAND btb-fleet-readiness-demo)
endif()
install(TARGETS btb-fleet-readiness-demo RUNTIME DESTINATION bin)
