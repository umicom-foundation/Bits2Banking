#-----------------------------------------------------------------------------
# Bits2Banking
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin GTK host using the installed Framework banking adapter.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.26)
project(UmicomBankWorkspaceLab LANGUAGES C)
find_package(UmicomFramework CONFIG REQUIRED)
if(NOT TARGET Umicom::bank_operations_gtk4)
    message(FATAL_ERROR "Install a Framework SDK containing bank_operations_gtk4 and GTK4 development dependencies.")
endif()
add_executable(bank-workspace main.c)
set_target_properties(bank-workspace PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(bank-workspace PRIVATE Umicom::bank_operations_gtk4)
