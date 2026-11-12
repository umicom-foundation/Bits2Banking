<!--
Umicom Bits2Banking
File: labs/framework/qt-component-model/README.md

PURPOSE:
Build and inspect a Qt model backed by the shared Framework C registry.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# A Qt model over Framework components

This laboratory keeps the component registry in Umicom Framework C and uses C++ only for the Qt model adapter. It stores button specifications in memory. It does not create a window, perform a banking transaction, write a document or contact a service.

## Follow the data

1. A caller supplies two Qt strings to **appendButton** on the model's thread.
2. The adapter rejects embedded zero characters because the C setters accept terminated text. Local UTF-8 byte arrays remain alive throughout the C calls.
3. Framework setters and the registry check byte capacities, component validity and duplicate IDs. A separate heap allocation holds the candidate registry.
4. After admission, the adapter announces one new row, exchanges the registry owner, and completes the notification. Refusals leave the live model unchanged.
5. **data** returns copied Qt values. The adapter never exposes a mutable registry pointer. Row order is the C registry's insertion order.

The entire operation, including refusal notifications, refuses nested mutations with **UMI_STATUS_BUSY**. This prevents a signal listener from changing state before the original call returns. Read-only signal observers can inspect the old or new row count at the appropriate boundary. Signal handlers must not throw or synchronously delete the model. All model access belongs to its owning thread; queue cross-thread work. The early wrong-thread refusal is a diagnostic guard, not permission to race object destruction.

## Prepare and qualify

Use Qt 6.5 or later, CMake 3.26 or later, Ninja, a C++20 compiler and a matching installed Framework SDK that exports **Umicom::ui_components**. The SDK must include the C linkage declarations and component registry admission fixes taught in this module. A Windows build also needs a compatible resource compiler. The exported branding helper embeds the canonical Umicom ICO and stages the shared SVG assets.

Replace both example prefixes below with your actual SDK and native Qt kit. The Qt version in the sample path is illustrative. Match compiler family, architecture, runtime and configuration; a MinGW Qt kit cannot consume an arbitrary MSVC SDK. Make the matching Qt and Framework runtime libraries discoverable in your command environment. Run each command separately and stop on an error.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking
cmake -S labs/framework/qt-component-model -B build/qt-component-model -G Ninja -DCMAKE_BUILD_TYPE=Debug "-DCMAKE_PREFIX_PATH=C:/sdk/umicom;C:/Qt/6.5.3/mingw_64" -DBUILD_TESTING=ON
cmake --build build/qt-component-model
ctest --test-dir build/qt-component-model -R "^btb[.]qt_component_model[.]contract$" --output-on-failure
.\build\qt-component-model\btb-qt-component-demo.exe
~~~

A successful demonstration prints **save: Save**, then **Duplicate status: 5; rows: 1**, and exits with zero. The CTest entry runs six Qt Test cases, with initialization and cleanup reported separately by Qt Test. Expected results are instructions for qualification, not evidence that these commands have already run.

The native kit restriction is intentional. The earlier profile lab remains the course's web/mobile exercise; this installed-SDK model lab does not claim that a desktop archive works on WebAssembly, Android or iOS.

## Read failures by stage

- Configuration: inspect the selected package directories, exported component and Qt Core/Test availability.
- Compilation: check the actual included Framework headers and C++ standard.
- Linking: inspect missing C symbols, runtime/architecture compatibility and the matching library revision.
- Loading: inspect required DLLs before interpreting an absent test result as a model failure.
- Test failure: preserve the case name, input, emitted signal sequence and source revisions. A duplicate refusal should produce no insertion signal.
- Native visual work: remains separate. This headless lab proves no font, DPI, focus, accessibility, desktop deployment or browser/device behavior.

No allocation-failure injection or cross-thread stress test is included. The explicit nothrow registry allocations are handled, but Qt's own allocation behavior is governed by the Qt/runtime configuration. The example does not promise universal out-of-memory recovery.

Continue with [the Learning Qt course](../../../content/courses/learning-qt/index.html#component-model). The Qt references explain [list models](https://doc.qt.io/qt-6/qabstractlistmodel.html), [model publication and thread affinity](https://doc.qt.io/qt-6/qabstractitemmodel.html), [model consistency checks](https://doc.qt.io/qt-6/qabstractitemmodeltester.html) and [signal observation](https://doc.qt.io/qt-6/qsignalspy.html).
