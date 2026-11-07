#-----------------------------------------------------------------------------
# Bits to Banking
# File: labs/framework/statement-review/CMakeLists.txt
#
# PURPOSE:
#   Link the statement laboratory to the installed Framework bank-feed component.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(BitsBankStatementReview LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS bank_feed)
add_executable(btb-statement-review main.c)
target_link_libraries(btb-statement-review PRIVATE Umicom::bank_feed)
set_target_properties(btb-statement-review PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.bank.statement_review COMMAND btb-statement-review)
    set_tests_properties(learning.bank.statement_review PROPERTIES TIMEOUT 15)
endif()
