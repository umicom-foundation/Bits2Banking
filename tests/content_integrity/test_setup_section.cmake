#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: tests/content_integrity/test_setup_section.cmake
#
# PURPOSE:
#   Check that setup recognition accepts existing prose and rejects hidden or empty guidance.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.22)
include("${CMAKE_CURRENT_LIST_DIR}/setup_section.cmake")
if(CASE STREQUAL "recap")
    set(_document [==[# Lesson

## Setup recap

Open the prepared project.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "recap-subtitle")
    set(_document [==[## Setup recap: Install tools
Use the project README.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "prepare")
    set(_document [==[## Prepare
Open Input.kt and Progress.kt.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "prepare-detail")
    set(_document [==[## Prepare a working Android project
Run the unchanged template first.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "before")
    set(_document [==[## Before you begin
Complete the previous screen exercise.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "set-up")
    set(_document [==[## Set up
Check the CMake target and selected ABI.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "crlf")
    # Construct CRLF in the value rather than relying on this file's line endings.
    set(_document "## Prepare\r\n\r\nOpen the sample.\r\n")
    set(_expected TRUE)
elseif(CASE STREQUAL "semicolon")
    set(_document [==[## Prepare
Open the source; keep the existing project.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "comment-before")
    set(_document [==[<!-- retained header -->
## Prepare
Open the project.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "empty")
    set(_document [==[## Setup recap

]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "next-section")
    set(_document [==[## Prepare

## Work through the example
This belongs to another section.
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "comment-only")
    set(_document [==[## Prepare
<!-- Open a project. -->
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "hidden-heading")
    set(_document [==[<!--
## Setup recap
Open the project.
-->
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "unclosed-comment")
    set(_document [==[<!--
## Setup recap
Open the project.
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "fenced-heading")
    set(_document [==[```markdown
## Prepare
Example only.
```
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "tilde-fence")
    set(_document [==[~~~markdown
## Prepare
Example only.
~~~
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "short-close")
    set(_document [==[````
```
## Prepare
Still in code.
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "fence-then-setup")
    set(_document [==[```
example
```
## Prepare
Open the project.
]==])
    set(_expected TRUE)
elseif(CASE STREQUAL "code-only-setup")
    set(_document [==[## Prepare
```
cmake --build build
```
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "indented-heading")
    set(_document [==[    ## Prepare
    This is code.
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "third-level")
    set(_document [==[### Prepare
Nested text.
]==])
    set(_expected FALSE)
elseif(CASE STREQUAL "missing")
    set(_document [==[## Understand the idea
Text.
]==])
    set(_expected FALSE)
else()
    message(FATAL_ERROR "Unknown setup case: ${CASE}")
endif()
BtbHasSetupSection("${_document}" _actual)
if(NOT "${_actual}" STREQUAL "${_expected}")
    message(FATAL_ERROR "Setup case ${CASE}: expected ${_expected}, got ${_actual}")
endif()
