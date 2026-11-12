#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/framework-toolchain-selection/check.cmake
#
# PURPOSE:
#   Check complete native lab output without accepting partial evidence.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
if(NOT DEFINED TOOL OR NOT DEFINED SCENARIO)
    message(FATAL_ERROR "TOOL and SCENARIO are required")
endif()
if(SCENARIO STREQUAL "storage")
    set(expected "storage: failed metadata is representable; unusable conversion preserves output\n")
elseif(SCENARIO STREQUAL "selection")
    set(expected "selection: refused environment preserves selection and both owners\nownership: process entries refer to receiving environment storage\n")
elseif(SCENARIO STREQUAL "compiler")
    set(expected "compiler: repeated selection replaces driver and profile together\n")
elseif(SCENARIO STREQUAL "pic")
    set(expected "pic: explicit compile intent maps to -fPIC; unmapped check preserves plan\n")
else()
    message(FATAL_ERROR "Unknown scenario")
endif()
execute_process(COMMAND "${TOOL}" "${SCENARIO}"
    RESULT_VARIABLE result OUTPUT_VARIABLE output ERROR_VARIABLE error
    ENCODING UTF-8 TIMEOUT 20)
string(REPLACE "\r\n" "\n" output "${output}")
if(NOT result STREQUAL "0" OR NOT error STREQUAL "" OR NOT output STREQUAL expected)
    message(FATAL_ERROR "Scenario ${SCENARIO} failed: ${result}; ${error}; ${output}")
endif()
