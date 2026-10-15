# Bits2Banking | Umicom Foundation | C23 isolated deployment review laboratory.
# Compose previous *actual* targets; no copy of their C implementation.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingDeploymentRehearsal LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/../maintenance-review/CMakeLists.txt")
    message(FATAL_ERROR "Merge Update 41 first: labs/native/maintenance-review is required.")
endif()
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../maintenance-review"
                 "${CMAKE_CURRENT_BINARY_DIR}/previous-maintenance")
add_library(btb-deployment-review-lib STATIC deployment_review.c)
target_include_directories(btb-deployment-review-lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb-deployment-review-lib PUBLIC btb-maintenance-review-lib)
add_executable(btb-deployment-review-demo main.c)
add_executable(btb-deployment-review-test test_deployment.c)
target_link_libraries(btb-deployment-review-demo PRIVATE btb-deployment-review-lib)
target_link_libraries(btb-deployment-review-test PRIVATE btb-deployment-review-lib)
foreach(target IN ITEMS btb-deployment-review-lib btb-deployment-review-demo btb-deployment-review-test)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
# There is deliberately no installer or service-manager execution here.
if(BUILD_TESTING)
    foreach(case_name IN ITEMS plan invalid-plan bad-hash mismatch-revision
            evidence-digest evidence-source invalid-flags no-stage stale-stage
            missing-runtime missing-config stale-verification fully-qualified
            rollback restored copy-ownership replayed-evidence maintenance-changed
            maintenance-regress preserve-output mutation)
        add_test(NAME "bits2banking.deployment-review.${case_name}"
                 COMMAND btb-deployment-review-test "${case_name}")
    endforeach()
    add_test(NAME bits2banking.deployment-review.demo COMMAND btb-deployment-review-demo)
endif()
# Learners may stage the harmless demo into a private directory they own.
# No system locations, registry entries, shortcuts or background services.
install(TARGETS btb-deployment-review-demo RUNTIME DESTINATION bin)
