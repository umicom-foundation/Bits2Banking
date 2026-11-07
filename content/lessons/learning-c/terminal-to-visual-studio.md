# Lab: move a working C program into Visual Studio

An IDE combines an editor, navigation, build controls and debugging facilities. It should make the workflow easier to see. The compiler still translates the program, and saving a file still does not build it.

## Setup recap

This Windows lab starts with GCC, CMake, Ninja and GDB installed through MSYS2 UCRT64. Confirm their `--version` commands in PowerShell. If you have not installed them, use [the terminal setup lab](terminal-lab.md). Obtain a local Bits2Banking source checkout and choose a practice folder. The source example used here is independent of the full Umicom Applications build.

## 1. Install the IDE

Follow [Microsoft's Visual Studio installation guide](https://learn.microsoft.com/en-us/visualstudio/install/install-visual-studio?view=visualstudio). Select **Desktop development with C++**, which includes native development and CMake integration. Choose an edition appropriate to your licence. This course uses Visual Studio IDE on Windows; Linux users can continue with the same CMake commands in bash and a local editor.

## 2. Copy and open the existing lab

In PowerShell:

```powershell
New-Item -ItemType Directory -Force 'C:\umicom-learning'
Copy-Item -Recurse 'C:\umicom\Umicom-Bits2Banking\labs\native\first-c-programs' 'C:\umicom-learning\first-c-programs'
Set-Location 'C:\umicom-learning\first-c-programs'
```

Use the copy command only when its destination does not already exist. In Visual Studio choose **File → Open → Folder** and open this practice folder. Open `greeting.c` from the folder view. Keep any automatic IDE configuration separate from the `build-ucrt` folder used below; a build cache belongs to one compiler and source location.

## 3. Configure, build and test in the IDE terminal

Choose **View → Terminal** and select PowerShell. Enter each command separately and stop on errors:

```powershell
Set-Location 'C:\umicom-learning\first-c-programs'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build-ucrt -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-ucrt --target btb-first-greeting
.\build-ucrt\btb-first-greeting.exe
ctest --test-dir build-ucrt -R '^bits2banking\.first_c\.greeting$' --output-on-failure --no-tests=error
```

`-S` identifies source, `-B` a separate generated build directory. The generator `Ninja` schedules work. The explicit compiler preserves this lab's UCRT64 toolchain. `--target` names one executable. `-R` selects the named test using a regular expression; the anchors require its complete name. Expect `Hello, learner.` from the executable and one executed passing test if the unmodified lab builds correctly.

Do not assume the IDE's toolbar is using this same compiler. Before switching to toolbar builds, configure a matching preset and verify its output. [Microsoft's CMake documentation](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170) describes that integration.

## 4. Make a visible change

Change the greeting string in `greeting.c` to a sentence of your choice. Save with Ctrl+S. Rebuild the same target and run it. The old output test should fail because its expected text remains in `expected/greeting.txt`. Decide whether the changed output was intended. Either restore the original source or update the expected file deliberately to describe the intended result. Rebuild and rerun the selected test.

## 5. Pause in a compatible debugger

The executable built above contains GCC debug information. Use its matching GDB in the terminal:

```text
gdb .\build-ucrt\btb-first-greeting.exe
break main
run
next
continue
quit
```

`break main` requests a pause at the entry function. `run` starts it, `next` advances over a source line, and `continue` resumes. Exact line numbers depend on the file. An IDE's default Microsoft debugger is not automatically a debugger for this GCC build. Configure compatible integration explicitly before relying on its debug button.

## 6. Broaden the check when needed

Build the remaining lab targets with `cmake --build build-ucrt`, then run `ctest --test-dir build-ucrt --output-on-failure --no-tests=error`. The current lab registers eight output checks and two contract checks: ten total. A failure or skip is not a pass. The focused greeting check is useful after a greeting-only change; a shared counting-rule change requires its affected contract checks too.

Continue with [the existing Visual Studio product guide](../05-engineering/learning-visual-studio.md) for opening a real Umicom repository, or [the Framework SDK consumer lab](../umicom-development/sdk-practical-lab.md) to build a small client using installed shared libraries.

[Learning C contents](index.md)
