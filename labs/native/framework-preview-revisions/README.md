![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Preview revisions with Framework

This console lab shows why completing an older preview must preserve newer edits.
It calls the real Framework reload service. It does not start a compiler worker,
watch files, load GTK objects or launch a preview process.

Read the [interactive development module](../../../content/courses/learning-gtk4/lessons/21-choose-an-interactive-development-tool.html)
for the terminology, line-by-line walkthrough and exercises.

1. Locate this folder inside Bits2Banking. Use a C23 compiler, CMake 3.25 or later
   and Ninja from one compatible toolchain.
2. From the repository root, configure against an installed SDK. Replace the
   example SDK path with your actual installation:

~~~powershell
cmake -S labs/native/framework-preview-revisions -B build/preview-sdk -G Ninja -DCMAKE_PREFIX_PATH=C:/SDKs/Umicom
cmake --build build/preview-sdk --target btb-preview-revisions --parallel 2
ctest --test-dir build/preview-sdk -V
~~~

Run the commands separately and stop on an error. The SDK must export
Umicom::frontend and include the capture/acknowledge APIs. An older header or
library is not made compatible by copying just one of them.

For focused source study, use a different build folder and explicitly name the
Framework checkout:

~~~powershell
cmake -S labs/native/framework-preview-revisions -B build/preview-study -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/learning/Umicom-Applications/framework
cmake --build build/preview-study --target btb-preview-revisions --parallel 2
ctest --test-dir build/preview-study -V
~~~

This mode compiles only the production reload service and its text helper. It
does not qualify SDK discovery, installed libraries or GUI deployment.

Expected walkthrough output:

~~~text
Captured 2 paths at generation 1
Applied generation 2: acknowledged=1 pending=2
Pending counter.c revision 11
Pending dialog.ui revision 30
Applied generation 3: acknowledged=2 pending=0
~~~

The host owns both allocated objects and frees them on every exit. Framework
borrows the pointers during calls. The snapshot stays unchanged until
acknowledgement or discard. Revisions must change when content changes; calls
must be serialised. Failed work must not be acknowledged.

The path names represent events in memory. No counter.c, theme.css or dialog.ui
is read or written by this lab. Change the revision numbers and predict the
pending list before rerunning the test.
