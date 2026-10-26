# Bits2Banking | Sammy Hegab, Umicom Foundation | MIT
# Link the actual OS parser; do not copy a second implementation into a lesson.
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingOsBootPlan LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
include(CTest)
set(UMICOM_OS_SOURCE "" CACHE PATH "Umicom OS source checkout")
if(NOT EXISTS "${UMICOM_OS_SOURCE}/boot/foundation/config.c" OR
   NOT EXISTS "${UMICOM_OS_SOURCE}/boot/foundation/boot.h" OR
   NOT EXISTS "${UMICOM_OS_SOURCE}/boot/foundation/boot_diagnostic.h" OR
   NOT EXISTS "${UMICOM_OS_SOURCE}/boot/foundation/admission.c" OR
   NOT EXISTS "${UMICOM_OS_SOURCE}/boot/foundation/boot_admission.h")
    message(FATAL_ERROR "Set UMICOM_OS_SOURCE to the Umicom OS source checkout")
endif()
add_library(btb-os-config STATIC "${UMICOM_OS_SOURCE}/boot/foundation/config.c"
    "${UMICOM_OS_SOURCE}/boot/foundation/admission.c")
target_include_directories(btb-os-config PUBLIC "${UMICOM_OS_SOURCE}/boot/foundation")
add_executable(btb-os-plan main.c)
target_link_libraries(btb-os-plan PRIVATE btb-os-config)
if(BUILD_TESTING)
    add_executable(btb-os-admission-tests test_admission.c)
    target_link_libraries(btb-os-admission-tests PRIVATE btb-os-config)
    foreach(_admission IN ITEMS normal requested hostname)
        add_test(NAME "bits2banking.os_admission.${_admission}" COMMAND btb-os-admission-tests "${_admission}")
        set_tests_properties("bits2banking.os_admission.${_admission}" PROPERTIES TIMEOUT 10)
    endforeach()
    add_executable(btb-os-plan-tests test_plan.c)
    target_link_libraries(btb-os-plan-tests PRIVATE btb-os-config)
    foreach(_case IN ITEMS order rollback cycle recovery)
        add_test(NAME "bits2banking.os_plan.${_case}" COMMAND btb-os-plan-tests "${_case}")
        set_tests_properties("bits2banking.os_plan.${_case}" PROPERTIES TIMEOUT 10)
    endforeach()
endif()
foreach(_target IN ITEMS btb-os-config btb-os-plan btb-os-plan-tests btb-os-admission-tests)
    if(TARGET ${_target} AND CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${_target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()

# Use the same guest policy as the OS; these cases deliberately use synthetic
# observations and do not pretend to test Linux credential or mount syscalls.
if(NOT EXISTS "${UMICOM_OS_SOURCE}/boot/foundation/guest_environment.c" OR
   NOT EXISTS "${UMICOM_OS_SOURCE}/boot/foundation/guest_environment.h")
    message(FATAL_ERROR "The OS checkout must include its guest environment policy")
endif()
if(BUILD_TESTING)
    add_executable(btb-os-environment-tests test_environment.c
        "${UMICOM_OS_SOURCE}/boot/foundation/guest_environment.c")
    target_include_directories(btb-os-environment-tests PRIVATE "${UMICOM_OS_SOURCE}/boot/foundation")
    foreach(_environment IN ITEMS complete missing group temporary-mount)
        add_test(NAME "bits2banking.os_environment.${_environment}" COMMAND btb-os-environment-tests "${_environment}")
        set_tests_properties("bits2banking.os_environment.${_environment}" PROPERTIES TIMEOUT 10)
    endforeach()
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(btb-os-environment-tests PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endif()
