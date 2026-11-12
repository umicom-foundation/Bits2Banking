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

# Exercise the setup contract independently of the current course content.
# A future heading change must not admit empty or preserved-only guidance.
if(BUILD_TESTING)
    foreach(_case IN ITEMS
        recap
        recap-subtitle
        prepare
        prepare-detail
        before
        set-up
        crlf
        semicolon
        comment-before
        empty
        next-section
        comment-only
        hidden-heading
        unclosed-comment
        fenced-heading
        tilde-fence
        short-close
        fence-then-setup
        code-only-setup
        indented-heading
        third-level
        missing)
        add_test(NAME btb.education.setup.${_case}
            COMMAND "${CMAKE_COMMAND}" "-DCASE=${_case}"
                -P "${CMAKE_CURRENT_LIST_DIR}/test_setup_section.cmake")
        set_tests_properties(btb.education.setup.${_case} PROPERTIES
            TIMEOUT 10 LABELS "education;setup;contract")
    endforeach()
endif()

# Source prerequisites are separate from the Python hook and rendered-site checks.
if(BUILD_TESTING)
    foreach(_case IN ITEMS
        markdown
        fragment
        query
        single-quote
        external
        commented
        missing-manuscript
        outside-content
        missing-adapter
        unconfigured-adapter
        lab-source
        local-file
        unclosed-comment)
        add_test(NAME btb.education.course_links.${_case}
            COMMAND "${CMAKE_COMMAND}" "-DCASE=${_case}"
                "-DFIXTURE_ROOT=${CMAKE_CURRENT_BINARY_DIR}/course-link-fixtures"
                -P "${CMAKE_CURRENT_LIST_DIR}/test_course_links.cmake")
        set_tests_properties(btb.education.course_links.${_case} PROPERTIES
            TIMEOUT 15 LABELS "education;publication;source-links")
    endforeach()
endif()

# Course source maps may name external Umicom code without requiring its checkout.
# Validate that distinction while retaining strict local laboratory existence.
if(BUILD_TESTING)
    foreach(_case IN ITEMS
        local-nested local-nested-missing local-nested-directory local-nested-parent
        local local-missing local-directory compiler-relative compiler-sibling kernel-sibling framework-sibling compiler-public framework-public kernel-public studio-public unapproved-repository branch-change query fragment empty-segment dot-segment parent-segment extra-parent absolute encoded trailing-slash local-traversal empty os-public)
        add_test(NAME btb.education.source_reference.${_case}
            COMMAND "${CMAKE_COMMAND}" "-DCASE=${_case}"
                "-DFIXTURE_ROOT=${CMAKE_CURRENT_BINARY_DIR}/source-reference-fixtures/${_case}"
                -P "${CMAKE_CURRENT_LIST_DIR}/test_source_reference.cmake")
        set_tests_properties(btb.education.source_reference.${_case} PROPERTIES
            TIMEOUT 15 LABELS "education;source;identity")
    endforeach()
endif()

# OS runtime lessons extend existing boot evidence; check both publication routes
# and declared source boundaries without mistaking these checks for guest runs.
if(BUILD_TESTING)
    add_test(NAME btb.education.os_runtime_course
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_os_runtime_course.cmake")
    set_tests_properties(btb.education.os_runtime_course PROPERTIES
        TIMEOUT 30 LABELS "education;os;navigation")
endif()

if(BUILD_TESTING)
    add_test(NAME btb.education.file_evidence_course
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_file_evidence_course.cmake")
    set_tests_properties(btb.education.file_evidence_course PROPERTIES TIMEOUT 30
        LABELS "education;content;framework;evidence")
endif()


# General discovery complements topic-specific teaching checks. New course
# metadata must remain paired and reachable without relying on a fixed syllabus
# count or weakening earlier course contracts.
if(BUILD_TESTING)
    add_test(NAME btb.education.course_discovery
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_course_discovery.cmake")
    set_tests_properties(btb.education.course_discovery PROPERTIES TIMEOUT 240
        LABELS "education;navigation;editions")
    foreach(_case IN ITEMS valid nested quoted-navigation comment-only title-only
            trailing-comment other-section missing-mapping duplicate-mapping
            wrong-mapping missing-html missing-manuscript wrong-depth
            escaping-manuscript duplicate-lesson shared-manuscript malformed-metadata
            sibling-course duplicate-normalized escaping-html registry-object course-object)
        add_test(NAME btb.education.course_discovery.${_case}
            COMMAND "${CMAKE_COMMAND}" "-DCASE=${_case}"
                "-DFIXTURE_ROOT=${CMAKE_CURRENT_BINARY_DIR}/course-discovery-fixtures"
                -P "${CMAKE_CURRENT_LIST_DIR}/test_course_discovery.cmake")
        set_tests_properties(btb.education.course_discovery.${_case} PROPERTIES
            TIMEOUT 15 LABELS "education;navigation;editions;contract")
    endforeach()
endif()

# Include the nested module selected by Studio in the owner education suite.
# Root course catalogues alone cannot detect a stale copy of its resource hashes.
if(BUILD_TESTING)
    add_test(NAME btb.education.studio_learning_collection
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_studio_learning_collection.cmake")
    set_tests_properties(btb.education.studio_learning_collection PROPERTIES
        TIMEOUT 30 LABELS "education;studio;content;identity")
endif()

# Both build-tool courses share one real Java fixture and distinct published routes.
if(BUILD_TESTING)
    add_test(NAME btb.education.jvm_build_courses
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_jvm_build_courses.cmake")
    set_tests_properties(btb.education.jvm_build_courses PROPERTIES TIMEOUT 30 LABELS "education;navigation;jvm")
endif()

# Practical observation teaching must preserve both published editions.
if(BUILD_TESTING)
    add_test(NAME btb.education.observation_course
        COMMAND "${CMAKE_COMMAND}" "-DREPOSITORY_ROOT=${_btb_repo_root}"
            -P "${CMAKE_CURRENT_LIST_DIR}/check_observation_course.cmake")
    set_tests_properties(btb.education.observation_course PROPERTIES TIMEOUT 30 LABELS "education;navigation;forms")
endif()

# Presentation contracts complement route checks: paired lessons must retain
# actual scoped table cells, not Markdown flattened into an HTML paragraph.
add_executable(btb-lesson-tables-test test_lesson_tables.c)
target_compile_features(btb-lesson-tables-test PRIVATE c_std_23)
if(MSVC)
    target_compile_options(btb-lesson-tables-test PRIVATE /W4)
else()
    target_compile_options(btb-lesson-tables-test PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
endif()
if(BUILD_TESTING)
    add_test(NAME btb.education.lesson_tables.selftest COMMAND btb-lesson-tables-test --self-test)
    add_test(NAME btb.education.lesson_tables.joins
        COMMAND btb-lesson-tables-test "${_btb_repo_root}/content/courses/building-a-compiler-in-c/lessons/69-validate-joins-on-all-forward-paths.html" 3 9)
    add_test(NAME btb.education.lesson_tables.guest-selectors
        COMMAND btb-lesson-tables-test "${_btb_repo_root}/content/courses/umicom-kernel-from-scratch/lessons/115-execute-forward-vm-paths-in-user-mode.html" 2 7)
    add_test(NAME btb.education.lesson_tables.parse-bounds
        COMMAND btb-lesson-tables-test "${_btb_repo_root}/content/courses/building-a-compiler-in-c/lessons/72-bound-recursive-expression-parsing.html" 3 4)
endif()
