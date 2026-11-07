# How a program asks the Kernel for a service

A program needs help to do some jobs. It may need to read a file, send a message or finish running. The Kernel controls those services and checks which requests are allowed. In this lesson we will follow one small, read-only request in the real Umicom Kernel: asking which native interface is available.

You can begin by reading the explanation and diagrams. The optional practical section uses the Kernel's existing tests; it does not ask you to write a kernel or change your computer's operating system. If files, memory and instructions are new to you, start with [Introduction to Computers](../../../courses/learning-computer-architecture/index.html). For C functions and numbers, use [Learning C](../../../courses/learning-c/index.html).

## 1. Understand the two sides

A **program** is a set of instructions. A running instance is often called a **process**. Its own memory contains its instructions and working data. The **Kernel** manages protected resources and decides how programs may use them.

**Privilege** means authority to perform an operation. A normal program must not gain authority just by writing a number that happens to resemble a Kernel address. Instead it makes a **system call**, also called a **syscall**: a structured request across a controlled boundary.

The experimental Umicom RV64 monitor currently handles these calls in machine mode, or M-mode. Its native programs execute in user mode, or U-mode. RV64 means a 64-bit RISC-V instruction environment. This is a specific experimental execution model; it does not describe how every operating system handles calls.

 <svg viewbox="0 0 760 265" role="img" aria-labelledby="call-title call-description" style="max-width:100%;height:auto">
<title id="call-title">A request crosses the checked Kernel boundary and returns</title>
<desc id="call-description">A user program places a request in registers. ECALL enters the monitor, which checks origin, budget and instructions. A scalar result returns to the program.</desc>
<rect x="5" y="15" width="215" height="150" rx="12" fill="#e3f5f4" stroke="#087784"></rect>
<rect x="275" y="15" width="210" height="150" rx="12" fill="#f3f7fb" stroke="#203247"></rect>
<rect x="540" y="15" width="215" height="150" rx="12" fill="#e3f5f4" stroke="#087784"></rect>
<g font-family="Segoe UI,Arial,sans-serif" font-size="18" fill="#192c3e" text-anchor="middle">
<text x="112" y="45">User program</text><text x="112" y="82">a7 = request number</text><text x="112" y="110">a0 = selector</text><text x="112" y="138">a1 = 0, a2 = 0</text>
<text x="380" y="45">Checked boundary</text><text x="380" y="82">Origin and budget</text><text x="380" y="110">Executable instruction</text><text x="380" y="138">Safe continuation</text>
<text x="647" y="45">Kernel query</text><text x="647" y="82">Read contract value</text><text x="647" y="110">No user buffer</text><text x="647" y="138">No new authority</text>
<text x="380" y="220">The result returns in a0; the program continues after ECALL.</text>
</g>
<path d="M225 90 H265 M257 84 L265 90 L257 96 M490 90 H530 M522 84 L530 90 L522 96" fill="none" stroke="#087784" stroke-width="3"></path>
</svg>

 The drawing describes the implemented request path. It is an explanatory diagram, not a screenshot of a running application.

## 2. Learn what the registers carry

A **register** is a small named storage location inside the processor. Registers hold values the processor is working with. Names such as `a0` identify particular registers; they are not filenames or memory addresses.

Umicom's basic native syscall convention uses `a7` for the operation number and `a0`, `a1` and `a2` for three arguments. An **argument** is an input to an operation. The RISC-V `ecall` instruction transfers control to the monitor. This controlled transfer is a **trap**; in this case it is deliberate, not evidence that the program crashed.

An **application binary interface**, abbreviated **ABI**, is the agreement that lets compiled code communicate. It defines register use, operation numbers and data layouts. A C header describes names for the compiler; the ABI also describes what happens when the compiled instructions run.

| Register | Discovery request | Example |
| --- | --- | --- |
| `a7` | Choose ABI discovery | 3 |
| `a0` | Choose the version value | 0 |
| `a1` | Reserved argument | 0 |
| `a2` | Reserved argument | 0 |

**Reserved** means the caller must use the defined neutral value, zero. It does not mean the value is ignored. Nonzero reserved arguments are refused so a typo cannot silently acquire a meaning in a later interface.

## 3. Ask a question without passing a pointer

The real header `include/umicom/kernel/user_abi.h` gives readable names to the numbers. The existing wrapper moves C arguments into the required registers and executes the instruction. In `kernel/user_payload.c`, find this call:

```text
observation->abiVersion = UmicomRiscvUserSystemCall(
    UMICOM_USER_CALL_ABI_QUERY, UMICOM_USER_ABI_QUERY_VERSION, 0U, 0U);
```

Read it from right to left once: the function receives the operation, selector and two zero values. Its result is assigned to `observation->abiVersion`. The arrow accesses a field through a pointer to the program's own observation record. That record is not passed as an argument to this syscall.

`0U` is zero written as an unsigned integer, a number type that does not represent negative values. A **selector** chooses which one of several supported answers is requested. Discovery returns a single number; it does not copy a structure to an address supplied by the program.

The version result is `0x00010000`. The `0x` prefix indicates hexadecimal, a base-16 number system. This value is 65,536 in ordinary decimal notation. Its upper 16-bit field contains major version 1 and its lower 16-bit field contains minor version 0. The number identifies an interface contract, not a release date or build identifier.

## 4. Check compatibility before asking about features

An older Kernel that does not implement discovery returns the existing *unknown call* result, 1. A feature answer can also legitimately be 1. Therefore the program must check VERSION first. Without that check, it could mistake an error for a feature.

After establishing compatibility, selectors can ask for:

- The compiled optional service routes.
- The native register word width: 64 bits.
- The byte order: little-endian, encoded as 1.
- The base page size: 4,096 bytes.
- The COPY operation's maximum: 64 bytes.
- The per-session syscall budget: 32 calls.

A **byte** contains eight bits. **Little-endian** describes how the bytes of a multi-byte number are ordered: the least significant byte comes first. A **page** is a fixed-size unit used for memory mappings. A **budget** limits work: even a read-only question counts as a syscall, and repeated questions cannot run indefinitely.

An unknown selector or a nonzero reserved argument returns a refusal with every bit set: `0xffffffffffffffff`. A zero feature mask is a successful answer meaning that none of the optional routes is compiled. Success and failure must be interpreted using the operation's rules, not a guess that every nonzero number is an error.

## 5. Distinguish availability from permission

The feature answer is a **bit mask**. Each bit represents one yes/no fact. Messages use bit value 1, blocking communication 2, files 4, streams 8 and service reports 16. An image containing all five returns 1 + 2 + 4 + 8 + 16 = 31.

If the file bit is present, a file-operation route exists in that image. The program still needs valid service setup, an appropriate handle and the required rights. A **handle** is a token naming an owned resource; it is not permission to use every resource. Discovery does not create handles or grant rights.

<details>

<summary>Does a feature answer of 31 mean any program may read any file?</summary>

No. It only describes the compiled service routes. The file service still checks its caller, handles, rights, buffer addresses and request.

</details>

<details>

<summary>Why does the minimal host fixture report 0 while the guest image reports 31?</summary>

The host fixture links the basic monitor without the optional services. The normal RV64 image includes those services. The same dispatcher reports its actual composition.

</details>

## 6. Follow the implementation before running it

1. Open `include/umicom/kernel/user_abi.h`. Find operation 3 and selectors 0 through 6.
2. Open `kernel/user_monitor.c`. Find `UmicomKernelUserTrapDispatch`. Notice that origin, instruction and budget checks happen before the query.
3. Find `UmicomKernelUserAbiQuery`. It selects a scalar value and rejects nonzero reserved arguments.
4. Return to the dispatcher. Notice that only saved `a0` and the continuation instruction address change after a normal discovery result.
5. Open `tests/user_memory/user_memory_tests.c`. The fixed expected values check the public numbers independently. Additional cases check refusal, register preservation and admission boundaries.
6. Open `kernel/user_validation.c`. The real guest checks two isolated address spaces and verifies Kernel-side counts, protected data and resource cleanup.

A **continuation** is the place where execution resumes. ECALL occupies four bytes in this contract, so normal completion advances past it. The Kernel checks that the next instruction belongs to executable user memory before resuming.

## 7. Run the optional Kernel exercise

Use the Kernel repository's `docs/WINDOWS_BEGINNER_SETUP.md` to install and verify its tools first. The following commands assume the checkout is `C:\umicom\umicom-kernel` and MSYS2 UCRT64 tools are installed at `C:\msys64\ucrt64\bin`. Adjust paths if your setup differs. Run one command at a time and stop on an error.

First, run the host fixture. This is an ordinary program using synthetic aligned memory. It tests the real allocator, mapper and dispatcher but cannot prove processor privilege transitions.

```text
Set-Location "C:\umicom\umicom-kernel"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\tests\user_memory" -B ".\build\user-memory-host" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe
cmake --build ".\build\user-memory-host" --parallel 2
ctest --test-dir ".\build\user-memory-host" -R "^kernel[.]user_boundary[.]abi-" --output-on-failure --no-tests=error
```

`-S` selects source, `-B` selects a separate build folder, and `-G Ninja` selects a build tool. CMake first prepares the build; the second command compiles and links. CTest's `-R` selects matching test names. Expect eight selected ABI cases to pass. A skipped or timed-out case has not passed.

Then qualify the real RISC-V path if the cross-compiler and emulator are available:

```text
cmake --preset riscv64-clang-debug -DBUILD_TESTING=ON
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug -R "^kernel[.]riscv64[.](abi_discovery|user_execution)$" --output-on-failure --no-tests=error
```

A **preset** stores named configuration choices. A **cross-compiler** builds instructions for a different target machine. QEMU supplies an emulated RISC-V machine in which the guest executes its real U-mode instructions. The current-image test fixture builds the required image before launching those tests.

Expected guest output includes `UMICOM_KERNEL_ABI_DISCOVERY_READY`. It appears only after both discovery cases satisfy their checks. Preserve the full output, exit result and source identity; a copied readiness line alone is not evidence of success. These commands are learner instructions, not a claim about your computer's results.

## 8. Predict, investigate and explain

1. Predict the response to VERSION with the second reserved argument set to 1. Find the matching regression case and compare your prediction with its assertion.
2. Explain why the call budget still applies even though the query never writes user memory.
3. Calculate the mask for messages and file operations only: 1 + 4. Which other bits are absent?
4. Explain why a successful host fixture and a successful guest test answer different questions.

If CMake cannot find a compiler, return to tool setup. If CTest reports no tests, check the build directory and spelling of the filter. If the current-image fixture fails, resolve its compiler or linker output first. Do not launch an old image and treat it as evidence for changed source.

Continue reading `docs/NATIVE_ABI_DISCOVERY.md` and `docs/USER_MEMORY_BOUNDARIES.md` in the Kernel repository. The Framework's portable system services remain a separate layer; this query alone does not make a Framework graphical application run on the experimental Kernel.

Use the [connected learning map](../../../courses/learning-paths.html#kernel) to revisit memory, C and system-layer concepts, or return to [the course contents](../../../courses/umicom-kernel-from-scratch/index.html).

[Next: Create a file and run a program at the Kernel console](08-files-at-the-console.md)

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/07-native-system-calls.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Keep firmware-owned pages out of the allocator](06-reserved-pages.md)
