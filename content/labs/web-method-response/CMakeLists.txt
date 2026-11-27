# -----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: content/labs/web-method-response/CMakeLists.txt
#
# PURPOSE:
#   Build a native C23 exercise against the public Umicom Framework web target.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
# -----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25)
project(UmicomReadRouteMethods LANGUAGES C)

# Load the SDK from the installation selected by the learner.
find_package(UmicomFramework CONFIG REQUIRED)

add_executable(read-route-methods read_route_methods.c)
target_compile_features(read-route-methods PRIVATE c_std_23)
target_link_libraries(read-route-methods PRIVATE Umicom::web)
