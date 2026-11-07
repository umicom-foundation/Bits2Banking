# Umicom Framework
# File: CMakeLists.txt
# PURPOSE: Build a VHDL simulation through the ordinary project workflow.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.26)
project(learning_cpu LANGUAGES NONE)
include(CTest)
find_program(GHDL_EXECUTABLE NAMES ghdl REQUIRED)
set(work_dir "${CMAKE_CURRENT_BINARY_DIR}/ghdl-work")
file(MAKE_DIRECTORY "${work_dir}")
set(cpu_source "${CMAKE_CURRENT_SOURCE_DIR}/rtl/learning_cpu.vhd")
set(bench_source "${CMAKE_CURRENT_SOURCE_DIR}/tests/tb_learning_cpu.vhd")
# Build outputs stay in the build tree; dependencies trigger analysis after edits.
add_custom_command(OUTPUT "${work_dir}/analysis.stamp"
  COMMAND "${GHDL_EXECUTABLE}" -a --std=08 "--workdir=${work_dir}" "${cpu_source}" "${bench_source}"
  COMMAND "${GHDL_EXECUTABLE}" -e --std=08 "--workdir=${work_dir}" tb_learning_cpu
  COMMAND "${CMAKE_COMMAND}" -E touch "${work_dir}/analysis.stamp"
  DEPENDS "${cpu_source}" "${bench_source}" "${GHDL_EXECUTABLE}"
  WORKING_DIRECTORY "${work_dir}" VERBATIM)
add_custom_target(cpu_analysis ALL DEPENDS "${work_dir}/analysis.stamp")
add_custom_target(simulate
  COMMAND "${GHDL_EXECUTABLE}" -r --std=08 "--workdir=${work_dir}" tb_learning_cpu --assert-level=error --wave=cpu.ghw
  DEPENDS cpu_analysis WORKING_DIRECTORY "${work_dir}" VERBATIM)
if(BUILD_TESTING)
  add_test(NAME cpu.instructions COMMAND "${GHDL_EXECUTABLE}" -r --std=08 "--workdir=${work_dir}" tb_learning_cpu --assert-level=error)
  set_tests_properties(cpu.instructions PROPERTIES TIMEOUT 15 WORKING_DIRECTORY "${work_dir}")
endif()

# The composed program owns a separate GHDL work library. Independent targets
# may build concurrently without writing the same analysis database.
set(program_work_dir "${CMAKE_CURRENT_BINARY_DIR}/ghdl-program")
file(MAKE_DIRECTORY "${program_work_dir}")
set(program_sources
  "${cpu_source}"
  "${CMAKE_CURRENT_SOURCE_DIR}/rtl/learning_program.vhd"
  "${CMAKE_CURRENT_SOURCE_DIR}/rtl/learning_system.vhd"
  "${CMAKE_CURRENT_SOURCE_DIR}/tests/tb_learning_system.vhd")
add_custom_command(OUTPUT "${program_work_dir}/analysis.stamp"
  COMMAND "${GHDL_EXECUTABLE}" -a --std=08 "--workdir=${program_work_dir}" ${program_sources}
  COMMAND "${GHDL_EXECUTABLE}" -e --std=08 "--workdir=${program_work_dir}" tb_learning_system
  COMMAND "${CMAKE_COMMAND}" -E touch "${program_work_dir}/analysis.stamp"
  DEPENDS ${program_sources} "${GHDL_EXECUTABLE}"
  WORKING_DIRECTORY "${program_work_dir}" VERBATIM)
add_custom_target(program_analysis ALL DEPENDS "${program_work_dir}/analysis.stamp")
add_custom_target(simulate_program
  COMMAND "${GHDL_EXECUTABLE}" -r --std=08 "--workdir=${program_work_dir}" tb_learning_system --assert-level=error --wave=program.ghw
  DEPENDS program_analysis WORKING_DIRECTORY "${program_work_dir}" VERBATIM)
if(BUILD_TESTING)
  add_test(NAME cpu.program COMMAND "${GHDL_EXECUTABLE}" -r --std=08 "--workdir=${program_work_dir}" tb_learning_system --assert-level=error)
  set_tests_properties(cpu.program PROPERTIES TIMEOUT 15 WORKING_DIRECTORY "${program_work_dir}")
endif()
