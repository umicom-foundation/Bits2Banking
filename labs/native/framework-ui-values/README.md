![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Own UI values with the installed Framework SDK

This C23 client uses real Framework value, property, reactive store and archive APIs. It has six scenarios that explain ownership and refused publication without creating a native window or executing a product command.

Read the source beside the paired lessons in the Framework development course. The application does not implement its own string container, property storage or archive encoder.

## Build the matching installed client

1. Qualify and install the corresponding Framework source through the owner workflow.
2. Confirm that the installed SDK includes the ui component and the value-admission APIs.
3. Run each command separately and stop on errors. Adjust the prefix if your installation differs.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-ui-values"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
.\build\btb-framework-ui-values.exe alias
~~~

These commands have not been executed for this authored laboratory. The expected result is six passing checks, each comparing complete output, exit zero and an empty error stream.

## Follow the six scenarios

| Argument | Expected observation | Boundary |
| --- | --- | --- |
| alias | Title becomes Umicom | Input may refer to the existing string |
| refused-title | Oversized text leaves integer 42 intact | Failure preserves the whole previous value |
| publish | Caller changes; stored title stays Accepted title | The bag owns an independent copy |
| invalid-value | Unsupported kind is refused; one property remains | Admission precedes publication |
| revision | Put is refused; ready stays readable at UINT64_MAX | Revisions never wrap into a new observation |
| archive | Invalid kind preserves output; valid integer can be measured | Archives reuse owner validation |

For example, run:

~~~powershell
.\build\btb-framework-ui-values.exe revision
~~~

Expected output:

~~~text
Status: CAPACITY_EXCEEDED
Readable value: ready
Revision: 18446744073709551615
Shared value observations only; no GUI or command execution.
~~~

The revision scenario deliberately sets the public record to its boundary inside this isolated fixture. Production clients must not edit live revisions to bypass admission. A new owner lifetime requires a separate, deliberate application decision.

## Inspect ownership and cleanup

The property bag is created and destroyed with Framework APIs. The large fixed-capacity reactive store is heap allocated, initialized by Framework and freed after its borrowers have finished. Caller value records remain separate from stored copies.

Every observation is checked before it is printed as an expected outcome. A failure goes through cleanup and exits unsuccessfully. An expected refusal can therefore produce a successful laboratory exit: the scenario verifies that the refusal preserved state, rather than pretending the refused operation succeeded.

## Branding and presentation

The installed Framework branding helper supplies approved SVG assets and embeds the Windows ICO through RC. This console client requests NO_RUNTIME_DEPLOYMENT because it does not launch GTK. The course uses the approved shared learning stylesheet, including Segoe UI and Cascadia Code fallbacks.

Inspect resource staging and executable metadata during owner qualification. A source reference to the correct logo is not evidence that every operating system rendered it correctly.

## Diagnose a mismatch

If a symbol is missing, check that headers and libraries come from the same updated installed SDK. Do not mix a new header directory with an old binary library. If refused-title changes the integer, or invalid-value changes a property, retain the complete output and inspect the SDK's value publication implementation.

If the revision scenario succeeds in writing a replacement, the installed store may still recycle the maximum revision. Do not weaken the check to accept that result. Confirm source and installation identity before rebuilding.

Compiler, linker, scenario execution, native resources and website rendering remain owner-run and unverified. Passing these six cases would qualify this installed client; it would not by itself qualify Studio, Trader or a native UI workflow.
