# Bits2Banking | Umicom Foundation | Sammy Hegab | Native C23 only
# Standalone educational C23 data model. No Git process or Framework source copied.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingGitThreeWay LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

add_library(btb-git-three-way STATIC merge.c)
target_include_directories(btb-git-three-way PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-git-three-way-demo merge_demo.c)
add_executable(btb-git-three-way-test test_merge.c)
target_link_libraries(btb-git-three-way-demo PRIVATE btb-git-three-way)
target_link_libraries(btb-git-three-way-test PRIVATE btb-git-three-way)

foreach(target IN ITEMS btb-git-three-way btb-git-three-way-demo btb-git-three-way-test)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

if(BUILD_TESTING)
    set(BTB_THREE_WAY_CASES
        empty unchanged ours_only theirs_only identical_edits
        ours_delete theirs_delete both_delete ours_add theirs_add same_add
        different_edits different_adds delete_edit edit_delete
        choose_base choose_ours choose_theirs choose_delete explicit_absent_choice
        resolve_once no_resolve_on_clean resolve_input_atomic
        pending_output_atomic reject_duplicate reject_invalid_key
        reject_unterminated snapshot_full_atomic plan_overflow_atomic
        plan_invalid_atomic ordering deep_copy reject_tamper no_truncation
        mutation_50000)
    foreach(testcase IN LISTS BTB_THREE_WAY_CASES)
        add_test(NAME "bits2banking.git_three_way.${testcase}"
                 COMMAND btb-git-three-way-test "${testcase}")
    endforeach()
    add_test(NAME bits2banking.git_three_way.demo COMMAND btb-git-three-way-demo)
endif()
