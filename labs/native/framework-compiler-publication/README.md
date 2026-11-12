![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Compiler publication laboratory

Use an installed Umicom Framework SDK to explore request metadata, complete command publication and supported policy dialects. The client is C23 and links Umicom::compiler. Its provider names describe proposed drivers; it starts none of them.

Read the [compiler publication lessons](../../../content/courses/umicom-development/index.html#compiler-publication) after the compiler preview module. Prerequisites are C arrays, structures, borrowed pointers, returned status values and a matching installed SDK.

1. Qualify and install the matching Framework headers and libraries.
2. Select the matching C compiler and use a fresh laboratory build directory.
3. Configure with the actual installation prefix, then build and run the four observation cases.
4. Stop on a failed command and retain its complete output. The following commands are for owner execution and have not been run for this authored lab.

~~~powershell
cmake -S C:\umicom\Umicom-Bits2Banking\labs\native\framework-compiler-publication -B C:\umicom\_local\build\compiler-publication-lab -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=C:\umicom\_local\install\framework
cmake --build C:\umicom\_local\build\compiler-publication-lab
ctest --test-dir C:\umicom\_local\build\compiler-publication-lab --output-on-failure
~~~

Adjust the installation prefix to the SDK you actually qualified. Missing checked-snapshot, explicit-directory or policy declarations indicate a source/SDK mismatch, not permission to substitute an older API silently. The application branding helper supplies the canonical Umicom Windows icon and version resource. This console client does not request automatic runtime deployment.

| Scenario | Observation |
| --- | --- |
| keys | Directory, debug flags and collection roles distinguish request metadata |
| transaction | A refused database update preserves the complete centre and previous output |
| refresh | Replanning one source updates its command and keeps each owner's pointers independent |
| policy | MSVC spelling is explicit; unsupported sanitizer and reproducibility intents are refused |

Run an individual case with btb-framework-compiler-publication.exe and the scenario name. Every observation line follows a checked condition. The CTest script compares all output, an empty error stream and the process result. Cases that use the centre allocate its large fixed collections on the heap; the transaction case also allocates a complete comparison owner. Allocation refusal is reported instead of continuing with missing storage.

A successful keys case does not prove a cache artifact is fresh: source contents, dependencies, driver versions and environment are not in that metadata key. A successful transaction case demonstrates serialized memory publication, not crash recovery. A successful policy case checks strings and refusal behavior, not installed sanitizer support.

If a case fails, record the SDK revision, compiler, scenario and complete diagnostic. Confirm the same installed headers and libraries are selected. Then compare the narrower Framework regression before changing the lab's expected output. Keep malformed input and intended unsupported-policy refusal distinct from a broken test.

This lab is authored and awaits owner execution. No compiler driver, application, linker, sanitizer runtime or native UI was launched during its preparation.
