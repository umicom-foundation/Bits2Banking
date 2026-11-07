# Test the boundary between a program and the Kernel

A program can ask a kernel to copy bytes, but an address supplied by that program is not automatically trustworthy. The kernel must check whether the entire range belongs to the caller and permits the requested access. This lab uses Umicom Kernel's existing host checks to study that decision without booting a machine.

## Setup recap

You need Umicom Kernel sources, a C23 compiler, CMake and Ninja. Use [terminal setup](../../learning-c/terminal-lab.md) for tool installation and command basics. On Windows, add `C:\msys64\ucrt64\bin` to the current PowerShell PATH. On Linux, use the native compiler for your host. This exercise runs a test executable on the host, with test-owned memory representing physical pages. It does not boot a guest or prove hardware behaviour.

A page is a fixed-size region used by the memory manager. A virtual address is the address a program uses; a mapping connects it to backing storage and permissions. Read [native Kernel and host models](01-native-kernel-and-host-models.md) if these terms are new.

## 1. Find the files

In `umicom-kernel/tests/user_memory/CMakeLists.txt`, inspect the source list and test cases. The executable uses the actual Kernel memory implementation with a controlled fixture. The fixture supplies known pages so each test can change one condition.

Write this diagram on paper:

```text
request: start + byte count + access
    → reject overflow
    → inspect every covered page
    → check ownership and permissions
    → copy only after validation
```

Checking only the first page is insufficient. A range can begin in writable memory and finish in a read-only or unmapped page.

## 2. Build the isolated host check

PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S 'C:/umicom/umicom-kernel/tests/user_memory' -B 'C:/umicom-learning/kernel-user-memory' -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build 'C:/umicom-learning/kernel-user-memory' --parallel 2
ctest --test-dir 'C:/umicom-learning/kernel-user-memory' -R '^kernel\.user_boundary\.(cross-page-read|cross-page-write|span-write-readonly-second|range-wrap|partial-destination)$' --output-on-failure --no-tests=error
```

Bash:

```bash
cmake -S "$HOME/umicom/umicom-kernel/tests/user_memory" -B "$HOME/umicom-learning/kernel-user-memory" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build "$HOME/umicom-learning/kernel-user-memory" --parallel 2
ctest --test-dir "$HOME/umicom-learning/kernel-user-memory" -R '^kernel\.user_boundary\.(cross-page-read|cross-page-write|span-write-readonly-second|range-wrap|partial-destination)$' --output-on-failure --no-tests=error
```

The expected selection contains five tests. A refusal test passes when an invalid request is correctly refused; it does not mean the Kernel allowed that request.

## 3. Explain each outcome

| Case | Question it investigates |
|---|---|
| cross-page-read | Can a valid read cross a page boundary? |
| cross-page-write | Can a valid write cross a page boundary? |
| span-write-readonly-second | Is a request refused when a later page forbids writing? |
| range-wrap | Is arithmetic wrapping around the address range rejected? |
| partial-destination | Is the destination protected from incomplete copying? |

Locate each name in the test source. For one successful and one refused case, record the initial bytes, requested range, expected result and final bytes. This four-part description makes a useful regression test: a test kept to prevent a repaired defect returning.

## Exercise and troubleshooting

Draw two adjacent pages and place a four-byte request two bytes before their boundary. Label the second page read-only. A read may be permitted if ownership and mapping are valid; a write must be refused. Explain why checking the first two bytes alone would be unsafe.

If no tests match, check the checkout and spelling rather than removing `--no-tests=error`. A compile failure belongs to the host test build; capture its first diagnostic before trying QEMU. Passing host checks should later be complemented by native boot and fault tests. Continue with [native program contract discovery](16-discover-the-native-program-contract.md), or return to the [Kernel course](index.md).

[Previous: Inspect file bytes in hexadecimal](14-inspect-binary-files.md)
