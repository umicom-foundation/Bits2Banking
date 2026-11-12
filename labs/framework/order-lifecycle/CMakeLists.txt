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
# The earlier trading-only dependency is retained for review. The observation
# example additionally uses the shared UI value contract without opening a GUI.
# find_package(UmicomFramework CONFIG REQUIRED COMPONENTS trading)
# The preceding component set remains for review. The market client uses the
# shared toolkit-neutral action controller as well as trading and UI values.
# find_package(UmicomFramework CONFIG REQUIRED COMPONENTS trading ui)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS trading ui trading_ui)
add_executable(btb-order-lifecycle main.c)
set_target_properties(btb-order-lifecycle PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(btb-order-lifecycle PRIVATE Umicom::trading)
include(CTest)
if(BUILD_TESTING)
  add_test(NAME learning.trading.order-lifecycle COMMAND btb-order-lifecycle)
  set_tests_properties(learning.trading.order-lifecycle PROPERTIES TIMEOUT 15)
endif()

# This client uses the canonical workspace in the exported trading component.
# It remains a terminal example; no GUI adapter or second fill engine is added.
add_executable(btb-order-execution execution.c)
set_target_properties(btb-order-execution PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(btb-order-execution PRIVATE Umicom::trading)
if(BUILD_TESTING)
  foreach(scenario IN ITEMS partial replay conflict cancel filled tiny overfill invalid)
    add_test(NAME "learning.trading.order-execution.${scenario}" COMMAND btb-order-execution "${scenario}")
    set_tests_properties("learning.trading.order-execution.${scenario}" PROPERTIES TIMEOUT 15)
  endforeach()
endif()

add_executable(btb-revision-value revision_value.c)
set_target_properties(btb-revision-value PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(btb-revision-value PRIVATE Umicom::ui)
if(BUILD_TESTING)
  foreach(scenario IN ITEMS policy-ioc policy-fok)
    add_test(NAME "learning.trading.order-execution.${scenario}" COMMAND btb-order-execution "${scenario}")
    set_tests_properties("learning.trading.order-execution.${scenario}" PROPERTIES TIMEOUT 15)
  endforeach()
  foreach(scenario IN ITEMS small boundary maximum)
    add_test(NAME "learning.trading.revision-value.${scenario}" COMMAND btb-revision-value "${scenario}")
    set_tests_properties("learning.trading.revision-value.${scenario}" PROPERTIES TIMEOUT 15)
  endforeach()
endif()

# One synthetic client exercises public owners; no external provider is contacted.
add_executable(btb-market-observation market_observation.c)
set_target_properties(btb-market-observation PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(btb-market-observation PRIVATE Umicom::trading_ui)
if(BUILD_TESTING)
  foreach(scenario IN ITEMS depth invalid-depth metadata tape alerts remove protect draft)
    add_test(NAME "learning.trading.market-observation.${scenario}" COMMAND btb-market-observation "${scenario}")
    set_tests_properties("learning.trading.market-observation.${scenario}" PROPERTIES TIMEOUT 15)
  endforeach()
endif()

# Identity and lifetime examples are ordinary SDK consumers. They neither
# duplicate Framework policy nor access opaque workspace fields.
add_executable(btb-identity-lifetime identity_lifetime.c)
set_target_properties(btb-identity-lifetime PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(btb-identity-lifetime PRIVATE Umicom::trading)
if(BUILD_TESTING)
  foreach(scenario IN ITEMS watchlist query quota navigation)
    add_test(NAME "learning.trading.identity-lifetime.${scenario}" COMMAND btb-identity-lifetime "${scenario}")
    set_tests_properties("learning.trading.identity-lifetime.${scenario}" PROPERTIES TIMEOUT 15)
  endforeach()
endif()

# All lesson executables consume the installed canonical brand resources. The
# shared helper embeds the Windows ICO and stages SVG masters; these console
# clients do not need GTK runtime deployment or a graphical entry point.
if(WIN32)
  enable_language(RC)
endif()
# The preceding four-target list is retained for review; include the new client
# in the same resource owner rather than adding a second branding path.
# foreach(lesson_target IN ITEMS btb-order-lifecycle btb-order-execution btb-revision-value btb-market-observation)
foreach(lesson_target IN ITEMS btb-order-lifecycle btb-order-execution btb-revision-value btb-market-observation btb-identity-lifetime)
  umicom_apply_application_branding(
    TARGET "${lesson_target}"
    PRODUCT_NAME "Umicom Bits2Banking Trading Laboratory"
    INTERNAL_NAME "${lesson_target}"
    NO_RUNTIME_DEPLOYMENT)
endforeach()
