#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/wt-profile/CMakeLists.txt
#
# PURPOSE:
#   Build the Wt view over the shared portable C policy and register explicit server-event checks.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.26)
project(Bits2BankingWtProfile LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Wt requires C++; the validation algorithm remains Framework C23. A source
# selection builds that exact leaf and never configures the whole Framework.
set(BTB_FRAMEWORK_SOURCE "" CACHE PATH "Absolute Framework source root for the portable C target")
if(BTB_FRAMEWORK_SOURCE)
    if(NOT IS_ABSOLUTE "${BTB_FRAMEWORK_SOURCE}" OR
       NOT EXISTS "${BTB_FRAMEWORK_SOURCE}/cmake/UmicomProfileName.cmake")
        message(FATAL_ERROR "BTB_FRAMEWORK_SOURCE must be an absolute Framework root containing UmicomProfileName.cmake")
    endif()
    include("${BTB_FRAMEWORK_SOURCE}/cmake/UmicomProfileName.cmake")
else()
    find_package(UmicomFramework CONFIG REQUIRED COMPONENTS profile_name)
endif()
find_package(Wt CONFIG REQUIRED COMPONENTS Wt HTTP)
# Some Wt package revisions import optional targets without enforcing requested
# components. Verify actual imported targets before defining the lab consumers.
if(NOT TARGET Wt::Wt OR NOT TARGET Wt::HTTP)
    message(FATAL_ERROR "Install matching Wt core and HTTP connector packages")
endif()
add_library(btb-wt-profile-view STATIC profile_application.cpp)
target_link_libraries(btb-wt-profile-view PUBLIC Umicom::profile_name Wt::Wt)
add_executable(btb-wt-profile main.cpp)
target_link_libraries(btb-wt-profile PRIVATE btb-wt-profile-view Wt::HTTP)
# Only intentionally public assets belong here. Never use the source directory
# as the default document root in the accompanying launch instructions.
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/public")
include(CTest)
if(BUILD_TESTING)
    if(NOT TARGET Wt::Test)
        message(FATAL_ERROR "BUILD_TESTING requires Wt::Test (libwttest). Install it, or explicitly disable tests for an application-only build")
    endif()
    add_executable(btb-wt-profile-test test_application.cpp)
    target_link_libraries(btb-wt-profile-test PRIVATE btb-wt-profile-view Wt::Test)
    foreach(case initial click enter boundaries embedded-nul unicode plain-output repeated fresh-session)
        add_test(NAME "btb.wt_profile.${case}" COMMAND btb-wt-profile-test "${case}")
        set_tests_properties("btb.wt_profile.${case}" PROPERTIES
            TIMEOUT 20 LABELS "learning;wt;profile;server-events")
    endforeach()
endif()

# The security-wide executable composition is retained for review. The narrow
# policy target removes account/platform dependencies; the same view now serves
# the HTTP application and in-memory event fixture without duplicating logic.
if(FALSE)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS security)
find_package(Wt CONFIG REQUIRED COMPONENTS Wt HTTP)
add_executable(btb-wt-profile main.cpp profile_application.cpp)
target_link_libraries(btb-wt-profile PRIVATE Umicom::security Wt::Wt Wt::HTTP)
endif()
