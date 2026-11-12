<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/24-qualify-the-installed-model-lab.md

PURPOSE:
Qualify the model lab and record its limits

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Qualify the model lab and record its limits

## Prepare a coherent environment

The laboratory README contains the complete command sequence. Use a native Qt 6.5-or-later kit, C++20 compiler, CMake and matching installed Framework SDK. The SDK must export ui_components and the shared branding helper. Replace the example SDK paths with actual installations. Keep compiler family, architecture and runtime compatible. Stop at the first failed command.

## Build and execute deliberately

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking
cmake -S labs/framework/qt-component-model -B build/qt-component-model -G Ninja -DCMAKE_BUILD_TYPE=Debug "-DCMAKE_PREFIX_PATH=C:/sdk/umicom;C:/Qt/6.5.3/mingw_64" -DBUILD_TESTING=ON
cmake --build build/qt-component-model
ctest --test-dir build/qt-component-model -R "^btb[.]qt_component_model[.]contract$" --output-on-failure
.\build\qt-component-model\btb-qt-component-demo.exe
~~~

The demonstration should print save: Save, then Duplicate status: 5; rows: 1 and return zero. CTest should report the btb.qt_component_model.contract entry, whose Qt Test program exercises six cases. These are expected observations for a successful run. Until you execute the commands, record them as unrun.

## Keep the release record precise

| Stage | Record | What it establishes |
| --- | --- | --- |
| Configure | SDK and Qt prefixes, compiler, generator | Dependency selection |
| Build | Source revisions and build output | Compilation and linkage for that kit |
| CTest | Case output and exit result | The exercised memory and signal contracts |
| Demo | Text output and exit code | The supplied command-line journey |
| GUI or device | Separate target and interaction evidence | Only the observed target behavior |

## Extend through the shared boundary

For a future product, add the approved view around this model and keep reusable component policy in Framework. If persistence is required, use the relevant Framework archive and owner publication contract; saving raw C structure bytes is not a portable document format. If a target changes to Android, iOS or the browser, qualify its own SDK and runtime instead of copying this desktop library.

## Exercise and worked answer

A build succeeds but CTest cannot load a Qt DLL. What passed? Compilation and linkage produced an artifact under the recorded configuration. The model tests did not run. Correct the runtime search environment, rerun the test, and preserve both observations. The earlier web/mobile profile lessons remain a separate exercise; this new model lab does not silently replace their qualification.

## Read the source

[labs/framework/qt-component-model/README.md](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-component-model/README.md). Use the matching local revision when offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Check model consistency without launching a GUI](23-model-consistency-without-a-window.md)
