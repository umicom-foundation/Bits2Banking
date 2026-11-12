![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Own compiler metadata and argument plans with Framework

This C23 laboratory uses the installed Umicom compiler component. Seven small scenarios demonstrate target and ABI aliasing, malformed catalogue admission, refused request edits, late plan failures, borrowed pointer rebasing and exhausted revisions.

The client builds metadata. It does not launch a compiler, inspect an SDK installation, link a target program or launch an application. Read it alongside the compiler ownership module in the Framework development course.

## Build against the matching installed SDK

1. Qualify and install the corresponding Framework source through the owner workflow.
2. Confirm that the prefix contains the compiler component and the request/plan storage APIs.
3. Run each command separately and stop on errors. Change the prefix if your installation differs.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-compiler-ownership"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
.\build\btb-framework-compiler-ownership.exe views
~~~

These commands have not been executed for this authored laboratory. The expected result is seven passing CTest cases. Each compares complete output, exit zero and an empty error stream.

If a symbol is missing, first check that headers and libraries came from the same Framework installation. A new include directory combined with an older library cannot qualify the added API.

## Follow the seven scenarios

| Argument | Expected observation | Shared boundary |
| --- | --- | --- |
| target | A rejected replacement retains the accepted triple | Atomic initialization and borrowed text |
| abi | Borrowed identifier and target survive replacement | Metadata ownership and existing defaults |
| catalogue | An oversized count is refused without changing bytes | Count admission before lookup |
| request | Oversized option is refused; a borrowed option is copied | Incremental failure preservation |
| publication | A late argument failure retains the previous plan | Whole-plan publication |
| views | Published and copied views belong to their receiving plan | Pointer rebasing and lifetime |
| revision | Append is refused while the retained argument stays readable | Finite observation identities |

For example:

~~~powershell
.\build\btb-framework-compiler-ownership.exe publication
~~~

Expected output:

~~~text
Late argument failure: previous plan retained
Previous argument: previous
Compiler metadata only; no compiler process or application launch.
~~~

The client checks those invariants before printing them. An expected refusal can therefore produce a successful laboratory exit; the refused operation itself has not succeeded.

## Read the ownership choices

Large request, plan and registry records use static fixture storage to avoid depending on the default thread-stack allowance. This teaching program runs one scenario serially. A concurrent product needs its established owner and synchronization rules; shared static globals are not a general application design.

The catalogue and revision examples deliberately inject boundary metadata into isolated records. Do not clamp counts or reset live revisions to conceal a producer error. Correct the producer or establish a deliberate new owner lifetime.

A plan owns its argument bytes but exposes borrowed pointers into them. After a value copy, call umi_compiler_plan_arguments on the copy. Consume exactly argument_count entries; the view does not promise a NULL sentinel. Do not retain it beyond the receiving plan's lifetime.

## Branding and visible evidence

CMake uses the installed umicom_apply_application_branding helper. It stages approved SVG resources and embeds the approved Windows ICO through RC. NO_RUNTIME_DEPLOYMENT keeps this console lab from requesting GTK runtime deployment.

The paired lessons use the shared approved learning stylesheet with Segoe UI and Cascadia Code fallbacks. Inspect the staged assets and native executable metadata during owner qualification. Source references and hashes do not demonstrate how a particular operating system or renderer displayed them.

## Diagnose a mismatch without weakening the check

If publication alters the retained argument, confirm that the installed provider planner contains the staged publication change. If views still point into the original plan, inspect pointer rebuilding after publication and copying. If an exhausted append succeeds, check source and installation identity before assuming the boundary policy changed.

Preserve complete commands, output and tested revisions. Stop after a failed build so an older executable cannot be mistaken for the current client.

Compiler, linker, seven-case execution, resource rendering and website rendering remain owner-run and unverified. A future pass would qualify this installed metadata client only. Actual provider action mappings, tool invocation, allocation-failure injection and Studio workflows require separate evidence.
