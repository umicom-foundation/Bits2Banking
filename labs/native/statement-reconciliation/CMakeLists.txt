# Bits2Banking | Sammy Hegab, Umicom Foundation | MIT
# Consume the installed shared implementation instead of copying financial rules.
cmake_minimum_required(VERSION 3.25)
project(BitsStatementReconciliation LANGUAGES C)
include(CTest)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS bank_feed)
add_executable(statement-reconciliation main.c)
set_target_properties(statement-reconciliation PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(statement-reconciliation PRIVATE Umicom::bank_feed)
if(MSVC)
    target_compile_options(statement-reconciliation PRIVATE /W4)
else()
    target_compile_options(statement-reconciliation PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    add_test(NAME education.statement.match COMMAND statement-reconciliation)
    set_tests_properties(education.statement.match PROPERTIES
        PASS_REGULAR_EXPRESSION "Difference: 0.00" TIMEOUT 20)
    add_test(NAME education.statement.difference COMMAND statement-reconciliation 110.26)
    set_tests_properties(education.statement.difference PROPERTIES
        PASS_REGULAR_EXPRESSION "Difference: 0.01" TIMEOUT 20)
    add_test(NAME education.statement.invalid COMMAND statement-reconciliation invalid)
    set_tests_properties(education.statement.invalid PROPERTIES WILL_FAIL TRUE TIMEOUT 20)
endif()
