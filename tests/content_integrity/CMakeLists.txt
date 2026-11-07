#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/CMakeLists.txt
#
# PURPOSE:
#   Register native C23 content integrity gates and course navigation checks.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
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

# Course pairing and setup checks cover published routes without claiming
# that an Android device, a language compiler or a Flutter UI has been run.
if(BUILD_TESTING)
    add_test(NAME btb.education.mobile_native_courses
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_mobile_native_courses.cmake")
    set_tests_properties(btb.education.mobile_native_courses PROPERTIES
        TIMEOUT 60 LABELS "education;navigation;mobile")
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

# Source relationships are checked without building or executing the website.
if(BUILD_TESTING)
    # Verify standalone browser routes as well as paired manuscripts; this
    # catches source-tree links that would disappear from a published course.
    add_test(NAME btb.education.systems_practical_labs
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_systems_practical_labs.cmake")
    set_tests_properties(btb.education.systems_practical_labs PROPERTIES
        TIMEOUT 30 LABELS "education;framework;navigation")
    add_test(NAME btb.education.learning_paths
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_learning_paths.cmake")
endif()

# Keep displayed beginner examples tied to their executable laboratory source.
if(BUILD_TESTING)
    add_test(NAME btb.education.first_c_course
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_first_c_course.cmake")
endif()

# The Framework course has both standalone pages and published manuscripts.
# Check shared identities and navigable source-reading chapters together.
if(BUILD_TESTING)
    add_test(NAME btb.education.framework_course
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_framework_course.cmake")
    set_tests_properties(btb.education.framework_course PROPERTIES
        TIMEOUT 10 LABELS "education;framework;navigation")
endif()

# Keep both lesson editions, their sequence and project references connected.
# This validates authored navigation, not executable laboratory behaviour.
if(BUILD_TESTING)
    add_test(NAME btb.education.programming_projects
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_programming_projects.cmake")
    set_tests_properties(btb.education.programming_projects PROPERTIES
        TIMEOUT 60 LABELS "education;navigation;programming")
endif()

# Platform chapters share stable identities across browser and manuscript
# editions. This gate checks the route graph, not toolchain or device behaviour.
if(BUILD_TESTING)
    add_test(NAME btb.education.connected_platform_courses
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_connected_platform_courses.cmake")
    set_tests_properties(btb.education.connected_platform_courses PROPERTIES
        TIMEOUT 60 LABELS "education;navigation;platforms")
endif()

# Community handouts and the first project share one source route. The C
# example is built here so its documented behaviour stays executable.
if(BUILD_TESTING)
    add_test(NAME btb.education.community_route
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_community_route.cmake")
    set_tests_properties(btb.education.community_route PROPERTIES
        TIMEOUT 30 LABELS "education;community;navigation")
    add_subdirectory("${_btb_repo_root}/content/community/examples/notes-word-count"
        "community-notes")
endif()
