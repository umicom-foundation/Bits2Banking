# Bits2Banking | Umicom Foundation | C23 Driver Lifecycle learning | MIT
cmake_minimum_required(VERSION 3.24)
project(Bits2BankingDriverLifecycle LANGUAGES C)
include(CTest)
# The earlier service owner already composes interrupt-ownership. Link it
# rather than copying a second interrupt implementation into this exercise.
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../service-recovery"
    "${CMAKE_CURRENT_BINARY_DIR}/service-recovery")
add_library(btb_driver_lifecycle STATIC driver.c)
target_include_directories(btb_driver_lifecycle PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(btb_driver_lifecycle PUBLIC btb_service_recovery)
set_target_properties(btb_driver_lifecycle PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
add_executable(btb-driver-lifecycle main.c)
add_executable(btb-driver-lifecycle-test test_driver.c)
foreach(target IN ITEMS btb_driver_lifecycle btb-driver-lifecycle btb-driver-lifecycle-test)
    set_target_properties(${target} PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
    endif()
endforeach()
target_link_libraries(btb-driver-lifecycle PRIVATE btb_driver_lifecycle)
target_link_libraries(btb-driver-lifecycle-test PRIVATE btb_driver_lifecycle)
if(BUILD_TESTING)
    add_test(NAME bits2banking.driver_lifecycle.demo COMMAND btb-driver-lifecycle)
    add_test(NAME bits2banking.driver_lifecycle.contracts COMMAND btb-driver-lifecycle-test)
    set_tests_properties(bits2banking.driver_lifecycle.demo bits2banking.driver_lifecycle.contracts
        PROPERTIES LABELS "education;c23;driver;ownership")
endif()
