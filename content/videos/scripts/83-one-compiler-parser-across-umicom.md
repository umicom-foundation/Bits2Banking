# Episode 83 — One Compiler Parser for Every Umicom Application

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Companion chapters:** 242–243 and 248 · **Format:** 10–13 minutes  
**Implementation:** Framework C23 interfaces and direct CMake/CTest commands.

## Learning outcomes

The audience will distinguish configure, compile, link and test failures; understand why Windows paths defeat simple colon splitting; and identify the canonical Umicom Framework diagnostics parser.

## 00:00–01:40 — A real engineering problem

**Visual:** An editor pane shows `C:/umicom/Notes/src/main.c:17:8: error: missing declaration`. Beside it, display a broken parser that mistakes the drive letter `C:` for the source location separator.

**Narration:** “A build log is text, but an IDE needs a precise path, position and severity. A broken parser can send a developer to the wrong file or hide the actual compiler error. We should not maintain a different compiler grammar in Studio, Trader and every learning application.”

## 01:40–04:10 — Inspect Framework's parser

Open `framework/include/umicom/diagnostics/compiler_parser.h`, then `framework/include/umicom/build/parser.h`. Point out `UmiCompilerDiagnosticParseText`, `umi_build_parse_diagnostic_line`, and `umi_build_parse_output`.

Explain the difference between a recognised diagnostic and ordinary log output, then introduce `UmiBuildDiagnosticList.dropped`. A message refused for capacity reasons has not vanished from the real build; the raw transcript still matters.

## 04:10–07:30 — Follow the failure stage

**Visual:** Diagram `diagnostics-pipeline-update35.svg`. Run CMake configure, build and CTest separately in a disposable lab. Freeze the terminal at the *first* failing stage. Explain why a target that never compiled is not a failed runtime test.

**On-screen direct commands:**

```powershell
cmake -S ".\labs\native\build-evidence" -B ".\output\learning-build\build-evidence" -G Ninja -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\build-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\build-evidence" --output-on-failure
```

If the local toolchain cannot configure or compile, narrate that outcome accurately rather than continuing as though the later gates passed.

## 07:30–10:45 — Bounded adapter contract

Open `labs/native/build-evidence/framework_bridge.c` and explain that it copies already parsed Framework records. The path and message must fit completely. If they do not, the adapter returns a failure and leaves the existing snapshot untouched. That makes incomplete evidence visible.

**Narration:** “Framework owns parsing and production build history. The teaching model only explores how a consumer interprets those records. Reusability is enforced by linking contracts, not by copying source files.”

## End — Exercise

Give viewers four anonymised outputs: GCC error, linker's undefined reference, CTest `Not Run`, and Ninja `FAILED:` without a recognised diagnostic. They must classify the stage, state what evidence is missing, and specify where the fix belongs. Avoid altering production files while practising.
