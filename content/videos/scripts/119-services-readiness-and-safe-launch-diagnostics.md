# Episode 119 — Services: why running does not mean ready

**Bits to Banking · Umicom Foundation · Teaching script · Update 42**  
**Presenter:** Umicom Foundation contributors  
**Format:** Approximately 6–8 minutes, screen capture and vector diagrams  
**Linked chapters:** 70–71  
**Coding standard:** C23/Assembly for implementation; PowerShell/Linux commands are interactive instructions, not new scripts.

## Purpose

Give complete beginners a meaningful demonstration rather than a list of unexplained commands. The viewer sees what the instructor types, why it is safe, what result is expected, and how to record a different result without guessing. Use an ordinary practice account. Do not show personal identifiers, secrets or real client records.

## Scene-by-scene teaching script

### 00:00–00:55 · Introduce the misconception

**Visual direction:** Show a fake dashboard with green Process and red Storage dependency.

**Narration:** A process can exist while the service is not ready to do useful work.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 00:55–02:05 · Observe service status

**Visual direction:** Show `Get-Service -Name Spooler` and a Linux `systemctl --user ...` example.

**Narration:** We are reading, not stopping or restarting, services. Missing systemd is a meaningful environmental difference.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 02:05–03:15 · Inspect a failed launch

**Visual direction:** Open a fictional `missing DLL` message beside a full executable path.

**Narration:** The loader may fail before our C23 program starts. We should identify the correct boundary.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 03:15–04:30 · Review controlled evidence

**Visual direction:** Compare a terminal launch with a desktop shortcut launch without changing PATH globally.

**Narration:** An extra development folder on PATH can make a local run succeed while a packaged desktop launch fails.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

### 04:30–05:50 · Choose recovery criteria

**Visual direction:** Show a maintenance record moving from failed verification to separately tested restoration.

**Narration:** RESTORED does not mean the new version succeeded. The old baseline needs independent checks.

**Instructor pause:** Give the viewer a moment to read the command or diagram. Say which folder or machine the demonstration applies to, and explain that the command output may vary across Windows and Linux hosts.

## Viewer exercise

Write a five-sentence incident report for a fictional Umicom Notes startup failure without recommending disabling security controls.

## Expected understanding

Viewers should distinguish observation from action and from simulation. Where a tool or file is absent, the correct classroom answer is **not run / not available**, not an invented successful screen. Any step that modifies a private practice directory must show its destination clearly before the instructor presses Enter.

## Accessibility and quality review

Provide captions, alt text for diagrams, keyboard-readable commands, a readable monospaced font and a transcript. Do not use colour alone to indicate success or failure. Preserve command syntax exactly, especially backticks in PowerShell and quoted paths with spaces. Keep each recorded command and its output on screen long enough to follow without pausing. Cite the relevant Markdown chapter, native C23 source and current build instructions in the episode description.
