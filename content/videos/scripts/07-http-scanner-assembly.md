# Read HTTP line endings in C and Assembly — video script

**Duration:** approximately 9–12 minutes

## 0:00–1:30 — The bytes inside a web request

**Narration:** “Every web request reaches a server as bytes. The beginning of a common HTTP/1.1 request contains a method, an address and a version, followed by a line ending. That line ending is not something we invent for this lesson. It is the pair of byte values 13 and 10, commonly called carriage return and line feed. Our job is to locate those bytes without reading beyond the memory that the operating system gave us.”

**On screen:** Show the exact bytes in the request `GET / HTTP/1.1\r\n`. Highlight the final two values and show what happens when the last byte is missing.

## 1:30–4:00 — Write and test the C code first

**Narration:** “The C function receives a pointer and a length. It checks that there are at least two bytes. Then it compares adjacent pairs. Notice that the loop does not read the byte after the buffer. This is a small rule with large consequences. A mistaken memory read may crash a server or disclose unrelated data.”

**On screen:** Open the actual `labs/native/http-header-scanner/scanner.c`, `scanner.h` and `test_scanner.c` files. Show how the test suite includes empty buffers, one-byte buffers and a CRLF pair at the very end.

## 4:00–7:30 — Translate one operation into Assembly

**Narration:** “Assembly instructions depend on a processor's instruction set, while argument registers also depend on the operating system's calling convention. On Windows x86-64, these two arguments arrive in RCX and RDX. On Linux x86-64, they arrive in RDI and RSI. RISC-V64 uses A0 and A1. Our Assembly files explicitly account for these differences. The result is zero or one, so our C tests can compare both implementations.”

**On screen:** Compare `scan_x86_64.S` and `scan_riscv64.S`, highlighting argument registers, the comparison of 13 and 10, the loop, and return. Display the C source alongside the Assembly source.

## 7:30–10:30 — Build both versions

**Narration:** “CMake builds the portable C version and includes Assembly only on a supported target. We run the same test cases through both. This proves agreement on the cases we tested; it does not automatically make the Assembly version faster. Performance is something we would measure before using specialised code in a reusable server.”

**On screen:** Follow the commands in [HTTP bytes with C and Assembly](../../lessons/05-engineering/42-http-and-assembly.md). Run once with Assembly enabled, and once with `-DBITS_HTTP_ENABLE_ASSEMBLY=OFF`. Show passing CTest results.

## 10:30–12:00 — From this helper to a real server

**Narration:** “A web server needs far more than a line-ending detector. It must validate the method, hostname, URL, directory boundaries and file sizes. Those responsibilities remain in C inside the shared Umicom Framework. We use a small Assembly exercise to understand what a processor does, not to replace a carefully designed application architecture.”

**On screen:** Open the native C [web-server lesson](../../lessons/05-engineering/39-build-a-c-web-server.md), then the Umicom Framework repository. Invite viewers to review the code and explain the result to another learner.
