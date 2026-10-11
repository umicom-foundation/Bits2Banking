# Umicom Foundation — Bits2Banking native memory-access laboratory.
# Build the same C23 source with GCC or Clang. No Framework copy is embedded.
cmake_minimum_required(VERSION 3.24)
project(UmicomCacheMemoryLesson LANGUAGES C)
include(CTest)
add_executable(umicom-cache-memory main.c)
set_target_properties(umicom-cache-memory PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED ON C_EXTENSIONS OFF)
if(MSVC)
    target_compile_options(umicom-cache-memory PRIVATE /W4)
else()
    target_compile_options(umicom-cache-memory PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    add_test(NAME education.native.cache_memory COMMAND umicom-cache-memory)
endif()
