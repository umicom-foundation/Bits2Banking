<!--
Umicom Bits2Banking
File: labs/native/framework-control-inspection/README.md

PURPOSE:
Build and explore a small Framework-owned control discovery journey.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Framework control inspection lab

This small desktop example demonstrates a shared Umicom Framework service. It finds a named control, reveals a tagged control and reports duplicate names. It never sends a trade, saves a document or performs a banking action. Its Confirm button changes only a counter in memory.

## Before you begin

A compiler translates C source into an executable. CMake describes the build and locates its dependencies. Ninja executes the necessary compilation and linking commands. GTK4 supplies the window and controls. The Framework SDK supplies the reusable lookup and reveal services.

Install a C23-capable compiler, CMake 3.25 or newer, Ninja, pkg-config and GTK4 development files. Use an installed Framework SDK containing Umicom::ui_gtk4 and umi_gtk4_automation_find_named_widget_checked. The headers and library must come from the same SDK revision. You need a desktop session to display the window.

## Windows: PowerShell

1. Open PowerShell.
2. Change to the lab folder. Set-Location selects a folder; it does not change any source file.
3. Add the UCRT64 compiler and GTK DLL folder to this terminal's Path.
4. Configure a separate build directory, build, then launch. Stop at the first error.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-control-inspection"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/applications"
cmake --build build --parallel 2
& ".\build\btb-control-inspection.exe"
```

Replace the SDK prefix if you installed it elsewhere. The SDK and this lab must use compatible compiler and GTK dependencies.

## Linux: Bash

Install the development tools through your distribution, then select your installed SDK location:

```bash
cd ~/umicom/Umicom-Bits2Banking/labs/native/framework-control-inspection
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk"
cmake --build build --parallel 2
./build/btb-control-inspection
```

These commands build this lab against installed libraries. They do not rebuild the Framework source tree.

## Follow the experiment

1. Choose Inspect by name while Review is collapsed. Expect Unique control found, Section: collapsed and Confirmations: 0.
2. Choose Reveal review section. Expect the section to open, with no confirmation performed.
3. Click Confirm. Expect Confirmations: 1.
4. Collapse Review and inspect again. The control still exists and the count stays at 1.
5. Enable the duplicate-name checkbox and inspect. Expect More than one matching control.
6. Choose Reveal. The unique Framework tag remains independent of the deliberately duplicated GTK name.
7. Disable the checkbox. Inspect should again find one named control.
8. Close the window. Expect the program to return to the terminal.

These are expected results for your run, not a claim that this source has been qualified on your machine.

## Read the code

- main creates GtkApplication and enters its event loop.
- activate constructs one window and attaches its LabWindow state with an automatic cleanup function.
- window_state retrieves that window's state.
- inspect_clicked calls the checked Framework lookup and reports its status without changing the section.
- reveal_clicked explicitly navigates to the tagged control and reacquires it afterwards.
- confirm_clicked increments the counter after checking its maximum.
- duplicate_toggled changes the second control's GTK name to reproduce ambiguity.
- collapse_clicked changes the expander's state.
- status_text translates a small set of service results into readable messages.

Controls belong to the window tree. Lookup results are borrowed. The object-bound signal connections associate callback lifetime with the window. Extend the example by adding another independently named control, not by copying the Framework traversal into this lab.

## If something goes wrong

If CMake cannot find UmicomFrameworkConfig.cmake, correct CMAKE_PREFIX_PATH. If the ui_gtk4 component is absent, install a Framework SDK that includes it. If linking reports an undefined checked-lookup symbol, ensure the installed header and library contain the same API revision. Missing DLL errors on Windows usually require the matching runtime directories on Path. A headless session cannot demonstrate a visible GTK journey.

If a click has no effect, record which control was visible, whether its section was expanded and the displayed status. Check the corresponding signal connection before changing business logic.

## Lessons

Open [Learning GTK4](../../../content/courses/learning-gtk4/index.html#control-inspection) for the nine-lesson sequence and [the first manuscript](../../../content/lessons/06-umicom/learning-gtk4/12-identify-a-control.md) for a text edition.
