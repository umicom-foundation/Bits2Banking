#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_jvm_build_courses.cmake
#
# PURPOSE:
#   Verify both JVM course editions resolve their actual shared lab and routes.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
if(NOT DEFINED REPOSITORY_ROOT)
    message(FATAL_ERROR "REPOSITORY_ROOT is required")
endif()
include("${CMAKE_CURRENT_LIST_DIR}/course_links.cmake")
file(READ "${REPOSITORY_ROOT}/mkdocs.yml" site)
foreach(course IN ITEMS learning-maven learning-gradle learning-xml)
    set(category "05-engineering")
    if(course STREQUAL "learning-xml")
        set(category "04-web")
    endif()
    set(base "${REPOSITORY_ROOT}/content/courses/${course}")
    file(READ "${base}/course.json" metadata)
    file(READ "${base}/index.html" contents)
    string(JSON count LENGTH "${metadata}" lessons)
    if(count LESS 3)
        message(FATAL_ERROR "Missing introductory build workflow: ${course}")
    endif()
    math(EXPR last "${count} - 1")
    foreach(i RANGE 0 ${last})
        string(JSON route GET "${metadata}" lessons ${i} path)
        string(JSON title GET "${metadata}" lessons ${i} title)
        string(JSON manuscript GET "${metadata}" lessons ${i} manuscript)
        get_filename_component(slug "${route}" NAME_WE)
        if(NOT manuscript STREQUAL "../../lessons/${category}/${course}/${slug}.md")
            message(FATAL_ERROR "Mismatched course edition: ${route}")
        endif()
        file(READ "${base}/${route}" html)
        file(READ "${base}/${manuscript}" markdown)
        BtbCheckCourseLinks("${html}" "${base}/${route}" "${REPOSITORY_ROOT}")
        foreach(text IN ITEMS "<h1>${title}</h1>" "umicom-wordmark-on-dark.svg" "umicom.ico")
            string(FIND "${html}" "${text}" found)
            if(found LESS 0)
                message(FATAL_ERROR "Missing title or approved identity: ${route}: ${text}")
            endif()
        endforeach()
        string(FIND "${contents}" "${route}" listed)
        string(FIND "${site}" "lessons/${category}/${course}/${slug}.md" navigable)
        string(FIND "${markdown}" "# ${title}" heading)
        if(listed LESS 0 OR navigable LESS 0 OR heading LESS 0)
            message(FATAL_ERROR "Undiscoverable or mismatched edition: ${route}")
        endif()
    endforeach()
endforeach()
foreach(file IN ITEMS pom.xml build.gradle.kts settings.gradle.kts README.md
        src/main/java/org/umicom/learning/BuildIdentity.java
        src/test/java/org/umicom/learning/BuildIdentityTest.java)
    if(NOT EXISTS "${REPOSITORY_ROOT}/labs/build-tools/jvm-identity/${file}")
        message(FATAL_ERROR "Missing shared JVM lab: ${file}")
    endif()
endforeach()
message(STATUS "JVM course sources and discovery agree; Java compilation and tests are separate checks")
