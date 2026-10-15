# Episode 120 — C23 deployment evidence and the complete private-stage capstone

**Bits to Banking · Umicom Foundation · Teaching script · Update 42**  
**Presenter:** Umicom Foundation contributors  
**Format:** Approximately 6–8 minutes, screen capture and vector diagrams  
**Linked chapters:** 72 and 301–303  
**Coding standard:** C23/Assembly for implementation; PowerShell/Linux commands are interactive instructions, not new scripts.

## Purpose

Give complete beginners a meaningful demonstration rather than a list of unexplained commands. The viewer sees what the instructor types, why it is safe, what result is expected, and how to record a different result without guessing. Use an ordinary practice account. Do not show personal identifiers, secrets or real client records.

## Scene-by-scene teaching script

### 00:00–00:55 · Introduce the bounded review

**Visual direction:** Open `deployment_review.h`, highlight the source revision and digest fields.

**Narration:** These values are fictional claims supplied by the caller; the library does not hash real files.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 00:55–02:05 · Show real code ownership

**Visual direction:** Display `admin_evidence.h`, `service_readiness.h`, `maintenance_review.h`, `deployment_review.h`.

**Narration:** Each layer owns one question. We compose existing C23 libraries instead of copying their implementation.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 02:05–03:30 · Run the focused negative tests

**Visual direction:** Run CTest cases `missing-runtime`, `stale-verification`, `rollback`, `restored`.

**Narration:** An incomplete or stale release must not be shown as qualified. Recovery gets its own status.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 03:30–04:40 · Run the full inherited test suite

**Visual direction:** Run the full CTest command and read the actual summary.

**Narration:** The reference Linux environment registered 79 tests. Your environment should report its own real count.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 04:40–05:45 · Stage only the practice executable

**Visual direction:** Run the documented `cmake --install` command to the approved private prefix.

**Narration:** We do not change registry entries, global services, users, firewall rules or real Umicom Kernel images.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 05:45–06:50 · Report actual evidence and next owner

**Visual direction:** Show an example support note and the `git status`/`git add -A` review path.

**Narration:** The update can be committed to Bits2Banking after review, but production Framework changes require separate approval and tests.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

## Viewer exercise

Identify exactly what the C23 review checked, what it only assumed, and which Umicom Framework owners would supply real evidence.

## Expected understanding

Viewers should distinguish observation from action and from simulation. Where a tool or file is absent, the correct classroom answer is **not run / not available**, not an invented successful screen. Any step that modifies a private practice directory must show its destination clearly before the instructor presses Enter.

## Accessibility and quality review

Provide captions, alt text for diagrams, keyboard-readable commands, a readable monospaced font and a transcript. Do not use colour alone to indicate success or failure. Preserve command syntax exactly, especially backticks in PowerShell and quoted paths with spaces. Keep each recorded command and its output on screen long enough to follow without pausing. Cite the relevant Markdown chapter, native C23 source and current build instructions in the episode description.
