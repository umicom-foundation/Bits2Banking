#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/account-balances/CMakeLists.txt
#
# PURPOSE:
#   Build the account-balance example against the installed Framework finance component.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingAccountBalances LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS finance)
add_executable(btb-account-balances main.c)
target_link_libraries(btb-account-balances PRIVATE Umicom::finance)
set_target_properties(btb-account-balances PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.banking.account-balances COMMAND btb-account-balances)
    set_tests_properties(learning.banking.account-balances PROPERTIES TIMEOUT 15)
endif()
