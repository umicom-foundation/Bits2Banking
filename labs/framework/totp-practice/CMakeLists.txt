#-----------------------------------------------------------------------------
# Umicom Bits2Banking
# File: labs/framework/totp-practice/CMakeLists.txt
#
# PURPOSE:
#   Link independent authenticator lessons to the shared Framework services.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.24)
project(Bits2BankingTotpPractice LANGUAGES C)
include(CTest)

if(DEFINED UMICOM_FRAMEWORK_SOURCE)
    # Compile the checked primary Framework units, so a learner can inspect
    # the source and results together before using an installed package.
    add_library(totp-practice-security STATIC
        "${UMICOM_FRAMEWORK_SOURCE}/src/base/utf8.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/security/secrets.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/security/totp.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/security/totp_enrollment.c"
        "${UMICOM_FRAMEWORK_SOURCE}/src/security/totp_platform.c")
    target_include_directories(totp-practice-security PUBLIC "${UMICOM_FRAMEWORK_SOURCE}/include")
    target_compile_features(totp-practice-security PUBLIC c_std_23)
    if(WIN32)
        target_link_libraries(totp-practice-security PUBLIC bcrypt)
    endif()
    add_library(Umicom::security ALIAS totp-practice-security)
else()
    find_package(Umicom CONFIG REQUIRED COMPONENTS security)
endif()

# Enrollment is pure bounded data. The verification examples select the
# current Windows CNG lane for the published SHA-1 fixture used here.
set(exercises enrollment)
if(WIN32)
    list(APPEND exercises replay provider_failure)
endif()
foreach(exercise IN LISTS exercises)
    add_executable(totp-practice-${exercise} ${exercise}.c)
    set_target_properties(totp-practice-${exercise} PROPERTIES
        C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    target_link_libraries(totp-practice-${exercise} PRIVATE Umicom::security)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(totp-practice-${exercise} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror)
    endif()
    if(BUILD_TESTING)
        add_test(NAME lesson.totp.${exercise} COMMAND totp-practice-${exercise})
    endif()
endforeach()
