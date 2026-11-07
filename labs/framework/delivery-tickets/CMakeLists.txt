#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/delivery-tickets/CMakeLists.txt
#
# PURPOSE:
#   Build the Framework delivery-ticket consumer example.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.26)
project(Bits2BankingDeliveryTickets LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS messaging)
add_executable(btb-delivery-tickets main.c)
target_link_libraries(btb-delivery-tickets PRIVATE Umicom::messaging)
include(CTest)
if(BUILD_TESTING)
    add_test(NAME learning.messaging.delivery-tickets COMMAND btb-delivery-tickets)
    set_tests_properties(learning.messaging.delivery-tickets PROPERTIES
        PASS_REGULAR_EXPRESSION "Stale release rejected; replacement remains owned.")
endif()
