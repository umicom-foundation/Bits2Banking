# Bits2Banking | Sammy Hegab, Umicom Foundation | MIT
# Check successful completion, stdout and stderr as separate observations.
cmake_minimum_required(VERSION 3.24)
if(NOT DEFINED PROGRAM OR NOT DEFINED EXPECTED)
    message(FATAL_ERROR "Supply PROGRAM and EXPECTED")
endif()
execute_process(COMMAND "${PROGRAM}" RESULT_VARIABLE _result
    OUTPUT_VARIABLE _output ERROR_VARIABLE _error TIMEOUT 5)
if(NOT _result STREQUAL "0")
    message(FATAL_ERROR "Program did not complete successfully: ${_result}\n${_error}")
endif()
file(READ "${EXPECTED}" _expected)
# The C text stream may emit CRLF on Windows. Only newline spelling is normalised;
# missing lines, extra output, changed words and unexpected diagnostics still fail.
string(REPLACE "\r\n" "\n" _output "${_output}")
string(REPLACE "\r\n" "\n" _expected "${_expected}")
if(NOT _output STREQUAL _expected OR NOT _error STREQUAL "")
    message(FATAL_ERROR "Output differs. Expected=[${_expected}] Received=[${_output}] stderr=[${_error}]")
endif()
