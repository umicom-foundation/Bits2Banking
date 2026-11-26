# Umicom Bits2Banking
# File: content/labs/native/umicom-c-brew-time/check-brew-time.cmake
#
# PURPOSE:
# Check command results, rejected input and bytecode preservation.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

if(NOT EXISTS "${TOOL}" OR NOT IS_DIRECTORY "${SOURCE}" OR WORK STREQUAL "")
    message(FATAL_ERROR "The configured workshop requires TOOL, SOURCE and WORK.")
endif()

# Use a fresh test output directory even when a learner repeats a CTest run.
# A previous artifact remains available and cannot turn a command into a pass.
string(RANDOM LENGTH 16 ALPHABET abcdef0123456789 run_id)
set(run "${WORK}/${run_id}")
file(MAKE_DIRECTORY "${run}")

function(expect expected_status expected_output expected_error)
    execute_process(COMMAND "${TOOL}" ${ARGN} WORKING_DIRECTORY "${run}"
        RESULT_VARIABLE status OUTPUT_VARIABLE actual ERROR_VARIABLE error TIMEOUT 30)
    string(REPLACE "\r\n" "\n" actual "${actual}")
    # The fixture specifies exact status and selected output independently.
    if(NOT status STREQUAL "${expected_status}" OR NOT actual MATCHES "${expected_output}" OR
       NOT error MATCHES "${expected_error}")
        message(FATAL_ERROR "Unexpected result for ${ARGN}\nExit ${status}\nOutput ${actual}\nDiagnostic ${error}")
    endif()
endfunction()

if(CASE STREQUAL "source")
    expect(0 "" "^$" check "${SOURCE}/brew-time.uc")
    expect(0 "Result: 255" "^$" run "${SOURCE}/brew-time.uc")
    expect(1 "^$" ".+" check "${SOURCE}/brew-time-invalid.uc")
elseif(CASE STREQUAL "artifact")
    set(artifact "${run}/brew-time.umcb")
    expect(0 "" "^$" compile "${SOURCE}/brew-time.uc" "${artifact}")
    file(SHA256 "${artifact}" before)
    expect(0 "Result: 255" "^$" exec "${artifact}")
    expect(0 "operations=same" "^$" compare-operations "${SOURCE}/brew-time.uc" "${SOURCE}/brew-time-spelling.uc")
    expect(1 "operations=different" "^$" compare-operations "${SOURCE}/brew-time.uc" "${SOURCE}/brew-time-constant.uc")
    file(SHA256 "${artifact}" after)
    if(NOT before STREQUAL after)
        message(FATAL_ERROR "Execution or comparison modified a saved artifact.")
    endif()
elseif(CASE STREQUAL "input")
    set(artifact "${run}/brew-time-input.umcb")
    expect(0 "" "^$" compile-input "${SOURCE}/brew-time-input.uc" "${artifact}")
    expect(0 ".+" "^$" budget-input "${artifact}")
    expect(0 ".+" "^$" check-input-fuel "${artifact}" 64)
    expect(0 "Result: 255" "^$" exec-input "${artifact}" 4 --max-steps 64)
    expect(0 "Result: 195" "^$" exec-input "${artifact}" 3 --max-steps 64)
    expect(0 "Result: -1" "^$" exec-input "${artifact}" 0 --max-steps 64)
    expect(1 "^$" "budget" exec-input "${artifact}" 4 --max-steps 1)
elseif(CASE STREQUAL "preview")
    expect(0 "preview ok\n255\nok\n240" "^$" script --typed "${SOURCE}/brew-time-preview.ucs")
elseif(CASE STREQUAL "block")
    expect(0 "^255\n$" "^$" script --block "${SOURCE}/brew-time-script.ucs")
    expect(1 "^$" ".+" script --block "${SOURCE}/brew-time-script-error.ucs")
elseif(CASE STREQUAL "rollback")
    # File input stops at the first refusal. Redirection selects the stream
    # policy, which continues and shows the last accepted value afterward.
    execute_process(COMMAND "${TOOL}" script --stdin INPUT_FILE "${SOURCE}/brew-time-rollback.stdin"
        RESULT_VARIABLE status OUTPUT_VARIABLE actual ERROR_VARIABLE error TIMEOUT 30)
    string(REPLACE "\r\n" "\n" actual "${actual}")
    if(NOT status STREQUAL "1" OR NOT actual MATCHES "ok\n255\n$" OR NOT error MATCHES ".+")
        message(FATAL_ERROR "Rollback did not preserve 255 with an accompanying refusal: ${status}\n${actual}\n${error}")
    endif()
elseif(CASE STREQUAL "regions")
    execute_process(COMMAND "${TOOL}" regions "${SOURCE}/brew-time-regions.umc" --json
        RESULT_VARIABLE status OUTPUT_VARIABLE report ERROR_VARIABLE error TIMEOUT 30)
    if(NOT status STREQUAL "0" OR NOT error STREQUAL "")
        message(FATAL_ERROR "The region inventory failed: ${error}")
    endif()
    string(JSON classification GET "${report}" classificationOnly)
    string(JSON count LENGTH "${report}" regions)
    if(NOT classification OR count LESS 1)
        message(FATAL_ERROR "Expected a classification report with at least one region.")
    endif()
    file(READ "${SOURCE}/brew-time-regions.umc" original)
    math(EXPR last "${count} - 1")
    set(found FALSE)
    foreach(index RANGE 0 ${last})
        string(JSON language GET "${report}" regions ${index} language)
        if(language STREQUAL "python")
            string(JSON offset GET "${report}" regions ${index} offset)
            string(JSON length GET "${report}" regions ${index} bytes)
            string(SUBSTRING "${original}" ${offset} ${length} span)
            string(FIND "${span}" "Brew timer ?> display" marker)
            if(NOT marker EQUAL -1)
                set(found TRUE)
            endif()
        endif()
    endforeach()
    if(NOT found)
        message(FATAL_ERROR "Could not read the entire Python practice string using its reported region.")
    endif()
    expect(1 "^$" ".+" regions "${SOURCE}/brew-time-unclosed-region.umc" --json)
else()
    message(FATAL_ERROR "Unknown workshop case ${CASE}")
endif()
