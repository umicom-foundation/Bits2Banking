# Bits to Banking | Umicom Foundation | C23 contributor Notes laboratory.
# Build metadata, not a scripting-language implementation.
cmake_minimum_required(VERSION 3.24)
project(BtbContributorNotes LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)

add_library(btb-contributor-notes STATIC notes.c)
target_include_directories(btb-contributor-notes PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-contributor-notes-demo main.c)
add_executable(btb-contributor-notes-test test_notes.c)
target_link_libraries(btb-contributor-notes-demo PRIVATE btb-contributor-notes)
target_link_libraries(btb-contributor-notes-test PRIVATE btb-contributor-notes)
foreach(target IN ITEMS btb-contributor-notes btb-contributor-notes-demo btb-contributor-notes-test)
  if(MSVC)
    target_compile_options(${target} PRIVATE /W4)
  else()
    target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
  endif()
endforeach()
if(BUILD_TESTING)
  foreach(testCase IN ITEMS add update too-long capacity missing invalid ownership)
    add_test(NAME "bits2banking.contributor_notes.${testCase}"
             COMMAND btb-contributor-notes-test "${testCase}")
  endforeach()
  add_test(NAME bits2banking.contributor_notes.demo COMMAND btb-contributor-notes-demo)
endif()

# Optional real Umicom Framework build-planning API consumer. This is compiled
# only when a compatible, separately installed Framework SDK is supplied.
# No framework source files are copied into this educational repository.
option(BTB_ENABLE_FRAMEWORK_PLANNER_EXAMPLE
       "Build a real Framework SDK consumer (requires installed UmicomFramework)" OFF)
if(BTB_ENABLE_FRAMEWORK_PLANNER_EXAMPLE)
  find_package(UmicomFramework CONFIG REQUIRED)
  if(NOT TARGET Umicom::build)
    message(FATAL_ERROR "Installed Framework SDK lacks Umicom::build")
  endif()
  add_executable(btb-framework-build-plan-example framework_planner_example.c)
  target_link_libraries(btb-framework-build-plan-example PRIVATE Umicom::build)
  set_target_properties(btb-framework-build-plan-example PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED ON)
  if(BUILD_TESTING)
    add_test(NAME bits2banking.contributor_notes.framework_plan
             COMMAND btb-framework-build-plan-example)
  endif()
endif()
