# Video 17 — Test failures before they reach users

**Duration:** Approximately 18–22 minutes  
**Related chapters:** [Allocation failures](../../lessons/03-native-code/64-test-allocation-failures.md), [Bounded HTTP bytes](../../lessons/03-native-code/65-parse-bounded-http-bytes.md), [Seeded tests](../../lessons/05-engineering/66-fuzz-bytes-and-check-contracts.md)  
**Code repository:** [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking)

## 00:00–03:30 — A Notes application that must not lose work

**On screen:** A simple text editor with a note titled *Review the Framework API*.

**Narration:**

Imagine that you are editing an important note. You replace the title and body, then press Save. At that moment, the application tries to allocate memory for the new text. One allocation succeeds. The next fails.

What should happen to the note? The answer is simple: the old note should still be there. The user asked for one complete change, not half a change. This is the principle we will practise with a small C23 application.

In C, dynamic storage has an owner. Someone must decide when it is allocated, when it can be used and when it is released. If the caller owns a character array and sends it to a Notes model, the model cannot safely remember that address forever. The caller may change the array or let it go out of scope. Our Notes model makes its own copies and releases them when the note is destroyed.

We can explain that policy in plain English, but how do we know the implementation respects it when memory runs out? We write a test which deliberately makes the allocator fail.

## 03:30–08:00 — Make the allocator refuse a request

**On screen:** Open `labs/native/fault-injection/note.h` and `test_note.c`.

**Narration:**

The laboratory supplies two function pointers: one to allocate memory and another to release it. An allocator is a pair of operations with a shared context. The context is a small structure that counts allocation attempts and records the one attempt we want to fail.

The first test refuses the very first allocation. The Notes model must report that memory was unavailable, and it must not pretend that a note was created.

Next, we let the first allocation succeed and refuse the second. This case matters because some temporary memory is now live. The program must release that temporary title before returning a failure, otherwise it would leak memory.

When we already have a saved note, replacement becomes even more important. Our code prepares the new title and new body first. If both are ready, we release the old copies and publish the replacement. If either fails, the old note, its revision and its text remain unchanged.

Let's run the code:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\fault-injection" -B ".\output\learning-build\fault-injection" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\fault-injection" --parallel 2
ctest --test-dir ".\output\learning-build\fault-injection" --output-on-failure
```

The test should pass. More importantly, we can explain what it checked: both possible replacement-allocation failures, retained revision, retained previous text and zero outstanding allocations at the end.

## 08:00–11:30 — From owned text to untrusted bytes

**On screen:** Show hexadecimal bytes spelling `GET /docs/ HTTP/1.1` followed by `0D 0A`.

**Narration:**

A note can receive text from an editor. A web server can receive bytes from another computer. In both cases, the input arrives from outside the component that must process it.

But a network message is not necessarily a C string. A C string ends at a zero byte. A socket read produces some number of bytes, and those bytes may not contain a zero terminator at all. If we call `strlen` and assume one is present, the program may read past the valid buffer.

In our second laboratory, the parser receives two things: a pointer to the bytes and a byte count. It checks the count before reading. It also checks that the line ends with CRLF, that the method is supported, that the path matches our narrow rules and that the HTTP version is one we decided to teach.

The parser creates a temporary output structure. Only after every check succeeds does it copy that structure into the caller's output. A malformed request must not leave a partially updated result.

This is the same idea we used for the Notes replacement, applied to a completely different task.

## 11:30–16:30 — Run many malformed requests safely

**On screen:** Open `test_request_line.c` and `fuzz_request_line.c`, then run CTest.

**Narration:**

First, the unit tests check known problems: a request with no proper line ending, an embedded zero byte, an unsupported method, a path containing `..` and a request with the wrong version. Every rejected request must leave the output unchanged.

Then we go further. Instead of writing every bad input by hand, we use a deterministic generator. It creates five thousand arbitrary byte buffers and five thousand requests where one byte was changed. The generator starts with the same seed each time, so if we discover a problem we can reproduce the exact sequence that produced it.

The test uses a property rather than a list of expected parsed paths. If the parser accepts input, the result must have a valid method, an absolute path and a supported version. If it refuses input, the output structure must still contain the pattern with which it began.

Let's configure and run this laboratory:

```powershell
cmake -S ".\labs\native\http-byte-parser" -B ".\output\learning-build\http-byte-parser" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\http-byte-parser" --parallel 2
ctest --test-dir ".\output\learning-build\http-byte-parser" --output-on-failure
```

We expect two passing tests. This is useful evidence, but it is not a claim that all possible network inputs are safe. A deterministic generator and a coverage-guided fuzzer are different tools. A real HTTP server must also handle networking, requests split across reads, authentication, timeouts, path security and service permissions.

## 16:30–19:30 — Connect the exercise to Umicom Framework

**On screen:** Open `include/umicom/base/memory.h`, then `include/umicom/web/server.h` in Umicom Framework.

**Narration:**

Our two laboratories are small enough to inspect in one sitting. The actual Umicom Framework already has reusable allocator and web-server contracts. We do not intend to replace those with our teaching models.

Instead, the laboratories give you a way to understand their important boundaries: who owns memory, how a caller reports failure, how bytes are validated, when state is published and how a component refuses unsafe input.

Open the Framework's allocator header and find `UmiAllocator`. Open the web-server header and identify how the server receives a request through the Framework service rather than calling a socket from every application.

As you become more experienced, try adding a negative test before fixing a new defect. A negative test deliberately presents an invalid condition and checks that the program responds safely. When the same failure can be reproduced, measured and explained, it becomes easier for another contributor to review your change.

## 19:30–End — Practical challenge

**On screen:** Show the source files and the written lessons.

**Narration:**

Your first challenge is to add another test to the Notes model: ask it to replace a title using an invalid byte sequence and confirm that the revision does not change. Your second challenge is to add an HTTP request line with a query string and confirm that our deliberately narrow parser refuses it.

Run the test suites again. Compare the results before and after your change. Then explain in your own words why the rejected operation did not damage any previously accepted state.

The complete source code and chapters are linked from Bits2Banking. Service to Many Leads to Greatness. What you learn becomes even more useful when you help someone else understand it.
