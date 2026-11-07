# One C activity, several interfaces

This lab extends the existing [Framework activity](../framework-activity/README.md). That project owns the exercise-count rule. These adapters translate inputs and results without copying that rule.

## Source map

- `../framework-activity/activity.c`: the existing count rule, using Framework's `UmiStatus` contract.
- `bridge.c`: signed platform input becomes a checked call; a result of -1 means no change.
- `button.c`: caller-owned state detects a newly pressed button.
- `test_bridge.c`: negative values, zero, the last accepted value and oversized values.
- `test_button.c`: held inputs, release, independent devices and rejected updates.
- [Android](../../mobile/android-framework-activity/README.md), [iPhone](../../mobile/iphone-framework-activity/README.md) and [browser](../../web/framework-activity/README.md): presentations of the same model.

## Build the host checks

Install a C23 compiler, CMake and Ninja. Obtain an installed Umicom Framework SDK built for the same operating system and architecture. In PowerShell, from the Bits2Banking checkout:

~~~powershell
cmake -S labs/native/activity-adapters -B build/activity-adapters -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/applications"
cmake --build build/activity-adapters
ctest --test-dir build/activity-adapters --output-on-failure --no-tests=error
~~~

On Linux or macOS use the same commands with your installed SDK prefix, for example `-DCMAKE_PREFIX_PATH="$HOME/umicom-sdk"`. Run one command at a time; stop on failure. A successful run reports two passing adapter checks. This is an expected result, not a report of a completed run.

If CMake cannot find `UmicomFrameworkConfig.cmake`, locate that file in the installed SDK and use its installation prefix. Do not substitute a Windows library when compiling for another target.

## Trace a button

Start with `BtbActivityButton state = {0};`. Feed false, true, true, false, true. The completed counts should be 0, 1, 1, 1, 2. The repeated true is a held button. A physical switch can bounce between true and false very quickly; this model does not debounce electrical input. A board-specific GPIO and timer adapter must do that before calling this function.

The model has no heap allocation, device registers, interrupts or threads. Use one owner for each state object. This host exercise does not flash a board or demonstrate a working microcontroller port.

## Check the boundary

The browser, Android and iPhone examples compile the existing activity source for their own target. Their first lab uses Framework status declarations, not the full desktop SDK. Adding hashing, storage or other Framework services requires target-built libraries and a review of their platform dependencies. A successful counter is not evidence that GTK4 or every Framework component runs on a phone.

