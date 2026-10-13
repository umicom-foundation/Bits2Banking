# Bits to Banking | Umicom Foundation | Sammy Hegab | MIT
# Educational C23 policy model; no custom Git client or compiler parser.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingChangeImpact LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

add_library(btb-change-impact STATIC impact.c)
target_include_directories(btb-change-impact PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-change-impact-demo impact_demo.c)
add_executable(btb-change-impact-test test_impact.c)
target_link_libraries(btb-change-impact-demo PRIVATE btb-change-impact)
target_link_libraries(btb-change-impact-test PRIVATE btb-change-impact)

foreach(target IN ITEMS btb-change-impact btb-change-impact-demo btb-change-impact-test)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

if(BUILD_TESTING)
    set(BTB_IMPACT_CASES
        graph_empty graph_null duplicate_modules name_empty name_space name_overflow
        invalid_gates capacity module_atomic edge_added edge_duplicate cycle_self
        cycle_indirect edge_atomic corrupted_graph sha1_valid sha256_valid revision_short
        revision_bad_hex revision_too_long plan_empty_changes plan_unknown_index
        plan_transitive plan_targeted plan_ui_change plan_atomic assess_ready
        assess_stale assess_missing assess_failed assess_not_run assess_dropped
        assess_incomplete_log assess_unreviewed assess_overlap assess_badmask
        assess_badboolean assess_atomic assess_extra_pass assess_multiple
        assess_sha256 deterministic_mutations)
    foreach(case_name IN LISTS BTB_IMPACT_CASES)
        add_test(NAME "bits2banking.change_impact.${case_name}"
            COMMAND btb-change-impact-test "${case_name}")
    endforeach()
    add_test(NAME bits2banking.change_impact.demo COMMAND btb-change-impact-demo)
endif()

# Existing Framework ownership: optional only, without vendored or copied APIs.
# Use this only with a compatible installed Framework SDK; an independent lab
# build does not require Framework and does not claim integration was tested.
option(BTB_WITH_UMICOM_FRAMEWORK "Build read-only Framework VCS/diagnostics consumer" OFF)
if(BTB_WITH_UMICOM_FRAMEWORK)
    find_package(UmicomFramework CONFIG REQUIRED)
    add_executable(btb-framework-readonly-example framework_example.c)
    target_link_libraries(btb-framework-readonly-example PRIVATE Umicom::vcs Umicom::build)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(btb-framework-readonly-example PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endif()
