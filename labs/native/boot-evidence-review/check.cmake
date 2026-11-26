#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/boot-evidence-review/check.cmake
#
# PURPOSE:
#   Verify the exact educational review output and process status.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
execute_process(COMMAND "${TOOL}" "${CASE}"
    RESULT_VARIABLE status
    OUTPUT_VARIABLE report
    ERROR_VARIABLE diagnostic
    OUTPUT_STRIP_TRAILING_WHITESPACE
    TIMEOUT 5
)
if(NOT status STREQUAL EXPECT_EXIT)
    message(FATAL_ERROR "Case ${CASE} returned ${status}, expected ${EXPECT_EXIT}: ${diagnostic}")
endif()
if(NOT report STREQUAL EXPECT_OUTPUT OR NOT diagnostic STREQUAL "")
    message(FATAL_ERROR "Case ${CASE} produced an unexpected report: ${report} ${diagnostic}")
endif()
