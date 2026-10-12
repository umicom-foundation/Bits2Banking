# Bits2Banking | Umicom Foundation | Sammy Hegab | MIT
# Standalone C23 educational gate: consumes provided evidence, never calls Git.
cmake_minimum_required(VERSION 3.24)
project(BtbGitReleaseEvidence LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

add_library(btb-git-release-gate STATIC gate.c)
target_include_directories(btb-git-release-gate PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-git-release-gate-demo gate_demo.c)
add_executable(btb-git-release-gate-test test_gate.c)
target_link_libraries(btb-git-release-gate-demo PRIVATE btb-git-release-gate)
target_link_libraries(btb-git-release-gate-test PRIVATE btb-git-release-gate)
foreach(target IN ITEMS btb-git-release-gate btb-git-release-gate-demo btb-git-release-gate-test)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
endforeach()
if(BUILD_TESTING)
    foreach(scenario IN ITEMS
            commit_ready push_ready pin_ready detached behind unknown_remote
            conflicting_index untracked unstaged no_staged unreviewed
            push_index push_no_ahead failed_build unrun_tests failed_docs
            dirty_child unpublished_child mismatch_sha malformed_sha
            malformed_input stale_snapshot many_issues
            failure_atomic deterministic_mutations pin_unrelated_stage
            child_tests_not_run child_tests_failed build_not_run
            docs_not_run tests_failed malformed_unterminated_sha
            malformed_zero_sha demo)
        if(scenario STREQUAL "demo")
            add_test(NAME bits2banking.release_gate.${scenario} COMMAND btb-git-release-gate-demo)
        else()
            add_test(NAME bits2banking.release_gate.${scenario} COMMAND btb-git-release-gate-test ${scenario})
        endif()
    endforeach()
endif()
