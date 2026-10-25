# Umicom Foundation / Bits2Banking — test-only native C23 structural gate.
# No new runtime; never modifies any source, lessons or generated website.
cmake_minimum_required(VERSION 3.22)
project(umicom_bits2banking_content_integrity C)
include(CTest)
get_filename_component(_btb_repo_root "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
add_executable(btb-content-inventory-test test_content_inventory.c)
target_compile_features(btb-content-inventory-test PRIVATE c_std_23)
if(MSVC)
    target_compile_options(btb-content-inventory-test PRIVATE /W4)
else()
    target_compile_options(btb-content-inventory-test PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(BUILD_TESTING)
    add_test(NAME btb.education.inventory
        COMMAND btb-content-inventory-test "${_btb_repo_root}")
    add_test(NAME btb.education.rejections
        COMMAND btb-content-inventory-test --self-test)
endif()

# Batch 03: native C23, append-only HTML navigation staging / validation.
# Source files are read-only. The --stage operation writes complete pages into
# a caller-named external staging directory, for manual Beyond Compare review.
# Avoid implementing web publishing operations in Python/PowerShell.
add_executable(btb-lesson-navigation ../../tools/course_navigation_stage.c)
target_compile_features(btb-lesson-navigation PRIVATE c_std_23)
if(MSVC)
    target_compile_options(btb-lesson-navigation PRIVATE /W4)
else()
    target_compile_options(btb-lesson-navigation PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(BUILD_TESTING)
    add_test(NAME btb.education.navigation.selftest
        COMMAND btb-lesson-navigation --self-test)
    # Run full navigation validation AFTER staged full HTML files are merged.
    add_test(NAME btb.education.navigation
        COMMAND btb-lesson-navigation --verify "${_btb_repo_root}")
endif()
