# Umicom Bits2Banking
# File: labs/framework/wt-profile/CMakeLists.txt
# PURPOSE: Build an optional Wt web view over the installed C Framework.
# AUTHOR AND ORGANISATION: Sammy Hegab / Umicom Foundation
# LICENCE: MIT
cmake_minimum_required(VERSION 3.26)
project(Bits2BankingWtProfile LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS security)
find_package(Wt CONFIG REQUIRED COMPONENTS Wt HTTP)
add_executable(btb-wt-profile main.cpp profile_application.cpp)
target_link_libraries(btb-wt-profile PRIVATE Umicom::security Wt::Wt Wt::HTTP)
