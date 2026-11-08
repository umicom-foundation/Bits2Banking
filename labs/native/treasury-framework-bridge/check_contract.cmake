# Umicom Bits2Banking
# File: check_contract.cmake
# PURPOSE: Check successful amounts and refusal exit/output contracts.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
function(check_forecast left right code expected)
    execute_process(COMMAND "${PROGRAM}" "${left}" "${right}" RESULT_VARIABLE result
        OUTPUT_VARIABLE output ERROR_VARIABLE error TIMEOUT 3)
    string(REPLACE "\r\n" "\n" output "${output}")
    if(NOT "${result}" STREQUAL "${code}" OR NOT "${output}" STREQUAL "${expected}")
        message(FATAL_ERROR "Unexpected exit or stdout for '${left}'/'${right}': ${result} ${output} ${error}")
    endif()
endfunction()
check_forecast(125000 140000 0 "-15000\n")
check_forecast(0 0 0 "0\n")
check_forecast(9223372036854775807 0 0 "9223372036854775807\n")
check_forecast(0 9223372036854775807 0 "-9223372036854775807\n")
check_forecast(9223372036854775808 0 2 "")
check_forecast(-1 0 2 "")
check_forecast(" 1" 0 2 "")
check_forecast("1.25" 0 2 "")
check_forecast("" 0 2 "")
