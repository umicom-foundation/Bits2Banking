![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Copy reflected metadata without borrowing its old arrays

This C23 exercise uses Umicom Framework's reflection registry and explicit
snapshot-copy operation. It demonstrates why copying a C struct does not
necessarily produce independent ownership of the memory its pointers describe.
No live application object is inspected, edited or copied.

## What happens

1. Describe two unsigned integer fields with the public reflection macros.
   offsetof and sizeof supply their layout; no offset is guessed by hand.
2. Create a registry limited to one type, module and resource, then register the
   descriptor and request a caller-owned snapshot.
3. Assign that snapshot struct to another allocation. Its arrays are copied,
   but the embedded descriptor pointers still refer to the original arrays.
4. Ask the explicit copy API to copy that shallow snapshot. Expect refusal,
   because its nonempty pointers do not refer to its own arrays.
5. Copy the original through umi_reflection_type_snapshot_copy. Expect its
   populated pointers to refer into the destination's own arrays.
6. Destroy the registry and change the original snapshot. The independent copy
   remains unchanged. Discard the shallow copy before freeing its referenced
   allocation. Never dereference an invalid pointer as a teaching demonstration.
7. Free every caller allocation through a common cleanup path.

Each snapshot has bounded embedded metadata arrays and is deliberately kept off
the thread stack in this exercise. Three calloc calls and the registry creation
are checked for failure. The Framework copy operation itself does not allocate.
Allocating off the stack is not permission to allocate an unlimited number of
snapshots in a real application; use a bounded cache and documented lifetimes.

## Build against an installed SDK

Use an SDK that contains the snapshot-copy symbol and matching headers. Run the
commands from this lab directory, one at a time, stopping on errors. Replace the
example SDK directory with your actual installation. Use the same toolchain and
architecture as the SDK producer.

~~~powershell
cmake -S . -B build-sdk -G Ninja -DCMAKE_PREFIX_PATH=C:/UmicomSDK
cmake --build build-sdk
ctest --test-dir build-sdk --output-on-failure --no-tests=error
~~~

The default path uses find_package(UmicomFramework CONFIG REQUIRED COMPONENTS
reflection) and links Umicom::reflection. It does not clone Framework or embed
its implementation in the application. A missing component is a configuration
error; a missing symbol normally means the selected library is older than the
header or the feature was not included in that SDK. Do not solve either problem
by inventing an application-local copy of the registry implementation.

## Run an explicit source exercise

For focused development checks, a separate build can select an existing matching
Framework source tree. This path compiles only the metadata, registry and thread
owner needed by this exercise. It does not test an installed package, the full
Framework library graph or any application's native UI.

~~~powershell
cmake -S . -B build-source -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom-mirror/Umicom-Applications/framework
cmake --build build-source
ctest --test-dir build-source --output-on-failure --no-tests=error
~~~

Keep source and installed modes in separate build directories. Both use the
Framework branding helper for the supplied SVG resources and Windows ICO;
there is no application-specific logo implementation. This console exercise
requires no GUI deployment or model download.

## Expected output and failures

~~~text
A struct assignment keeps the original array pointer.
The explicit copy refuses a shallow snapshot.
A later source edit leaves the independent copy unchanged.
Independent metadata: 2 fields; first field width
No live application object was copied or modified.
~~~

CTest checks a zero process exit. The executable also checks pointer identity,
refusal status, independent array contents, registry-independent lifetime and
output I/O failure. A successful source exercise does not prove that a separate
installed SDK contains the same source revision.

The descriptor contains type information, not authority to read arbitrary
memory. A field's byte offset does not establish that an application object is
still alive, belongs to this type or may be edited. Range validation, resource
admission, concurrency, permissions and object lifetime remain separate concerns.

Try changing the original field label in the source. Predict why the shallow
descriptor sees that change while its copied inline array does not. Then explain
why the explicit copy sees neither change. This distinction is the central
lesson; a raw memcpy cannot repair pointer relationships automatically.

## Describe resource formats without trusting their contents

The second executable, umicom-reflection-media-labels, registers descriptive
metadata through the same Framework owner. It accepts the legacy umicom.layout
identifier and concrete application/json and image/svg+xml labels. It refuses
parameters and wildcard ranges. It does not parse HTTP headers or open a file.

Use either build mode above, then run the resource-labels CTest case. Expected
output includes three accepted labels, one refused parameterized label, and
confirmation that a refused replacement preserved image/svg+xml. The program
bounds every literal copy, checks Framework status values and destroys its
registry through one cleanup path. Registry capacities are deliberately one.

Read [resource metadata admission](../../../content/lessons/03-native-code/safer-c-programming/43-admit-resource-labels-without-trusting-content.md)
for definitions, commands, failure recovery and the distinction between a label,
a registered media type, decoder support and trustworthy content. A source-only
run cannot establish that a separately installed SDK includes the same behavior.
