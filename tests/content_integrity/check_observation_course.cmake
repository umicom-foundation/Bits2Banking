#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_observation_course.cmake
#
# PURPOSE:
#   Verify the new observation course and continued HTML routes in both editions.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#---------------------------------------------------------------------------
if(NOT DEFINED REPOSITORY_ROOT)
    message(FATAL_ERROR "REPOSITORY_ROOT is required")
endif()
include("${CMAKE_CURRENT_LIST_DIR}/course_links.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/setup_section.cmake")
file(READ "${REPOSITORY_ROOT}/mkdocs.yml" navigation)
file(READ "${REPOSITORY_ROOT}/knowledge/registries/lesson-media.json" media)
foreach(course IN ITEMS weight-management-framework learning-html)
    set(category "06-umicom")
    set(first 0)
    set(minimum 8)
    if(course STREQUAL "learning-html")
        set(category "04-web")
        set(first 10)
        set(minimum 14)
    endif()
    set(base "${REPOSITORY_ROOT}/content/courses/${course}")
    file(READ "${base}/course.json" metadata)
    file(READ "${base}/index.html" contents)
    file(READ "${REPOSITORY_ROOT}/content/lessons/${category}/${course}/index.md" written)
    string(JSON count LENGTH "${metadata}" lessons)
    if(count LESS minimum)
        message(FATAL_ERROR "Missing practical sequence: ${course}")
    endif()
    math(EXPR last "${count} - 1")
    foreach(i RANGE ${first} ${last})
        string(JSON route GET "${metadata}" lessons ${i} path)
        string(JSON title GET "${metadata}" lessons ${i} title)
        string(JSON manuscript GET "${metadata}" lessons ${i} manuscript)
        get_filename_component(slug "${route}" NAME_WE)
        if(NOT manuscript STREQUAL "../../lessons/${category}/${course}/${slug}.md")
            message(FATAL_ERROR "Mismatched manuscript: ${course}/${route}")
        endif()
        file(READ "${base}/${route}" html)
        file(READ "${base}/${manuscript}" markdown)
        BtbCheckCourseLinks("${html}" "${base}/${route}" "${REPOSITORY_ROOT}")
        foreach(fragment IN ITEMS "umicom-wordmark-on-dark.svg" "umicom.ico" "<h1>${title}</h1>" "Before you begin")
            string(FIND "${html}" "${fragment}" found)
            if(found LESS 0)
                message(FATAL_ERROR "Missing lesson identity or preparation: ${route}: ${fragment}")
            endif()
        endforeach()
        foreach(pair IN ITEMS "contents|${route}" "written|${slug}.md" "navigation|lessons/${category}/${course}/${slug}.md" "media|${slug}.html")
            string(REPLACE "|" ";" parts "${pair}")
            list(GET parts 0 variable)
            list(GET parts 1 required)
            string(FIND "${${variable}}" "${required}" found)
            if(found LESS 0)
                message(FATAL_ERROR "Missing ${variable} route: ${course}/${slug}")
            endif()
        endforeach()
        string(FIND "${markdown}" "# ${title}" heading)
        if(heading LESS 0)
            message(FATAL_ERROR "Written title differs: ${route}")
        endif()
    endforeach()
endforeach()
message(STATUS "Observation and HTML source routes agree; platform execution remains separate")
