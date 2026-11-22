#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/graphics/raster-from-scratch/check_ppm.cmake
#
# PURPOSE:
#   Verify exact PPM bytes and safe output-name refusal.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

file(MAKE_DIRECTORY "${WORK}")
string(RANDOM LENGTH 20 ALPHABET "0123456789abcdef" suffix)
set(image "${WORK}/raster-${suffix}.ppm")
execute_process(COMMAND "${EXAMPLE}" "${image}" RESULT_VARIABLE run OUTPUT_VARIABLE output
    ERROR_VARIABLE error TIMEOUT 10)
if(NOT "${run}" STREQUAL "0" OR NOT output MATCHES "Wrote an 80 x 48 RGB image")
    message(FATAL_ERROR "The example could not write its new image: ${run} ${output} ${error}")
endif()

# Assert the file contract separately from the C memory tests. Inspect selected
# byte offsets as a reader would, then make sure a second run cannot replace it.
file(SIZE "${image}" bytes)
file(READ "${image}" header OFFSET 0 LIMIT 13 HEX)
file(READ "${image}" background OFFSET 13 LIMIT 3 HEX)
file(READ "${image}" clipped_left OFFSET 1693 LIMIT 3 HEX)
file(READ "${image}" second_rectangle OFFSET 4441 LIMIT 3 HEX)
file(READ "${image}" line_pixel OFFSET 10819 LIMIT 3 HEX)
if(NOT bytes EQUAL 11533 OR NOT header STREQUAL "50360a38302034380a3235350a"
        OR NOT background STREQUAL "142640" OR NOT clipped_left STREQUAL "4aa8df"
        OR NOT second_rectangle STREQUAL "f4bb47" OR NOT line_pixel STREQUAL "ffffff")
    message(FATAL_ERROR "The PPM header, length, or selected pixels differ from the example contract")
endif()
file(SHA256 "${image}" before)
execute_process(COMMAND "${EXAMPLE}" "${image}" RESULT_VARIABLE repeat
    ERROR_VARIABLE repeat_error TIMEOUT 10)
file(SHA256 "${image}" after)
if(NOT "${repeat}" STREQUAL "1" OR NOT "${before}" STREQUAL "${after}"
        OR NOT repeat_error MATCHES "Could not produce a new PPM image")
    message(FATAL_ERROR "The example must refuse an existing path and preserve that file")
endif()
message(STATUS "PPM layout, selected pixels and exclusive create passed: ${before}")
