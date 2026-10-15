# Bits2Banking | Umicom Foundation | Native C23 remote-access review.
# This teaching example composes previous actual C23 targets; it never adds
# another implementation of deployment, service management, Git or SSH.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingRemoteAccessReview LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/../deployment-rehearsal/CMakeLists.txt")
  message(FATAL_ERROR "Merge Update 42 and its Update 39-41 prerequisites first.")
endif()
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../deployment-rehearsal"
                 "${CMAKE_CURRENT_BINARY_DIR}/previous-deployment")
add_library(btb-remote-access-review-lib STATIC remote_access_review.c)
target_include_directories(btb-remote-access-review-lib PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(btb-remote-access-review-lib PUBLIC btb-deployment-review-lib)
add_executable(btb-remote-access-review-demo main.c)
add_executable(btb-remote-access-review-test test_remote.c)
target_link_libraries(btb-remote-access-review-demo PRIVATE btb-remote-access-review-lib)
target_link_libraries(btb-remote-access-review-test PRIVATE btb-remote-access-review-lib)
foreach(target IN ITEMS btb-remote-access-review-lib btb-remote-access-review-demo btb-remote-access-review-test)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4)
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
  endif()
endforeach()
if(BUILD_TESTING)
  foreach(case_name IN ITEMS pending approved-evidence host-key transport scope
      privilege credentials recovery reviewer read-only stale outside-window
      revision mismatched-plan same-person bad-flag repeat atomic-output
      rollback restored mutations)
    add_test(NAME "bits2banking.remote-review.${case_name}"
             COMMAND btb-remote-access-review-test "${case_name}")
  endforeach()
  add_test(NAME bits2banking.remote-review.demo COMMAND btb-remote-access-review-demo)
endif()
# Only private-prefix staging is permitted in the manual exercise.
install(TARGETS btb-remote-access-review-demo RUNTIME DESTINATION bin)
