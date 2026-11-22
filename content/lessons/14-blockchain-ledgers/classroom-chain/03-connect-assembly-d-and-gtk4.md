![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Connect Assembly, D and GTK4

[Previous: Replay balances and choose a valid fork](02-replay-balances-and-choose-a-valid-fork.md) · [Course contents](index.md)

Keep the ledger rules in the C core. Assembly can teach how a single operation crosses the calling boundary. A D program can call the same C function. GTK4 can present accepted results. Separating these responsibilities gives you one matchable set of rules and several ways to use it.

Bitcoin Core uses C++ for its node implementation and Qt for its optional graphical interface. The Bitcoin protocol defines shared behavior that different languages can implement. A GTK4 client for this lab presents the local classroom exercise. Building a separate client requires its own data model and validation decisions before it could implement any part of the Bitcoin protocol. [Bitcoin Core source](https://github.com/bitcoin/bitcoin/tree/master/src) · [Bitcoin Core Qt guide](https://github.com/bitcoin/bitcoin/blob/master/src/qt/README.md)

## Compare a tiny Assembly function with C

The ABI is the calling convention two compiled pieces of code agree to follow. For a first pointer argument, Windows x64 uses `RCX` and the x86-64 System V ABI uses `RDI`. The optional `target_x86_64.S` passes the selected register to the same short comparison. The caller still supplies a 32-byte buffer and retains ownership.

1. On x86-64 with a GNU-style toolchain on Windows or Linux, add `-DCLASSROOM_ENABLE_X86_64_ASM=ON` to the [first lesson’s configure command](01-run-a-native-classroom-chain.md#build-the-lab).
2. Build, then run `ctest --test-dir build/classroom-chain -R classroom_chain.assembly_abi --output-on-failure --no-tests=error`.
3. Read `test_chain.c`. The fixture compares the two functions for all 256 leading byte values plus a null pointer. Look up `xorl`, `cmpb` and `sete` in an instruction reference and explain why the result in `EAX` is exactly zero or one.

The C implementation stays the reference. An Assembly routine might be useful after profiling, and this exercise establishes calling and result parity. It provides no measurement of speed or energy cost. [Microsoft x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention) · [System V x86-64 ABI](https://gitlab.com/x86-psABIs/x86-64-ABI)

## Call the same function from D

Open `labs/native/classroom-chain/check_target.d` and find the `extern(C)` declaration. D owns the byte array. The C function reads from the pointer during the call, and D can immediately use or release the array afterward. The D client tests an accepted and a refused byte without translating the ledger algorithm.

With a matching 64-bit Linux C/D toolchain and the archive from the earlier C build, try:

```sh
ldc2 labs/native/classroom-chain/check_target.d build/classroom-chain/libbits2banking-classroom-chain.a -of=build/classroom-chain/check-target
./build/classroom-chain/check-target
```

Exit code zero means both comparisons matched. If the linker cannot read the archive, check that the C and D toolchains agree on architecture, object format and C runtime. The D client is an optional source exercise. The required native CMake checks cover C and the separately enabled Assembly fixture. [D interface to C](https://dlang.org/spec/interfaceToC.html)

## Plan a read-only GTK4 view

A future view can show three balances and the branch result. Give the window a copy of the accepted result. The window event handler can request validation but should update labels only after the C core returns success. Keep long operations off the UI event loop if you later increase the work budget. The classroom executable delivers a console trace, while the GTK4 portion is a design exercise.

```text
WHEN the learner selects a classroom history
    ASK the C ledger to replay the history
    IF validation succeeds THEN
        SHOW the three accepted balances and their total
    ELSE
        KEEP the previous accepted balances and SHOW the refusal
    END IF
END WHEN
```

If a learner presses the button twice or changes a record during review, which balances should remain visible? Sketch both screens and label where the authoritative C result enters each callback. This exercise also prepares you for drawing the same three balances with a graphics library. Embed the approved Umicom artwork at the application boundary using Framework’s existing resources. [GTK4 application lifecycle](https://docs.gtk.org/gtk4/class.Application.html)

[Previous: Replay balances and choose a valid fork](02-replay-balances-and-choose-a-valid-fork.md) · [Course contents](index.md) · [Study Bitcoin’s source code](../../../courses/introduction-to-bitcoin-source-code/index.html)
