<!--
Umicom Bits2Banking
File: content/simple-steps/build-project.md

PURPOSE:
Build and test the coffee project using CMake and CTest.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# 11. Build and test the project with CMake

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use the original practice folder from Step 3. This exercise works with your local copy of `coffee.c`.

1. Go to the project and open a new file for its build instructions.

   ```powershell
   Set-Location -LiteralPath (Join-Path $env:USERPROFILE 'Bits2Banking-Practice\coffee-timer')
   notepad .\CMakeLists.txt
   ```

2. Save the following as `CMakeLists.txt`. `add_executable` names the program and its source file. `set_target_properties` selects C23. The last two lines register a check that runs the program and expects a successful exit.

   ```cmake
   cmake_minimum_required(VERSION 3.21)
   project(Coffee LANGUAGES C)
   # Keep the build pointed at the same source you compiled by hand.
   add_executable(coffee coffee.c)
   set_target_properties(coffee PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED YES C_EXTENSIONS NO)
   # Give CTest a named check that runs the built program.
   enable_testing()
   add_test(NAME coffee_runs COMMAND coffee)
   ```

3. Run these lines in PowerShell. Adjust `$ucrt` if you installed MSYS2 to a different folder in Step 4. Run each command separately and stop if it reports an error.

   ```powershell
   $ucrt = 'C:\msys64\ucrt64\bin'
   $env:Path = "$ucrt;$env:Path"
   & "$ucrt\cmake.exe" -S . -B build -G Ninja "-DCMAKE_C_COMPILER=$ucrt\gcc.exe" "-DCMAKE_MAKE_PROGRAM=$ucrt\ninja.exe"
   & "$ucrt\cmake.exe" --build build
   & "$ucrt\ctest.exe" --test-dir build --output-on-failure
   ```

4. Look for `coffee_runs` and `Passed`. Then check the number yourself.

   ```powershell
   .\build\coffee.exe
   ```

   The program prints 180 seconds if you kept the change from Step 7, or 240 seconds if you set it back to four minutes.

[Previous step — Clone your repository](git-clone.md) · [Next step — Plan a robot’s route](maze.md) · [Full CMake course](../courses/learning-cmake/index.html)
