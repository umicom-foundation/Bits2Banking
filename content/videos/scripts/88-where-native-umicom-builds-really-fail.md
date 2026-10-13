# Episode 88 — Where native Umicom builds really fail

**Bits to Banking · Umicom Foundation · Presenter script**  
**Companion lessons:** Chapters 258–259 and 262 · **Estimated running time:** 12–14 minutes.

## Begin with evidence (0:00–2:00)

**On screen:** Show `build-failure-triage-update36.svg`, then a saved, fictional CMake/Ninja build transcript with a compile error, link error and CTest Not Run report. Label each excerpt as illustrative.

**Narration:** “The first visible error narrows our investigation but does not necessarily identify the original mistake. Configure, compile, link, test, launch and package are separate stages. We will retain their evidence rather than suppress messages or rewrite the first file named in an error.”

## Walk through a compiler diagnostic (2:00–5:00)

Open Framework's public `include/umicom/build/parser.h` and the example `framework_example.c`. The sample calls `umi_build_parse_diagnostic_line` instead of splitting text at the first colon. Explain why Windows drive letters, line and column numbers, and diagnostic truncation require a tested parser.

**Narration:** “Umicom Framework already owns this capability. A second parser in Studio or Bits2Banking would make the same text produce inconsistent problems. We reuse the public library and keep the raw output when it cannot represent a complete diagnostic.”

## Test and crash categories (5:00–10:00)

Show how to run `ctest --output-on-failure` in a configured lab. Explain a *failed* case versus a *not-run* case and a process crash versus a build failure. Show a stored example of Windows `0xC0000409` and Linux SIGSEGV as symptoms, not diagnoses. Illustrate how a separate Clang ASan/UBSan build can narrow many memory problems but does not replace Windows GUI and packaging tests.

**On screen:** Run `assess_failed`, `assess_not_run`, and `assess_incomplete_log`. These tests pass by proving that the review was **blocked**.

## Closure (10:00–14:00)

**Narration:** “Repair the smallest confirmed defect, preserve existing public contracts and comments, recompile the affected targets, run focused tests and then the complete required suite. Do not fix an error by deleting the failing test or staging unrelated work.”

**Audience task:** Write the first three commands you would use for an unbuilt CTest executable, and three different checks for an executable that starts and crashes. Record which evidence would distinguish the two situations.

**Production boundary:** The demonstration intentionally does not reproduce a destructive crash in a user's application checkout.
