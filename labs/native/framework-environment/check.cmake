#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-environment/check.cmake
#
# PURPOSE:
#   Require exact installed-consumer outcomes.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------


# Invoke the installed consumer, then compare the exact exit and output.
# An abnormal termination cannot satisfy an expected refusal.
if(NOT DEFINED TOOL OR NOT DEFINED CASE)
    message(FATAL_ERROR "TOOL and CASE are required")
endif()
if(CASE STREQUAL "compose" OR CASE STREQUAL "alias")
    set(_expected "COURSE=practice\nMODE=release\n")
elseif(CASE STREQUAL "borrow")
    set(_expected "COURSE=practice\nMODE=lease\n")
elseif(CASE STREQUAL "refusal")
    set(_expected "refused malformed overlay; previous=retained\n")
elseif(CASE STREQUAL "kit")
    set(_expected "UMICOM_TOOLCHAIN_KIT=kit.practice\nUMICOM_TOOLCHAIN_PROFILE=practice\nUMICOM_TARGET_TRIPLE=synthetic-target\nCC=kit-compiler\n")
elseif(CASE STREQUAL "kit-refusal")
    set(_expected "refused malformed kit override; previous=retained\n")
elseif(CASE STREQUAL "cross-partial")
    set(_expected "partial discovery retained; target=synthetic-cross-target; not ready\n")
elseif(CASE STREQUAL "kit-revision")
    set(_expected "revision exhausted; sysroot=sdk/target\n")
elseif(CASE STREQUAL "kit-overlap")
    set(_expected "overlapping replacement; sysroot=target\n")
else()
    message(FATAL_ERROR "Unknown scenario")
endif()
execute_process(COMMAND "${TOOL}" "${CASE}"
    RESULT_VARIABLE _result OUTPUT_VARIABLE _out ERROR_VARIABLE _error TIMEOUT 8)
string(REPLACE "\r\n" "\n" _out "${_out}")
if(NOT "${_result}" STREQUAL "0" OR NOT "${_out}" STREQUAL "${_expected}" OR
        NOT "${_error}" STREQUAL "")
    message(FATAL_ERROR "Unexpected result ${_result}: ${_out} ${_error}")
endif()
