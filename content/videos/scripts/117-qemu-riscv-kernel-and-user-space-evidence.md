# Episode 117 — QEMU, RISC-V, kernel boot and separate evidence

**Bits to Banking · Umicom Foundation · Teaching script · Update 42**  
**Presenter:** Umicom Foundation contributors  
**Format:** Approximately 6–8 minutes, screen capture and vector diagrams  
**Linked chapters:** 63–65  
**Coding standard:** C23/Assembly for implementation; PowerShell/Linux commands are interactive instructions, not new scripts.

## Purpose

Give complete beginners a meaningful demonstration rather than a list of unexplained commands. The viewer sees what the instructor types, why it is safe, what result is expected, and how to record a different result without guessing. Use an ordinary practice account. Do not show personal identifiers, secrets or real client records.

## Scene-by-scene teaching script

### 00:00–00:55 · Start with the guest stages

**Visual direction:** Display firmware → kernel → root filesystem → applications illustration.

**Narration:** A QEMU window opening does not mean the guest successfully started.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 00:55–02:05 · List the RISC-V virtual machine

**Visual direction:** Show `qemu-system-riscv64 -machine help` and highlight `virt` only if the tool is available.

**Narration:** Machine help lists supported virtual boards. We are not launching a guest yet.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 02:05–03:15 · Learn from executable architecture

**Visual direction:** Show `uname -m` on Linux or host processor architecture on Windows; compare an x86-64 and a RISC-V label.

**Narration:** The filename does not determine which instruction set a binary contains. The build must match the target.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 03:15–04:30 · Read image metadata

**Visual direction:** Show a deliberately small image diagram and a sample `qemu-img info` report from a verified, disposable practice image.

**Narration:** A disk image may have different virtual and physical sizes; do not point tools at real device paths.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 04:30–05:50 · Identify real proof

**Visual direction:** Show a redacted QEMU serial console example and a separate test report.

**Narration:** Host CTest, kernel boot and user-space readiness are distinct claims, each requiring direct evidence.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

## Viewer exercise

Draw the exact evidence chain you would need to say that an Umicom Kernel image booted in QEMU.

## Expected understanding

Viewers should distinguish observation from action and from simulation. Where a tool or file is absent, the correct classroom answer is **not run / not available**, not an invented successful screen. Any step that modifies a private practice directory must show its destination clearly before the instructor presses Enter.

## Accessibility and quality review

Provide captions, alt text for diagrams, keyboard-readable commands, a readable monospaced font and a transcript. Do not use colour alone to indicate success or failure. Preserve command syntax exactly, especially backticks in PowerShell and quoted paths with spaces. Keep each recorded command and its output on screen long enough to follow without pausing. Cite the relevant Markdown chapter, native C23 source and current build instructions in the episode description.
