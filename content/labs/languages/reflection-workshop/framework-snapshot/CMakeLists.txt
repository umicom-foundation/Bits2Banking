# Umicom Bits2Banking
# File: content/labs/languages/reflection-workshop/framework-snapshot/CMakeLists.txt
#
# PURPOSE:
#   Build the reflection snapshot sample against the installed Framework SDK.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

cmake_minimum_required(VERSION 3.25)
project(Bits2BankingReflectionSnapshot LANGUAGES C)

# Require the installed public component so the lesson uses the same
# dependency boundary as a Framework application.
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS reflection)

add_executable(framework-registry-snapshot registry_snapshot.c)
set_target_properties(framework-registry-snapshot PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
)
target_link_libraries(framework-registry-snapshot PRIVATE Umicom::reflection)
