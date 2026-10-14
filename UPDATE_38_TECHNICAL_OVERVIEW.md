# Major Update 38 — Technical and educational overview

## Why a separate introductory course?

The existing Bits2Banking software-engineering sequence teaches individual tools alongside native C23 development. A dedicated system-administration pathway makes it possible for a new learner to start with the keyboard, current directory, file ownership and computer information before being asked to build C23 or publish Git commits. The lessons are written for a broad age range without removing professional terminology; each term is defined at first use.

## Relationship to earlier lessons

- The new course reuses the principles of previous PowerShell chapters 264–267 but expands scope to explicit Windows/Linux comparisons, services, permissions, logs, networks, storage, backups and fault isolation.
- It reuses earlier Git chapters 272–275 as an introductory pathway, then directs learners to deeper Git history, submodules, conflict resolution and release gates in the 190–263 sequence.
- It reuses `labs/native/contributor-notes` conceptually, but introduces a much smaller **read-only** lab with no Python or PowerShell implementation scripts.
- The attached user guide is retained unchanged as a learning reference; its proposed auto-discovery commands are never presented as implemented.

## Content directories

- `content/lessons/08-system-administration/` — the dedicated course; 24 chapters, index, glossary, assessment and instructor notes.
- `content/lessons/05-engineering/` — chapters 284–287 in the existing sequential engineering curriculum.
- `content/videos/scripts/` — episodes 95–100.
- `content/assets/diagrams/` — nine self-contained SVG technical illustrations.
- `content/assets/screenshots/` — Windows search screenshot supplied by the course author.
- `content/assets/reference/` — unchanged contributed HTML project-creation document.
- `labs/native/sysadmin-readonly-text/` — portable C23 teaching laboratory and test fixtures.

## Practical teaching method

Every course chapter has a clear learning goal, a careful explanation of the problem, definitions, labelled shell-specific steps, actual expected observations, a realistic support scenario, negative cases, exercises, questions/answers and an Umicom architecture link. Windows PowerShell commands never substitute for a native C23 implementation. Linux commands are shown separately as Bash commands; they are not pasted into PowerShell.

## Architecture and security

The C23 lab's isolated `BtbTextInspectFile()` is appropriate for inspecting explicitly named classroom fixtures. It does **not** enforce sandbox containment or handle arbitrary untrusted path resolution. A production Umicom application must reuse Framework file/VFS and security contracts before adopting any comparable feature. The lab does not call Git, deploy changes or alter system settings.

## Publication

Merge new content into the existing repository using Beyond Compare. The current `mkdocs.yml` is intentionally not replaced; a reviewed snippet supplies all navigation additions. The course is separately readable in a standalone HTML edition without installing MkDocs. Existing historical lessons and manuscript navigation must be retained.
