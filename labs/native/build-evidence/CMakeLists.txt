# Bits2Banking | Umicom Foundation | Sammy Hegab | Native C23-first laboratory
# Standalone compilation does not require Git, Python, PowerShell or the SDK.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingBuildEvidence LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

add_library(btb-build-evidence STATIC evidence.c)
target_include_directories(btb-build-evidence PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-build-evidence-demo evidence_demo.c)
add_executable(btb-build-evidence-test test_evidence.c)
target_link_libraries(btb-build-evidence-demo PRIVATE btb-build-evidence)
target_link_libraries(btb-build-evidence-test PRIVATE btb-build-evidence)
set(BTB_EVIDENCE_TARGETS btb-build-evidence btb-build-evidence-demo btb-build-evidence-test)

# Real reuse option: the installed Framework owns BOTH parsers and process/Git.
# This target links imported SDK C libraries rather than copying source.
option(BTB_ENABLE_FRAMEWORK_SDK "Build the read-only Framework-backed example" OFF)
if(BTB_ENABLE_FRAMEWORK_SDK)
    find_package(UmicomFramework CONFIG REQUIRED)
    if(NOT TARGET Umicom::vcs OR NOT TARGET Umicom::build)
        message(FATAL_ERROR "Installed Framework must export Umicom::vcs and Umicom::build")
    endif()
    add_library(btb-build-evidence-framework STATIC framework_bridge.c)
    target_link_libraries(btb-build-evidence-framework
        PUBLIC btb-build-evidence Umicom::vcs Umicom::build)
    add_executable(btb-build-evidence-framework-demo framework_demo.c)
    target_link_libraries(btb-build-evidence-framework-demo
        PRIVATE btb-build-evidence-framework)
    list(APPEND BTB_EVIDENCE_TARGETS btb-build-evidence-framework
             btb-build-evidence-framework-demo)
endif()

foreach(target IN LISTS BTB_EVIDENCE_TARGETS)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

if(BUILD_TESTING)
    set(BTB_EVIDENCE_CASES
        sha40 sha256 sha_uppercase sha_short_rejected sha_nonhex_rejected
        sha_unterminated_rejected identity_requires_profile
        identity_requires_toolchain identity_requires_sequence
        identity_rejects_controls init_failure_atomic copied_problem_ownership
        invalid_stage_atomic invalid_severity_atomic
        unterminated_message_atomic control_character_atomic capacity_exact
        full_failure_atomic tests_before_build_refused negative_exit_rejected
        build_recorded_once problems_locked_after_build tests_sum_overflow
        tests_recorded_once seal_requires_build seal_once assessment_clean
        assessment_missing_tests assessment_zero_tests assessment_dropped
        assessment_build_failed assessment_compiler_error
        assessment_warning_budget assessment_failed_tests
        assessment_not_run_tests assessment_skipped_tests assessment_all_skipped
        assessment_stale_sha assessment_uppercase_sha_equivalent
        assessment_other_profile
        assessment_earliest_stage assessment_invalid_output_atomic
        compare_resolved compare_introduced compare_persisting
        compare_duplicate_multiset compare_line_shift compare_profile_refused
        compare_toolchain_refused compare_invalid_atomic
        compare_incomplete_current compare_skipped_current tamper_sealed_without_build
        tamper_invalid_problem mutation_50000)
    foreach(testcase IN LISTS BTB_EVIDENCE_CASES)
        add_test(NAME "bits2banking.build_evidence.${testcase}"
            COMMAND btb-build-evidence-test "${testcase}")
    endforeach()
    add_test(NAME bits2banking.build_evidence.demo
             COMMAND btb-build-evidence-demo)
    if(BTB_ENABLE_FRAMEWORK_SDK)
        add_test(NAME bits2banking.build_evidence.framework_demo
                 COMMAND btb-build-evidence-framework-demo)
    endif()
endif()
