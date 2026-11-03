# Build your first application with Umicom Framework

This project is an exercise counter. A console program prints a count, and an optional GTK4 window lets you increase it with a button. Both use the same C function. It is deliberately small so you can follow a change from source text to a visible result.

Before starting, work through [Learning C](../lessons/learning-c/index.md), including functions, pointers and separate source files. Then read the first module of [Umicom Framework Development](../lessons/umicom-development/index.md). This guide joins those lessons into one practical route.

## 1. Find the example

Open `labs/native/framework-activity` inside Bits2Banking. Make a practice copy in a folder you choose before experimenting. A repository is a folder whose changes are tracked by a version-control tool; keeping the original example makes comparison easier.

| File | What it contains | What to look for |
| --- | --- | --- |
| `activity.h` | The public declaration | The input count, output pointer and returned status |
| `activity.c` | The shared counting rule | Validation before changing the output |
| `console.c` | The console program | A call to the shared function and readable output |
| `window.c` | The GTK4 window | A button event calling the same function |
| `test_activity.c` | Six checks of the rule | Normal, boundary and invalid inputs |
| `CMakeLists.txt` | Build relationships | Which source files belong to each target |
| `README.md` | The example's purpose and limits | Expected results and links to setup instructions |

## 2. Follow the shared rule

`BtbActivityAdvance` receives the current count and a place to store the next count. A pointer is the way C refers to that storage. The function returns a Framework status: a value describing success or the kind of failure.

| Input | Expected status | Output |
| --- | --- | --- |
| 0 | OK | 1 |
| 999 | OK | 1000 |
| 1000 | Capacity exceeded | Unchanged |
| Above 1000 | Invalid argument | Unchanged |
| No output storage | Invalid argument | No write |

The output must remain unchanged on failure. That rule is part of the interface, not a detail for a particular window. Read the conditions in `activity.c` and trace one row at a time before editing anything.

## 3. Prepare the tools

Use the [Windows development setup](windows-development.md) and an installed Framework SDK that supplies the base component. An SDK contains headers, libraries and package information for building another program. This exercise consumes that package; it does not copy Framework source into the lab.

The [CMake lesson](../lessons/umicom-development/03-introduction-to-cmake.md) explains each command below. Replace the paths if your checkout or SDK is elsewhere. Run one stage at a time and stop if it reports an error.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\framework-activity" -B ".\build\framework-activity" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework;C:/msys64/ucrt64" -DBUILD_TESTING=ON
cmake --build ".\build\framework-activity" --parallel 2
ctest --test-dir ".\build\framework-activity" --output-on-failure --no-tests=error
& ".\build\framework-activity\btb-activity-console.exe"
```

Configure prepares the build rules. Build compiles and links the program. Test runs the six registered checks. Run starts the console program, whose expected output is `Completed exercises: 1`. These are expected results to check on your computer.

## 4. Make and inspect a small change

1. In your practice copy, open `console.c`.
2. Find the initial completed count. Change zero to two, leaving the shared rule unchanged.
3. Predict the result before building: one successful increment should produce three.
4. Save the file and build the same folder again. The build tool uses its dependency records to rebuild affected targets.
5. Run the console program. Compare its actual line with your prediction.
6. Run the tests again. Their inputs have not changed, so their six expectations remain the same.

If the result is still one, check that you saved the edited file and launched the executable from the matching build folder. A source file and a previously built program are separate files.

## 5. Understand a failure

Temporarily remove the semicolon from the assignment in your practice copy, then build. Read the first compiler error and the path and line it names. Restore the semicolon and build again. Do not launch an old executable as though the failed build succeeded.

Next read the `full` case in `test_activity.c`. It checks that a count of 1000 is refused and its output is unchanged. A program can compile successfully while returning the wrong result; this is why tests check behaviour as well as syntax.

For interactive debugging, place a breakpoint at `BtbActivityAdvance` using an IDE with a working debugger configuration. Step through the condition checks and inspect `current`, `next` and the output value. If your Studio build cannot start that debugger, continue with the console and test commands while recording the debugger error. A menu item alone is not evidence of a working debugger.

## 6. Add the window

Follow [Introduction to GTK4](../lessons/umicom-development/05-introduction-to-gtk4.md) to enable `BTB_ACTIVITY_GTK4`. A widget is an interface element. A signal reports an event. A callback is a C function connected to that event.

```text
Button click → Completed callback → BtbActivityAdvance
                                      ↓
                               status and count
                                      ↓
                                  label text
```

Start the window, click once and expect one. Click twice more and expect three. Close and reopen it; expect zero because this example does not save its count. The six logic tests do not replace this interaction check.

## 7. Extend without duplicating the rule

As an exercise, design a reset action. Write its contract first: which input it accepts, which output it produces and what happens on failure. Add independent checks before connecting a button. Put reusable rules in a shared service; keep a callback responsible for collecting input and presenting its result. This is the same separation used between Framework and Umicom applications.

Return to the [development course](../lessons/umicom-development/index.md) for the next module. The larger reader, workspace and financial examples are later studies, not requirements for completing this counter.
