# Episode 118 — Build, test and privately stage a C23 application

**Bits to Banking · Umicom Foundation · Teaching script · Update 42**  
**Presenter:** Umicom Foundation contributors  
**Format:** Approximately 6–8 minutes, screen capture and vector diagrams  
**Linked chapters:** 67–69 and 300  
**Coding standard:** C23/Assembly for implementation; PowerShell/Linux commands are interactive instructions, not new scripts.

## Purpose

Give complete beginners a meaningful demonstration rather than a list of unexplained commands. The viewer sees what the instructor types, why it is safe, what result is expected, and how to record a different result without guessing. Use an ordinary practice account. Do not show personal identifiers, secrets or real client records.

## Scene-by-scene teaching script

### 00:00–01:05 · Name the four engineering gates

**Visual direction:** Show configure, build, test and stage as separate boxes.

**Narration:** CMake configuration, Ninja compilation, CTest results and installation are not interchangeable.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 01:05–02:25 · Configure correctly

**Visual direction:** Run the Update 42 `cmake -S` and `-B` commands in PowerShell with MSYS2 UCRT64 GCC.

**Narration:** We keep generated files outside the source tree and use the exact compiler required by this laboratory.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 02:25–03:40 · Compile and inspect tests

**Visual direction:** Run `cmake --build ...` and `ctest --test-dir ... --output-on-failure`.

**Narration:** Read the actual test count. If any test fails or is not run, we say so rather than claiming success.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 03:40–04:50 · Stage in a private prefix

**Visual direction:** Check `Test-Path C:\umicom\learning-stage-update42`, then use `cmake --install ... --prefix` only for the agreed training path.

**Narration:** This writes a copied executable only to our chosen folder; it does not install a Windows service.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 04:50–06:15 · Launch from the new location

**Visual direction:** Use the full path to `btb-deployment-review-demo.exe`; show output.

**Narration:** A successful staged launch proves something about this specific training executable, not the production Umicom OS installer.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

## Viewer exercise

Explain why a build passing does not certify a Windows double-click launch on another machine.

## Expected understanding

Viewers should distinguish observation from action and from simulation. Where a tool or file is absent, the correct classroom answer is **not run / not available**, not an invented successful screen. Any step that modifies a private practice directory must show its destination clearly before the instructor presses Enter.

## Accessibility and quality review

Provide captions, alt text for diagrams, keyboard-readable commands, a readable monospaced font and a transcript. Do not use colour alone to indicate success or failure. Preserve command syntax exactly, especially backticks in PowerShell and quoted paths with spaces. Keep each recorded command and its output on screen long enough to follow without pausing. Cite the relevant Markdown chapter, native C23 source and current build instructions in the episode description.
