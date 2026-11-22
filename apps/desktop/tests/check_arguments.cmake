#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: apps/desktop/tests/check_arguments.cmake
#
# PURPOSE:
#   Check safe command admission without launching a desktop window.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#---------------------------------------------------------------------------

# Argument errors must exit before a display connection or course-path read.
set(manifest "learning-packs/native-statement-calculations.json")
set(expected "Supply both --root and --manifest once")
if(CASE STREQUAL "help")
    set(arguments --help)
elseif(CASE STREQUAL "root-only")
    set(arguments --root "${ROOT}")
elseif(CASE STREQUAL "manifest-only")
    set(arguments --manifest "${manifest}")
elseif(CASE STREQUAL "relative-root")
    set(arguments --root relative --manifest "${manifest}")
    set(expected "Choose an absolute library")
elseif(CASE STREQUAL "parent-manifest")
    set(arguments --root "${ROOT}" --manifest "../${manifest}")
    set(expected "Choose an absolute library")
elseif(CASE STREQUAL "duplicate")
    set(arguments --root "${ROOT}" --manifest "${manifest}" --root "${ROOT}")
elseif(CASE STREQUAL "extra")
    set(arguments --root "${ROOT}" --manifest "${manifest}" unexpected)
else()
    message(FATAL_ERROR "Unknown desktop argument case ${CASE}")
endif()

execute_process(COMMAND "${TOOL}" ${arguments}
    OUTPUT_VARIABLE output ERROR_VARIABLE error RESULT_VARIABLE code TIMEOUT 12)
if(CASE STREQUAL "help")
    if(NOT code STREQUAL "0" OR NOT output MATCHES "--root" OR NOT output MATCHES "--manifest")
        message(FATAL_ERROR "Help failed (${code}): ${output} ${error}")
    endif()
elseif(NOT code STREQUAL "1" OR NOT error MATCHES "${expected}")
    message(FATAL_ERROR "Expected argument refusal (${code}): ${output} ${error}")
endif()
