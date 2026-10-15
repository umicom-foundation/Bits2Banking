# Episode 127 — Configuration baselines, SHA-256 and safe patch plans

**Bits2Banking · Umicom Foundation · 8–10 minutes**  
**Companion:** System Administration Chapters 88–90; baseline and patch diagrams.

## Goal

Use a harmless Umicom Notes training file to distinguish configuration content, approved baselines, observed runtime state and controlled software updates.

### 00:00–01:30 — Why configuration matters

**Visual:** The same Notes executable appears in two labelled environments, development and training. Both use different fictional settings.

**Narration:** “One executable can behave differently because of configuration. A setting such as `listen_address=127.0.0.1` is ordinary example configuration. A password is not. We never place actual credentials in the book or our source repository.”

Explain loopback and how an all-interface bind would change network exposure. Do not start a live listener.

### 01:30–04:00 — Perform the local file exercise

**Screen:** PowerShell 7 open in a learner-owned environment. Create `$HOME\UmicomLearning\SecurityOps\notes-training.conf` exactly as in Chapter 88, with two fictional text lines. Confirm with `Get-Content`. Then make `notes-training.baseline.conf` using `Copy-Item`.

**Narration:** “We have created two ordinary text files in a personal practice folder. There are no services, secrets or privileged commands involved.”

**Demonstration:** Run `Get-FileHash -Algorithm SHA256` on each file, show matching hashes, edit the practice source file in a text editor and run the command again. One digest should change. Stress that an equal digest proves a content comparison, **not** that the configuration was approved or loaded by a running service.

### 04:00–06:50 — Why updates need more than an install result

**Visual:** Controlled-patch timeline: inventory → prepare → approve → apply → test → recover if necessary.

**Narration:** “An update can fix a serious security problem. That does not remove the need to check compatibility and the resulting business function. An update that compiles but breaks Notes saving has not passed its acceptance check.”

Show the read-only `winget upgrade` command with a clear notice that it lists candidates and may consult sources; do not install packages in this recording. On Debian/Ubuntu, show `apt list --upgradable` as an example for an authorised machine.

### 06:50–08:40 — Record separate outcomes

**Screen:** Review log includes Approved version, File digest, Installer result, Notes save/reopen result, and Restore result. The failed-change row remains failed even if the previous release is restored.

**Viewer practice:** Write a fictional change ticket, three acceptance criteria and a rollback trigger.

**Safety:** All created files remain in personal practice storage; no system packages, users, network rules or services are changed.
