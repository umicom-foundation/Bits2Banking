#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_os_runtime_course.cmake
#
# PURPOSE:
#   Keep OS boot-evidence and runtime lessons reachable in both published editions.
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
include("${CMAKE_CURRENT_LIST_DIR}/source_reference.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/course_links.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/setup_section.cmake")
set(base "${REPOSITORY_ROOT}/content/courses/umicom-os-from-scratch")
file(READ "${base}/course.json" metadata)
file(READ "${base}/index.html" html_index)
file(READ "${REPOSITORY_ROOT}/content/lessons/06-umicom/umicom-os-from-scratch/index.md" written_index)
file(READ "${REPOSITORY_ROOT}/mkdocs.yml" navigation)
file(READ "${REPOSITORY_ROOT}/knowledge/registries/lesson-media.json" media)
string(JSON count LENGTH "${metadata}" lessons)
if(count LESS 30)
    message(FATAL_ERROR "The OS boot-evidence and runtime sequence is incomplete")
endif()
function(RequireOsRoute text fragment context)
    string(FIND "${text}" "${fragment}" position)
    if(position LESS 0)
        message(FATAL_ERROR "${context}: missing ${fragment}")
    endif()
endfunction()
math(EXPR last "${count} - 1")
foreach(i RANGE 18 ${last})
    string(JSON route GET "${metadata}" lessons ${i} path)
    string(JSON manuscript GET "${metadata}" lessons ${i} manuscript)
    string(JSON source GET "${metadata}" lessons ${i} source)
    get_filename_component(slug "${route}" NAME_WE)
    if(NOT route MATCHES "^lessons/[0-9]+-[a-z0-9-]+[.]html$" OR
            NOT manuscript STREQUAL "../../lessons/06-umicom/umicom-os-from-scratch/${slug}.md")
        message(FATAL_ERROR "OS lesson identity mismatch: ${route}")
    endif()
    file(READ "${base}/${route}" html)
    file(READ "${base}/${manuscript}" markdown)
    RequireOsRoute("${html_index}" "href=\"${route}\"" "Browser contents")
    RequireOsRoute("${written_index}" "(${slug}.md)" "Written contents")
    RequireOsRoute("${navigation}" "lessons/06-umicom/umicom-os-from-scratch/${slug}.md" "Published navigation")
    RequireOsRoute("${media}" "content/courses/umicom-os-from-scratch/${route}" "Lesson media")
    BtbCheckCourseLinks("${html}" "${base}/${route}" "${REPOSITORY_ROOT}")
    BtbValidateSourceReference("${source}" "${REPOSITORY_ROOT}" valid reason)
    if(NOT valid)
        message(FATAL_ERROR "Invalid OS source reference: ${source}: ${reason}")
    endif()
    if(i GREATER 25)
        BtbHasSetupSection("${markdown}" prepared)
        if(NOT prepared)
            message(FATAL_ERROR "OS runtime lesson lacks preparation: ${route}")
        endif()
        RequireOsRoute("${markdown}" "(index.md)" "Runtime manuscript return")
    endif()
    math(EXPR previous "${i} - 1")
    string(JSON previous_route GET "${metadata}" lessons ${previous} path)
    get_filename_component(previous_slug "${previous_route}" NAME_WE)
    RequireOsRoute("${html}" "href=\"${previous_slug}.html\"" "Previous OS lesson")
    RequireOsRoute("${markdown}" "(${previous_slug}.md)" "Previous OS manuscript")
    if(i LESS last)
        math(EXPR next "${i} + 1")
        string(JSON next_route GET "${metadata}" lessons ${next} path)
        get_filename_component(next_slug "${next_route}" NAME_WE)
        RequireOsRoute("${html}" "href=\"${next_slug}.html\"" "Next OS lesson")
        RequireOsRoute("${markdown}" "(${next_slug}.md)" "Next OS manuscript")
    endif()
endforeach()
