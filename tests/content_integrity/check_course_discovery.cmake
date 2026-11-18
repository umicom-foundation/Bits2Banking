#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/check_course_discovery.cmake
#
# PURPOSE:
#   Check every declared course pair and active manuscript navigation route without building a site.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
include("${CMAKE_CURRENT_LIST_DIR}/course_discovery.cmake")
if(NOT DEFINED REPOSITORY_ROOT)
    message(FATAL_ERROR "REPOSITORY_ROOT must identify the checkout")
endif()
CheckCourseDiscovery("${REPOSITORY_ROOT}" _error _lessons)
if(NOT _error STREQUAL "")
    message(FATAL_ERROR "${_error}")
endif()
message(STATUS "Course discovery inspected ${_lessons} declared lesson pairs")

# Course discovery covers routes; source-reading links also need the existing
 # publication contract. Check the continued native-language and AI courses
 # here so a locally existing repository file cannot masquerade as a site page.
include("${CMAKE_CURRENT_LIST_DIR}/course_links.cmake")
foreach(_course IN ITEMS learning-freebasic learning-d preparing-llm-training-data generative-ai-foundations)
    set(_base "${REPOSITORY_ROOT}/content/courses/${_course}")
    file(READ "${_base}/course.json" _course_metadata)
    string(JSON _course_count LENGTH "${_course_metadata}" lessons)
    if(_course_count LESS 1)
        message(FATAL_ERROR "Course has no declared lessons: ${_course}")
    endif()
    math(EXPR _course_last "${_course_count} - 1")
    foreach(_chapter RANGE 0 ${_course_last})
        string(JSON _lesson_path GET "${_course_metadata}" lessons ${_chapter} path)
        file(READ "${_base}/${_lesson_path}" _lesson_html)
        BtbCheckCourseLinks("${_lesson_html}" "${_base}/${_lesson_path}" "${REPOSITORY_ROOT}")
    endforeach()
endforeach()
