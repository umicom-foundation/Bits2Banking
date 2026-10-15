# Episode 116 — Hosts, guests and the first safe VM laboratory

**Bits to Banking · Umicom Foundation · Teaching script · Update 42**  
**Presenter:** Umicom Foundation contributors  
**Format:** Approximately 6–8 minutes, screen capture and vector diagrams  
**Linked chapters:** 61–62  
**Coding standard:** C23/Assembly for implementation; PowerShell/Linux commands are interactive instructions, not new scripts.

## Purpose

Give complete beginners a meaningful demonstration rather than a list of unexplained commands. The viewer sees what the instructor types, why it is safe, what result is expected, and how to record a different result without guessing. Use an ordinary practice account. Do not show personal identifiers, secrets or real client records.

## Scene-by-scene teaching script

### 00:00–01:00 · The confusing menu

**Visual direction:** Show Windows Terminal beside a diagram of the host computer and a separate guest VM.

**Narration:** A terminal is an application on an operating system. A guest virtual machine runs a separate operating system. We should not mix those ideas.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 01:00–02:10 · Read the host architecture

**Visual direction:** Type `Get-CimInstance Win32_ComputerSystem` and `Get-CimInstance Win32_Processor` slowly.

**Narration:** The CPU information belongs to the host. It does not tell us that a Linux guest is installed or running.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 02:10–03:15 · Find QEMU without running it

**Visual direction:** Run `Get-Command qemu-system-riscv64 -ErrorAction SilentlyContinue`.

**Narration:** No output simply means QEMU cannot be found; it is not a failure of your knowledge or a reason to run administrator commands.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 03:15–04:30 · Plan the safe guest

**Visual direction:** Show a proposed learning directory and a table of approved ISO source, digest and guest architecture.

**Narration:** We choose a disposable virtual disk, keep host-folder sharing disabled, and verify inputs before booting anything.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 04:30–05:45 · Distinguish isolation and backups

**Visual direction:** Draw host files, virtual disk and a separate backup.

**Narration:** A snapshot and a backup are different. We will not partition, format or write a real disk in this beginner lesson.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

## Viewer exercise

Explain host, guest, virtual disk, ISO and two settings that could allow guest access to host resources.

## Expected understanding

Viewers should distinguish observation from action and from simulation. Where a tool or file is absent, the correct classroom answer is **not run / not available**, not an invented successful screen. Any step that modifies a private practice directory must show its destination clearly before the instructor presses Enter.

## Accessibility and quality review

Provide captions, alt text for diagrams, keyboard-readable commands, a readable monospaced font and a transcript. Do not use colour alone to indicate success or failure. Preserve command syntax exactly, especially backticks in PowerShell and quoted paths with spaces. Keep each recorded command and its output on screen long enough to follow without pausing. Cite the relevant Markdown chapter, native C23 source and current build instructions in the episode description.
