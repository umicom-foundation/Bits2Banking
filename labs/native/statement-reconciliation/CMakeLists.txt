# Bits2Banking | Sammy Hegab, Umicom Foundation | MIT
# Consume the installed shared implementation instead of copying financial rules.
cmake_minimum_required(VERSION 3.25)
project(BitsStatementReconciliation LANGUAGES C)
include(CTest)
# Keep the original lookup for review. The active lookup below adds an actionable
# explanation when the shared SDK is absent or its requested component is missing.
# The example still links the installed Framework; it never copies its rules.
if(FALSE)
    find_package(UmicomFramework CONFIG REQUIRED COMPONENTS bank_feed)
endif()

# Ask the package to check its component first, then explain the installation
# prerequisite before CMake reaches target_link_libraries. Add future components
# to this lookup and the target check together so incomplete SDKs fail early.
find_package(UmicomFramework CONFIG QUIET COMPONENTS bank_feed)
if(NOT UmicomFramework_FOUND OR NOT TARGET Umicom::bank_feed)
    message(FATAL_ERROR
        "This example needs an installed Umicom Framework SDK with bank_feed.\n"
        "Build Umicom-Applications and run cmake --install on that build first.\n"
        "Set CMAKE_PREFIX_PATH to the installation root, or UmicomFramework_DIR "
        "to the folder containing the installed UmicomFrameworkConfig.cmake.\n"
        "A configuration file in the Framework build directory is not an installed SDK.\n"
        "Follow the SDK installation steps linked from this example's README.md.\n"
        "Stop here: build and test commands require configuration to succeed.\n"
        "Package detail: ${UmicomFramework_NOT_FOUND_MESSAGE}")
endif()
add_executable(statement-reconciliation main.c)
set_target_properties(statement-reconciliation PROPERTIES
    C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
target_link_libraries(statement-reconciliation PRIVATE Umicom::bank_feed)
if(MSVC)
    target_compile_options(statement-reconciliation PRIVATE /W4)
else()
    target_compile_options(statement-reconciliation PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
endif()
if(BUILD_TESTING)
    add_test(NAME education.statement.match COMMAND statement-reconciliation)
    set_tests_properties(education.statement.match PROPERTIES
        PASS_REGULAR_EXPRESSION "Difference: 0.00" TIMEOUT 20)
    add_test(NAME education.statement.difference COMMAND statement-reconciliation 110.26)
    set_tests_properties(education.statement.difference PROPERTIES
        PASS_REGULAR_EXPRESSION "Difference: 0.01" TIMEOUT 20)
    add_test(NAME education.statement.invalid COMMAND statement-reconciliation invalid)
    set_tests_properties(education.statement.invalid PROPERTIES WILL_FAIL TRUE TIMEOUT 20)
endif()
