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
