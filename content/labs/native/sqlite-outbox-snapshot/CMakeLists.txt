#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/labs/native/sqlite-outbox-snapshot/CMakeLists.txt
#
# PURPOSE:
#   Build and run the isolated C23 snapshot exercise against SQLite.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(UmicomSqliteOutboxSnapshot LANGUAGES C)

# Link the host's SQLite development library. The lab creates all practice data.
find_package(SQLite3 REQUIRED)
add_executable(btb-sqlite-outbox-snapshot main.c)
# New FindSQLite3 releases name the imported target SQLite3::SQLite3. Older
# CMake releases keep the previous target, so both use the same system library.
if(TARGET SQLite3::SQLite3)
    target_link_libraries(btb-sqlite-outbox-snapshot PRIVATE SQLite3::SQLite3)
else()
    target_link_libraries(btb-sqlite-outbox-snapshot PRIVATE SQLite::SQLite3)
endif()
set_target_properties(btb-sqlite-outbox-snapshot PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-sqlite-outbox-snapshot PRIVATE /W4)
else()
    target_compile_options(btb-sqlite-outbox-snapshot PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()

# Run inside the caller's build folder so the source checkout stays untouched.
include(CTest)
if(BUILD_TESTING)
    add_test(NAME btb.education.sqlite_outbox_snapshot
        COMMAND btb-sqlite-outbox-snapshot)
    set_tests_properties(btb.education.sqlite_outbox_snapshot PROPERTIES
        TIMEOUT 20 LABELS "education;native;sqlite" RUN_SERIAL TRUE)

    # The original test remains the default. This mode uses a memory-only
    # record and checks both editors before a new revision can be published.
    add_test(NAME btb.education.sqlite_outbox_observed_edit
        COMMAND btb-sqlite-outbox-snapshot observed-edit)
    set_tests_properties(btb.education.sqlite_outbox_observed_edit PROPERTIES
        TIMEOUT 20 LABELS "education;native;sqlite")
endif()
