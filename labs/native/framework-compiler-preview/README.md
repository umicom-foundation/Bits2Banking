![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Compiler preview laboratory

Build a C23 client of the installed Framework compiler service. This laboratory compares action mappings, complete driver identities, ordered JSON arguments and refused output publication. It does not start a compiler, read its proposed source, create an object file or qualify a toolchain.

Read the four [compiler preview lessons](../../../content/courses/umicom-development/index.html#compiler-preview) after the compiler ownership module. Prerequisites are C structures, arrays, pointers, status handling and a matching installed Framework SDK. The executable uses canonical Umicom branding through the installed CMake branding helper, including Windows icon/version resources. Runtime deployment is deliberately disabled for this console client.

1. Build and install the matching Framework SDK through your normal owner qualification workflow.
2. Use a fresh client build directory and the actual SDK prefix. The commands below are examples for the owner to execute; they have not been run for this authored laboratory.
3. Build the client, then run its four observation cases. Stop on a failed command and retain the complete diagnostic output.

~~~powershell
cmake -S C:\umicom\Umicom-Bits2Banking\labs\native\framework-compiler-preview -B C:\umicom\_local\build\compiler-preview-lab -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=C:\umicom\_local\install\framework
cmake --build C:\umicom\_local\build\compiler-preview-lab
ctest --test-dir C:\umicom\_local\build\compiler-preview-lab --output-on-failure
~~~

Adjust the prefix to your installed SDK. Select the matching C compiler/toolchain in your shell before configuration. A stale SDK can lack the new action query or JSON declaration even when the mirror source contains it.

| Scenario | Observation |
| --- | --- |
| actions | Check and compile have different arguments; archive refusal keeps the previous plan |
| identity | An overlong driver is refused; a nonempty identity is not verified availability |
| json | Quotes, backslashes and spaces preserve argument boundaries |
| refusal | Short capacity and invalid UTF-8 keep all prior output bytes |

Run an individual scenario with the client executable and its name. Successful cases print their observations followed by **Preview metadata only; no compiler process was started.** Each printed statement follows a checked condition. The CTest script compares exit status, all output and empty standard error.

For native CLI integration, separately build the matching native Umicom tool and inspect **umicom compiler plan --help**. Its compiler preview is a different executable from this laboratory; do not infer its routing or Windows argument conversion from a library-only client pass. The Framework tests **framework.compiler.plan_json** and **framework.cli.compiler** cover separate layers.

If an assertion fails, record the SDK revision, client compiler, scenario, exit status and full output. Fix the failing boundary before moving to a driver execution experiment. A serialization failure preserves an in-memory output buffer. A later broken pipe can leave a partial stream, so JSON consumers also require complete parsing and a successful producer exit.

This laboratory and its checks are authored and await owner execution. Native UI appearance, compiler standard support, linking, application launch and generated machine code remain separate qualification work.
