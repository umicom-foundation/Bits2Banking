# Episode 126 — Security operations: observe, review and decide

**Bits2Banking · Umicom Foundation · 7–9 minutes**  
**Companion:** System Administration Chapters 85–87; diagrams: security review and identity lifecycle.

## Educational objective

Explain why a running service does not mean a secure service, how user and service identities differ, and why permissions and human approval remain separate from technical evidence.

### 00:00–01:10 — Start with a realistic problem

**Visual:** Fictional Umicom Notes workstation displays an application window; a separate card shows “Access-review status: not verified”.

**Narration:** “This window opens and the application appears to work. But does that prove the system is secure? No. A process can run while a service account has excessive permission, an old employee retains access, or backup recovery has never been tested. We start by separating what we observed from what we still need to establish.”

**Screen direction:** Display the observation → policy → gap → review diagram. Define confidentiality, integrity and availability in plain language. Ask students to name a failure of integrity that would not necessarily crash the application.

### 01:10–03:00 — Accounts and roles

**Visual:** Human operator, NotesService identity and independent Reviewer in separate lanes; do not show real usernames.

**Narration:** “A human account belongs to a person. A service account allows a background process to do a particular job. Both need an owner. Neither should receive every permission just for convenience. When someone joins a project, changes responsibility or leaves, access must be reviewed.”

**Live classroom demonstration:** On a learner-owned Windows machine, run `whoami` and `Get-LocalUser | Select-Object Name, Enabled` only if available. On Linux, use `id`. Explicitly cover how to respond to missing cmdlets and why live directory data must not be published.

### 03:00–05:10 — Groups, ACLs and inheritance

**Visual:** Group and ACL diagram, followed by a fictional Reader/Maintainer permission matrix.

**Narration:** “Groups make access administration manageable. But group membership is not enough to infer the full effective result when resource rules and inheritance exist. An Access denied message can be evidence that a security rule is working as intended. It is not a reason to open everything to everyone.”

**Teaching point:** Do not demonstrate permission-changing commands, sudo or administrator elevation. Show read-only `Get-Acl` for a learner-owned folder or `stat` for a Linux home directory.

### 05:10–07:20 — Prepare a reliable handover

**Visual:** Five-column evidence worksheet: check, expected state, observed result, timestamp, next owner.

**Narration:** “Write ‘Not verified’ whenever the observation is missing. A complete-looking but invented report can be more dangerous than a precise report with known gaps. An authorised person decides whether a change should take place; the machine cannot authorise itself merely by passing a health check.”

**Viewer practice:** Create three fictional evidence rows and mark one missing. Explain to a fellow learner why this should block promotion.

**Safety and accessibility:** Narrate all abbreviations on first use; supply subtitles and a text transcript. Never reveal actual identities or service information.
