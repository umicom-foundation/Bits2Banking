#-----------------------------------------------------------------------------
# Bits to Banking
# File: labs/native/course-catalogue-library/CMakeLists.txt
# PURPOSE: Build one reusable C23 static library, one client and one test.
# AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
# LICENCE: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingCourseCatalogue LANGUAGES C)
include(CTest)

add_library(btb_course_catalogue STATIC catalogue.c)
target_include_directories(btb_course_catalogue PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(btb-course-catalogue main.c)
target_link_libraries(btb-course-catalogue PRIVATE btb_course_catalogue)
add_executable(btb-course-catalogue-test test_catalogue.c)
target_link_libraries(btb-course-catalogue-test PRIVATE btb_course_catalogue)

foreach(target IN ITEMS btb_course_catalogue btb-course-catalogue btb-course-catalogue-test)
    set_target_properties(${target} PROPERTIES
        C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

if(BUILD_TESTING)
    add_test(NAME bits2banking.catalogue.library COMMAND btb-course-catalogue-test)
    add_test(NAME bits2banking.catalogue.demo COMMAND btb-course-catalogue)
    set_tests_properties(bits2banking.catalogue.demo PROPERTIES
        PASS_REGULAR_EXPRESSION "Total lessons: 21")
    set_tests_properties(bits2banking.catalogue.library bits2banking.catalogue.demo
        PROPERTIES LABELS "bits2banking;native;library;linking")
endif()

install(TARGETS btb_course_catalogue ARCHIVE DESTINATION lib)
install(FILES catalogue.h DESTINATION include/bits2banking)
install(TARGETS btb-course-catalogue RUNTIME DESTINATION bin)
