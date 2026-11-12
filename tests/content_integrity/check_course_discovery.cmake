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
