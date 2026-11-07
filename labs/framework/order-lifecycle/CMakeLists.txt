#-----------------------------------------------------------------------------
# Bits2Banking
# File: labs/framework/order-lifecycle/CMakeLists.txt
#
# PURPOSE:
#   Build the local order-lifecycle lesson against the Framework SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingOrderLifecycle LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS trading)
add_executable(btb-order-lifecycle main.c)
set_target_properties(btb-order-lifecycle PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(btb-order-lifecycle PRIVATE Umicom::trading)
include(CTest)
if(BUILD_TESTING)
  add_test(NAME learning.trading.order-lifecycle COMMAND btb-order-lifecycle)
  set_tests_properties(learning.trading.order-lifecycle PROPERTIES TIMEOUT 15)
endif()
