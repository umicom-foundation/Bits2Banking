#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/native/local-ai-routing/CMakeLists.txt
#
# PURPOSE:
#   Build a native client using the installed Framework AI and workspace services.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.25)
project(Bits2BankingLocalAiRouting LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED COMPONENTS ai ai_workspace)
include(CTest)
add_executable(btb-local-ai-routing main.c offline.c local.c)
target_link_libraries(btb-local-ai-routing PRIVATE Umicom::ai Umicom::ai_workspace)
set_target_properties(btb-local-ai-routing PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
if(MSVC)
    target_compile_options(btb-local-ai-routing PRIVATE /W4)
else()
    target_compile_options(btb-local-ai-routing PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(WIN32)
    enable_language(RC)
endif()
umicom_apply_application_branding(TARGET btb-local-ai-routing
    PRODUCT_NAME "Umicom Local AI Routing Learning Lab"
    INTERNAL_NAME btb-local-ai-routing NO_RUNTIME_DEPLOYMENT)
if(BUILD_TESTING)
    foreach(scenario selection capability context health dispatch policy invalid-port)
        add_test(NAME bits2banking.local-ai-routing.${scenario}
            COMMAND "${CMAKE_COMMAND}" "-DTOOL=$<TARGET_FILE:btb-local-ai-routing>"
                "-DSCENARIO=${scenario}" -P "${CMAKE_CURRENT_SOURCE_DIR}/check.cmake")
        set_tests_properties(bits2banking.local-ai-routing.${scenario}
            PROPERTIES TIMEOUT 10 LABELS "education;ai;native;offline")
    endforeach()
endif()
