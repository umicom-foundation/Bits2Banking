<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/29-see-which-library-ninja-will-link.md

PURPOSE:
See which library Ninja will link

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# See which library Ninja will link

CMake reads project instructions and writes a build plan for Ninja. The plan lists outputs such as a library or an executable and the inputs needed to produce each one. Those relationships form the **build graph**. An executable's link rule is one place to check which libraries it will use. [CMake command guide](https://cmake.org/cmake/help/latest/manual/cmake.1.html) · [Ninja build statements](https://ninja-build.org/manual.html#_build_statements)

## Follow three separate steps

| Step | What happens | What to record |
| --- | --- | --- |
| Configure and generate | CMake reads project settings, resolves targets and writes the Ninja plan. | The source folder, build folder and result of the configure command. |
| Build | Ninja follows the plan. The compiler translates C files into object files. The linker combines objects and libraries into an executable. | The selected target, link command and final build result. |
| Test | CTest runs the named checks from the specified build folder and records each outcome. | The test directory, test names and outcomes for the executable from the successful build. |

One project can have several build folders. A directory for a debug build can hold an earlier plan than a separate folder for a release build. Record the directory next to each observation so someone else can locate the same plan.

## 1. Prepare a tiny C project

For this exercise, use a folder you set aside for practice. You need PowerShell, CMake 3.25 or newer, Ninja and a C compiler with C23 support. Create these three files in the practice folder. Open PowerShell in that folder.

~~~cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.25)
project(BuildGraphPractice LANGUAGES C)

# Use the same language standard for the library and its future caller.
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(lesson_total STATIC total.c)
add_executable(lesson_check main.c)

enable_testing()
add_test(NAME lesson.total COMMAND lesson_check)
~~~

~~~c
/* total.c */
/* Keep the calculation in a library so the link rule has an input to find. */
int lesson_total(void)
{
    return 2 + 3;
}
~~~

~~~c
/* main.c */
/* Declare the function used from the library. */
int lesson_total(void);

int main(void)
{
    /* Exit with zero when the calculation gives the expected result. */
    return lesson_total() == 5 ? 0 : 1;
}
~~~

## 2. Inspect the first generated link rule

Configure the example. Run the second command after CMake reports successful generation.

~~~powershell
cmake -S . -B build -G Ninja
Select-String -LiteralPath './build/build.ninja' -Pattern '^build lesson_check(?:\.exe)?:' -Context 0,8
~~~

A Ninja build line for `lesson_check` identifies the executable and its link rule. The target may be called `lesson_check.exe` on Windows. Find the input list in that line and the nearby `LINK_LIBRARIES` setting when it is present. The first plan has no `lesson_total` input for `lesson_check`. The exercise only needs configuration at this stage.

A declaration tells the C compiler the name and type of a function. The linker still needs an object or library that contains the function's definition. A message such as `undefined reference` or `unresolved external symbol` identifies a missing definition during linking.

## 3. Change the project and read the plan again

Add this line below `add_executable(lesson_check main.c)` in `CMakeLists.txt`. It gives the executable a dependency on the library containing the calculation. `PRIVATE` makes that library a link requirement of this target. [CMake target link libraries](https://cmake.org/cmake/help/latest/command/target_link_libraries.html)

~~~cmake
target_link_libraries(lesson_check PRIVATE lesson_total)
~~~

Save the file and repeat the `Select-String` command before asking CMake or Ninja to build anything. The existing `build.ninja` still describes the earlier dependency list. Reading the generated file leaves it as it was. A typical CMake-generated build checks for changes and can regenerate the plan when a new build starts. A command that already ran or is already linking can still reflect the earlier plan. [CMake regeneration setting](https://cmake.org/cmake/help/latest/variable/CMAKE_SUPPRESS_REGENERATION.html)

## 4. Configure, build and test in order

Run the normal configure command for the same folder and generator. Inspect the new plan right after that command finishes. Look for the `lesson_total` archive in the target's inputs. Its prefix and extension depend on the compiler toolchain.

~~~powershell
cmake -S . -B build -G Ninja
Select-String -LiteralPath './build/build.ninja' -Pattern '^build lesson_check(?:\.exe)?:' -Context 0,8
~~~

Run the build command after configuration succeeds. Run the test command after the build succeeds.

~~~powershell
cmake --build build --target lesson_check --verbose
ctest --test-dir build -R '^lesson\.total$' --output-on-failure
~~~

Expect one passing test named `lesson.total`. Keep the regenerated link rule and the verbose command with that observation. If the library is absent after generation, check that the edited `CMakeLists.txt` belongs to the configured source folder and that the active target has the link requirement. If the library is listed and linking still fails, check which object defines the reported function and whether the name and declaration agree. If CTest lists zero cases, check the build folder and test name.

## Apply the same reasoning to a product build

In an Umicom Studio build or an Umicom Framework test fixture, identify the symbol in the linker diagnostic and the library that owns it. Compare the project declaration, the generated rule for the failing target and the command that actually ran. If the current source has the dependency but the recorded link command omitted it, keep that older observation with its build folder. At the next normal configure for that folder, check that the generated rule names the library, then build the target and run its focused tests. That gives each result a clear source and build identity.

[Course contents](index.md) · [Previous lesson · Read a Ninja progress record](28-read-a-ninja-progress-record.md) · [Related lesson · Recognize stale tests after a failed build](26-recognize-stale-tests-after-a-failed-build.md) · [HTML edition](../../../courses/learning-build-systems/lessons/29-see-which-library-ninja-will-link.html)

[Next lesson · Match a dry plan to its recipe digest](30-match-a-dry-plan-to-its-recipe-digest.md)
