# Bits2Banking | Umicom Foundation | C23 change-window review laboratory.
# Reuse Updates 39 and 40 source directly; never copy their implementation.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingMaintenanceReview LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/../service-readiness/CMakeLists.txt")
    message(FATAL_ERROR "Merge Update 40 first: labs/native/service-readiness is required.")
endif()
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../service-readiness"
                 "${CMAKE_CURRENT_BINARY_DIR}/previous-readiness")
add_library(btb-maintenance-review-lib STATIC maintenance_review.c)
target_include_directories(btb-maintenance-review-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-maintenance-review-lib PUBLIC btb-service-readiness-lib)
add_executable(btb-maintenance-review-demo main.c)
add_executable(btb-maintenance-review-test test_maintenance.c)
target_link_libraries(btb-maintenance-review-demo PRIVATE btb-maintenance-review-lib)
target_link_libraries(btb-maintenance-review-test PRIVATE btb-maintenance-review-lib)
foreach(target IN ITEMS btb-maintenance-review-lib btb-maintenance-review-demo btb-maintenance-review-test)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(BUILD_TESTING)
    foreach(case_name IN ITEMS baseline approval-identity backup-required rollback-plan
            premature-start approved-start ready-post warning-post blocked-post
            stale-post changed-service invalid-post late-post complete recovery-premature
            recovery-failed recovery-success recovery-capture cancel cancel-after-start
            revision-invalid explanation-capacity preserve mutation)
        add_test(NAME "bits2banking.maintenance-review.${case_name}"
                 COMMAND btb-maintenance-review-test "${case_name}")
    endforeach()
    add_test(NAME bits2banking.maintenance-review.demo COMMAND btb-maintenance-review-demo)
endif()
