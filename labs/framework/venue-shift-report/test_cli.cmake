#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/framework/venue-shift-report/test_cli.cmake
#
# PURPOSE:
#   Check the installed consumer's read and publication outcomes through its CLI.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
file(SHA256 "${EXAMPLES}/shift.csv" source_hash)
set(expected "Rows: 3\nMinutes: 100\nVisitors: 60\nSource SHA-256: ${source_hash}\n")

# Each check owns its practice folder, so a second run preserves the first receipt.
string(RANDOM LENGTH 12 ALPHABET 0123456789abcdef run_id)
set(run "${WORK}/${CASE}-${run_id}")
file(MAKE_DIRECTORY "${run}")
set(target "${run}/visitor receipt.txt")
set(input "${EXAMPLES}/shift.csv")
if(CASE STREQUAL "read")
    set(args "${input}")
elseif(CASE STREQUAL "save")
    set(args "${input}" "${target}")
elseif(CASE STREQUAL "refuse_bad")
    set(args "${EXAMPLES}/rejected.csv" "${target}")
elseif(CASE STREQUAL "refuse_existing")
    file(WRITE "${target}" "earlier receipt\n")
    set(args "${input}" "${target}")
elseif(CASE STREQUAL "refuse_large")
    string(REPEAT "X" 8193 oversize)
    file(WRITE "${run}/oversize.csv" "${oversize}")
    set(args "${run}/oversize.csv" "${target}")
else()
    message(FATAL_ERROR "unknown case ${CASE}")
endif()

execute_process(COMMAND "${APP}" ${args}
    RESULT_VARIABLE exit_code OUTPUT_VARIABLE output ERROR_VARIABLE diagnostic)
string(REPLACE "\r\n" "\n" output "${output}")
if(CASE MATCHES "^(read|save)$")
    if(NOT exit_code STREQUAL "0" OR NOT diagnostic STREQUAL "" OR NOT output STREQUAL expected)
        message(FATAL_ERROR "unexpected success output ${exit_code} ${output} ${diagnostic}")
    endif()
    if(CASE STREQUAL "save")
        file(READ "${target}" receipt)
        if(NOT receipt STREQUAL expected)
            message(FATAL_ERROR "file differs from accepted report")
        endif()
    endif()
else()
    if(NOT exit_code STREQUAL "1" OR NOT output STREQUAL "")
        message(FATAL_ERROR "refusal published a successful report or returned the wrong exit")
    endif()
    if(CASE STREQUAL "refuse_existing")
        file(READ "${target}" receipt)
        if(NOT receipt STREQUAL "earlier receipt\n" OR NOT diagnostic MATCHES "^receipt:")
            message(FATAL_ERROR "existing file bytes or receipt diagnostic differ")
        endif()
    elseif(EXISTS "${target}")
        message(FATAL_ERROR "refused input unexpectedly created a receipt")
    elseif(CASE STREQUAL "refuse_bad" AND NOT diagnostic MATCHES "^record 3:")
        message(FATAL_ERROR "expected a diagnostic for the bad logical record")
    elseif(CASE STREQUAL "refuse_large" AND NOT diagnostic MATCHES "^input:")
        message(FATAL_ERROR "expected an input size diagnostic")
    endif()
endif()
