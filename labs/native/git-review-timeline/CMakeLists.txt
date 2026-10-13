# Bits2Banking | Sammy Hegab | Umicom Foundation | Native C23 only
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingGitReviewTimeline LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

add_library(btb-git-review STATIC review.c)
target_include_directories(btb-git-review PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-git-review-demo review_demo.c)
add_executable(btb-git-review-test test_review.c)
target_link_libraries(btb-git-review-demo PRIVATE btb-git-review)
target_link_libraries(btb-git-review-test PRIVATE btb-git-review)

# Opt-in compile check of the genuine Umicom Framework header. No Framework
# source is copied into Bits2Banking, and the default standalone lab needs none.
set(BTB_FRAMEWORK_SOURCE_ROOT "" CACHE PATH "Local Umicom Framework source checkout (optional)")
if(BTB_FRAMEWORK_SOURCE_ROOT)
    if(NOT EXISTS "${BTB_FRAMEWORK_SOURCE_ROOT}/include/umicom/vcs/working_tree.h")
        message(FATAL_ERROR "Missing Framework public VCS header in BTB_FRAMEWORK_SOURCE_ROOT")
    endif()
    add_library(btb-git-review-framework-bridge OBJECT framework_bridge.c)
    target_include_directories(btb-git-review-framework-bridge PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${BTB_FRAMEWORK_SOURCE_ROOT}/include")
endif()

set(BTB_TARGETS btb-git-review btb-git-review-demo btb-git-review-test)
if(TARGET btb-git-review-framework-bridge)
    list(APPEND BTB_TARGETS btb-git-review-framework-bridge)
endif()
foreach(target IN LISTS BTB_TARGETS)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

if(BUILD_TESTING)
    set(BTB_REVIEW_TEST_CASES
        init invalid-init missing-observation baseline proofs detached behind
        remote-not-fresh unknown-ancestry conflict-priority dirty-child
        untracked advisories failed-build failed-test stale-evidence
        wrong-commit-evidence observation-invalidates rebuild-invalidates
        stale-report invalid-atomic sha256 invalid-sha contradictory
        nonmonotonic unborn read-only mutation-100k)
    foreach(testcase IN LISTS BTB_REVIEW_TEST_CASES)
        add_test(NAME "bits2banking.git_review.${testcase}"
                 COMMAND btb-git-review-test "${testcase}")
    endforeach()
    add_test(NAME bits2banking.git_review.demo COMMAND btb-git-review-demo)

    # Demonstrate genuine reuse of Update 32's C23 policy, WITHOUT duplicating
    # its code. When Update 32 has not been merged, say so rather than faking
    # that its integration regression ran.
    set(BTB_UPDATE32_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../git-release-evidence")
    if(EXISTS "${BTB_UPDATE32_DIR}/gate.c" AND
       EXISTS "${BTB_UPDATE32_DIR}/gate.h")
        add_library(btb-existing-release-gate STATIC "${BTB_UPDATE32_DIR}/gate.c")
        add_executable(btb-git-review-gate-test test_gate_composition.c)
        target_link_libraries(btb-git-review-gate-test PRIVATE
            btb-git-review btb-existing-release-gate)
        foreach(target IN ITEMS btb-existing-release-gate btb-git-review-gate-test)
            if(MSVC)
                target_compile_options(${target} PRIVATE /W4)
            else()
                target_compile_options(${target} PRIVATE
                    -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
            endif()
        endforeach()
        add_test(NAME bits2banking.git_review.release_gate_composition
                 COMMAND btb-git-review-gate-test)
    else()
        message(WARNING "Update 32 release-evidence lab is absent; release gate composition test NOT REGISTERED")
    endif()
endif()
